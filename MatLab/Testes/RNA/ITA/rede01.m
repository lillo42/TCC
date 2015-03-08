%% Programa para realizar o treinamento supervisionado de uma rede neural
%% artificial com arquitetura MLP para aprender o gr�fico complexo de uma
%% fun��o bi-dimensional.

% FASE 01: Obter os Padr�es de Treinamento para uma Fun��o Est�tica
% Complexa.
clear all                   % Apagar todas as vari�veis
clc                         % Apagar a tela
x=0:.1:10;                  % Vetor da vari�vel independente x
y=0:.1:10;                  % Vetor da vari�vel independente y
[X Y]=meshgrid(x,y);        % Malha Bidimensional do par ordenado (x,y)

Z=X.*sin(4*X)+1.1*Y.*sin(2*Y);  % Valor da vari�vel dependente Z especifi-
                                % cada no dom�nio da malha anterior.

mesh(X,Y,Z);                % Plota o gr�fico tridimensional (MALHA 3D)
title('Fun��o a Ser Interpolada Pela Rede Neural');
xlabel('Eixo X');
ylabel('Eixo Y');
zlabel('Eixo Z');
grid on
hold on
pause();

dim=10000;                  % N�mero Total de Padr�es de Treinamento
Xrna=10*rand(1,dim);        % Valores Aleat�rios de x no dom�nio [0, 10]
Yrna=10*rand(1,dim);        % Valores Aleat�rios de y no dom�nio [0, 10]
Zrna=Xrna.*sin(4*Xrna)+1.1*Yrna.*sin(2*Yrna);
plot3(Xrna,Yrna,Zrna,'.b');
title('Treinamento com 10000 Pontos');
P=[Xrna; Yrna];
T=Zrna;

% FASE 02 e 03: Cosntruindo a Rede e Pr�-processando os Padr�es de Treina-
% mento.
% 2) Cosntruindo a Rede MLP de nome "net".
% Cria uma fun��o de rede de nome "net" que representa uma arquitetura MLP.
net = feedforwardnet(30);
net = configure(net,P,T);

% 3) Pr�-processamento dos Dados.
% 3.1) Normaliza os padr�es de Treinamento de entrada\sa�da entre 0 e 1.
net.inputs{1}.processParams{2}.ymin=0;
net.inputs{1}.processParams{2}.ymax=1;
net.outputs{2}.processParams{2}.ymin=0;
net.outputs{2}.processParams{2}.ymax=1;

disp('net.inputs{1}.processFcns');
net.inputs{1}.processFcns
disp('net.inputs{1}.processParams{2}');
net.inputs{1}.processParams{2}

disp('net.outputs{2}.processFcns');
net.outputs{2}.processFcns
disp('net.outputs{2}.processParams{2}');
net.outputs{2}.processParams{2}
pause();
% 3.2) Dividindo os Dados em Tr�s Sub-Conjuntos Distintos:
%      Conjunto de Treinamento, Conjunto  de  Valida��o  e 
%      Conjunto de Erro de Teste.
net.divideFcn='dividerand';
net.divideParam.trainRatio=0.70;
net.divideParam.valRatio=0.15;
net.divideParam.testRatio=0.15;
% 3.3) Inicializando os Pesos da Rede.
net=init(net);

% FASE 04: Treinando a Rede Neural.
net.trainParam.showWindow=true;     % Exibe a Interface Gr�fica com o Usu�rio (GUI)
net.layers{1}.dimensions=30;        % N�mero de Neor�nios da Camada Interna
net.layers{1}.transferFcn='tansig'; % Fun��es de Ativa��o da Camada Interna
net.layers{2}.transferFcn='purelin';% Fun��es de Ativa��o da Camada de Sa�da
net.performFcn='mse';               % Determina o crit�rio de Performance do Treinameno   
net.trainFcn='trainlm';             % Determina o Algoritmo de Treinamento
net.trainParam.epochs=10000;        % N�mero M�ximo de �pocas de Treinamento
net.trainParam.time=120;            % Tempo M�ximo de Treinamento 
net.trainParam.lr=0.2;              % Taxa de Aprendizado 
net.trainParam.min_grad=10^-8;      % Valor M�nimo do Gradiente, Como Crit�rio de Parada 
net.trainParam.max_fail=1000;       % N�mero M�ximo de Intera��es Sem Decaimento do Gradiente    

[net, tr]=train(net,P,T);

% FASE 05: Testando a Rede Neural.
aux=size(X);
for i=1:1:aux(1)
    for j=1:1:aux(2)
        Paux=[X(i,j) Y(i,j)]'; 
        Zteste(i,j)=net(Paux);
    end
end
figure(1);
hold off
plot3(Xrna,Yrna,Zrna,'.r');
hold on
mesh(X,Y,Zteste);
grid

% FASE 06: Plotar Gr�ficos de Performance de Treinamento Neural.
% 6.1) Plotar os Padr�es de Treinamento Dividos em Treinamento, Valida��o e Teste.
% 6.1.1) Padr�es de Treinamento.
trIn(1,:)=P(1,tr.trainInd);
trIn(2,:)=P(2,tr.trainInd);
trOut=T(tr.trainInd);
% 6.1.2) Padr�es de Valida��o.
vIn(1,:)=P(1,tr.valInd);
vIn(2,:)=P(2,tr.valInd);
vOut=T(tr.valInd);
% 6.1.3) Padr�es de Teste.
tsIn(1,:)=P(1,tr.testInd);
tsIn(2,:)=P(2,tr.testInd);
tsOut=T(tr.testInd);
% 6.1.4) Plotar Gr�ficos.
figure(2);
plot3(trIn(1,:),trIn(2,:),trOut,'.b');
hold on
plot3(vIn(1,:),vIn(2,:),vOut,'.r');
plot3(tsIn(1,:),tsIn(2,:),tsOut,'.y');
grid on
legend('Azul: Treinamento','Vermelho: Valida��o','Amarelo: Teste');
% 6.2) Gr�fico do Erro Quadr�tico M�dio
figure(3);
plotperf(tr)
% 6.3) Gr�fico da Regress�o Entre as Sa�das da Rede e os "Alvos". 
Ztarget=T;
Zout=net(P);
trOut=Zout(tr.trainInd);
vOut=Zout(tr.valInd);
tsOut=Zout(tr.testInd);
trTarg=Ztarget(tr.trainInd);
vTarg=Ztarget(tr.valInd);
tsTarg=Ztarget(tr.testInd);
figure(4);
plotregression(trTarg,trOut,'Trainamento',vTarg,vOut,'Valida��o',tsTarg,tsOut,'Teste');


