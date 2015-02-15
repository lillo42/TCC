#include "lbp.h"

LBP::LBP()
{

}

LBP::~LBP()
{

}

void LBP::aplica(Mat &query)
{

    Mat ROI(Size(WIDTH_PADRAO,HEIGHT_PADRAO),CV_32FC1, Scalar::all(0));
    Mat LBP;
    Point roi;  // Armazena as coordenadas das Features
    DetectFace df;
    faces.clear();
    IMAGENSPOSITIVAS=0;
    IMAGENSNEGATIVAS=0;
    Size size(WIDTH_ROI,HEIGHT_ROI);
    Mat ROI_TRUE = Mat::zeros(size,CV_32FC1);
    for(int i = 0; i <= query.rows - HEIGHT_PADRAO ; i++)
    {
        roi.y = i;

        for(int j =0; j <= query.cols - WIDTH_PADRAO ; j++)
        {
            roi.x = j;

            query.operator ()(Rect(roi.x,roi.y,WIDTH_PADRAO,HEIGHT_PADRAO)).convertTo(ROI,CV_32FC1,1,0);
            resize(ROI,ROI_TRUE,size);
            padraoLocal(ROI_TRUE,LBP,RAIO,VIZINHAZA);

            Mat temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for(; it != it_end; ++it)
                temp.push_back(*it);


            PREDICAO = boost.predict( temp, Mat(),Range::all(),false,true);

            QString nome = QString("ROI00%1-%2.jpg").arg(i).arg(j);
            string result2 = nome.toUtf8().constData();


            if ( PREDICAO > 15)
            {
                df.predicao = PREDICAO;
                df.ponto = roi;
                faces.push_back( df );
                IMAGENSPOSITIVAS++;
            }
            else
                IMAGENSNEGATIVAS++;
        }
    }
}

void LBP::treina(Mat &query)
{
    extraiCaracteristicas(query);
}

void LBP::desenhaRetangulo(Mat &imagem)
{
    Point center;
    int radius, scale= 0.264583333; // Converte para mm

    for(unsigned long i = 0; i < faces.size(); i++)
    {
        rectangle(imagem,(Rect(faces[i].ponto.x,
                                faces[i].ponto.y,WIDTH_PADRAO+1,HEIGHT_PADRAO+1)),
                  CV_RGB(255, 255, 0), 1.5);
        // comparar distancia entre os rec, e verficar a media.... para eliminar falsos positivos.

        center.x = faces[i].ponto.x+WIDTH_PADRAO/2;
        center.y = faces[i].ponto.y+HEIGHT_PADRAO/2;
        radius = cvRound((WIDTH_PADRAO + HEIGHT_PADRAO)*0.25*scale);
        circle( imagem, center, radius,  CV_RGB(0,255,0), 2);

    }
}

void LBP::extraiCaracteristicas(Mat &query)
{
    Mat ROI(Size(WIDTH_PADRAO,HEIGHT_PADRAO),CV_32FC1, Scalar::all(0));
    Mat LBP;
    Point roi; // Armazena as coordenadas das Features

    Size size(WIDTH_ROI,HEIGHT_ROI);
    Mat ROI_TRUE = Mat::zeros(size,CV_32FC1);
    // convoluçao da imagens 32 x 36
    for(int i = 0; i <= query.rows - HEIGHT_PADRAO ; i=i+ANDA_HEIGHT)
    {
        roi.y = i;

        for(int j = 0; j <= query.cols - WIDTH_PADRAO ; j=j+ANDA_WIDTH)
        {
            roi.x = j;

            query.operator ()(Rect(roi.x,roi.y,WIDTH_PADRAO,HEIGHT_PADRAO)).convertTo(ROI,CV_32FC1,1,0);

            resize(ROI,ROI_TRUE,size);

            padraoLocal(ROI_TRUE,LBP,RAIO,VIZINHAZA);

            vector<float> temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for(; it != it_end; ++it)
                temp.push_back(*it);

            features.push_back(temp);
            temp.empty();
        }
    }
}

void LBP::padraoLocal(Mat &origem, Mat &destino, int raio, int vizinhaca)
{
    vizinhaca = max(min(vizinhaca,31),1);
    destino = Mat::zeros(origem.rows-2*raio, origem.cols-2*raio, CV_32FC1);

    for (int n=0; n<vizinhaca; n++)
    {
        // Pontos de amostragem
        float x = static_cast<float>(raio) * cos(2.0*M_PI*n/static_cast<float>(vizinhaca));
        float y = static_cast<float>(raio) * -sin(2.0*M_PI*n/static_cast<float>(vizinhaca));

        // Indices relativos
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));

        // Normalizacao
        float ty = y - fy;
        float tx = x - fx;

        // Interpolacao dos pesos
        float w1 = (1 - tx) * (1 - ty);
        float w2 =      tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 =      tx  *      ty;

        // Iterecao
        for (int i=raio; i < origem.rows-raio;i++)
        {
            for (int j=raio;j < origem.cols-raio;j++)
            {
                float t = w1*origem.at<float>(i+fy,j+fx) + w2*origem.at<float>(i+fy,j+cx) + w3*origem.at<float>(i+cy,j+fx) + w4*origem.at<float>(i+cy,j+cx);

                destino.at<float>(i-raio,j-raio) += ((t > origem.at<float>(i,j)) && (abs(t-origem.at<float>(i,j)) > numeric_limits<float>::epsilon())) << n;
            }
        }
    }
}

