#ifndef ARQUIVOTEXTO_H
#define ARQUIVOTEXTO_H

#include <QString>
#include <QList>
#include <QPair>
#include <QFile>
#include <QTextStream>

#include "ArquivoTxt/eredeneural.h"

class ArquivoTexto
{
public:
    ArquivoTexto();
    ~ArquivoTexto();

    void Salva(ERedeNeural &nn, QString filename);
};

#endif // ARQUIVOTEXTO_H
