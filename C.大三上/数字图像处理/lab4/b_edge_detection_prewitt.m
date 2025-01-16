% 读取并显示原始图像
f = imread('../imgs/room.tif');
f_gray = im2gray(f);  % 转换为灰度图

% 使用 Roberts 算子进行边缘检测
[gv, t1] = edge(f_gray, 'prewitt', 'vertical');
[gh, t2] = edge(f_gray, 'prewitt', 'horizontal');

% 显示水平和垂直边缘检测结果
figure;
subplot(1,2,1);
imshow(gh);
title('水平边缘检测结果');
subplot(1,2,2);
imshow(gv);
title('垂直边缘检测结果');

% 欧几里德距离
G_euclidean = sqrt(double(gh).^2 + double(gv).^2);
% 街区距离
G_cityblock = abs(double(gh)) + abs(double(gv));

% 显示梯度模结果
figure;

subplot(1,2,1);
imshow(G_euclidean, []);
title('梯度模（欧几里德距离）');
subplot(1,2,2);
imshow(G_cityblock, []);
title('梯度模（街区距离）');

% 绘制梯度模的直方图以确定阈值
figure;
histogram(G_euclidean);
title('梯度模的直方图（欧几里德距离）');
xlabel('灰度值');
ylabel('像素数');

% 根据直方图选择阈值进行二值化处理
T = input('请输入二值化的阈值（根据直方图选择合适的值）：');
BW = G_euclidean > T;

% 将结果转换为白底黑线条
BW_inverted = ~BW;

% 显示二值化处理结果
figure;
imshow(BW_inverted);
title(['二值化结果（阈值 = ', num2str(T), '）']);