I = imread('../imgs/room.tif');
if size(I, 3) == 3
    I = rgb2gray(I);
end
J = immultiply(I, 1.5);
figure;
subplot(1, 2, 1), imshow(I);
subplot(1, 2, 2), imshow(J);