clear all
clc

% 1) Criar Padrões de Entrada/Saída
P=-1:0.05:1;
T=sin(2*pi*P)+0.1*randn(size(P));
plot(P,T,'+r');
grid
xlabel('Eixo x');
ylabel('Eixo y');
title('Padrões de Treinamento');
pause

% 2) Criar uma arquitetura de rede MLP.
net = feedforwardnet(20);
net = configure(net,P,T);

% 3) Dividir Padrões em Treinamento, Validação e Teste.
net.divideFcn='dividerand';
net.divideParam.trainRatio=1.00;
net.divideParam.valRatio=0.00;
net.divideParam.testRatio=0.00;

% 4) Inicializando os Pesos da Rede.
net=init(net);

% 5) Treinando a Rede Neural.
net.trainParam.showWindow=true;         % Exibe a Interface Gráfica com o Usuário (GUI)
net.layers{1}.dimensions=20;            % Número de Neorônios da Camada Interna
net.layers{1}.transferFcn='tansig';     % Funções de Ativação da Camada Interna
net.layers{2}.transferFcn='purelin';    % Funções de Ativação da Camada de Saída
net.performFcn='mse';                   % Determina o critério de Performance do Treinameno   
net.trainFcn='trainbr';                 % Determina o Algoritmo de Treinamento   
%net.trainFcn='trainlm';                 % Determina o Algoritmo de Treinamento     
net.trainParam.epochs=10000;            % Número Máximo de Épocas de Treinamento
net.trainParam.time=30;                 % Tempo Máximo de Treinamento 
net.trainParam.lr=0.2;                  % Taxa de Aprendizado 
net.trainParam.min_grad=10^-18;         % Valor Mínimo do Gradiente, Como Critério de Parada 
net.trainParam.max_fail=1000;           % Número Máximo de Interações Sem Decaimento do Gradiente        
[net, tr]=train(net,P,T);

% 6) Simular as respostas de saída da rede MLP.
a=sim(net,P);
plot(P,T,'+r',P,a,'b');
grid
xlabel('Eixo x');
ylabel('Eixo y');
title('Resultado de Generalização da Rede');
