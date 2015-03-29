#ifndef LBPREDENEURAL_H
#define LBPREDENEURAL_H

#include "Base/lbpbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>

#include "RedeNeural/redeneural.h"

class LbpRedeNeural : public LbpBase
{
public:
    LbpRedeNeural();
    ~LbpRedeNeural();

    void Treina();


protected:
    int CalculaPredicao(Mat &frame);

private:
    RedeNeural rn;
};

#endif // LBPREDENEURAL_H
