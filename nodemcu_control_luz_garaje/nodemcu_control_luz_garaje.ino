// 
const int SENSOR_LUZ_PIN = A0;
const int SENSOR_CORRIENTE_PIN = D1;
const int SENSOR_PRESENCIA_PIN = D2;
const int ACTUADOR_RELE_LUZ_PIN = D3;

//
void setup() {
  //
  Serial.begin(9600);
  //
  pinMode(SENSOR_LUZ_PIN, INPUT);
  pinMode(SENSOR_CORRIENTE_PIN, INPUT);
  pinMode(SENSOR_PRESENCIA_PIN, INPUT);
  pinMode(ACTUADOR_RELE_LUZ_PIN, OUTPUT);
}

//
void loop() {
  //
  //tratar_deteccion_luz();
  //
  tratar_estado_motor_puerta();
  //
  //tratar_iluminacion_garaje();
  ////
  //tratar_deteccion_presencia();
  //
  esperar_tiempo_ciclo();
}

//
int luz_detectada = 0;
void tratar_deteccion_luz() {
  int luz_v = analogRead(SENSOR_LUZ_PIN);
  luz_detectada = (luz_v <= 200) ? 1 : 0;
  //luz_detectada = map(luz_detectada, 0, 1023, 0, 1023);
  
  Serial.print("luz_detectada: ");
  Serial.println(luz_detectada);
}

//
int presencia_detectada = 0;
void tratar_deteccion_presencia() {
  presencia_detectada = digitalRead(SENSOR_PRESENCIA_PIN);  
  Serial.print("presencia_detectada: ");
  Serial.println(presencia_detectada);
}

//
void esperar_tiempo_ciclo() {
   delay(1000);  
}

//
int rele_valor = LOW;
void tratar_iluminacion_garaje() {
  //digitalWrite(ACTUADOR_RELE_LUZ_PIN, rele_valor);
  //
  int encender_luz = (presencia_detectada && !luz_detectada);
  //
  digitalWrite(ACTUADOR_RELE_LUZ_PIN, encender_luz);
  rele_valor = (rele_valor == LOW) ? HIGH : LOW;
  Serial.print("rele_valor: ");
  Serial.println(rele_valor);
}

 //
int arranque_motor_detectado = 0;
void tratar_estado_motor_puerta() {
  arranque_motor_detectado = 1 - digitalRead(SENSOR_CORRIENTE_PIN);  
  Serial.print("arranque_motor_detectado: ");
  Serial.println(arranque_motor_detectado);

  //float current = getCorriente(SAMPLESNUMBER);
  //printMeasure("Intensidad: ", current, "A ,");
}

