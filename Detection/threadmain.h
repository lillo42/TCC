#ifndef THREADMAIN_H
#define THREADMAIN_H

//Qt
#include <QObject>
#include <QThread>
#include <QThreadPool>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QList>

//Opencv
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//Minhas classes
#include <LBP/lbpcontroller.h>

using namespace cv;
class ThreadMain : public QObject, QRunnable
{
    Q_OBJECT
public:
    explicit ThreadMain(QObject *parent = 0);
    ~ThreadMain();

    void run();

signals:

public slots:

private:
    LBPController *lbp;
    //QList<QString> listaImagens;
    QDir dir;

    void startThread();
    void CarregaImagens();
    void decideAcaoImage(QString nome, Mat &query);

    void acaoLBP(Mat &query, int acao);
    void acaoRN(Mat &query, int acao);

    int interpretaTipoProcessamento(QString &nome);
    int interpretaTreinoAplicacao(QString &nome);

};

#endif // THREADMAIN_H
