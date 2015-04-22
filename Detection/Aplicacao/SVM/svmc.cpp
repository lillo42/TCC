#include "svmc.h"

SVMC::SVMC()
{
    xml = "svm.xml";
}

SVMC::~SVMC()
{

}

void SVMC::Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica)
{
    Mat trainData, responses;
    ClassificadorBase::TreinoBase(caracteristica,naoCarracteristica,trainData,responses);

    clock_t tempoInicial = clock();
    // As amostras estao armazenadas em linhas ...
    cout << "Treinando..." << endl;
    svm.train(trainData,responses,Mat(),Mat(),parametro);

    cout << "Salvando treino ..." << endl;
    svm.save(xml.toStdString().c_str());

    clock_t tempoFinal = clock();

    cout << "Tempo de treino: " << ((tempoFinal - tempoInicial) /CLOCKS_PER_SEC) << endl;
}

float SVMC::Predicao(Mat image)
{
    return svm.predict(image);
}

void SVMC::LoadBoost()
{
    svm.load(xml.toStdString().c_str());
}

void SVMC::LoadParametros()
{
    parametro.svm_type = CvSVM::C_SVC;
    parametro.svm_type = CvSVM::C_SVC;
    parametro.kernel_type = CvSVM::RBF; //CvSVM::RBF, CvSVM::LINEAR ...
    parametro.degree = 0; // for poly
    parametro.gamma = 20; // for poly/rbf/sigmoid
    parametro.coef0 = 0; // for poly/sigmoid

    parametro.C = 7; // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
    parametro.nu = 0.0; // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
    parametro.p = 0.0; // for CV_SVM_EPS_SVR

    parametro.class_weights = NULL; // for CV_SVM_C_SVC
    parametro.term_crit.type = CV_TERMCRIT_ITER +CV_TERMCRIT_EPS;
    parametro.term_crit.max_iter = 1000;
    parametro.term_crit.epsilon = 1e-6;
}

