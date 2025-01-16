I = imread('../imgs/cameraman.tif');
background = imopen(I, strel('disk', 15));
I2 = imsubtract(I, background);
Ip = imdivide(I, I2);
figure, imshow(Ip, []);