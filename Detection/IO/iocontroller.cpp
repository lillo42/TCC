#include "iocontroller.h"

IOController::IOController(QObject *parent) : QObject(parent)
{

}

IOController::~IOController()
{

}

void IOController::Grava(QString path, Mat &query)
{
    QString filename = QDir::currentPath() + path;
    imwrite(filename.toStdString(),query);
}

