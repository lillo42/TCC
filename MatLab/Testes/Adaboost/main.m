 function main()
    clear all;
    
    pathName = 'C:\Users\Rafel\Documents\GitHub\TCC\Database\Pessoa\';
    extensao = '*.pgm';
    
%     files = dir(strcat(pathName,extensao));
%     Pessoa = [];
%     for n = 1 : 5 %length(files)
%         filename = files(n).name;
%         file = imread(strcat(pathName,filename));
 
%         Pessoa = [Pessoa, imhist(file)]; %#ok
%     end
    %       I=imread('rice.png');
%       mapping=getmapping(8,'u2'); 
%       H1=LBP(I,1,8,mapping,'h'); %LBP histogram in (8,1) neighborhood
%                                  %using uniform patterns
%       subplot(2,1,1),stem(H1);
%
%       H2=LBP(I);
%       subplot(2,1,2),stem(H2);
%
%       SP=[-1 -1; -1 0; -1 1; 0 -1; -0 1; 1 -1; 1 0; 1 1];
%       I2=LBP(I,SP,0,'i'); %LBP code image using sampling points in SP
%                           %and no mapping. Now H2 is equal to histogram
%                           %of I2.


%     pathName = 'C:\Users\Rafel\Documents\GitHub\TCC\Database\NPessoa\';
%     extensao = '*.jpg';
%     files = dir(strcat(pathName,extensao));
%     NPessoa =[];
%     
%     for n = 1 : 1 % length(files)
%         filename = files(n).name;
%         file = imread(strcat(pathName,filename));
%         
%         t = imhist(file);
% 
%         NPessoa = [NPessoa, imhist(file)]; %#ok
%     end
    
%     datafeatures=[Pessoa;NPessoa];
%     dataclass(1:257)=1; dataclass(258:512)=-1;
%     
%     [classestimate,model]=adaboost('train',datafeatures,dataclass,50);
%     
%     Pessoa=datafeatures(classestimate==1,:);
%     NPessoa=datafeatures(classestimate==-1,:); 
    
%     I=zeros(161,161);
%     for i=1:length(model)
%         
%       if(model(i).dimension==1)
%           if(model(i).direction==1)
%               rec=[-80 -80 80+model(i).threshold 160];
%           else
%               rec=[model(i).threshold -80 80-model(i).threshold 160 ];
%           end
%       else
%           if(model(i).direction==1)
%               rec=[-80 -80 160 80+model(i).threshold];
%           else
%               rec=[-80 model(i).threshold 160 80-model(i).threshold];
%           end
%       end
%       
%       rec=round(rec);
%       
%       y=rec(1)+81:rec(1)+81+rec(3); x=rec(2)+81:rec(2)+81+rec(4);
%       
%       I=I-model(i).alpha; I(x,y)=I(x,y)+2*model(i).alpha;    
%     end
%     
%     % Make some test data
%     pathName = 'C:\Users\Rafel\Documents\GitHub\TCC\Database\Teste\';
%     extensao = '*.jpg';
%     files = dir(strcat(pathName,extensao));
%     testdata = [];
%     for n = 1 : 1%length(files)
%         filename = files(n).name;
%         file = imread(strcat(pathName,filename));
% 
%         testdata = [testdata, imhist(file)]; %#ok
%     end
% 
%     % Classify the testdata with the trained model
%     testclass=adaboost('apply',testdata,model);
% 
%     % Show result
%     NPessoa=testdata(testclass==-1,:); Pessoa=testdata(testclass==1,:);
end

