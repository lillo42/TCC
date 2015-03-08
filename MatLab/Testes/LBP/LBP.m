    function [ LBP ] = LBP(I2)
        m=size(I2,1);
        n=size(I2,2);
        for i=2:m-1
            for j=2:n-1
                J0=I2(i,j);
                I3(i-1,j-1) = I2(i-1,j-1) >J0;
                I3(i-1,j) = I2(i-1,j) > J0;
                I3(i-1,j+1) = I2(i-1,j+1)> J0; 
                I3(i,j+1) = I2(i,j+1)> J0;
                I3(i+1,j+1)= I2(i+1,j+1) > J0; 
                I3(i+1,j)= I2(i+1,j) > J0; 
                I3(i+1,j-1)= I2(i+1,j-1)> J0; 
                I3(i,j-1)= I2(i,j-1)> J0;
                LBP(i,j)= I3(i-1,j-1)*2^7+I3(i-1,j)*2^6+I3(i-1,j+1)*2^5+I3(i,j+1)*2^4+I3(i+1,j+1)*2^3+I3(i+1,j)*2^2+I3(i+1,j-1)*2^1+I3(i,j-1)*2^0;
            end
        end
    end

    %% 
    function [lbp] = LbpGpu(I2)
        m=size(I2,1);
        n=size(I2,2);

        IG = gpuArray(I2);


    end

    
    %%LBP
% for p=3:size(listaImage)
%     image = imread(strcat(pathImageName,'\',listaImage(p,1).name));
%     m=size(image,1);
%     n=size(image,2);
%     display(strcat('Image ', p))
%     for i=2:m-1
%         for j=2:n-1
%             J0=image(i,j);
%             I3(i-1,j-1) = image(i-1,j-1) >J0;
%             I3(i-1,j) = image(i-1,j) > J0;
%             I3(i-1,j+1) = image(i-1,j+1)> J0; 
%             I3(i,j+1) = image(i,j+1)> J0;
%             I3(i+1,j+1)= image(i+1,j+1) > J0; 
%             I3(i+1,j)= image(i+1,j) > J0; 
%             I3(i+1,j-1)= image(i+1,j-1)> J0; 
%             I3(i,j-1)= image(i,j-1)> J0;
%             LBP(i,j)= I3(i-1,j-1)*2^7+I3(i-1,j)*2^6+I3(i-1,j+1)*2^5+I3(i,j+1)*2^4+I3(i+1,j+1)*2^3+I3(i+1,j)*2^2+I3(i+1,j-1)*2^1+I3(i,j-1)*2^0;
%         end
%     end
%     listaImageProcess{p-2,1} = LBP;
% end