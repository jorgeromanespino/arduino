// 
const int SENSOR_LUZ_PIN = A0;
const int SENSOR_CORRIENTE_PIN = D1;
const int SENSOR_PRESENCIA_PIN = D2;
const int ACTUADOR_RELE_LUZ_PIN = D3;
const int SENSOR_INTERRUPTOR_PIN = D0;

//
void setup() {
  //
  Serial.begin(9600);
  //
  pinMode(SENSOR_LUZ_PIN, INPUT);
  pinMode(SENSOR_CORRIENTE_PIN, INPUT);
  pinMode(SENSOR_PRESENCIA_PIN, INPUT);
  pinMode(ACTUADOR_RELE_LUZ_PIN, OUTPUT);
  pinMode(SENSOR_INTERRUPTOR_PIN, INPUT);
}

//
void loop() {
  //
  tratar_deteccion_luz();
  //
  tratar_interruptor_luz();
  //
  tratar_estado_motor_puerta();
  //
  tratar_deteccion_presencia();
  //
  tratar_iluminacion_garaje();
  //
  esperar_tiempo_ciclo();
}

//
int interruptor_conmutado_valor = 0;
int interruptor_conmutado_estado = 0;
int interruptor_conmutado_pulsado = 0;
void tratar_interruptor_luz() {  
  interruptor_conmutado_valor = digitalRead(SENSOR_INTERRUPTOR_PIN);
  interruptor_conmutado_pulsado = (interruptor_conmutado_valor != interruptor_conmutado_estado) ? 1 : 0;    
  interruptor_conmutado_estado = interruptor_conmutado_valor;
  //Serial.print("interruptor_conmutado_pulsado: ");
  //Serial.println(interruptor_conmutado_pulsado);
}

//
int luz_detectada = 0;
void tratar_deteccion_luz() {
  int luz_v = analogRead(SENSOR_LUZ_PIN);
  luz_detectada = (luz_v <= 200) ? 1 : 0;
  //luz_detectada = map(luz_detectada, 0, 1023, 0, 1023);
  
  //Serial.print("luz_detectada: ");
  //Serial.println(luz_detectada);
}

//
int presencia_detectada = 0;
void tratar_deteccion_presencia() {
  presencia_detectada = digitalRead(SENSOR_PRESENCIA_PIN);  
  //Serial.print("presencia_detectada: ");
  //Serial.println(presencia_detectada);
}

//
int arranque_motor_detectado = 0;
void tratar_estado_motor_puerta() {
  arranque_motor_detectado = 1 - digitalRead(SENSOR_CORRIENTE_PIN);  
  //Serial.print("arranque_motor_detectado: ");
  //Serial.println(arranque_motor_detectado);
}

//
void tratar_iluminacion_garaje() {
  if (arranque_motor_detectado) {
    // Se enciende la luz
    digitalWrite(ACTUADOR_RELE_LUZ_PIN, HIGH);
    Serial.println("arranque_motor_detectado");
  } else if (interruptor_conmutado_pulsado) {
    // Se conmuta la luz
    digitalWrite(ACTUADOR_RELE_LUZ_PIN, interruptor_conmutado_estado);
    Serial.println("interruptor_pulsado");
  } else if (presencia_detectada) {
    Serial.println("presencia_detectada");
    if (!luz_detectada) {
      // Se enciende la luz
      digitalWrite(ACTUADOR_RELE_LUZ_PIN, HIGH);      
      Serial.println("luz_detectada_off");
    } else {      
      Serial.println("luz_detectada_on");
    }
  }
}

//
void esperar_tiempo_ciclo() {
   delay(1000);  
}

