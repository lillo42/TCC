#include "leitor.h"

Leitor::Leitor()
{

}

Leitor::~Leitor()
{

}

void Leitor::LerImagemPasta(vector<Mat> &retorno, QString pasta)
{
    QDir diretorio(pasta);
    QStringList files = GetAllFilesNamesWithinFolder(diretorio);
    foreach (const QString file, files) {
        Mat frame = imread(file.toStdString().c_str());

        if (!frame.data){
            IplImage* img = cvLoadImage(file.toStdString().c_str());
            frame = Mat(img);
        }

        if(frame.data){
            retorno.push_back(frame);
        }
    }
}

QStringList Leitor::GetAllFilesNamesWithinFolder(QDir dir)
{
    QStringList retorno;

    QFileInfoList fileList = dir.entryInfoList();

    foreach (const QFileInfo &info, fileList)
        retorno.append(QString("%1/%2").arg(dir.path()).arg(info.fileName()));

    return retorno;
}

