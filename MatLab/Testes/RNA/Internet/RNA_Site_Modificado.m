function scan(img)
    pathName = 'C:\Users\Rafel\Documents\MatLab\Imagens\';
    extensao = '*.pgm';
    files = dir(strcat(pathName,extensao));
    hist = [];
    for n = 1 : length(files)
        filename = files(n).name;
        file = imread(strcat(pathName,filename));

        hist = [hist, file]; %#ok
    end

    som = selforgmap([10 10]);
    som = train(som, hist);
    t   = som(hist); %extract class data

    net = lvqnet(10);
    net = train(net, hist, t);

    like(img, hist, files, net)
end

function like(im, hist, files , net)
    hs = imhist(rgb2gray(imresize(im,[50 50])));
    cls = vec2ind(net(hs));
 
    [~, n] = size(hist);
    for i = 1 : n
        if(cls == vec2ind(net(hist(:, i))))
            figure('name', files(i).name);
            imshow(imresize(imread(files(i).name), [100 100]))
        end
    end
end