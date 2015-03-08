%% Programa para realizar o treinamento supervisionado de uma rede neural
%% artificial com arquitetura MLP para aprender o gráfico complexo de uma
%% função bi-dimensional.

% FASE 01: Obter os Padrões de Treinamento para uma Função Estática
% Complexa.
clear all                   % Apagar todas as variáveis
clc                         % Apagar a tela
x=0:.1:10;                  % Vetor da variável independente x
y=0:.1:10;                  % Vetor da variável independente y
[X Y]=meshgrid(x,y);        % Malha Bidimensional do par ordenado (x,y)

Z=X.*sin(4*X)+1.1*Y.*sin(2*Y);  % Valor da variável dependente Z especifi-
                                % cada no domínio da malha anterior.

mesh(X,Y,Z);                % Plota o gráfico tridimensional (MALHA 3D)
title('Função a Ser Interpolada Pela Rede Neural');
xlabel('Eixo X');
ylabel('Eixo Y');
zlabel('Eixo Z');
grid on
hold on
pause();

dim=10000;                  % Número Total de Padrões de Treinamento
Xrna=10*rand(1,dim);        % Valores Aleatórios de x no domínio [0, 10]
Yrna=10*rand(1,dim);        % Valores Aleatórios de y no domínio [0, 10]
Zrna=Xrna.*sin(4*Xrna)+1.1*Yrna.*sin(2*Yrna);
plot3(Xrna,Yrna,Zrna,'.b');
title('Treinamento com 10000 Pontos');
P=[Xrna; Yrna];
T=Zrna;

% FASE 02 e 03: Cosntruindo a Rede e Pré-processando os Padrões de Treina-
% mento.
% 2) Cosntruindo a Rede MLP de nome "net".
% Cria uma função de rede de nome "net" que representa uma arquitetura MLP.
net = feedforwardnet(30);
net = configure(net,P,T);

% 3) Pré-processamento dos Dados.
% 3.1) Normaliza os padrões de Treinamento de entrada\saída entre 0 e 1.
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
% 3.2) Dividindo os Dados em Três Sub-Conjuntos Distintos:
%      Conjunto de Treinamento, Conjunto  de  Validação  e 
%      Conjunto de Erro de Teste.
net.divideFcn='dividerand';
net.divideParam.trainRatio=0.70;
net.divideParam.valRatio=0.15;
net.divideParam.testRatio=0.15;
% 3.3) Inicializando os Pesos da Rede.
net=init(net);

% FASE 04: Treinando a Rede Neural.
net.trainParam.showWindow=true;     % Exibe a Interface Gráfica com o Usuário (GUI)
net.layers{1}.dimensions=30;        % Número de Neorônios da Camada Interna
net.layers{1}.transferFcn='tansig'; % Funções de Ativação da Camada Interna
net.layers{2}.transferFcn='purelin';% Funções de Ativação da Camada de Saída
net.performFcn='mse';               % Determina o critério de Performance do Treinameno   
net.trainFcn='trainlm';             % Determina o Algoritmo de Treinamento
net.trainParam.epochs=10000;        % Número Máximo de Épocas de Treinamento
net.trainParam.time=120;            % Tempo Máximo de Treinamento 
net.trainParam.lr=0.2;              % Taxa de Aprendizado 
net.trainParam.min_grad=10^-8;      % Valor Mínimo do Gradiente, Como Critério de Parada 
net.trainParam.max_fail=1000;       % Número Máximo de Interações Sem Decaimento do Gradiente    

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

% FASE 06: Plotar Gráficos de Performance de Treinamento Neural.
% 6.1) Plotar os Padrões de Treinamento Dividos em Treinamento, Validação e Teste.
% 6.1.1) Padrões de Treinamento.
trIn(1,:)=P(1,tr.trainInd);
trIn(2,:)=P(2,tr.trainInd);
trOut=T(tr.trainInd);
% 6.1.2) Padrões de Validação.
vIn(1,:)=P(1,tr.valInd);
vIn(2,:)=P(2,tr.valInd);
vOut=T(tr.valInd);
% 6.1.3) Padrões de Teste.
tsIn(1,:)=P(1,tr.testInd);
tsIn(2,:)=P(2,tr.testInd);
tsOut=T(tr.testInd);
% 6.1.4) Plotar Gráficos.
figure(2);
plot3(trIn(1,:),trIn(2,:),trOut,'.b');
hold on
plot3(vIn(1,:),vIn(2,:),vOut,'.r');
plot3(tsIn(1,:),tsIn(2,:),tsOut,'.y');
grid on
legend('Azul: Treinamento','Vermelho: Validação','Amarelo: Teste');
% 6.2) Gráfico do Erro Quadrático Médio
figure(3);
plotperf(tr)
% 6.3) Gráfico da Regressáo Entre as Saídas da Rede e os "Alvos". 
Ztarget=T;
Zout=net(P);
trOut=Zout(tr.trainInd);
vOut=Zout(tr.valInd);
tsOut=Zout(tr.testInd);
trTarg=Ztarget(tr.trainInd);
vTarg=Ztarget(tr.valInd);
tsTarg=Ztarget(tr.testInd);
figure(4);
plotregression(trTarg,trOut,'Trainamento',vTarg,vOut,'Validação',tsTarg,tsOut,'Teste');


