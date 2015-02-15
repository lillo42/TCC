#ifndef LBP_H
#define LBP_H

//OpenCV
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//STD
#include <vector>


//Qt
#include <QString>
//Defines
#define WIDTH_PADRAO  50//32 // cols
#define HEIGHT_PADRAO 60//36 //rows

#define WIDTH_ROI  50// cols
#define HEIGHT_ROI 60// rows

#define ANDA_WIDTH 6
#define ANDA_HEIGHT 6//64

#define RAIO 3
#define VIZINHAZA 24

using namespace cv;
using namespace std;

struct detF {
    float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por distância
    Point ponto;        // Localizacao a Face
} typedef DetectFace;

class LBP
{
public:
    LBP();
    ~LBP();

    void aplica(Mat &query);
    void treina(Mat &query);
    void desenhaRetangulo(Mat &imagem);


private:
    void extraiCaracteristicas(Mat &query);
    void padraoLocal(Mat &origem, Mat &destino, int raio, int vizinhaca);

    float PREDICAO;
    unsigned int IMAGENSPOSITIVAS, IMAGENSNEGATIVAS, AMOSTRA;

    CvBoost boost;

    vector< vector <float> > features;
    vector<DetectFace> faces;

};

#endif // LBP_H
