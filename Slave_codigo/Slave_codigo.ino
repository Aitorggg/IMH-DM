/*
  ------------------------------------------ DATOS PROGRAMA -----------------------------
  
  Descripción breve:
  Mediante estos dos programas enviamos una serie de datos desde el dispostivo master al dispositivo.
  La comunicación de ambos arduinos se realiza mediante el protocolo sincrono I2C, por dos cables. Uno es el clock (SCL) y otro para el dato (SDA)  
  
  Fecha: 25-02-2020
  Versión: nº 1.0
  Autores: Aitor García Guinea, Gonzalo Mier Uría, Ibai Ceberio Basañez  
  Revisor: Iván Araquistain Marquina
*/

/*         -------------- Wire lectura Slave  --------------------- */

  #include <Wire.h> // Incluimos la librería Wire para I2C
  #define slave_addr 8 // Definimos la dirección del I2C para el slave
  byte SlaveReceived = 0; //Variable donde almacenaremos el dato recibido desde el master 
 
 // Definimos los pines del led para cada color 
  int BLUE=3;
  int GREEN=5;
  int RED=6;

  void setup ()
  {
    Serial.begin(9600); //Setup del monitor serie
    Serial.println("I2C Demostración de Master");
    Wire.begin(slave_addr); // Inicializamos la comunicación I2C
      
    Wire.onReceive(receiveEvent); // función para arrancar cuando se requieran datos del master
    Wire.onRequest(requestEvent); // función para arrancar cuando se reciban datos del master   

    // Declaramos los pines de los led como salidas
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);
    
    // Ponemos los tres pines a nivel bajo, para asegurarnos de que lo estén 
    digitalWrite(RED, LOW); 
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
}

 // Esta función se llama el Esclavo recibe un valor desde el master 
  void receiveEvent (int howMany)                    
    { 
      SlaveReceived = Wire.read(); //Se usa para leer el valor recibido desde el master and store in variable SlaveReceived
    }

  //Se llama a esta función cuando el máster quiere un valor del slave
  void requestEvent()                                
    {
      int potvalue = analogRead(A0);                   // Lee el valor analógico (0-5V)
      byte SlaveSend = map(potvalue,0,1023,0,127);     // Convierte el valor digital de (0 to 1023) a (0 to 127)
      Wire.write(SlaveSend);                           // Envia un byte al master
    }





  /* 
   El loop es una función que se ejecuta una y otra vez, es decir, no para
   Se ejecutará uno de los Case dependiendo de lo que se haya pulsado
  */
  void loop()
    {
      if (Serial.available())
      {
       // char color = Serial.read();
       char color = Wire.read();
       switch (color)
       {
        case 'R':
          digitalWrite(RED, 1);
          Serial.println("RED sign turned on.");
          break;
        case 'B':
          digitalWrite(BLUE, 1);
          Serial.println("BLUE sign turned on.");
          break;
        case 'G':
          digitalWrite(GREEN, 1);
          Serial.println("GREEN sign turned on.");
          break;
        case 'Y':
          digitalWrite(RED, 1);
          digitalWrite(GREEN, 1);
          Serial.println("YELLOW sign turned on.");
          break;
        case 'P':
          digitalWrite(RED, 1);
          digitalWrite(BLUE, 1);
          Serial.println("PURPLE sign turned on.");
          break;
        case 'W':
          digitalWrite(RED, 1);
          digitalWrite(BLUE, 1);
          digitalWrite(GREEN, 1);
          Serial.println("WHITE sign turned on.");
          break;
       }
      }
      


  delay(3000); //Esperamos 3 segundos 

  // Ponemos a nivel bajo las tres salidas 
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
   }
