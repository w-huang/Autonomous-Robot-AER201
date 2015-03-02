char incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial.println((int) 0 * 10);
}

void loop() {
        int value = 0;
        // send data only when you receive data:
        if (Serial.available() > 0) {
          
                while(true){
                  incomingByte = Serial.read();
                  if (incomingByte == '\n')
                    break;
                  value = value * 10;
                  value += (int) (incomingByte - '0');
                  }
                Serial.print("I received: ");
                Serial.println(value);
              }
      delay(50);  
      }

