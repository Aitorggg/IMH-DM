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

/*         -------------- Wire escritura Master --------------------- */


  #include <Wire.h> // Incluimos la librería Wire para I2C
  #define slave_addr 8 // Definimos la dirección del I2C para el slave
 
  byte val; 

  // El setup es una función que se ejecuta una única vez 
  void setup ()
    {
      Serial.begin(9600); //Setup del monitor serie
      Serial.println("I2C Demostración de Master");
      Wire.begin(slave_addr); // Inicializamos la comunicación I2C
      
        
      Serial.println("Introducir un color para que se ilumine el led de un color. Escriba R, B, G, Y, P o W");
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
  */
  void loop()
    {
     // Escritura de carácteres al Slave
      Wire.beginTransmission(slave_addr);
      Wire.write(val);
      Serial.write(val);
      Wire.endTransmission();


      //Añadir los carácteres a String
      String respuesta = "";
      while (Wire.available())
      {
        char b = Wire.read();
        respuesta += b;
      }
      Serial.println(respuesta);//Sacar por el puerto serie la respuesta

   }
