% 读取并显示原始图像
f = imread('../imgs/room.tif');
f_gray = im2gray(f);  % 转换为灰度图

sigma = 1;
[edges, threshold] = edge(f_gray, 'log', [], sigma);

figure;
imshow(edges);
title(['LoG 边缘检测结果（sigma = ', num2str(sigma), '）']);

hsize = 2 * ceil(3 * sigma) + 1; % 滤波器的尺寸：根据 sigma 动态设置
LoG_filter = fspecial('log', hsize, sigma); % 使用 fspecial 创建 LoG 滤波器
LoG_response = imfilter(double(f_gray), LoG_filter, 'replicate'); % 对灰度图像应用 LoG 滤波器


% 绘制 LoG 滤波器响应的直方图以确定阈值
G_abs = abs(LoG_response);
figure;
histogram(G_abs(:), 256);
title('LoG 响应绝对值直方图');
xlabel('绝对值');
ylabel('像素数');

T = input('请输入二值化的阈值：');
BW = LoG_response > T;
BW_inverted = ~BW;

figure;
imshow(BW_inverted);
title(['二值化结果（阈值 = ', num2str(T), '，sigma = ', num2str(sigma), '）']);