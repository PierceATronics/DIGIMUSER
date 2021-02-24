% distortion vocal effect %

function output = dist(x,range,alpha,Fs)

for i = range:length(x)
   
    gain = 1;
    q = x*gain/max(abs(x));
    z = sign(-q)*(1-exp(sign(-q)*q));
    y = alpha * z * max(abs(x))/max(abs(z))+(1-alpha)*x;
    output = y * max(abs(x))/max(abs(y));
    
end
output = transpose(output);


% y = fuzzexp(x, gain, mix)
% Distortion based on an exponential function
% voice_clip    - input
% gain - amount of distortion, >0->
% mix  - mix of original and distorted sound, 1=only distorted
% x = voice_clip;
% gain = 1;
% mix = 0.5;
% q = x*gain/max(abs(x));
% z = sign(-q).*(1-exp(sign(-q).*q));
% y = mix * z * max(abs(x))/max(abs(z))+(1-mix)*x;
% y = y .* max(abs(x))/max(abs(y));