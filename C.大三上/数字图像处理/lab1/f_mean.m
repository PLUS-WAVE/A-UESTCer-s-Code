I = imread('../imgs/im1.tif');
I2 = imread('../imgs/im2.tif');
K = imdivide(imadd(I, I2), 2);
K = K(:, :, 1:3);
figure;
imshow(K)

figure;
Z = imlincomb(0.3,I,0.7,I2,0);
Z = Z(:, :, 1:3);
imshow(Z)