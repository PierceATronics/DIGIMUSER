const int pot1_pin = A5;

void setup(){

  Serial.begin(115200);

  //Resolution to read the potentiometer
  analogReadResolution(12);
}

void loop(){

  //Sample the potentiometer and cast into a 16-bits (15 fractional).
  int16_t pot1_val = (int16_t)(analogRead(pot1_pin) << 3);
  float pot1_val_float = (float)pot1_val / 32767.0;
  Serial.print("Normalized Pot Val: ");Serial.println(pot1_val_float);
  delay(100);
  
}
