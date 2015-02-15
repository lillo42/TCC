#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

//Qt
#include <QObject>
#include <QString>
#include <QDir>


//OpenCV
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
class IOController : public QObject
{
    Q_OBJECT
public:
    explicit IOController(QObject *parent = 0);
    ~IOController();

    void Grava(QString path,Mat &query);

signals:

public slots:
};

#endif // IOCONTROLLER_H
