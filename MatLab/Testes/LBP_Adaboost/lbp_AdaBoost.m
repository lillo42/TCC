function main()
    %Limpando dados
    clear all;
    clc;

    %Set local das imagens
    pathImage = 'C:\Users\Rafel\Downloads\TCC\fdv54\fdv54\face\';
    extensao = '*.png';

    %carregando imagens
    % 0 - Pessoas
    % 1 - Não Pessoas
    % 2 - Teste
    [X, t] = readImages(pathImage,extensao);
    
    Pessoa = [];
    
    for i = 1: t - 1
        I = X(1,i);
        
        l = lbp(I,1,8);
        %[height width channels] = size(file);
        
        Pessoa = [Pessoa, imhist(uint8(l))];
    end
end

function [ X, t ] = readImages(path, extensao)

files = dir(strcat(path,extensao));
X = [];
t = 0;
     for n = 1 : length(files)
         filename = files(n).name;
         file = double(imread(strcat(path,filename)));
         
         [height, width, channels] = size(file);
         
         X = [X, reshape(file,width*height,1)];
         t = t + 1;
     end
end