#include "classificadorbase.h"

ClassificadorBase::ClassificadorBase()
{

}

ClassificadorBase::~ClassificadorBase()
{

}

void ClassificadorBase::SetPastaCaracateristica(QString pastaCaracateristica)
{
    this->pastaCaracateristica = pastaCaracateristica;
}

QString ClassificadorBase::GetPastaCaracateristica()
{
    return this->pastaCaracateristica;
}

void ClassificadorBase::SetNaoPastaCaracateristica(QString pastaNaoCaracateristica)
{
    this->pastaNaoCaracateristica = pastaNaoCaracateristica ;
}

QString ClassificadorBase::GetNaoPastaCaracateristica()
{
    return this->pastaNaoCaracateristica;
}

void ClassificadorBase::SetPastaTeste(QString pastaTeste)
{
    this->pastaTeste = pastaTeste;
}

QString ClassificadorBase::GetPastaTeste()
{
    return this->pastaTeste;
}

void ClassificadorBase::SetPastaSalva(QString pastaSalva)
{
    this->pastaSalva = pastaSalva;
}

QString ClassificadorBase::GetPastaSalva()
{
    return this->pastaSalva;
}

void ClassificadorBase::LerImagemPasta(vector<Mat> &retorno, QString pasta)
{
    QDir diretorio(pasta);
    QStringList files = GetAllFilesNamesWithinFolder(diretorio);
    foreach (const QString file, files) {
        Mat frame = imread(file.toStdString().c_str(),CV_LOAD_IMAGE_GRAYSCALE);

        if (!frame.data){
            IplImage* img = cvLoadImage(file.toStdString().c_str(),CV_LOAD_IMAGE_GRAYSCALE);
            frame = Mat(img);
        }

        if(frame.data){
            retorno.push_back(frame);
        }
    }

}

QStringList ClassificadorBase::GetAllFilesNamesWithinFolder(QDir dir)
{
    QStringList retorno;

    QFileInfoList fileList = dir.entryInfoList();

    foreach (const QFileInfo &info, fileList)
        retorno.append(QString("%1/%2").arg(dir.path()).arg(info.fileName()));

    return retorno;

}

void ClassificadorBase::desenhaRetangulo(Mat &imagem)
{
    Point center;
    int radius, scale= 0.264583333; // Converte para mm

    for(unsigned long i = 0; i < faces.size(); i++) {
        rectangle(imagem,(Rect(faces[i].ponto.x,
                                faces[i].ponto.y,WIDTH+1,HEIGHT+1)),
                  CV_RGB(255, 255, 0), 1.5);
        // comparar distancia entre os rec, e verficar a media.... para eliminar falsos positivos.

        center.x = faces[i].ponto.x+WIDTH/2;
        center.y = faces[i].ponto.y+HEIGHT/2;
        radius = cvRound((WIDTH + HEIGHT)*0.25*scale);
        circle( imagem, center, radius,  CV_RGB(0,255,0), 2);

    }
}

const string ClassificadorBase::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "( %d-%m-%Y ) %X", &tstruct);

    return buf;
}

void ClassificadorBase::eliminaRepetidos(int &quantidade)
{
    unsigned i = 0;

    while (i+1 < faces.size() ) {

        if ((faces[i+1].ponto.x - faces[i].ponto.x <= WIDTH) &&
                (faces[i+1].ponto.y - faces[i].ponto.y <= HEIGHT)){

            if (faces[i+1].predicao > faces[i].predicao)
                faces.erase(faces.begin()+i);
            else
                faces.erase(faces.begin()+1+i);
            quantidade--;
        }
        else
            i++;
    }
}

