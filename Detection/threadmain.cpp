#include "threadmain.h"

ThreadMain::ThreadMain(QObject *parent) : QObject(parent)
{
    lbp = new LBPController();
    dir = QString("../Imagens");
}

ThreadMain::~ThreadMain()
{

}

void ThreadMain::run()
{

    startThread();

    forever
    {
        CarregaImagens();
    }
}

void ThreadMain::startThread()
{
    QThreadPool::globalInstance()->start(lbp);
}

void ThreadMain::CarregaImagens()
{
    Mat query;
    QString filename;
    QFileInfoList fileList = dir.entryInfoList();
    foreach (const QFileInfo &info, fileList){
        filename = QString("%1/%2").arg(dir.path()).arg(info.fileName());
        query = imread(filename.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
        decideAcaoImage(info.fileName(),query);
    }
}

void ThreadMain::decideAcaoImage(QString nome, Mat &query)
{
    int tipoReconhecimento = interpretaTipoProcessamento(nome);
    int tipoAcao = interpretaTreinoAplicacao(nome);

    if(tipoReconhecimento == 0)
        acaoLBP(query,tipoAcao);
    else if(tipoReconhecimento == 1)
        acaoRN(query,tipoAcao);
}

void ThreadMain::acaoLBP(Mat &query, int acao)
{
    if(acao == 0)
        lbp->addMatTreina(query);
    else if(acao == 1)
        lbp->addMatAplica(query);
}

void ThreadMain::acaoRN(Mat &query, int acao)
{

}

int ThreadMain::interpretaTipoProcessamento(QString &nome)
{
    if(nome.at(0) == 'L')
        return 0;
    else if(nome.at(0) == 'R')
        return 1;
    else
        return -1;
}

int ThreadMain::interpretaTreinoAplicacao(QString &nome)
{
    if(nome.at(1) == 'T')
        return 0;
    else if(nome.at(0) == 'A')
        return 1;
    else
        return -1;
}

