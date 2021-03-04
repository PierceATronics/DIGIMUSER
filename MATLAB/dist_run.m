% Runs dist.m, same as the other run files %

[voice_clip,Fs] = audioread('dist_test.wav');
duration = length(voice_clip)/Fs;
t = (0:((duration*Fs)-1)) * 1/Fs;
voice_clip = transpose(voice_clip);

output = zeros(1,length(voice_clip));

                                %audioread() uses stereo,
for i = 1:length(voice_clip)    %so we call the function for each channel

output(1,i) = dist(voice_clip(1,i),11); %left channel
output(2,i) = dist(voice_clip(2,i),11); %right channel

end

output = transpose(output);
audiowrite("output.wav", output, Fs); 

plot(t,output);
grid on;
grid minor;
xlabel('Time(s)');
ylabel('Amplitude');
title('Output Audio');

