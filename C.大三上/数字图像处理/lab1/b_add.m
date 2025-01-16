I = imread('../imgs/im1.tif');
J = imread('../imgs/im2.tif');
if size(I, 3) == 4
    I = I(:, :, 1:3);
end
if size(J, 3) == 4
    J = J(:, :, 1:3);
end

K = imadd(I, J);
figure;
subplot(1, 3, 1), imshow(I), title('图1')
subplot(1, 3, 2), imshow(J), title('图2')
subplot(1, 3, 3), imshow(K), title('叠加后');

RGB = imread('cameraman.tif');
RGB2 = imadd(RGB, 50);  % 增加亮度
RGB3 = imadd(RGB, -50); % 减少亮度
figure;
subplot(1, 3, 1), imshow(RGB);
subplot(1, 3, 2), imshow(RGB2);
subplot(1, 3, 3), imshow(RGB3);