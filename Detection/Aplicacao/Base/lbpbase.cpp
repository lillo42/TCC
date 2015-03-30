#include "lbpbase.h"

LbpBase::LbpBase()
{

}

LbpBase::~LbpBase()
{

}

bool LbpBase::AchouCaracteristica(Mat &image, bool desenha)
{
    bool retorno = false;
    Mat ROI(Size(width, height), CV_32FC1, Scalar::all(0));
    Mat LBP;
    DetectFeatures df;
    features.clear();
    Point roi;  // Armazena as coordenadas das Features
    Size size(width, height);
    Mat ROI_TRUE = Mat::zeros(size, CV_32FC1);

    // convolusao da imagens 32 x 36
    for (int i = 0; i <= image.rows - height; i+=height/2)
    {
        roi.y = i;

        for (int j = 0; j <= image.cols - width; j+=width/2)
        {
            roi.x = j;

            image.operator ()(Rect(roi.x, roi.y, width, height)).convertTo(ROI, CV_32FC1, 1, 0);
            resize(ROI, ROI_TRUE, size);
            lbp.AplicaLBP(ROI_TRUE, LBP, 1, 8);

            Mat temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for (; it != it_end; ++it)
                temp.push_back(*it);


            int predicao = CalculaPredicao(temp);

            if (predicao > valorAceitavelPredicao)
            {
                retorno = true;
                df.predicao = predicao; df.ponto = roi;
                features.push_back(df);
            }
        }
    }

    if (desenha)
    {
        RemoveReptidos();
        DesenhaRetangulo(image);
    }
    return retorno;
}

void LbpBase::SetPastaCaracateristica(QString pastaCaracateristica)
{
    this->pastaCaracateristica = pastaCaracateristica;
}

QString LbpBase::GetPastaCaracateristica()
{
    return this->pastaCaracateristica;
}

void LbpBase::SetNaoPastaCaracateristica(QString pastaNaoCaracateristica)
{
    this->pastaNaoCaracateristica = pastaNaoCaracateristica ;
}

QString LbpBase::GetNaoPastaCaracateristica()
{
    return this->pastaNaoCaracateristica;
}

void LbpBase::AplicaLBP(vector<Mat> &aplica)
{
    vector<Mat> retorno;
    cout << "Comencando a aplicar LBP" << endl;
    for (unsigned int i = 0; i < aplica.size(); i++)
    {
        Mat image = aplica.at(i);
        vector<Mat> temp = AplicaLBPImage(image);
        cout << "LBP aplicado ";

        for (unsigned int j = 0; j < temp.size(); j++)
            retorno.push_back(temp.at(j));

    }

    aplica.clear();

    cout << "Fim da aplicacao LBP" << endl;

    for (unsigned int i = 0; i < retorno.size(); i++)
        aplica.push_back(retorno.at(i));
}

void LbpBase::AplicaLBPCaracteristica(vector<Mat> &aplica)
{
    vector<Mat> retorno;
    cout << "Comencando a aplicar LBP" << endl;
    for (unsigned int i = 0; i < aplica.size(); i++)
    {
        Mat image = aplica.at(i);

        if(image.cols > 128 || image.rows > 128)
            continue;

        Mat mascara = Mat::zeros(128,128,0);
        int coluna = 64 - (image.cols / 2), linhas = 64 - (image.rows / 2);

        for(int i = 0;i < image.cols;i++)
        {
            int linhas2 = linhas;
            for(int j =0;j < image.rows;j++)
            {
                image.col(i).row(j).copyTo(mascara.col(coluna).row(linhas2));
                linhas2++;
            }
            coluna++;
        }

        vector<Mat> temp = AplicaLBPImage(mascara);
        cout << "LBP aplicado ";

        for (unsigned int j = 0; j < temp.size(); j++)
            retorno.push_back(temp.at(j));
    }

    aplica.clear();

    cout << "Fim da aplicacao LBP" << endl;

    for (unsigned int i = 0; i < retorno.size(); i++)
        aplica.push_back(retorno.at(i));
}

vector<Mat> LbpBase::AplicaLBPImage(Mat &image)
{
    vector<Mat> temp;

    Mat ROI(Size(width, height), CV_32FC1, Scalar::all(0));
    Mat LBP;
    Point roi; // Armazena as coordenadas das Features

    Size size(width, height);
    Mat ROI_TRUE = Mat::zeros(size, CV_32FC1);

    // convolusao da imagens 32 x 36
    for (int i = 0; i <= image.rows - HEIGHT; i = i + 6)
    {
        roi.y = i;

        for (int j = 0; j <= image.cols - WIDTH; j = j + 6)
        {
            roi.x = j;

            image.operator ()(Rect(roi.x, roi.y, width, height)).convertTo(ROI, CV_32FC1, 1, 0);

            lbp.AplicaLBP(ROI_TRUE, LBP, 1, 8);

            temp.push_back(LBP);
        }
    }
    return temp;
}

void LbpBase::RemoveReptidos()
{
    unsigned i = 0;

    while (i + 1 < features.size())
    {
        if ((features[i + 1].ponto.x - features[i].ponto.x <= width) &&
            (features[i + 1].ponto.y - features[i].ponto.y <= height))
        {

            if (features[i + 1].predicao > features[i].predicao)
                features.erase(features.begin() + i);
            else
                features.erase(features.begin() + 1 + i);
        }
        else
            i++;
    }

}

void LbpBase::DesenhaRetangulo(Mat &imagem)
{
    Point center;
    int radius, scale = 0.264583333; // Converte para mm

    for (unsigned long i = 0; i < features.size(); i++)
    {
        rectangle(imagem, (Rect(features[i].ponto.x,
            features[i].ponto.y, width + 1, height + 1)),
            CV_RGB(255, 255, 0), 1.5);

        // comparar distancia entre os rec, e verficar a media.... para eliminar falsos positivos.
        center.x = features[i].ponto.x + width / 2;
        center.y = features[i].ponto.y + height / 2;
        radius = cvRound((width + height)*0.25*scale);
        circle(imagem, center, radius, CV_RGB(0, 255, 0), 2);
    }

}

void LbpBase::Treina(vector<Mat> &caracteristicas, vector<Mat> &naoCaracteristicas)
{
    cout << "Lendo imagens" << endl;
    ler.LerImagemPasta(caracteristicas, pastaCaracateristica);
    ler.LerImagemPasta(naoCaracteristicas, pastaNaoCaracateristica);
    cout << "Terminou de ler" << endl;

    if (caracteristicas.size() <= 0 || naoCaracteristicas.size() <= 0)
        return;

    cout << "Aplicando LBP caracteristica" << endl;
    AplicaLBPCaracteristica(caracteristicas);

    cout << "Aplicando LBP Nao caracteristica" << endl;
    AplicaLBP(naoCaracteristicas);
}

