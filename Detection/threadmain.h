#ifndef THREADMAIN_H
#define THREADMAIN_H

#include <QObject>

class ThreadMain : public QObject
{
    Q_OBJECT
public:
    explicit ThreadMain(QObject *parent = 0);
    ~ThreadMain();

signals:

public slots:
};

#endif // THREADMAIN_H
