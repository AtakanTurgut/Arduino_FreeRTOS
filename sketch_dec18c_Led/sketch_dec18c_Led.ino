


void setup() {               
  
 
  pinMode(10, OUTPUT);//RB0
  pinMode(11, INPUT_PULLUP);//RB4
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  Serial.begin(9600); /* Seri haberlesme baslatildi */
}

void loop() {
  digitalWrite(10,LOW);
  delay(100);
 if (digitalRead(11)==0)
  {
    Serial.println("SW0");
  }
  
   

 }