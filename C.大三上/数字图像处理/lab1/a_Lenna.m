img_lenna = imread('../imgs/Lenna.jpg');
img_cameraman = imread('../imgs/cameraman.tif');

info_lenna = imfinfo('../imgs/Lenna.jpg');
info_cameraman = imfinfo('../imgs/cameraman.tif');
disp(info_lenna);
disp(info_cameraman);

figure;

subplot(1, 2, 1);
imshow(img_lenna);
title('Lenna.jpg');
text(10, 10, sprintf('Size: %dx%d', info_lenna.Width, info_lenna.Height), 'Color', 'white', 'FontSize', 12);

subplot(1, 2, 2);
imshow(img_cameraman);
title('Cameraman.tif');
text(10, 10, sprintf('Size: %dx%d', info_cameraman.Width, info_cameraman.Height), 'Color', 'white', 'FontSize', 12);


bw_img = im2bw(img_cameraman, 0.5);
info_cameraman = imfinfo('cameraman.tif');
figure;
imshow(bw_img);
title('Binary Image of Cameraman');
text(10, 10, sprintf('Size: %dx%d', info_cameraman.Width, info_cameraman.Height), 'Color', 'white', 'FontSize', 12);


