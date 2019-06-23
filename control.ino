long butonOn = 32;// 16753245;
long butonMode = 33;// 16736925;
void infra() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == butonOn) {
      enable = 1;
    } else if (results.value == butonMode) {
      enable = 0;
    }
    irrecv.resume();
  }
}

void manevra(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  int AcXoff, AcYoff, AcZoff, GyXoff, GyYoff, GyZoff;

  //Acceleration data correction
  AcXoff = -950;
  AcYoff = -300;
  AcZoff = 0;

  GyXoff = 480;
  GyYoff = 170;
  GyZoff = 210;

  //read accel data
  AcX = (Wire.read() << 8 | Wire.read()) + AcXoff;
  AcY = (Wire.read() << 8 | Wire.read()) + AcYoff;
  AcZ = (Wire.read() << 8 | Wire.read()) + AcYoff;

  GyX = (Wire.read() << 8 | Wire.read()) + GyXoff;
  GyY = (Wire.read() << 8 | Wire.read()) + GyYoff;
  GyZ = (Wire.read() << 8 | Wire.read()) + GyZoff;

  //get pitch/roll
  getAngle(AcX, AcY, AcZ);
}
