#ifndef LEITOR_H
#define LEITOR_H

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <vector>
#include <iostream>

#include <QString>
#include <QDir>

using namespace cv;
using namespace std;

class Leitor
{
public:
    Leitor();
    ~Leitor();

    void LerImagemPasta(vector<Mat>& retorno, QString pasta);

private:
    QStringList GetAllFilesNamesWithinFolder(QDir dir);
};

#endif // LEITOR_H
