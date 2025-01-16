x = imread('../imgs/Lenna.tif');
x = rgb2gray(x);  % 彩图转化为灰度图
figure(1);
subplot(121);
imshow(x);
title('原图')

quality=10;
y = jpegencode(x, quality);  % 进行近似JPEG编码
X = jpegdecode(y);  % 进行解码

subplot(122);
imshow(X);
title('jpeg压缩后')

e = double(x) - double(X);
[m, n] = size(e);
erms = sqrt(sum(e(:).^2) / (m * n));  % 计算均方根误差
cr = imageratio(x, y);  % 计算压缩比
fprintf('quality: %f\n', quality);
fprintf('均方根误差: %f\n', erms);
fprintf('压缩比: %f\n', cr);
