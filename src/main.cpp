#include <all-include.h>


/* PINS DEFINITIONS  */
#define  OUTPUT_led_1  14
#define  INPUT_on_sw  38
#define  INPUT_off_sw  39
#define  INPUT_MEF_sw1  36
#define  INPUT_MEF_sw2  34
#define tiempoAntiRebote 200

typedef enum {Led_OFF, Led_ON}MOORE;

MOORE estados;

typedef enum {lectura_1, espera_1, lectura_2} pulsador_MEf_1;

pulsador_MEf_1 P_1_estado=lectura_1, P_2_estado=lectura_1;

int contador_pulsador_1, contador_pulsador_2;

void funcion_pulsador_1 (void){

  static unsigned long ActualMilis;

  switch (P_1_estado)
  {
  case lectura_1:
    if(!digitalRead(INPUT_MEF_sw1)){
      P_1_estado = espera_1;
      ActualMilis=millis();
    }
    /* si no esta activo el pulsador no hago nada */
    break;
  
  case espera_1:
    if(millis()>= (ActualMilis+tiempoAntiRebote))
    {
      P_1_estado=lectura_2;
    }
    break;

  case lectura_2:
    if(!digitalRead(INPUT_MEF_sw1))
    {
     ++contador_pulsador_1; 
    }  
    P_1_estado=lectura_1;
    break;

  default:
    // Serial.begin(9600);
    Serial.print("error en MEF pulsador, estado no declarado");
    break;
  }
}

void funcion_pulsador_2 (void){

  static unsigned long ActualMilis;

  switch (P_2_estado)
  {
  case lectura_1:
    if(!digitalRead(INPUT_MEF_sw2)){
      P_1_estado = espera_1;
      ActualMilis=millis();
    }
    /* si no esta activo el pulsador no hago nada */
    break;
  
  case espera_1:
    if(millis()>= (ActualMilis+tiempoAntiRebote))
    {
      P_1_estado=lectura_2;
    }
    break;

  case lectura_2:
    if(!digitalRead(INPUT_MEF_sw2))
    {
     ++contador_pulsador_2; 
    }  
    P_1_estado=lectura_1;
    break;

  default:
    // Serial.begin(9600);
    Serial.print("error en MEF pulsador, estado no declarado");
    break;
  }
}

/**
 * @brief Configurá los pines como entradas y salidas digitales
 * 
 * Esta función es útil para ordenar el código
 * 
 * @param void  
 * @param void
 * @return void
 * 
 * @note esta función usa la librería de arduino, no es la forma más optima a nivel recursos
 * @see otraFuncion()
 */
void pins_config (void){
  /*   DECLARACIÓN GPIO */  

  pinMode(OUTPUT_led_1,OUTPUT);
  pinMode(INPUT_on_sw,INPUT);
  pinMode(INPUT_off_sw,INPUT);
  pinMode(INPUT_MEF_sw1,INPUT);
  pinMode(INPUT_MEF_sw2,INPUT);

}
/**
 * @brief inicializa las salidas
 * 
 * Esta función es útil para ordenar el código
 * 
 * @param void  
 * @param void
 * @return void
 * 
 * @note esta función usa la librería de arduino, no es la forma más optima a nivel recursos
 * @see otraFuncion()
 */
void OUTPUTS_init (void){

  digitalWrite(OUTPUT_led_1,LOW);
}

void setup(){
  pins_config();
  OUTPUTS_init();
  /* inicializo MEF */
  estados=Led_OFF;
  Serial.begin(9600);
  Serial.print("serial iniciado");
  
}

void loop(){
  funcion_pulsador_1();
  funcion_pulsador_2();
  switch (estados)
  {
  case Led_OFF:
    digitalWrite(OUTPUT_led_1, LOW);  
    digitalRead(INPUT_on_sw)? estados=Led_ON : estados=Led_OFF;

  break;

  case Led_ON:
    digitalWrite(OUTPUT_led_1, HIGH);    
    digitalRead(INPUT_off_sw)? estados=Led_OFF : estados=Led_ON;
  break;
  default:
    
    break;
  }
  if(Serial.read() == '1') 
  {
    digitalWrite(BUILTIN_LED,HIGH);
    delay(1000);
    digitalWrite(BUILTIN_LED,LOW);
    delay(1000);

  } 

}



// Ejemplo de ej 3 con libreria string 
/* 
String textoLargo = "Este es un texto largo que quiero desplazar.";
int indiceDesplazamiento = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    String subcadena = textoLargo.substring(indiceDesplazamiento, indiceDesplazamiento + 30);
    Serial.println(subcadena);

    indiceDesplazamiento++;

    if (indiceDesplazamiento >= textoLargo.length()) {
        indiceDesplazamiento = 0;
    }

    delay(100); // Espera 100 milisegundos entre cada desplazamiento
}
 */