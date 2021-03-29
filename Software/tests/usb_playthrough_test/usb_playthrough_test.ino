#include <Audio.h>


AudioInputUSB     usb1;
AudioOutputI2S    cs4344_dac;

//Simple pass through of the USB input audio to the DAC output.
AudioConnection   connection_1(usb1, 0, cs4344_dac, 0);

void setup() {
  // put your setup code here, to run once:
  AudioMemory(8);
}

void loop() {
  // put your main code here, to run repeatedly:

}
