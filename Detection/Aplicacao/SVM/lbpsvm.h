#ifndef LBPSVM_H
#define LBPSVM_H


#include "Base/lbpbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>

#include "SVM/svmc.h"

#include <QString>

class LbpSVM : public LbpBase
{
public:
    LbpSVM();
    ~LbpSVM();

    void Treina();
    void Load();
    void TesteHardCode();

protected:
    int CalculaPredicao(Mat &frame);

private:
    SVMC boost;
};

#endif // LBPSVM_H
