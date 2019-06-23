void avarii(int k) {
  verifica(3, 0);
  for (int i = 0; i < k; i++) {
    digitalWrite(27, 1);
    digitalWrite(29, 1);
    delay(400);
    digitalWrite(27, 0);
    digitalWrite(29, 0);
    delay(400);
  }
}
