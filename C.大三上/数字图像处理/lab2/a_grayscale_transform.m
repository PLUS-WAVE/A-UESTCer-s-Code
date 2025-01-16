f = imread('../imgs/medicine_pic.jpg');
imhist(f, 256);
g1 = imadjust(f, [0 1], [1 0]);
figure;
subplot(1,2,1), imshow(g1), title('明暗转换');

g2 = imadjust(f, [0.5 0.75], [0 1]);
subplot(1,2,2), imshow(g2), title('灰度级扩展');

g = imread('../imgs/point.jpg');
h = log(1 + double(g));
h = mat2gray(h);
h = im2uint8(h);
figure, imshow(h);