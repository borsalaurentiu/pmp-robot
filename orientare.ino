long duration, cm;

int distanta() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //  cm = duration / 58;
  //  return cm * 3 / 2;

  cm = duration / 40;
  //Serial.println(cm);
  return cm;
}

void verifica(int pin, int directie) {
  srv.attach(pin);
  switch (directie) {
    case 1: //delay(500);
      srv.write(45);
      delay(500);
      break;
    case 0: //delay(500);
      srv.write(90);
      delay(500);
      break;
    case -1: //delay(500);
      srv.write(135);
      delay(500);
      break;
    default:
      srv.write(90);
      break;
  }
  srv.detach();
}


void vireaza(int pin, int directie) {
  viraj.attach(pin);
  switch (directie) {
    case 1: //delay(500);
      viraj.write(65);
      delay(500);
      break;
    case 0: //delay(500);
      viraj.write(90);
      delay(500);
      break;
    case -1: //delay(500);
      viraj.write(135);
      delay(500);
      break;
    default:
      viraj.write(90);
      break;
  }
  viraj.detach();
}



void getAngle(int Vx, int Vy, int Vz) {
  double x = Vx;
  double y = Vy;
  double z = Vz;

  pitch = atan(x / sqrt((y * y) + (z * z)));
  roll = atan(y / sqrt((x * x) + (z * z)));
  //convert radians into degrees

  pitch = (int) (pitch * (180.0 / 3.14));
  roll = (int) (roll * (180.0 / 3.14));
}
