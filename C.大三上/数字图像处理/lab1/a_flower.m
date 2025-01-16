img = imread('../imgs/flower.tif');
whos img;
imshow(img);
info = imfinfo('../imgs/flower.tif');
disp(info);
imwrite(img, 'outputs/flower_compressed.jpg', 'Quality', 50);
imwrite(img, 'outputs/flower.bmp');
