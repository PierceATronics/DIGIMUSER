%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DIGIMUSER - Vocal Effects Processor - Team 15
%%%%%%%%%%%%%%%% Flanger Effect %%%%%%%%%%%%%%%%%%%%

function output = Flanger(audio,sweep_freq,sweep_range,fs)

delay = 100;

G = 0.5;

for i = delay+sweep_range:length(audio)

    output(i) = audio(i) + G * audio(i-delay-round(sweep_range*sin(2*pi*i*sweep_freq/fs)));
end
output = transpose(output);
