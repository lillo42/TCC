#include "redeneural.h"

RedeNeural::RedeNeural()
{
    xml = "RedeNeural.xml";
    InicializaRede();
}

RedeNeural::~RedeNeural()
{

}

void RedeNeural::Treino()
{
    vector<Mat> caracteristicas, naoCaracteristicas;

    LerImagemPasta(caracteristicas,pastaCaracateristica);
    LerImagemPasta(naoCaracteristicas,pastaNaoCaracateristica);

    clock_t tempoInicial = clock();

    cout << "Extraindo Features de Amostras Positivas ." << endl;

    // Extrai caracteristicas Faces
    for (int i = 0; i < caracteristicas.size();i++)
    {
        Mat image = caracteristicas.at(i);
        extraiCaracteristicas(image);
    }
    valorTestePessoas = caracteristicas.size() * 0.1;

    cout  << "Extraindo Features de Amostras Negativas ";

    // Extrai caracteristicas Nao Faces
    for (int i = 0; i < naoCaracteristicas.size() ;i++)
    {
        Mat image = naoCaracteristicas.at(i);
        extraiCaracteristicas( image );
        cout << ".";
    }

    valorTestePessoas = naoCaracteristicas.size() * 0.1;

    int positivo = caracteristicas.size();

    cout << "\nFaces Positivas -> " << positivo  << endl;
    cout << "Faces Negativas -> " << Features.size() - positivo  << endl;
    cout << "Total de Amostras -> " << Features.size()  << endl;
    cout << "Features por Amostras -> " << Features[1].size()  << endl;
    cout << "Total de Features [ (Faces e NAO Faces) x Amostras ] -> " <<  Features[1].size() * Features.size() << endl;

    clock_t tempoInicial1 = clock();

    cout << "\nInicio do Treino -> " << currentDateTime() << endl;

    Treino(positivo);

    clock_t tempoFinal = clock();

    tempoTotalTreino = ((tempoFinal - tempoInicial1) / CLOCKS_PER_SEC );

    cout << "Tempo Extracao de Caracteristicas -> " << ((tempoInicial1 - tempoInicial) / CLOCKS_PER_SEC ) << " segundos" << endl;
    cout << "Tempo Treino -> " <<  tempoTotalTreino << " segundos" << endl;
    cout << "Tempo Total -> " << ((tempoFinal - tempoInicial) / CLOCKS_PER_SEC )  << " segundos" << endl;
    cout << "Fim do Treino -> " << currentDateTime() << endl;
    cout << "Treino Finalizado ! " << endl;

    PreencheParametro();
}

int RedeNeural::Teste(Mat &Query)
{
    Mat ROI(Size(WIDTH,HEIGHT),TIPO_MAT, Scalar::all(0));
    Mat LBP;
    Point roi;  // Armazena as coordenadas das Features
    DetectFace df;
    faces.clear();
    int retorno = 0;
    // convoluçao para gerar uma imagem de 320 x 240 px em NAO faces de 25 x 30 px
    for(int i = 0; i <= Query.rows - HEIGHT ; i++) {
        roi.y = i;

        for(int j =0; j <= Query.cols - WIDTH ; j++) {
            roi.x = j;

            Query.operator ()(Rect(roi.x,roi.y,WIDTH,HEIGHT)).convertTo(ROI,TIPO_MAT,1,0);


            lbp.Aplica(ROI,LBP,RAIO,VIZINHO);

            vector<float> temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for(; it != it_end; ++it) temp.push_back(*it);

            Mat test(1,temp.size(),TIPO_MAT);

            for(int k = 0; k < test.rows; k++)
                for(int l = 0; l < test.cols; l++)
                    test.at<float>(k,l) = temp[l];

            Mat response(1,2,TIPO_MAT);


            float PREDICAO = mlp.predict(test,response);

            int maxIndex = 0;
            float value=0.0f;
            float maxValue = response.at<float>(0,0);

            for(int index=0; index < 2; index++)
            {
                value = response.at<float>(0,index);
                if(value > maxValue)
                {
                    maxValue = value;
                    maxIndex = index;
                }
            }

            //maxIndex is the predicted class.
            if(PREDICAO == 0)
                PREDICAO = maxValue;

            if ( PREDICAO == 1.0f ) {
                df.predicao = PREDICAO; df.ponto = roi;
                faces.push_back( df );
                retorno++;
            }

            if(maxIndex == 0)
            {
                cout << "This is face \t" ;
            }

        }

    }
    return retorno;
}

