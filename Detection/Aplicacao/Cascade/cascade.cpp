#include "cascade.h"

Cascade::Cascade()
{
    xml = "lbpcascade_frontalface.xml";
}

Cascade::~Cascade()
{

}

void Cascade::Detecta(Mat &image,vector<Rect> &face )
{
    faces.detectMultiScale(image,face,1.1, 2, 0, Size(80, 80));
}


void Cascade::LoadBoost()
{
    faces.load(xml.toStdString());
}

