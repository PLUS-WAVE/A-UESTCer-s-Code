%读取训练集
path_train = '../imgs/MNIST/train'; %训练集路径（自定义）
folders_train = fullfile(path_train,{'0' '1' '2' '3' '4' '5' '6' '7' '8' '9'}); %读取子目录
% 这行代码创建了一个包含训练集中所有子目录的单元格数组，这些子目录对应于数字0到9的类别。
imds_train = imageDatastore(folders_train,'FileExtensions','.jpg',...
'LabelSource','foldernames'); %读取所有图像路径
%这行代码创建了一个imageDatastore对象，用于存储训练集中所有图像的路径，并且根据文件夹名称自动为图像分配标签。
[imdsTrain,imdsValidation] = splitEachLabel(imds_train,0.9,0.1); %拆分出验证集
% 将训练数据集分为训练集和验证集，其中90%的数据用于训练，10%的数据用于验证。
%读取测试集
path_test = '../imgs/MNIST/test'; %测试集路径（自定义）
folders_test = fullfile(path_test,{'0' '1' '2' '3' '4' '5' '6' '7' '8' '9'});%创建了一个包含测试集中所有子目录的单元格数组
imds_test = imageDatastore(folders_test,'FileExtensions','.jpg',...
'LabelSource','foldernames');

%图像增强
pixelRange = [-2 2]; %平移范围
scaleRange = [0.9 1.1]; %缩放范围。定义了图像增强的参数，包括随机平移的范围和缩放的范围。
imageAugmenter = imageDataAugmenter( ...
'RandXTranslation',pixelRange, ...
'RandYTranslation',pixelRange, ...
'RandXScale',scaleRange, ...
'RandYScale',scaleRange); %定义图像增强器
augimdsTrain = augmentedImageDatastore([28,28],imds_train, ...
'DataAugmentation',imageAugmenter); %图像增强这行代码创建了一个增强的图像数据存储，用于存储增强后的图像数据。


%% 设计（或者读取）网络
layers = [
imageInputLayer([28 28 1],"Name","imageinput")
convolution2dLayer([5 5],32,"Name","conv_1","Padding","same","Stride",[2 2])
reluLayer("Name","relu_1")
batchNormalizationLayer("Name","batchnorm_1")
convolution2dLayer([3 3],32,"Name","conv_2","Padding","same")
reluLayer("Name","relu_2")
fullyConnectedLayer(512,"Name","fc_1")
batchNormalizationLayer("Name","batchnorm_2")
reluLayer("Name","relu_3")
fullyConnectedLayer(10,"Name","fc_2")
softmaxLayer("Name","softmax")
classificationLayer("Name","classoutput")];
%这段代码定义了一个卷积神经网络的结构，
% 包括输入层、两个卷积层、两个ReLU激活层、批量归一化层、一个全连接层、Softmax层和分类输出层。
% analyzeNetwork(layers) %分析网络


%% 训练网络
options = trainingOptions('sgdm', ...
'MiniBatchSize',512, ...
'MaxEpochs',1, ...
'InitialLearnRate',1e-2, ...
'Shuffle','every-epoch', ...
'ValidationData',imdsValidation, ...
'ValidationFrequency',3, ...
'Verbose',1, ...
'Plots','training-progress'); %设置训练策略
%这段代码设置了训练网络的选项，
% 包括优化器、批量大小、最大训练周期、初始学习率、
% 是否每个周期都打乱数据、验证数据集、验证频率、是否显示训练过程中的详细信息以及是否显示训练进度图。
global trainedNet;
trainedNet = trainNetwork(augimdsTrain,layers,options); %训练

%% 测试模型
[YPred,probs] = classify(trainedNet,imds_test); 
accuracy = mean(YPred == imds_test.Labels)
%测试了训练好的模型在测试集上的性能，计算了预测结果与实际标签一致的比例，即准确率。

