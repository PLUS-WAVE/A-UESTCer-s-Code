I = imread('../imgs/pollen.jpg');
J = histeq(I);

figure;
subplot(1,2,1), imshow(I), title('原图像');
subplot(1,2,2), imshow(J), title('均衡化后的图像');

figure;
subplot(1,2,1), imhist(I, 64), title('原图像直方图');
subplot(1,2,2), imhist(J, 64), title('均衡化后的直方图');
