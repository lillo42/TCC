#include "adaboost.h"

AdaBoost::AdaBoost()
{
    xml = "Adaboost.xml";
}

AdaBoost::~AdaBoost()
{

}

void AdaBoost::Treino()
{
    vector<Mat> caracteristicas, naoCaracteristicas;

    LerImagemPasta(caracteristicas,pastaCaracateristica);
    LerImagemPasta(naoCaracteristicas,pastaNaoCaracateristica);

    clock_t tempoInicial = clock();

    cout << "Extraindo Features de Amostras Positivas ." << endl;

    // Extrai caracteristicas Faces
    for (size_t i = 0; i < caracteristicas.size();i++)
    {
        Mat image = caracteristicas.at(i);
        extraiCaracteristicas(image);
    }

    cout  << "Extraindo Features de Amostras Negativas ";

    // Extrai caracteristicas Nao Faces
    for (size_t i = 0; i < naoCaracteristicas.size() ;i++)
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

int AdaBoost::Teste(Mat &Query)
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

            int PREDICAO = boost.predict( temp, Mat(),Range::all(),false,true);

            QString nome = QString("ROI00%1-%2.jpg").arg(i).arg(j);

            if ( PREDICAO > 12 ) {
                df.predicao = PREDICAO; df.ponto = roi;
                faces.push_back( df );
                retorno++;
            }

        }

    }
    return retorno;
}

void AdaBoost::Load()
{
    boost.load(xml.toStdString().c_str());
}

void AdaBoost::Treino(int quantidadePositiva)
{

    Size DIM(Features[1].size(),Features.size()); // (width, height)

    Mat trainData( DIM, CV_32FC1, Scalar::all(0) );
    Mat responses( Size(1, Features.size()), CV_32SC1, Scalar::all(0) );

    //  --------- Carrega os vetores em cv::Mat para a fase de Treino --------------

    for(std::vector<int>::size_type i = 0; i < Features.size(); i++)

        if ( i < quantidadePositiva )
            responses.at<int>(0,i) = 1;
        else
            responses.at<int>(0,i) = -1;


    for(int k = 0; k < trainData.rows; k++)
        for(int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k,l) = Features[k][l];

    // -----------------------------------------------------------------------------

    Features.clear();

    if ( responses.depth() == CV_32SC1 && trainData.depth() == CV_32FC1 )
    {
        // As amostras estao armazenadas em linhas ...
        boost.train(trainData, CV_ROW_SAMPLE, responses); //, Mat(), Mat(), Mat(), Mat(), BoostParams(CvBoost::REAL, 100, 0.95, 5, false, 0));
        boost.save( xml.toStdString().c_str() );
    }
    else
        cout << "Os dados para treino ou resposta estão em formatos errado !";
}

