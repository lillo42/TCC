%% Inicializa��o
%Limpando todas a variaveis antes de come�ar
clear all
clc %Limpa a tela

%TODO: Deixar de maneira dinamica
pathName = 'C:\Users\Rafel\Documents\MatLab\Imagens' %Lendo pasta com as imagens
listaImage = dir(pathName); %Carrega conteudo dentro das pasta

%cria uma matriz para armazenar as de imagens de tamanho N x 1
listaImageProcess = cell(size(listaImage) - 3,1);


%% Carrega Imagens
%Loop para carregar as imagens em uma lista
for p=3:size(listaImage)
    %Carrega a imagem
    image = imread(strcat(pathName,'\',listaImage(p,1).name));
    %Mostra na tela a imagens
    %display(strcat('Image ', int2str(p)))
    
    %Adiciona na lista
    listaImageProcess{p-2,1} = image;
end

%%Carrega parametros para a rede neural
%Matriz para a rede neural
PImagens=[];
TImagens=[];
%Loop para carregar
for i=1:1:40 %TODO: verificar como colocar um n�mero maior para a rede neural
    PImagens = [PImagens listaImageProcess(i,1)'];
    TImagens = [TImagens listaImageProcess(i+1,1)'];  
end

P = PImagens;
T = TImagens;

%% Rede Neural

%1) Criando a rede com arquitetura MLP
net  = feedforwardnet(20);
net = configure(net,P,T);

%2) Dividir Padr�es em Treinamento, Valida��o e Teste.
net.divideFcn='dividerand';
net.divideParam.tainRatio=1.00;
net.divideParam.valRatio=0.00;
net.divideParam.testRatio=0.00;

%3) Inicializando os Pesos da Rede.
net=init(net);

%4) Treinando a Rede Neural.
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
