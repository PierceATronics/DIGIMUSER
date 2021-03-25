%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DIGIMUSER - Vocal Effects Processor - Team 15
%%%%%%%%%%%%%%%% Flanger Effect %%%%%%%%%%%%%%%%%%%%

function output = Flanger(audio,sweep_freq,sweep_range,fs)

delay = 100;//ms

G = 0.5;//gain

for i = delay+sweep_range:length(audio)

    output(i) = audio(i) + G * audio(i-delay-round(sweep_range*sin(2*pi*i*sweep_freq/fs))); //%needs to be an array?
end
output = transpose(output);

//pot would adjust the delay
//and sweep_frequency