void RedeNeural::TesteHardCodeMonitorado(QString nomeArquivo)
{
    vector<Mat> images;
    LerImagemPasta(images,pastaTeste);

    cout << "Comecando o Teste" << endl;
    for (int i = 0; i<images.size();i++)   // Teste com amostra de Faces nas Amostras
    {
        clock_t tempoInicial = clock();

        Mat imgQN = images.at(i);
        int r = Teste( imgQN );
        eliminaRepetidos(r);
        salva.imagens.append(r);
        cout << "\t pos = " << r << "\t neg = " << endl;// << busca2.IMAGENSNEGATIVAS << endl;
        QString nome = QString("/p%1.jpg").arg(i+1);
        nome = pastaSalva + nome;
        desenhaRetangulo(imgQN);
        imwrite(nome.toStdString(),imgQN);

        clock_t tempoFinal = clock();

        cout << "Tempo total de reconhecimento: " << ((tempoFinal - tempoInicial) / CLOCKS_PER_SEC ) << " segundos"<< endl;
    }

    cout << "Acabou o Teste" << endl;
}

void RedeNeural::TesteTreino()
{
    vector<Mat> images;
    LerImagemPasta(images,pastaTeste);

    if(valorTesteNPessoas == 0)
        valorTesteNPessoas = 900;
    if(valorTestePessoas == 0)
        valorTestePessoas = 39;

    int total = valorTestePessoas + valorTesteNPessoas;

    Mat resultado(images.size(),CLASSES,TIPO_MAT);

    for(int i = 0;i < total;i++)
    {
        if(i < valorTestePessoas)
            resultado.at<float>(i,0) = 1;
        else
            resultado.at<float>(i,1) = 1;
    }

    int acertos = 0;
    int erros =  0;

    cout << "Comecando o Teste" << endl;
    for (int c = 0; c<images.size();c++)   // Teste com amostra de Faces nas Amostras
    {
        Mat Query = images.at(c);
        Mat ROI(Size(WIDTH,HEIGHT),TIPO_MAT, Scalar::all(0));
        Mat LBP;
        Point roi;

        // convoluçao para gerar uma imagem de 320 x 240 px em NAO faces de 25 x 30 px
        for(int i = 0; i <= Query.rows - HEIGHT ; i++)
        {
            roi.y = i;

            for(int j =0; j <= Query.cols - WIDTH ; j++)
            {
                roi.x = j;

                Query.operator ()(Rect(roi.x,roi.y,WIDTH,HEIGHT)).convertTo(ROI,TIPO_MAT,1,0);


                lbp.Aplica(ROI,LBP,RAIO,VIZINHO);

                vector<float> temp;

                MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

                for(; it != it_end; ++it) temp.push_back(*it);

                Mat test(1,temp.size(),TIPO_MAT);

                for(int k = 0; k < test.rows; k++)
                    for(int l = 0; l < test.cols; l++)
                        test.at<float>(k,l) = temp[l];

                Mat response(1,CLASSES,TIPO_MAT);


                mlp.predict(test,response);

                int maxIndex = 0;
                float value=0.0f;
                float maxValue = response.at<float>(0,0);

                for(int index=1; index < CLASSES; index++)
                {
                    value = response.at<float>(0,index);
                    if(value > maxValue)
                    {
                        maxValue = value;
                        maxIndex = index;
                    }
                }

                printf("Testing Sample %i -> class result (digit %d)\n", c, maxIndex);

                //maxIndex is the predicted class.
                //cout << "Imagens:" << c << " maxIndex:" << maxIndex << " valor no vetor: " << resultado.at<float>(i,maxIndex) << endl;
                if(resultado.at<float>(c,maxIndex) != 1.0f)
                {
                    erros++;
                    cout << "Imagens:" << c << " maxIndex:" << maxIndex << " valor no vetor: " << resultado.at<float>(i,maxIndex) << endl;
                }
                else
                    acertos++;
            }

        }
    }

    cout << "\nResults on the testing dataset\n" << endl;
    cout << "\tCorrect classification:" << acertos << endl;
    cout <<"\tWrong classifications:" << erros << endl;
}

