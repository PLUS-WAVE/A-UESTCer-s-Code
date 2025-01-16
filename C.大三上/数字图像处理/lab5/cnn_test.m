%%函数
function DigitRecognition_gui
global trainedNet; %定义一个全局变量，用于存储预先训练的神经网络

% 创建第一个figure，用于显示文本框和导入按钮
fig1 = figure('Name', '导入按钮', ...
'NumberTitle', 'off', 'Position', [100, 100, 400, 200]);

% 添加文本框和导入按钮
txtResult = uicontrol('Style', 'text', 'Parent', fig1, ...
'Position', [20, 140, 360, 20], ...
'String', '', 'HorizontalAlignment', 'center');
btnLoad = uicontrol('Style', 'pushbutton', 'Parent', fig1, ...
'String', 'Load Image', ...
'Position', [20, 80, 160, 30], ...
'Callback', @loadImage);

% 创建第二个figure，用于显示图像
fig2 = figure('Name', '图像显示', ...
'NumberTitle', 'off', 'Position', [420, 100, 400, 400]);
axImage = axes('Parent', fig2, 'Position', [0.05, 0.05, 0.9, 0.9]);

% 回调函数
function loadImage(src, event)
[file, path] = uigetfile({'*.jpg;*.jpeg;*.png', 'Image Files (*.jpg, *.jpeg, *.png)'}, ...
'Select an Image');
if isequal(file, 0) || isequal(path, 0)
return;
end
imgPath = fullfile(path, file);
I = imread(imgPath);
imshow(I, 'Parent', axImage);

% 这里添加你的预测代码
scores = predict(trainedNet, single(I));
for i = 1:length(scores)
score = scores(i);
fprintf('probability %d: %.10f\n', (i-1), score);
end
%标记概率最大值以及最大值所对应的数字
max_score = max(scores);
max_index = find(scores == max_score);
fprintf('max_score %d: %.10f\n', max_score);
fprintf('digit %d: %.10f\n', (max_index - 1));

% 创建第三个figure，显示概率
fig3 = figure('Name', '概率显示', ...
'NumberTitle', 'off', ...
'Position', [100, 100, 640, 480]);

% 创建一个表格
table = uitable('Parent', fig3, ...
'Position', [50, 50, 800, 400], ...
'Data', [0:9; scores], ...
'ColumnName', {});


end
end

