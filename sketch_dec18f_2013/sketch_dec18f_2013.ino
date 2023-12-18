bool s0DegerGeldiMi = false;
bool s1DegerGeldiMi = false;
bool s2DegerGeldiMi = false;
bool s3DegerGeldiMi = false;


void setup() {               
  
 
  pinMode(2, OUTPUT);//RB0
  pinMode(4, INPUT_PULLUP);//RB4
  pinMode(5, INPUT_PULLUP);//RB4
  pinMode(6, INPUT_PULLUP);//RB4
  pinMode(7, INPUT_PULLUP);//RB4
  

  Serial.begin(9600); /* Seri haberlesme baslatildi */
}

void loop() {
  digitalWrite(2,LOW);
  delay(200);
 if (digitalRead(4)==0)
  {
    Serial.println("SW0");
    s0DegerGeldiMi = true;
    // digitalWrite(8,HIGH);
  }
  if (digitalRead(5)==0)
  {
    Serial.println("SW1");
    if(s0DegerGeldiMi){
      s1DegerGeldiMi = true;
    }

  }
  if (digitalRead(6)==0)
  {
    Serial.println("SW2");
    // s2DegerGeldiMi = true;
    if(s1DegerGeldiMi){
      s2DegerGeldiMi = true;
    }

  }
  if (digitalRead(7)==0)
  {
    Serial.println("SW3");
     if(s2DegerGeldiMi){
      s3DegerGeldiMi = true;
    }
  }

  if(s0DegerGeldiMi && s1DegerGeldiMi && s2DegerGeldiMi && s3DegerGeldiMi){
    Serial.println("parola dogru");
    digitalWrite(8,HIGH);
    delay(1000);
    s0DegerGeldiMi = false;
    s1DegerGeldiMi = false;
    s2DegerGeldiMi = false;
    s3DegerGeldiMi = false;

  }
 }