void ClassificadorBase::extraiCaracteristicas(Mat &Query)
{
    Mat ROI(Size(WIDTH,HEIGHT),TIPO_MAT, Scalar::all(0));
    Mat LBP;
    Point roi; // Armazena as coordenadas das Features

    // convoluçao para converter uma imagem de 320 x 240 px em faces de 25 x 30 px
    for(int i = 0; i <= Query.rows - HEIGHT ; i = i + HEIGHT_ANDA) {
        roi.y = i;

        for(int j = 0; j <= Query.cols - WIDTH ; j = j + WIDTH_ANDA) {
            roi.x = j;

            Query.operator ()(Rect(roi.x,roi.y,WIDTH,HEIGHT)).convertTo(ROI,TIPO_MAT,1,0);

            lbp.Aplica(ROI,LBP,RAIO,VIZINHO);

            vector<float> temp;

            MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();

            for(; it != it_end; ++it) temp.push_back(*it);

            Features.push_back(temp);
            temp.empty();
        }
    }
}

void ClassificadorBase::TesteTreino()
{
	vector<Mat> images;
   LerImagemPasta(images,pastaTeste);
  
    int valorTesteNPessoas = 900;
    int valorTestePessoas = 39;
  
    int total = valorTestePessoas + valorTesteNPessoas;

    vector<float> resultado;

    for(int i = 0;i < total;i++)
    {
        if(i < valorTestePessoas)
            resultado.push_back(1);
        else
            resultado.push_back(-1);
    }
  
  	 for(int i = 0; i <images.size();i++)
    {
      	int acerto = 0, erros = 0;
      	Mat image = images.at(i);
      	Teste(image, acerto, erros);

        //maxIndex is the predicted class.
        //cout << "Imagens:" << c << " maxIndex:" << maxIndex << " valor no vetor: " << resultado.at<float>(i,maxIndex) << endl;
        if(acerto == 1 && resultado[i] == -1 )
        {
          erros++;
          cout << "Imagens:" << i  << " valor no vetor: " << resultado[i] << endl;
        }
     }
}

void ClassificadorBase::Load()
{

}

void ClassificadorBase::Treino()
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

void ClassificadorBase::TesteHardCode()
{
    vector<Mat> images;
    LerImagemPasta(images,pastaTeste);

    cout << "Comecando o Teste" << endl;
    for (int i = 0; i<images.size();i++)   // Teste com amostra de Faces nas Amostras
    {
        clock_t tempoInicial = clock();

        Mat imgQN = images.at(i);
        int positivo = 0, negativo = 0;
        Teste( imgQN, positivo, negativo );
        eliminaRepetidos(positivo);
        cout << "\t pos = " << positivo << "\t neg = " << negativo << endl;// << busca2.IMAGENSNEGATIVAS << endl;
        QString nome = QString("/p%1.jpg").arg(i+1);
        nome = pastaSalva + nome;
        desenhaRetangulo(imgQN);
        imwrite(nome.toStdString(),imgQN);

        clock_t tempoFinal = clock();

        cout << "Tempo total de reconhecimento: " << ((tempoFinal - tempoInicial) / CLOCKS_PER_SEC ) << " segundos"<< endl;
    }

    cout << "Acabou o Teste" << endl;
}

void ClassificadorBase::Treino(int quantidadePositiva)
{

}

void ClassificadorBase::Teste(Mat &query, int &positivo, int &negativo)
{
   Mat ROI(Size(WIDTH,HEIGHT),CV_32FC1, Scalar::all(0));
    Mat LBP;
    Point roi;  // Armazena as coordenadas das Features
    DetectFace df;
    faces.clear();
    // convoluçao para gerar uma imagem de 320 x 240 px em NAO faces de 25 x 30 px
    for(int i = 0; i <= query.rows - HEIGHT ; i++) {
        roi.y = i;

        for(int j =0; j <= query.cols - WIDTH ; j++) {
            roi.x = j;

            query.operator ()(Rect(roi.x,roi.y,WIDTH,HEIGHT)).convertTo(ROI,CV_32FC1,1,0);


            lbp.Aplica(ROI,LBP,RAIO,VIZINHO);

            int PREDICAO = CalculaPredict(LBP);

            if ( ValorAceitavel(PREDICAO) ) 
            {
                df.predicao = PREDICAO; df.ponto = roi;
                faces.push_back( df );
                positivo++;
            }
            else
            	negativo++;

        }

    }
}

float ClassificadorBase::CalculaPredict(Mat &image)
{
    return image.rows;
}

bool ClassificadorBase::ValorAceitavel(float predict)
{
    return  predict != 0;
}

