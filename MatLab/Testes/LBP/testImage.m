I = imread('C:\Users\Rafel\Documents\MatLab\Imagens\s010.pgm');
figure;

lbp = LBP(I);

imshow(lbp);
title('tes')


pathName = 'C:\Users\Rafel\Documents\MatLab\Imagens'
listImage = dir(pathName);

for p=3:size(listImage)
    image = imread(strcat(pathName,'\',listImage(p,1).name));
    imageLBP = LBP(image);
end