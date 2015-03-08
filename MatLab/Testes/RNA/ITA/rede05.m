clear all
clc

% 1) Criar Padr�es de Entrada/Sa�da
camargos=load('Camargos.txt');           % Vetor 42 x 12 (de 1971 at� 2012)

Pcamargos=[];
Tcamargos=[];
for i=1:1:40 
    Pcamargos = [Pcamargos camargos(i,:)'];
    Tcamargos = [Tcamargos camargos(i+1,:)'];  
end
P=[Pcamargos];
T=[Tcamargos];

% 2) Criar uma arquitetura de rede MLP.
net = feedforwardnet(20);
net = configure(net,P,T);

% 3) Dividir Padr�es em Treinamento, Valida��o e Teste.
net.divideFcn='dividerand';
net.divideParam.trainRatio=1.00;
net.divideParam.valRatio=0.00;
net.divideParam.testRatio=0.00;

% 4) Inicializando os Pesos da Rede.
net=init(net);

% 5) Treinando a Rede Neural.
net.trainParam.showWindow=true;         % Exibe a Interface Gr�fica com o Usu�rio (GUI)
net.layers{1}.dimensions=20;            % N�mero de Neor�nios da Camada Interna
net.layers{1}.transferFcn='tansig';     % Fun��es de Ativa��o da Camada Interna
net.layers{2}.transferFcn='purelin';    % Fun��es de Ativa��o da Camada de Sa�da
net.performFcn='mse';                   % Determina o crit�rio de Performance do Treinameno   
%net.trainFcn='trainbr';                 % Determina o Algoritmo de Treinamento (Bayesian Regularization)   
%net.trainFcn='trainrp';                 % Determina o Algoritmo de Treinamento (Resilient Backpropagation)     
net.trainFcn='trainlm';                 % Determina o Algoritmo de Treinamento (Levenberg-Marquardt) 
net.trainParam.epochs=1000000;          % N�mero M�ximo de �pocas de Treinamento
net.trainParam.time=60;                 % Tempo M�ximo de Treinamento (em segundos)
net.trainParam.lr=0.2;                  % Taxa de Aprendizado 
net.trainParam.min_grad=10^-18;         % Valor M�nimo do Gradiente, Como Crit�rio de Parada 
net.trainParam.max_fail=100000;         % N�mero M�ximo de Intera��es Sem Decaimento do Gradiente        
[net, tr]=train(net,P,T);

% 6) Simular as respostas de sa�da da rede MLP.
% 6.1) Plotar Padr�es de Treinamento
xP=1:1:(41*12);
xF=(41*12)+1:1:42*12;
XcamargosP=[];
for i=1:1:41
    XcamargosP=[XcamargosP camargos(i,:)];
end
XcamargosF=camargos(42,:);
plot(xP,XcamargosP,'b',xF,XcamargosF,'r')
xlabel('Meses')
ylabel('Vaz�o')
title('Vaz�o do Rio Camargos')
grid
% 6.2) Plotar Resultados da Simula��o
hold on
xS=1:1:(42*12);
PsA=camargos(1,:)';
Ms=PsA;
for i=1:1:41
    PsD=sim(net,PsA);
    Ms=[Ms PsD];
    PsA=PsD;
end
yS=[];
for i=1:1:42
    yS=[yS Ms(:,i)'];
end
plot(xS,yS,':m');




