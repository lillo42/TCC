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

    cout  << "Extraindo Features de Amostras Negativas ";

    // Extrai caracteristicas Nao Faces
    for (int i = 0; i < naoCaracteristicas.size() ;i++)
    {
        Mat image = naoCaracteristicas.at(i);
        extraiCaracteristicas( image );
        cout << ".";
    }

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

    cout << "Tempo Extracao de Caracteristicas -> " << ((tempoInicial1 - tempoInicial) / CLOCKS_PER_SEC ) << " segundos" << endl;
    cout << "Tempo Treino -> " << ((tempoFinal - tempoInicial1) / CLOCKS_PER_SEC ) << " segundos" << endl;
    cout << "Tempo Total -> " << ((tempoFinal - tempoInicial) / CLOCKS_PER_SEC )  << " segundos" << endl;
    cout << "Fim do Treino -> " << currentDateTime() << endl;
    cout << "Treino Finalizado ! " << endl;
}

int RedeNeural::Teste(Mat &Query)
{
    Mat ROI(Size(WIDTH,HEIGHT),CV_32FC1, Scalar::all(0));
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

            Query.operator ()(Rect(roi.x,roi.y,WIDTH,HEIGHT)).convertTo(ROI,CV_32FC1,1,0);


            lbp.Aplica(ROI,LBP,RAIO,VIZINHO);

            Mat temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for(; it != it_end; ++it) temp.push_back(*it);

            Mat test;
            InverteLinhaColuna(temp,test);

            Mat response(1,2,CV_32F);

            cout << "Layers count: " <<  mlp.get_layer_count() << endl;
            cout << "Layers size: " <<  mlp.get_layer_sizes() << endl;
            cout << "Teste Cols: " <<  test.cols << endl;

            if(test.cols != 644)
            {
                cout << "Temos um problema aqui!!" << endl;
                return -1;
            }


            float PREDICAO = mlp.predict(test,response);// boost.predict( temp, Mat(),Range::all(),false,true);

            //QString nome = QString("ROI00%1-%2.jpg").arg(i).arg(j);

            if ( PREDICAO > 12 ) {
                df.predicao = PREDICAO; df.ponto = roi;
                faces.push_back( df );
                retorno++;
            }

        }

    }
    return retorno;
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

    Size DIM(Features[1].size(),Features.size()); // (width, height)

    Mat trainData( DIM, CV_32FC1, Scalar::all(0) );
    Mat responses( Size(1, Features.size()), CV_32SC1, Scalar::all(0) );

    //  --------- Carrega os vetores em cv::Mat para a fase de Treino --------------

    for(std::vector<int>::size_type i = 0; i < Features.size(); i++)
    {
        if ( i < quantidadePositiva )
            responses.at<int>(i,0) = 1;
        else
            responses.at<int>(i,0) = -1;
    }


    for(int k = 0; k < trainData.rows; k++)
        for(int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k,l) = Features[k][l];

    // -----------------------------------------------------------------------------

    Features.clear();

    if ( responses.depth() == CV_32FC1 && trainData.depth() == CV_32FC1 )
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
    criteria.max_iter = 10000;
    criteria.epsilon = 0.00001f;
    criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
}

void RedeNeural::CriaRede()
{
    Mat layers = CriaLayes();
    int activateFunc = CvANN_MLP::SIGMOID_SYM;//CvANN_MLP::IDENTITY; //CvANN_MLP::SIGMOID_SYM CvANN_MLP::GAUSSIAN
    mlp.create(layers,activateFunc);
}

Mat RedeNeural::CriaLayes()
{
//    Mat layers = cv::Mat(4, 1, CV_32SC1);

//    layers.row(0) = Scalar(644);
//    layers.row(1) = Scalar(10);
//    layers.row(2) = Scalar(15);
//    layers.row(3) = Scalar(2);


    // define the structure for the neural network (MLP)
    // The neural network has 3 layers.
    // - one input node per attribute in a sample so 256 input nodes
    // - 16 hidden nodes
    // - 10 output node, one for each class.

    Mat layers(3, 1, CV_32SC1);
    layers.at<int>(0, 0) = 644;//input layer
    layers.at<int>(1, 0) = 16;//hidden layer
    layers.at<int>(2, 0) = 2;//output layer
    return layers;
}

void RedeNeural::InverteLinhaColuna(Mat &original, Mat &retorno)
{
    retorno = Mat(2,original.rows,CV_32F);
    for(int i = 0;i < original.rows;i++)
    {
        for(int j = 0; j < original.cols;j++)
        {
            original.row(i).col(j).copyTo(retorno.row(j).col(i));
        }
    }
}
