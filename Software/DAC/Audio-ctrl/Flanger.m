%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DIGIMUSER - Vocal Effects Processor - Team 15
%%%%%%%%%%%%%%%% Flanger Effect %%%%%%%%%%%%%%%%%%%%

function output = Flanger(audio,sweep_freq,sweep_range,fs)

delay = 100;//ms range 0 -

G = 0.75;//gain

sweep_freq = 0.5;//recommended

for i = delay+sweep_range:length(audio)

    output(i) = audio(i) + G * audio(i-delay-round(sweep_range*sin(2*pi*i*sweep_freq/fs))); //%needs to be an array?
end
output = transpose(output);

//pot would adjust the delay
//

//delay range(ms) 0-15

//range for G?0-1. will stay at 0.75
// sweep frequency 0.5

//flange delay = AUDIO_BLOCK_SAMPLES * 2

//sweep_range - length of sweep

//teensy efect
//#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
//short l_delayline[FLANGE_DELAY_LENGTH];

int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;



/////
//result = sample(0) + sample(dt + depthsin(2PI*Fe))