%% Adaboost
function [estimateclasstotal,model]=adaboost(mode,datafeatures,dataclass_or_model,itt)
    % This function AdaBoost, consist of two parts a simpel weak classifier and
    % a boosting part:
    % The weak classifier tries to find the best treshold in one of the data
    % dimensions to sepparate the data into two classes -1 and 1
    % The boosting part calls the clasifier iteratively, after every classification
    % step it changes the weights of miss-classified examples. This creates a
    % cascade of "weak classifiers" which behaves like a "strong classifier"
    %
    %  Training mode:
    %    [estimateclass,model]=adaboost('train',datafeatures,dataclass,itt)
    %  Apply mode:
    %    estimateclass=adaboost('apply',datafeatures,model)
    % 
    %  inputs/outputs:
    %    datafeatures : An Array with size number_samples x number_features
    %    dataclass : An array with the class off all examples, the class
    %                 can be -1 or 1
    %    itt : The number of training itterations
    %    model : A struct with the cascade of weak-classifiers
    %    estimateclass : The by the adaboost model classified data
    %               
    %  %% Example
    %
    %  example.m
    %
    %  Function is written by D.Kroon University of Twente (August 2010)

    switch(mode)
        case 'train'
            % Train the adaboost model

            % Set the data class 
            dataclass=dataclass_or_model(:);
            model=struct;

            % Weight of training samples, first every sample is even important
            % (same weight)
            D=ones(length(dataclass),1)/length(dataclass);

            % This variable will contain the results of the single weak
            % classifiers weight by their alpha
            estimateclasssum=zeros(size(dataclass));

            % Calculate max min of the data
            boundary=[min(datafeatures,[],1) max(datafeatures,[],1)];
            % Do all model training itterations
            for t=1:itt
                % Find the best treshold to separate the data in two classes
                [estimateclass,err,h] = WeightedThresholdClassifier(datafeatures,dataclass,D);

                % Weak classifier influence on total result is based on the current
                % classification error
                alpha=1/2 * log((1-err)/max(err,eps));

                % Store the model parameters
                model(t).alpha = alpha;
                model(t).dimension=h.dimension;
                model(t).threshold=h.threshold;
                model(t).direction=h.direction;
                model(t).boundary = boundary;
                % We update D so that wrongly classified samples will have more weight
                D = D.* exp(-model(t).alpha.*dataclass.*estimateclass);
                D = D./sum(D);

                % Calculate the current error of the cascade of weak
                % classifiers
                estimateclasssum=estimateclasssum +estimateclass*model(t).alpha;
                estimateclasstotal=sign(estimateclasssum);
                model(t).error=sum(estimateclasstotal~=dataclass)/length(dataclass);
                if(model(t).error==0), break; end
            end

        case 'apply' 
            % Apply Model on the test data
            model=dataclass_or_model;

            % Limit datafeatures to orgininal boundaries
            if(length(model)>1);
                minb=model(1).boundary(1:end/2);
                maxb=model(1).boundary(end/2+1:end);
                datafeatures=bsxfun(@min,datafeatures,maxb);
                datafeatures=bsxfun(@max,datafeatures,minb);
            end

            % Add all results of the single weak classifiers weighted by their alpha 
            estimateclasssum=zeros(size(datafeatures,1),1);
            for t=1:length(model);
                estimateclasssum=estimateclasssum+model(t).alpha*ApplyClassTreshold(model(t), datafeatures);
            end
            % If the total sum of all weak classifiers
            % is less than zero it is probablly class -1 otherwise class 1;
            estimateclasstotal=sign(estimateclasssum);

        otherwise
            error('adaboost:inputs','unknown mode');
    end
end

