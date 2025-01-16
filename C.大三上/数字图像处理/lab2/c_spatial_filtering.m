%% 高斯
Im = imread('../imgs/electric.tif');
if size(Im, 3) == 3
    I = rgb2gray(Im);
else
    I = Im;
end

J = imnoise(I, 'gauss', 0.02);
% J = imnoise(I, 'salt & pepper', 0.02);

ave1 = fspecial('average', 3);
ave2 = fspecial('average', 5);

K = filter2(ave1, J) / 255;
L = filter2(ave2, J) / 255;

M = medfilt2(J, [3 3]);
N = medfilt2(J, [5 5]);

figure;
subplot(2, 3, 1), imshow(I), title('原图');
subplot(2, 3, 2), imshow(J), title('高斯噪声');
subplot(2, 3, 3), imshow(K), title('均值滤波(3x3)');
subplot(2, 3, 4), imshow(L), title('均值滤波(5x5)');
subplot(2, 3, 5), imshow(M), title('中值滤波(3x3)');
subplot(2, 3, 6), imshow(N), title('中值滤波(5x5)');


%% 椒盐
Im = imread('../imgs/electric.tif');
if size(Im, 3) == 3
    I = rgb2gray(Im);
else
    I = Im;
end

% J = imnoise(I, 'gauss', 0.02);
J = imnoise(I, 'salt & pepper', 0.02);

ave1 = fspecial('average', 3);
ave2 = fspecial('average', 5);

K = filter2(ave1, J) / 255;
L = filter2(ave2, J) / 255;

M = medfilt2(J, [3 3]);
N = medfilt2(J, [5 5]);

figure;
subplot(2, 3, 1), imshow(I), title('原图');
subplot(2, 3, 2), imshow(J), title('椒盐噪声');
subplot(2, 3, 3), imshow(K), title('均值滤波(3x3)');
subplot(2, 3, 4), imshow(L), title('均值滤波(5x5)');
subplot(2, 3, 5), imshow(M), title('中值滤波(3x3)');
subplot(2, 3, 6), imshow(N), title('中值滤波(5x5)');

