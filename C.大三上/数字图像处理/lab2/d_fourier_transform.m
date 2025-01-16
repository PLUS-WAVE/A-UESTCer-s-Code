I = imread('../imgs/pollen.jpg');
if size(I,3) == 3
    I = rgb2gray(I);
end
imshow(I);
title('原图像');

fftI = fft2(double(I));

sfftI = fftshift(fftI);
RR = real(sfftI);
II = imag(sfftI);
A = sqrt(RR.^2 + II.^2);
A = log(A + 1);
A = mat2gray(A);
figure;
imshow(A);
title('频谱幅度');

A_only = abs(sfftI);
phase_zero = zeros(size(sfftI));

fftA_only = A_only .* exp(1i * phase_zero);

IA = ifft2(ifftshift(fftA_only));
IA = real(IA);
IA = mat2gray(IA);
figure;
imshow(IA);
title('仅幅度反变换的图像');

phase_only = angle(sfftI);
A_constant = ones(size(sfftI));

fftPhase_only = A_constant .* exp(1i * phase_only);

IP = ifft2(ifftshift(fftPhase_only));
IP = real(IP);
IP = mat2gray(IP);
figure;
imshow(IP);
title('仅相位反变换的图像');

figure;
subplot(1,3,1); imshow(I); title('原图像');
subplot(1,3,2); imshow(IA); title('仅幅度反变换');
subplot(1,3,3); imshow(IP); title('仅相位反变换');
