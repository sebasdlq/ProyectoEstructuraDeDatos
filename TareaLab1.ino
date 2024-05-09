#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
 
#define ANCHO 128
#define ALTO 64

#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

const byte FILAS = 4;
const byte COLUMNAS = 4;
char keys[FILAS][COLUMNAS] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {19,18,5,17}; 
byte pinesColumnas[COLUMNAS] = {16, 4, 0, 2}; 

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); 

char tecla; //Variable de teclado
int Contador_desplazamiento = 0; //Contador de desplazamiento de pantalla
String Id_pantalla = "MPrincipal"; //Identificador de pantalla actual
int Contador_pulsador = 0; //Contador de pulsador

//Tarea 1 - VARIABLES
bool loged = false;
String password = "0000";
String current_password = "";

//Tarea 3 - Contador
bool increasing = true;

//Pines
#define Pulsador_pin 13
#define Switch1_pin 35
#define Switch2_pin 32
#define Switch3_pin 34
#define LED1_pin 27
#define Buzzer_pin 15

void Mostrar (String menu[], int n) { //Función que muestra el menú en la pantalla
  oled.setCursor(0, 0);
  if (n > 2) {
    for (int i = 0; i < 3; i++) { //Muestra solo tres elementos a la vez
      oled.print(Contador_desplazamiento + i + 1);
      oled.print(".");
      oled.println(menu[Contador_desplazamiento + i]);
    }
  } else {
    for (int i = 0; i < 2; i++) { //Muestra solo tres elementos a la vez
      oled.print(Contador_desplazamiento + i + 1);
      oled.print(".");
      oled.println(menu[Contador_desplazamiento + i]);
    }
  }
}

