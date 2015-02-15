#include <QCoreApplication>
#include <QThreadPool>
#include <threadmain.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //ThreadMain *t = new ThreadMain();
    //QThreadPool::globalInstance()->start(t);

    return a.exec();
}