function [estimateclass,err,h] = WeightedThresholdClassifier(datafeatures,dataclass,dataweight)
    % This is an example of an "Weak Classifier", it caculates the optimal
    % threshold for all data feature dimensions.
    % It then selects the dimension and  treshold which divides the 
    % data into two class with the smallest error.

    % Number of treshold steps
    ntre=2e5;

    % Split the data in two classes 1 and -1
    r1=datafeatures(dataclass<0,:); w1=dataweight(dataclass<0);
    r2=datafeatures(dataclass>0,:); w2=dataweight(dataclass>0);

    % Calculate the min and max for every dimensions
    minr=min(datafeatures,[],1)-1e-10; maxr=max(datafeatures,[],1)+1e-10;

    % Make a weighted histogram of the two classes
    p2c= ceil((bsxfun(@rdivide,bsxfun(@minus,r2,minr),(maxr-minr)))*(ntre-1)+1+1e-9);   p2c(p2c>ntre)=ntre;
    p1f=floor((bsxfun(@rdivide,bsxfun(@minus,r1,minr),(maxr-minr)))*(ntre-1)+1-1e-9);  p1f(p1f<1)=1;
    ndims=size(datafeatures,2);
    i1=repmat(1:ndims,size(p1f,1),1);  i2=repmat(1:ndims,size(p2c,1),1);
    h1f=accumarray([p1f(:) i1(:)],repmat(w1(:),ndims,1),[ntre ndims],[],0);
    h2c=accumarray([p2c(:) i2(:)],repmat(w2(:),ndims,1),[ntre ndims],[],0);

    % This function calculates the error for every all possible treshold value
    % and dimension
    h2ic=cumsum(h2c,1);
    h1rf=cumsum(h1f(end:-1:1,:),1); h1rf=h1rf(end:-1:1,:);
    e1a=h1rf+h2ic;
    e2a=sum(dataweight)-e1a;

    % We want the treshold value and dimension with the minimum error
    [err1a,ind1a]=min(e1a,[],1);  dim1a=(1:ndims); dir1a=ones(1,ndims);
    [err2a,ind2a]=min(e2a,[],1);  dim2a=(1:ndims); dir2a=-ones(1,ndims);
    A=[err1a(:),dim1a(:),dir1a(:),ind1a(:);err2a(:),dim2a(:),dir2a(:),ind2a(:)];
    [err,i]=min(A(:,1)); dim=A(i,2); dir=A(i,3); ind=A(i,4);
    thresholds = linspace(minr(dim),maxr(dim),ntre);
    thr=thresholds(ind);

    % Apply the new treshold
    h.dimension = dim; 
    h.threshold = thr; 
    h.direction = dir;
    estimateclass=ApplyClassTreshold(h,datafeatures);
end

function y = ApplyClassTreshold(h, x)
    % Draw a line in one dimension (like horizontal or vertical)
    % and classify everything below the line to one of the 2 classes
    % and everything above the line to the other class.
    if(h.direction == 1)
        y =  double(x(:,h.dimension) >= h.threshold);
    else
        y =  double(x(:,h.dimension) < h.threshold);
    end
    y(y==0) = -1;
end

%% LBP
%LBP returns the local binary pattern image or LBP histogram of an image.
%  J = LBP(I,R,N,MAPPING,MODE) returns either a local binary pattern
%  coded image or the local binary pattern histogram of an intensity
%  image I. The LBP codes are computed using N sampling points on a 
%  circle of radius R and using mapping table defined by MAPPING. 
%  See the getmapping function for different mappings and use 0 for
%  no mapping. Possible values for MODE are
%       'h' or 'hist'  to get a histogram of LBP codes
%       'nh'           to get a normalized histogram
%  Otherwise an LBP code image is returned.
%
%  J = LBP(I) returns the original (basic) LBP histogram of image I
%
%  J = LBP(I,SP,MAPPING,MODE) computes the LBP codes using n sampling
%  points defined in (n * 2) matrix SP. The sampling points should be
%  defined around the origin (coordinates (0,0)).
%
%  Examples
%  --------
%       I=imread('rice.png');
%       mapping=getmapping(8,'u2'); 
%       H1=LBP(I,1,8,mapping,'h'); %LBP histogram in (8,1) neighborhood
%                                  %using uniform patterns
%       subplot(2,1,1),stem(H1);
%
%       H2=LBP(I);
%       subplot(2,1,2),stem(H2);
%
%       SP=[-1 -1; -1 0; -1 1; 0 -1; -0 1; 1 -1; 1 0; 1 1];
%       I2=LBP(I,SP,0,'i'); %LBP code image using sampling points in SP
%                           %and no mapping. Now H2 is equal to histogram
%                           %of I2.

