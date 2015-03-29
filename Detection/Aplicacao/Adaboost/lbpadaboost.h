#ifndef LBPADABOOST_H
#define LBPADABOOST_H

#include "Base/lbpbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>

#include "Adaboost/adaboost.h"

#include <QString>

class LbpAdaBoost :public LbpBase
{
public:
    LbpAdaBoost();
    ~LbpAdaBoost();

    void Treina();

protected:
    int CalculaPredicao(Mat &frame);

private:
    Adaboost boost;
};

#endif // LBPADABOOST_H
