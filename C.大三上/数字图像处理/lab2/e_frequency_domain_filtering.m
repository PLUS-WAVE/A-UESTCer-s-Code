%% 傅里叶变换和频谱显示
f = imread('../imgs/pollen.jpg');
if size(f, 3) == 3
    f = rgb2gray(f);
end
imshow(f);

F = fft2(f);  % 进行二维傅里叶变换
S = fftshift(log(1 + abs(F)));  % 中心化频谱
S = gscale(S);  % 标准化频谱以显示
figure, imshow(S), title('图片频谱图像');

%% 低通滤波
h = fspecial('sobel');  % 生成空间Sobel算子
figure, freqz2(h), title('频域滤波器图像');  % 显示滤波器的频谱响应

PQ = paddedsize(size(f));  % 调整滤波器大小以适应图像
H = freqz2(h, PQ(1), PQ(2));  % 生成频域中的Sobel滤波器
H1 = ifftshift(H);  % 将原点移动到频谱矩阵左上角

figure;
subplot(1, 2, 1), imshow(abs(H), []), title('Sobel滤波器频域图形');
subplot(1, 2, 2), imshow(abs(H1), []), title('重排列后的Sobel滤波器频域图形');

% 空域滤波
gs = imfilter(double(f), h);  % 使用Sobel滤波器进行空间滤波
% 频域滤波
gf = dftfilt(f, H1);  % 使用频域滤波器

figure;
subplot(2, 2, 1), imshow(gs, []), title('空域滤波');
subplot(2, 2, 2), imshow(gf, []), title('频域滤波');
subplot(2, 2, 3), imshow(abs(gs), []), title('空域滤波(绝对值)');
subplot(2, 2, 4), imshow(abs(gf), []), title('频域滤波(绝对值)');


%% 高通滤波
f = imread('../imgs/number.tif');
if size(f, 3) == 3
    f = rgb2gray(f);
end

PQ = paddedsize(size(f));  % 调整滤波器大小
D0 = 0.05 * PQ(1);  % 设置高斯高通滤波器的截止频率
H = hpfilter('gaussian', PQ(1), PQ(2), D0);  % 生成高斯高通滤波器

g = dftfilt(f, H);  % 进行高通滤波处理

figure;
subplot(1, 2, 1), imshow(f), title('原图像');
subplot(1, 2, 2), imshow(g, []), title('高斯高通滤波后');

%% 图像复原消除条纹噪声
f = imread('../imgs/clown.tif');
if size(f, 3) == 3
    f = rgb2gray(f);
end
f = double(f);

F = fft2(f);
F_shifted = fftshift(F);

% 显示原始频谱
S = log(1 + abs(F_shifted));
figure('Name', '频域滤波分析');
subplot(2,2,1);
imshow(S, []);
title('原始频谱');

% 分析整个频谱
[M, N] = size(f);
P = abs(F_shifted);

% 设置中心区域掩码
center_v = floor(M/2) + 1;
center_u = floor(N/2) + 1;
window_v = round(M * 0.05);
window_u = round(N * 0.05);
P(center_v-window_v:center_v+window_v, center_u-window_u:center_u+window_u) = 0;

% 找出显著峰值
threshold = mean(P(:)) + 12*std(P(:));
[peak_rows, peak_cols] = find(P > threshold);

% 筛选局部最大值
peaks = [];
locs_v = [];
locs_u = [];
min_dist = 5;

for i = 1:length(peak_rows)
    row = peak_rows(i);
    col = peak_cols(i);
    % 获取局部窗口
    row_start = max(1, row-min_dist);
    row_end = min(M, row+min_dist);
    col_start = max(1, col-min_dist);
    col_end = min(N, col+min_dist);
    window = P(row_start:row_end, col_start:col_end);
    
    % 检查是否为局部最大值
    if P(row,col) == max(window(:))
        peaks = [peaks P(row,col)];
        locs_v = [locs_v row];
        locs_u = [locs_u col];
    end
end

% 创建带阻滤波器
H = ones(M, N);
D0 = 3;

% 对每个检测到的峰值创建带阻滤波器
for k = 1:length(locs_v)
    v = locs_v(k);
    u = locs_u(k);
    % 找对称位置
    v_sym = 2*center_v - v;
    u_sym = 2*center_u - u;

    [X, Y] = meshgrid(1:N, 1:M);
    H = H .* (1 - exp(-((X-u).^2 + (Y-v).^2)/(2*D0^2)));
    H = H .* (1 - exp(-((X-u_sym).^2 + (Y-v_sym).^2)/(2*D0^2)));
end

% 应用滤波器
G_shifted = F_shifted .* H;
G = ifftshift(G_shifted);
g = real(ifft2(G));

subplot(2,2,2);
imshow(S, []);
hold on;
plot(locs_u, locs_v, 'r+', 'MarkerSize', 10);
plot(2*center_u-locs_u, 2*center_v-locs_v, 'r+', 'MarkerSize', 10);
title('检测到的峰值位置');

subplot(2,2,3);
imshow(H, []);
title('带阻滤波器');

subplot(2,2,4);
imshow(uint8(g), []);
title('滤波后结果');

% 打印检测到的位置
fprintf('检测到的频率位置：\n');
for k = 1:length(locs_v)
    fprintf('位置 %d: (%d, %d)\n', k, locs_v(k)-center_v, locs_u(k)-center_u);
end