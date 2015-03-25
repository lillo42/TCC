%I=imread("/path/to/image.jpg");
	%%	G=rgb2gray(I);
	%%	L=lbp(G)
    
    I = imread('C:\Users\Rafel\Documents\GitHub\TCC\Database\Pessoa\s010.pgm');
    L = lbp(I,1,8);
    imshow(uint8(L));