


void setup() {               
  
 
  pinMode(2, OUTPUT);//RB0
  pinMode(4, INPUT_PULLUP);//RB4
  

  Serial.begin(9600); /* Seri haberlesme baslatildi */
}

void loop() {
  digitalWrite(2,LOW);
  delay(10);
 if (digitalRead(4)==0)
  {
    Serial.println("SW0");
  digitalWrite(8,HIGH);

  }
  
  
   

 }