function result = lbp(varargin) % image,radius,neighbors,mapping,mode)
    % Version 0.3.3
    % Authors: Marko Heikkil?and Timo Ahonen

    % Changelog
    % Version 0.3.2: A bug fix to enable using mappings together with a
    % predefined spoints array
    % Version 0.3.1: Changed MAPPING input to be a struct containing the mapping
    % table and the number of bins to make the function run faster with high number
    % of sampling points. Lauge Sorensen is acknowledged for spotting this problem.


    % Check number of input arguments.
    error(nargchk(1,5,nargin));

    image=varargin{1};
    d_image=double(image);

    if nargin==1
        spoints=[-1 -1; -1 0; -1 1; 0 -1; -0 1; 1 -1; 1 0; 1 1];
        neighbors=8;
        mapping=0;
        mode='h';
    end

    if (nargin == 2) && (length(varargin{2}) == 1)
        error('Input arguments');
    end

    if (nargin > 2) && (length(varargin{2}) == 1)
        radius=varargin{2};
        neighbors=varargin{3};

        spoints=zeros(neighbors,2);

        % Angle step.
        a = 2*pi/neighbors;

        for i = 1:neighbors
            spoints(i,1) = -radius*sin((i-1)*a);
            spoints(i,2) = radius*cos((i-1)*a);
        end

        if(nargin >= 4)
            mapping=varargin{4};
            if(isstruct(mapping) && mapping.samples ~= neighbors)
                error('Incompatible mapping');
            end
        else
            mapping=0;
        end

        if(nargin >= 5)
            mode=varargin{5};
        else
            mode='h';
        end
    end

    if (nargin > 1) && (length(varargin{2}) > 1)
        spoints=varargin{2};
        neighbors=size(spoints,1);

        if(nargin >= 3)
            mapping=varargin{3};
            if(isstruct(mapping) && mapping.samples ~= neighbors)
                error('Incompatible mapping');
            end
        else
            mapping=0;
        end

        if(nargin >= 4)
            mode=varargin{4};
        else
            mode='h';
        end   
    end

    % Determine the dimensions of the input image.
    [ysize xsize] = size(image);



    miny=min(spoints(:,1));
    maxy=max(spoints(:,1));
    minx=min(spoints(:,2));
    maxx=max(spoints(:,2));

    % Block size, each LBP code is computed within a block of size bsizey*bsizex
    bsizey=ceil(max(maxy,0))-floor(min(miny,0))+1;
    bsizex=ceil(max(maxx,0))-floor(min(minx,0))+1;

    % Coordinates of origin (0,0) in the block
    origy=1-floor(min(miny,0));
    origx=1-floor(min(minx,0));

    % Minimum allowed size for the input image depends
    % on the radius of the used LBP operator.
    if(xsize < bsizex || ysize < bsizey)
      error('Too small input image. Should be at least (2*radius+1) x (2*radius+1)');
    end

    % Calculate dx and dy;
    dx = xsize - bsizex;
    dy = ysize - bsizey;

    % Fill the center pixel matrix C.
    C = image(origy:origy+dy,origx:origx+dx);
    d_C = double(C);

    bins = 2^neighbors;

    % Initialize the result matrix with zeros.
    result=zeros(dy+1,dx+1);

    %Compute the LBP code image

    for i = 1:neighbors
      y = spoints(i,1)+origy;
      x = spoints(i,2)+origx;
      % Calculate floors, ceils and rounds for the x and y.
      fy = floor(y); cy = ceil(y); ry = round(y);
      fx = floor(x); cx = ceil(x); rx = round(x);
      % Check if interpolation is needed.
      if (abs(x - rx) < 1e-6) && (abs(y - ry) < 1e-6)
        % Interpolation is not needed, use original datatypes
        N = image(ry:ry+dy,rx:rx+dx);
        D = N >= C; 
      else
        % Interpolation needed, use double type images 
        ty = y - fy;
        tx = x - fx;

        % Calculate the interpolation weights.
        w1 = roundn((1 - tx) * (1 - ty),-6);
        w2 = roundn(tx * (1 - ty),-6);
        w3 = roundn((1 - tx) * ty,-6) ;
        % w4 = roundn(tx * ty,-6) ;
        w4 = roundn(1 - w1 - w2 - w3, -6);

        % Compute interpolated pixel values
        N = w1*d_image(fy:fy+dy,fx:fx+dx) + w2*d_image(fy:fy+dy,cx:cx+dx) + ...
    w3*d_image(cy:cy+dy,fx:fx+dx) + w4*d_image(cy:cy+dy,cx:cx+dx);
        N = roundn(N,-4);
        D = N >= d_C; 
      end  
      % Update the result matrix.
      v = 2^(i-1);
      result = result + v*D;
    end

    %Apply mapping if it is defined
    if isstruct(mapping)
        bins = mapping.num;
        for i = 1:size(result,1)
            for j = 1:size(result,2)
                result(i,j) = mapping.table(result(i,j)+1);
            end
        end
    end

    if (strcmp(mode,'h') || strcmp(mode,'hist') || strcmp(mode,'nh'))
        % Return with LBP histogram if mode equals 'hist'.
        result=hist(result(:),0:(bins-1));
        if (strcmp(mode,'nh'))
            result=result/sum(result);
        end
    else
        %Otherwise return a matrix of unsigned integers
        if ((bins-1)<=intmax('uint8'))
            result=uint8(result);
        elseif ((bins-1)<=intmax('uint16'))
            result=uint16(result);
        else
            result=uint32(result);
        end
    end

