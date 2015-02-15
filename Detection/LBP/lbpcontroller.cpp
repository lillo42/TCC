#include "lbpcontroller.h"

LBPController::LBPController(QObject *parent) : QObject(parent)
{
    path = "LocalPatterns";
}

LBPController::~LBPController()
{

}

void LBPController::run()
{
    Mat mat;
    forever
    {
        if(!listaAplica.isEmpty())
        {
            mat = listaAplica.first();
            aplica(mat);
            listaAplica.removeFirst();
        }
        if(!listaTreina.isEmpty())
        {
            mat = listaTreina.first();
            treina(mat);
            listaTreina.removeFirst();
        }
    }
}

void LBPController::addMatTreina(Mat &image)
{
    listaTreina.append(image);
}

void LBPController::addMatAplica(Mat &image)
{
    listaAplica.append(image);
}

void LBPController::aplica(Mat &query)
{
    lbp.aplica(query);
    lbp.desenhaRetangulo(query);
    io.Grava(path,query);
}

void LBPController::treina(Mat &query)
{
    lbp.treina(query);
}



