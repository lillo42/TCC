#ifndef LBPCONTROLLER_H
#define LBPCONTROLLER_H

#include <QObject>

class LBPController : public QObject
{
    Q_OBJECT
public:
    explicit LBPController(QObject *parent = 0);
    ~LBPController();

signals:

public slots:
};

#endif // LBPCONTROLLER_H
