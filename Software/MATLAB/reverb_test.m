close all;
clear all;
%#####################REVERB TEST##################################
% Author: David Pierce Walker-Howell
% Description: IIR Comb filter reverb.
%##################################################################
[x, fs] = audioread('H_n_S_Licks_17.wav');
x = transpose(x); x=x(1,:);
N = (size(x)); N = N(2);

C1 = 0.75; M1=4000; g1=0.50;
y1 = iircomb(x, C1, g1, M1);
C2 = 0.75; M2 = 6000; g2=0.50;
y2 = iircomb(x, C2, g2, M2);
%sound(y1 + y2, fs);

C = [0.25, 0.25, 0.25, 0.25];
M = [2048, 2944, 3968, 5120];
g = [0.75, 0.75, 0.75, 0.75];

c1 = iircomb(x, C(1), g(1), M(1));
c2 = iircomb(x, C(2), g(2), M(2));
c3 = iircomb(x, C(3), g(3), M(3));
c4 = iircomb(x, C(4), g(4), M(4));

y = c1 + c2 + c2 + c4;
y = y ./ max(y);
sound(x, fs);
pause(int32(length(x) * 1/fs));
sound(y, fs);
%audiowrite('reverb_test.wav', y, fs);