void RedeNeural::CarregaConfiguracao(QString arquivoConfiguracao)
{

}

void RedeNeural::Load()
{
    mlp.load(xml.toStdString().c_str());
}

void RedeNeural::Treino(int quantidadePositiva)
{
    //Size DIM(Features[1].size(),Features.size()); // (width, height)

//    Mat trainData( Features.size(),2, CV_32FC1);
//    Mat responses( Features.size(),1, CV_32FC1);

    Size DIM(Features[1].size(),Features.size());

    Mat trainData( DIM, TIPO_MAT, Scalar::all(0) );
    Mat responses( Size(2, Features.size()), TIPO_MAT, Scalar::all(0) );

    //  --------- Carrega os vetores em cv::Mat para a fase de Treino --------------

    for(int i = 0; i < Features.size(); i++)
    {
        if ( i < quantidadePositiva )
            responses.at<float>(i,0) = 1.0;
        else
            responses.at<float>(i,1) = 1.0;
    }


    for(int k = 0; k < trainData.rows; k++)
        for(int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k,l) = Features[k][l];

    // -----------------------------------------------------------------------------

    Features.clear();

   if ( responses.depth() == TIPO_MAT && trainData.depth() == TIPO_MAT )
    {
        // As amostras estao armazenadas em linhas ...
        //boost.train(trainData, CV_ROW_SAMPLE, responses); //, Mat(), Mat(), Mat(), Mat(), BoostParams(CvBoost::REAL, 100, 0.95, 5, false, 0));
        int flag = 0;//CvANN_MLP::NO_OUTPUT_SCALE;
        mlp.train(trainData,responses, Mat(),Mat(),params,flag);
        //boost.save( xml.toStdString().c_str() );
        mlp.save(xml.toStdString().c_str());
    }
    else
       cout << "Os dados para treino ou resposta estão em formatos errado !";
}

void RedeNeural::PreencheParametro()
{
    if(params.train_method == CvANN_MLP_TrainParams::BACKPROP)
    {
        salva.metodo = "BP";
        salva.bp_dw_scale = params.bp_dw_scale;
        salva.bp_moment_scale == params.bp_moment_scale;
    }
    else
    {
        salva.metodo = "RP";
        salva.rp_dw0 = params.rp_dw0;
        salva.rp_dw_max = params.rp_dw_max;
        salva.rp_dw_min = params.rp_dw_min;
        salva.rp_dw_minus = params.rp_dw_minus;
        salva.rp_dw_plus = params.rp_dw_plus;
    }

    salva.max_iter = criteria.max_iter;
    salva.epsilon = criteria.epsilon;
    salva.criteriaType = criteria.type;

    salva.funcaoAtivacao = activateFunc;
}

void RedeNeural::InicializaRede()
{
    SetTermCriteria();
    SetTrainsParams();
    CriaRede();
}

void RedeNeural::SetTrainsParams()
{
    params.train_method = CvANN_MLP_TrainParams::BACKPROP;//CvANN_MLP_TrainParams::RPROP;
    params.bp_dw_scale = 0.1;//0.05f;
    params.bp_moment_scale = 0.1;//0.05f;
    params.term_crit = criteria;
}

void RedeNeural::SetTermCriteria()
{
    criteria.max_iter = 1000;
    criteria.epsilon = 0.01;
    criteria.type = CV_TERMCRIT_ITER + CV_TERMCRIT_EPS;
}

void RedeNeural::CriaRede()
{
    Mat layers = CriaLayes();
    activateFunc = CvANN_MLP::SIGMOID_SYM; //CvANN_MLP::IDENTITY; // CvANN_MLP::GAUSSIAN
    mlp.create(layers,activateFunc);
}

Mat RedeNeural::CriaLayes()
{
    // define the structure for the neural network (MLP)
    // The neural network has 3 layers.
    // - one input node per attribute in a sample so 256 input nodes
    // - 16 hidden nodes
    // - 10 output node, one for each class.

    Mat layers(3, 1, CV_32S);
    layers.at<int>(0, 0) = ATTRIBUTES;//input layer
    layers.at<int>(1, 0) = 16;//hidden layer
    layers.at<int>(2, 0) = CLASSES;//output layer
    return layers;

    QList<int> camadas;
    camadas.append(16);
    salva.camdaOculta = camadas;
}

