void StartMotor (int m1, int m2, int forward, int speed) {
  if (speed == 0) { // oprire
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  } else {
    if (forward) {
      digitalWrite(m2, 0);
      analogWrite (m1, speed * 2.55); // folosire PWM
    } else {
      digitalWrite(m1, 0);
      analogWrite(m2, speed * 2.55);
    }
  }
}

void opreste() {
  digitalWrite(stopuri, 1);
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(300);
  digitalWrite(stopuri, 0);
}
void opresteF() {
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
}

void mergeInainte() {
  StartMotor (mpin00, mpin01, 1, 40);
  StartMotor (mpin10, mpin11, 1, 40);
}
void mergeInapoi() {
  StartMotor (mpin00, mpin01, 0, 40);
  StartMotor (mpin10, mpin11, 0, 40);
}

void ocolesteStanga() {
  int t0 = 0, dT = 0;
  digitalWrite(27, 1);
  delay(400);
  digitalWrite(27, 0);
  delay(400);
  digitalWrite(27, 1);
  delay(400);
  digitalWrite(27, 0);

  verifica(3, 0);
  vireaza(5, -1);
  t0 = millis();
  while (dT < 500 && enable != 0) {
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 0, 80);
    StartMotor (mpin10, mpin11, 0, 80);
  }
  opreste();

  vireaza(5, 0);
  dT = 0;
  t0 = millis();
  while (dT < 1000 && enable != 0) {
    if (distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 80);
    StartMotor (mpin10, mpin11, 1, 80);
  }

  vireaza(5, -1);
  dT = 0;
  t0 = millis();
  while (dT < 800 && enable != 0) {
    if (distanta() > 0 && distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 70);
    StartMotor (mpin10, mpin11, 1, 70);
  }

  vireaza(5, 1);
  dT = 0;
  t0 = millis();
  while (dT < 150 && enable != 0) {
    if (distanta() > 0 && distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 80);
    StartMotor (mpin10, mpin11, 1, 80);
  }
here:
  opreste();
  vireaza(5, 0);
}



void ocolesteDreapta() {
  int t0 = 0, dT = 0;
  digitalWrite(29, 1);
  delay(400);
  digitalWrite(29, 0);
  delay(400);
  digitalWrite(29, 1);
  delay(400);
  digitalWrite(29, 0);

  verifica(3, 0);
  vireaza(5, 1);
  t0 = millis();
  while (dT < 500 && enable != 0) {
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 0, 80);
    StartMotor (mpin10, mpin11, 0, 80);
  }
  opreste();

  vireaza(5, 0);
  dT = 0;
  t0 = millis();
  while (dT < 1000 && enable != 0) {
    if (distanta() > 0 && distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 80);
    StartMotor (mpin10, mpin11, 1, 80);
  }

  vireaza(5, 1);
  dT = 0;
  t0 = millis();
  while (dT < 800 && enable != 0) {
    if (distanta() > 0 && distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 70);
    StartMotor (mpin10, mpin11, 1, 70);
  }

  vireaza(5, -1);
  dT = 0;
  t0 = millis();
  while (dT < 150 && enable != 0) {
    if (distanta() > 0 && distanta() < 20 ) goto here;
    dT = millis() - t0;
    StartMotor (mpin00, mpin01, 1, 80);
    StartMotor (mpin10, mpin11, 1, 80);
  }
here:
  opreste();
  vireaza(5, 0);
}
