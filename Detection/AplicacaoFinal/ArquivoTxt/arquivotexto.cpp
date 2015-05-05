#include "arquivotexto.h"

ArquivoTexto::ArquivoTexto()
{

}

ArquivoTexto::~ArquivoTexto()
{

}

void ArquivoTexto::Salva(ERedeNeural &nn, QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
        return;
    QTextStream stream(&file);

    stream << "Parametros:" << endl;

    //Critei
    stream << "\t Critei:" << endl;
    stream << "\t\t max_iter:" << nn.max_iter << endl;
    stream << "\t\t epsilon:" << nn.epsilon << endl;
    stream << "\t\t criteriaType:" << nn.criteriaType << endl;

    stream << endl;

    //Metodo de treino
    stream << "\t Parametros para treino:" << endl;
    stream << "\t\t Metodo de treino:" << nn.metodo.toStdString().c_str() << endl;
    if(nn.metodo == "BP")
    {
        stream << "\t\t bp_dw_scale:" << nn.bp_dw_scale << endl;
        stream << "\t\t bp_moment_scale:" << nn.bp_moment_scale << endl;
    }
    else
    {
        stream << "\t\t rp_dw0:" << nn.rp_dw0 << endl;
        stream << "\t\t rp_dw_plus:" << nn.rp_dw_plus << endl;
        stream << "\t\t rp_dw_minus:" << nn.rp_dw_minus << endl;
        stream << "\t\t rp_dw_min:" << nn.rp_dw_min << endl;
        stream << "\t\t rp_dw_max:" << nn.rp_dw_max << endl;
    }

    stream << endl;

    //Camadas
    stream << "\t Camadas Escondidas" << nn.rp_dw0 << endl;
    stream << "\t\t Quantidade" << nn.camdaOculta.size() << endl;
    for(int i = 0; i < nn.camdaOculta.size();i++)
        stream << "\t\t Camada " << i << "Numero neuronios:" << nn.camdaOculta.at(i) << endl;

    stream << endl;

    stream << "\t Funcao de Aticao" << nn.rp_dw0 << endl;
    stream << "\t\t Funcao de Aticao" << nn.funcaoAtivacao << endl;

    stream << endl;

    //Resultados
    stream << "Resultado:" << endl;

    //Tempo
    stream << "\t Tempo" << endl;
    stream << "\t\t tempo de treino:" << nn.tempoTreino << endl;

    stream << endl;

    //imagens
    stream << "\t Imagens" << endl;
    stream << "\t\t Quantidade no teste:" << nn.imagens.size() << endl;
    for(int i = 0;i < nn.imagens.size();i++)
        stream << "\t\t Imagem:" << i << "Quantidade achada: " << nn.imagens.at(i) << endl;

    file.close();
}