end

function x = roundn(x, n)
    error(nargchk(2, 2, nargin, 'struct'))
    validateattributes(x, {'single', 'double'}, {}, 'ROUNDN', 'X')
    validateattributes(n, ...
        {'numeric'}, {'scalar', 'real', 'integer'}, 'ROUNDN', 'N')

    if n < 0
        p = 10 ^ -n;
        x = round(p * x) / p;
    elseif n > 0
        p = 10 ^ n;
        x = p * round(x / p);
    else
        x = round(x);
    end
end

%%Get mapping
%GETMAPPING returns a structure containing a mapping table for LBP codes.
%  MAPPING = GETMAPPING(SAMPLES,MAPPINGTYPE) returns a
%  structure containing a mapping table for
%  LBP codes in a neighbourhood of SAMPLES sampling
%  points. Possible values for MAPPINGTYPE are
%       'u2'   for uniform LBP
%       'ri'   for rotation-invariant LBP
%       'riu2' for uniform rotation-invariant LBP.
%
%  Example:
%       I=imread('rice.tif');
%       MAPPING=getmapping(16,'riu2');
%       LBPHIST=lbp(I,2,16,MAPPING,'hist');
%  Now LBPHIST contains a rotation-invariant uniform LBP
%  histogram in a (16,2) neighbourhood.
%

function mapping = getmapping(samples,mappingtype)
    % Version 0.2
    % Authors: Marko Heikkil?, Timo Ahonen and Xiaopeng Hong

    % Changelog
    % 0.1.1 Changed output to be a structure
    % Fixed a bug causing out of memory errors when generating rotation
    % invariant mappings with high number of sampling points.
    % Lauge Sorensen is acknowledged for spotting this problem.

    % Modified by Xiaopeng HONG and Guoying ZHAO
    % Changelog
    % 0.2
    % Solved the compatible issue for the bitshift function in Matlab
    % 2012 & higher

    matlab_ver = ver('MATLAB');
    matlab_ver = str2double(matlab_ver.Version);

    if matlab_ver < 8
        mapping = getmapping_ver7(samples,mappingtype);
    else
        mapping = getmapping_ver8(samples,mappingtype);
    end
end

