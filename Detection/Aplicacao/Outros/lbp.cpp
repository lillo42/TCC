#include "lbp.h"

LBP::LBP()
{

}

LBP::~LBP()
{

}

void LBP::AplicaLBP(Mat &origem, Mat &destino, int raio, int vizinho)
{
    vizinho = max(min(vizinho, 31), 1);
    destino = Mat::zeros(origem.rows - 2 * raio, origem.cols - 2 * raio, CV_32FC1);

    for (int n = 0; n< vizinho; n++)
    {
        // Pontos de amostragem
        float x = static_cast<float>(raio)* cos(2.0*M_PI*n / static_cast<float>(vizinho));
        float y = static_cast<float>(raio)* -sin(2.0*M_PI*n / static_cast<float>(vizinho));

        // Indices relativos
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));

        // Normalizacao
        float ty = y - fy;
        float tx = x - fx;

        // Interpolacao dos pesos
        float w1 = (1 - tx) * (1 - ty);
        float w2 = tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 = tx  *      ty;

        // Iterecao
        for (int i = raio; i < origem.rows - raio; i++)
        {
            for (int j = raio; j < origem.cols - raio; j++)
            {
                float t = w1*origem.at<float>(i + fy, j + fx) + w2*origem.at<float>(i + fy, j + cx) + w3*origem.at<float>(i + cy, j + fx) + w4*origem.at<float>(i + cy, j + cx);

                destino.at<float>(i - raio, j - raio) += ((t > origem.at<float>(i, j)) && (abs(t - origem.at<float>(i, j)) > numeric_limits<float>::epsilon())) << n;
            }
        }
    }
}

