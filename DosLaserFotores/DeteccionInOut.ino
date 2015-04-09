const int pinLedAzul = 2;
const int pinLedAmarillo = 3;
const int pinAnalogicoFotoResistencia1 = 0;
const int pinAnalogicoFotoResistencia2 = 1;
const int voltajeUmbral = 970;
boolean estadoSensor[2] = {false, false};
boolean luzEstable = false;

void setup() {
  pinMode(pinLedAzul, OUTPUT);
  pinMode(pinLedAmarillo, OUTPUT);
  Serial.begin(9600);
  apagarTodosLosLeds();
  esperarEstabilizacionDeLaserEnLosSensores();
}

void apagarTodosLosLeds() {
  digitalWrite(pinLedAzul, LOW);
  digitalWrite(pinLedAmarillo, LOW);
}

void esperarEstabilizacionDeLaserEnLosSensores() {
  while(!luzEstable) {
    continuarPrograma();
    luzEstable = (estadoSensor[0] && estadoSensor[1]);
  }
}

void continuarPrograma() {
  int voltajeFotoResistencia = leerVoltajeFotoResistencia(pinAnalogicoFotoResistencia1);
  cambiarEstadoLed(pinLedAzul, voltajeFotoResistencia, &estadoSensor[0]);
  voltajeFotoResistencia = leerVoltajeFotoResistencia(pinAnalogicoFotoResistencia2);
  cambiarEstadoLed(pinLedAmarillo, voltajeFotoResistencia, &estadoSensor[1]);
}

int leerVoltajeFotoResistencia(int pinAnalogico) {
  return analogRead(pinAnalogico);
}

void cambiarEstadoLed(int pinLed, int voltajeFotoResistencia, boolean *estado) {
  if(voltajeFotoResistencia > voltajeUmbral)
  {
    digitalWrite(pinLed, HIGH);
    *estado = true;
  } else
  {
    digitalWrite(pinLed, LOW);
    *estado = false;
  }
}

void loop() {
  Serial.println("Luz estable!");
  while(luzEstable) {
    continuarPrograma();
    boolean iniciaProcesoSalida = (estadoSensor[0] == 1 && estadoSensor[1] == 0);
    boolean iniciaProcesoEntrada = (estadoSensor[0] == 0 && estadoSensor[1] == 1);
    boolean continuaProceso = iniciaProcesoSalida || iniciaProcesoEntrada;
    
    while(continuaProceso) {
      continuarPrograma();
      continuaProceso = (estadoSensor[0] == 1 && estadoSensor[1] == 0) || (estadoSensor[0] == 0 && estadoSensor[1] == 1);
    }
    
    continuaProceso = (estadoSensor[0] == 0 && estadoSensor[1] == 0);
    if(continuaProceso) {
      while(continuaProceso) {
        continuarPrograma();
        continuaProceso = (estadoSensor[0] == 0 && estadoSensor[1] == 0);
      }
      
      boolean continuaProcesoSalida = (estadoSensor[0] == 0 && estadoSensor[1] == 1);
      if(iniciaProcesoSalida && continuaProcesoSalida) {
        while(continuaProcesoSalida) {
          continuarPrograma();
          continuaProcesoSalida = (estadoSensor[0] == 0 && estadoSensor[1] == 1);
        }
        if(estadoSensor[0] == 1 && estadoSensor[1] == 1) {
          Serial.println("Una Persona Salio");
        }
      }
      
      boolean continuaProcesoEntrada = estadoSensor[0] == 1 && estadoSensor[1] == 0;
      if(iniciaProcesoEntrada && continuaProcesoEntrada) {
        while(continuaProcesoEntrada) {
          continuarPrograma();
          continuaProcesoEntrada = (estadoSensor[0] == 1 && estadoSensor[1] == 0);
        }
        if(estadoSensor[0] == 1 && estadoSensor[1] == 1) {
          Serial.println("Una Persona Entro");
        }
      }
    }
    
    luzEstable = (estadoSensor[0] && estadoSensor[1]);
  }
  Serial.println("Luz inestable!");
  esperarEstabilizacionDeLaserEnLosSensores();
}


