clear all
clc

% 1) Criar Padr�es de Entrada/Sa�da
P=-1:0.05:1;
T=sin(2*pi*P)+0.1*randn(size(P));
plot(P,T,'+r');
grid
xlabel('Eixo x');
ylabel('Eixo y');
title('Padr�es de Treinamento');
pause

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
net.trainFcn='trainbr';                 % Determina o Algoritmo de Treinamento   
%net.trainFcn='trainlm';                 % Determina o Algoritmo de Treinamento     
net.trainParam.epochs=10000;            % N�mero M�ximo de �pocas de Treinamento
net.trainParam.time=30;                 % Tempo M�ximo de Treinamento 
net.trainParam.lr=0.2;                  % Taxa de Aprendizado 
net.trainParam.min_grad=10^-18;         % Valor M�nimo do Gradiente, Como Crit�rio de Parada 
net.trainParam.max_fail=1000;           % N�mero M�ximo de Intera��es Sem Decaimento do Gradiente        
[net, tr]=train(net,P,T);

% 6) Simular as respostas de sa�da da rede MLP.
a=sim(net,P);
plot(P,T,'+r',P,a,'b');
grid
xlabel('Eixo x');
ylabel('Eixo y');
title('Resultado de Generaliza��o da Rede');