void Desplazamiento (int n, int elementos) { //Función para desplazar el menú
  switch (tecla) {
    case 'A':
    //Desplaza hacia arriba si el contador es mayor a 0
    if (Contador_desplazamiento > 0) { 
     Contador_desplazamiento--;
    }
    break;
    case 'B':
    //Desplaza hacia abajo si el contador es menor al tamaño del vector menos los elementos mostrados en pantalla
    if (Contador_desplazamiento < n - elementos) {  
     Contador_desplazamiento++;
    }
    break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(Switch1_pin, INPUT); //Switch 1
  pinMode(Switch2_pin, INPUT); //Switch 2
  pinMode(Switch3_pin, INPUT); //Switch 3
  pinMode(Pulsador_pin, INPUT); //Pulsador
  pinMode(LED1_pin, OUTPUT); //LED 1
  pinMode(Buzzer_pin, OUTPUT); //BUZZER
}

void loop() {
  int Pulsador = digitalRead(Pulsador_pin); //Lee el estado del pulsador
  int Estado_SW1 = digitalRead(Switch1_pin); //Lee el estado del switch 1
  int Estado_SW2 = digitalRead(Switch2_pin); //Lee el estado del switch 2
  int Estado_SW3 = digitalRead(Switch3_pin); //Lee el estado del switch 2

  if (Pulsador == 1) { //Pulsador se presiona
    if(increasing){
      Contador_pulsador++; //Aumenta el contador del pulsador
      tone(Buzzer_pin, 3000); //Buzzer emite sonido
      delay(200);
      noTone(Buzzer_pin);
      if(Contador_pulsador >= 10){
        increasing = false;
      }
    }else{
      Contador_pulsador--; //Aumenta el contador del pulsador
      tone(Buzzer_pin, 1000); //Buzzer emite sonido
      delay(200);
      noTone(Buzzer_pin);
      if(Contador_pulsador <= 0){
        increasing = true;
        tone(Buzzer_pin, 2000); //Buzzer emite sonido
        delay(1000);
        noTone(Buzzer_pin);
      }
    }
    
  }

  if (Estado_SW2 == 0) { //MODO LOCAL
    oled.clearDisplay(); //Limpia pantalla
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    digitalWrite(LED1_pin, 1); //Enciende led
    tecla = teclado.getKey(); //Obtiene la tecla presionada
    Serial.println(tecla);
    //Vectores donde se almacenan los menús
    String Menu_Principal[6] = {"Entradas", "Salidas", "Fecha y hora", "Memoria", "Motor"};
      String Menu_Entradas[3] = {"Switch 1", "Contador", "Vel"};
      String Menu_Salidas[2] = {"Rele", "Servo"};
        String Menu_Rele[2] = {"ON", "OFF"};
        String Menu_Servo[2] = {"+10 grados", "-10 grados"};
      String Menu_Memoria[2] = {"Historico pulsador", "Borrado de memoria"};
      String Menu_Motor[4] = {"ON", "OFF", "Giro L", "Giro R"};

    if(loged){
        //Cambios de identificador de pantalla según la tecla presionada
      switch (tecla) { //Tecla es presionada
        case '1':
        Contador_desplazamiento = 0;
        if (Id_pantalla == "MPrincipal") {
          Id_pantalla = "MEntradas";
        } else if (Id_pantalla == "MEntradas") {
          Id_pantalla = "MSwitch1";
        } else if (Id_pantalla == "MSalidas") {
          Id_pantalla = "MRele";
        } else if (Id_pantalla == "MMemoria") {
          Id_pantalla = "MHistorico";
        } else if (Id_pantalla == "MMotor") {
          
        } else if (Id_pantalla == "MRele") {

        } else if (Id_pantalla == "MServo") {

        }
        break;
        case '2':
        Contador_desplazamiento = 0;
        if (Id_pantalla == "MPrincipal") {
          Id_pantalla = "MSalidas";
        } else if (Id_pantalla == "MEntradas") {
          Id_pantalla = "MContador";
        } else if (Id_pantalla == "MSalidas") {
          Id_pantalla = "MServo";
        } else if (Id_pantalla == "MMemoria") {
          
        } else if (Id_pantalla == "MMotor") {

        } else if (Id_pantalla == "MRele") {

        } else if (Id_pantalla == "MServo") {

        }
        break;
        case '3':
        Contador_desplazamiento = 0;
        if (Id_pantalla == "MPrincipal") {
          Id_pantalla = "MFecha";
        } else if (Id_pantalla == "MEntradas") {
          Id_pantalla = "MVelocidad";
        } else if (Id_pantalla == "MMotor") {

        }
        break;
        case '4':
        Contador_desplazamiento = 0;
        if (Id_pantalla == "MPrincipal") {
          Id_pantalla = "MMemoria";
        } else if (Id_pantalla == "MMotor") {

        }
        break;
        case '5':
        Contador_desplazamiento = 0;
        if(Id_pantalla == "MPrincipal") {
          Id_pantalla = "MMotor";
        }
        break;
        case 'C':
        Contador_desplazamiento = 0;
        if (Id_pantalla == "MEntradas" || Id_pantalla == "MSalidas" || Id_pantalla == "MFecha" || Id_pantalla == "MMemoria" || Id_pantalla == "MMotor") {
          Id_pantalla = "MPrincipal";
        } else if (Id_pantalla == "MSwitch1" || Id_pantalla == "MContador" || Id_pantalla == "MVelocidad") {
          Id_pantalla = "MEntradas";
        } else if (Id_pantalla == "MRele" || Id_pantalla == "MServo") {
          Id_pantalla = "MSalidas";
        } else if (Id_pantalla == "MHistorico") {
          Id_pantalla = "MMemoria";
        }
        break;
      }

      if (Id_pantalla == "MPrincipal") {
        Mostrar (Menu_Principal, 5);
        Desplazamiento(5, 3); //Tamaño del vector es 5 y los elementos mostrados en pantalla 3
      } else if (Id_pantalla == "MEntradas") {
        Mostrar (Menu_Entradas, 3);
        Desplazamiento(3, 3);
      } else if (Id_pantalla == "MSalidas") {
        Mostrar (Menu_Salidas, 2);
      } else if (Id_pantalla == "MFecha") {
        
      } else if (Id_pantalla == "MMemoria") {
        Mostrar (Menu_Memoria, 2);
      } else if (Id_pantalla == "MMotor") {
        Mostrar (Menu_Motor, 4);
        Desplazamiento(4, 3);
      } else if (Id_pantalla == "MSwitch1") {
        oled.setCursor(45, 20);
        if (Estado_SW1 == 0) {
          oled.print("OFF");
        } else {
          oled.print("ON"); 
        }
      } else if (Id_pantalla == "MContador") {
        oled.setCursor(45, 20);
        oled.print(Contador_pulsador); 
      } else if (Id_pantalla == "MVelocidad") {

      } else if (Id_pantalla == "MRele") {
        Mostrar (Menu_Rele, 2);
      } else if (Id_pantalla == "MServo") {
        Mostrar (Menu_Servo, 2);
      } else if (Id_pantalla == "MHistorico") {
        
      }
    }else{
      //Debe de  poner la contrasena
      oled.clearDisplay();
      oled.setTextColor(WHITE);
      oled.setTextSize(1);
      oled.setCursor(0, 10);
      oled.print("Ingrese contrasena: ");
      oled.setCursor(0, 30);
      oled.print(current_password);
      

      switch(tecla){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case '*':
        case '#':
          current_password = current_password + tecla;
          if(current_password.length() == 4){
            if(current_password == password){
              loged = true;
            }
            current_password = "";
          }
          break;
      }
      
    }
    oled.display();
  } else { //MODO REMOTO
    Id_pantalla = "MPrincipal"; //Vuelve al menú principal
    Contador_desplazamiento = 0; //Reinicia el contador de desplazamiento
    digitalWrite(LED1_pin, 0); //Apaga el LED
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.setCursor(0, 20);
    if (Estado_SW3 == 0) {
      oled.print("BLUETOOTH");
    } else {
      oled.print("WIFI");
    }
    oled.display();
  }
}