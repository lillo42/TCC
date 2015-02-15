#ifndef LBPCONTROLLER_H
#define LBPCONTROLLER_H

//Qt
#include <QObject>
#include <QRunnable>
#include <QList>

//OpenCV
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

//Minhas classes
#include <LBP/lbp.h>
#include <IO/iocontroller.h>

using namespace cv;

class LBPController : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit LBPController(QObject *parent = 0);
    ~LBPController();

    void run();

    void addMatTreina(Mat &image);
    void addMatAplica(Mat &image);


signals:

public slots:

private:
    LBP lbp;
    QList<Mat> listaTreina;
    QList<Mat> listaAplica;
    QString path;
    IOController io;

    void aplica(Mat &query);
    void treina(Mat &query);

};

#endif // LBPCONTROLLER_H
