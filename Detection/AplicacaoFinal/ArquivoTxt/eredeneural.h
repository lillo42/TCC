#ifndef EREDENEURAL_H
#define EREDENEURAL_H

#include <QString>
#include <QPair>
#include <QList>

class ERedeNeural
{
public:
    ERedeNeural();
    ~ERedeNeural();

    int tempoTreino;
    QList<int> camdaOculta;

    int funcaoAtivacao;

    //Criteia
    int criteriaType;
    int    max_iter;
    double epsilon;

    //Parametros
    QString metodo;
    double bp_dw_scale, bp_moment_scale;
    double rp_dw0, rp_dw_plus, rp_dw_minus, rp_dw_min, rp_dw_max;

    QList<int> imagens;

};

#endif // EREDENEURAL_H