function mapping = getmapping_ver7(samples,mappingtype)

    disp('For Matlab version 7.x and lower');

    table = 0:2^samples-1;
    newMax  = 0; %number of patterns in the resulting LBP code
    index   = 0;

    if strcmp(mappingtype,'u2') %Uniform 2
        newMax = samples*(samples-1) + 3;
        for i = 0:2^samples-1
            j = bitset(bitshift(i,1,samples),1,bitget(i,samples)); %rotate left
            numt = sum(bitget(bitxor(i,j),1:samples));  %number of 1->0 and
                                                        %0->1 transitions
                                                        %in binary string
                                                        %x is equal to the
                                                        %number of 1-bits in
                                                        %XOR(x,Rotate left(x))
            if numt <= 2
                table(i+1) = index;
                index = index + 1;
            else
                table(i+1) = newMax - 1;
            end
        end
    end

    if strcmp(mappingtype,'ri') %Rotation invariant
        tmpMap = zeros(2^samples,1) - 1;
        for i = 0:2^samples-1
            rm = i;
            r  = i;

            for j = 1:samples-1
                r = bitset(bitshift(r,1,samples),1,bitget(r,samples)); %rotate
                %left
                if r < rm
                    rm = r;
                end
            end
            if tmpMap(rm+1) < 0
                tmpMap(rm+1) = newMax;
                newMax = newMax + 1;
            end
            table(i+1) = tmpMap(rm+1);
        end
    end

    if strcmp(mappingtype,'riu2') %Uniform & Rotation invariant
        newMax = samples + 2;
        for i = 0:2^samples - 1
            j = bitset(bitshift(i,1,samples),1,bitget(i,samples)); %rotate left
            numt = sum(bitget(bitxor(i,j),1:samples));
            if numt <= 2
                table(i+1) = sum(bitget(i,1:samples));
            else
                table(i+1) = samples+1;
            end
        end
    end

    mapping.table=table;
    mapping.samples=samples;
    mapping.num=newMax;
end

function mapping = getmapping_ver8(samples,mappingtype)

    disp('For Matlab version 8.0 and higher');

    table = 0:2^samples-1;
    newMax  = 0; %number of patterns in the resulting LBP code
    index   = 0;

    if strcmp(mappingtype,'u2') %Uniform 2
        newMax = samples*(samples-1) + 3;
        for i = 0:2^samples-1

            i_bin = dec2bin(i,samples);
            j_bin = circshift(i_bin',-1)';              %circularly rotate left
            numt = sum(i_bin~=j_bin);                   %number of 1->0 and
                                                        %0->1 transitions
                                                        %in binary string
                                                        %x is equal to the
                                                        %number of 1-bits in
                                                        %XOR(x,Rotate left(x))

            if numt <= 2
                table(i+1) = index;
                index = index + 1;
            else
                table(i+1) = newMax - 1;
            end
        end
    end

    if strcmp(mappingtype,'ri') %Rotation invariant
        tmpMap = zeros(2^samples,1) - 1;
        for i = 0:2^samples-1
            rm = i;

            r_bin = dec2bin(i,samples);

            for j = 1:samples-1

                r = bin2dec(circshift(r_bin',-1*j)'); %rotate left    
                if r < rm
                    rm = r;
                end
            end
            if tmpMap(rm+1) < 0
                tmpMap(rm+1) = newMax;
                newMax = newMax + 1;
            end
            table(i+1) = tmpMap(rm+1);
        end
    end

    if strcmp(mappingtype,'riu2') %Uniform & Rotation invariant
        newMax = samples + 2;
        for i = 0:2^samples - 1

            i_bin =  dec2bin(i,samples);
            j_bin = circshift(i_bin',-1)';
            numt = sum(i_bin~=j_bin);

            if numt <= 2
                table(i+1) = sum(bitget(i,1:samples));
            else
                table(i+1) = samples+1;
            end
        end
    end

    mapping.table=table;
    mapping.samples=samples;
    mapping.num=newMax;
end
