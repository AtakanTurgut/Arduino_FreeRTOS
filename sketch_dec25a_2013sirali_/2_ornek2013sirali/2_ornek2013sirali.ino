#include <frt.h>
#include <Arduino_FreeRTOS.h>

void vSenderTask( void *pvParameters );
void  vReceiverTask( void *pvParameters );



QueueHandle_t xQueue;
const int32_t *anahtar0=2;
const int32_t *anahtar1=3;
const int32_t *anahtar2=4;
const int32_t *anahtar3=5;

void setup() 
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); //0
  pinMode(3, INPUT_PULLUP); //1
  pinMode(4, INPUT_PULLUP); //2
  pinMode(5, INPUT_PULLUP); //3
  pinMode(6, OUTPUT); //ANAHTARLARIN BİRİNCİ SIRASINI KONTROL İÇİN
  pinMode(7, OUTPUT);//LED İÇİN


  digitalWrite(6,LOW); //DENEY KARTI ÜZERİNDEKİ ANAHTARLARDAN BİRİNCİ SIRAYI KULLANIMA AÇAR.
  Serial.println("anahtar ayarlandı");
  
  
  xQueue = xQueueCreate( 4, sizeof( int32_t ) );
  


  //BaseType_t türünde değer döndüren görevler  
   xTaskCreate( 
     vReceiverTask
      ,  "vReceiverTask"   // A name just for humans
      ,  128  // Stack size
      ,  NULL
      ,  2  // priority
      ,  NULL );
    xTaskCreate( 
     vSenderTask
      ,  "sender1"   // A name just for humans
      ,  512  // Stack size
      ,  (void*)anahtar0 //0.anahtar dinleme parametre
      ,  2  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      , "sender2"   // A name just for humans
      ,  512  // Stack size
      ,  (void*)anahtar1 //1.anahtar dinleme parametre
      ,  2  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      , "sender3"   // A name just for humans
      ,  512  // Stack size
      ,  (void*)anahtar2 //2.anahtar dinleme parametre
      ,  2  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      ,  "sender4"   // A name just for humans
      ,  512  // Stack size
      ,  (void*)anahtar3 //3.anahtar dinleme parametre
      ,  2    // priority
      ,  NULL );
   
   

   
      vTaskStartScheduler();
  }
 



void loop()
{
  // Empty. Things are done in Tasks.
 
}

/*--------------------------------------------------*/
/*---------------------- Görev Tanımları ---------------------*/
/*--------------------------------------------------*/

void vSenderTask(void *pvParameters)  // This is a task.
{
  
  
  int32_t portNumber;
  int32_t yuklenecekDeger;
  Serial.begin(9600);
  BaseType_t xStatus;
  
  portNumber=(int32_t) pvParameters;
  
  
    /*
     * Her portu (anahtarı) farklı bir görev kontrol etmektedir. Parametre olarak port no gönderildi
     * port no değerine göre kuyruğa yüklenen değer -2 eklenerek anahtar no belirlendi. Farklı bir algoritma düşünülebilir. 
     * (bana kolay gibi geldi :).) 
     * 2. port 0 bilgisi, 3. port 1 bilgisi, 4.port 2 bilgisi, 5. port 3 bilgisi yüklendi.
     * 
     * Anahtarın üst üste basılmasını engellemek için 3 sn bekletme yapıldı (bakınız 1111). Bu süre değiştirilebilir. 
     */
  for (;;) // 
  {
    
    if (digitalRead(portNumber)==LOW)
      {
      yuklenecekDeger=portNumber-2;
      xStatus=xQueueSendToBack(xQueue, &yuklenecekDeger, 0); //son parametre bekleme süresidir. 0 doğrudan dönmeyi sağlar.
      Serial.print("Gönderilen=");
      Serial.println(yuklenecekDeger);
      vTaskDelay(3000/ portTICK_PERIOD_MS);//1111
      
      }
    else
      {
        //Serial.println("anahtar basilması bekleniyor");
        
      }
  taskYIELD();// diğer göevlerin çalışmasını bekler
 }
}
void vReceiverTask(void *pvParameters)  // This is a task.
{
  
  //Değişken tanımları
  Serial.begin(9600);
  int32_t IReceivedValue;
  BaseType_t xStatus;
  const TickType_t xTicksToWait=pdMS_TO_TICKS(100);
  
  
  

  for (;;) // 
  {
    if( uxQueueMessagesWaiting( xQueue ) != 0 )
      {
        //Serial.println("Kuyruk boş olmalı");
        
      }
      /* Verilen durum diyagramına göre çözümdür.
       * Kuyruk tamamen dolu ise şifreyi kontrol eder
       * Şifrenin herhangi bir karakteri yanlış ise "Şifre Yanlış" yazar ve Kuyruğu resetler
       * Şifrenin tüm karakterleri doğru ise "Şifre Doğru" yazar ve Led Yakıp Söndürülür. Kuyruk resetlerinir.
       */
      
      if (uxQueueSpacesAvailable(xQueue)==0)//Kuyruk 4 elemanlı olduğu için kontrol kuyrul tamamen dolunca yapılmaktadır
      {
          xQueueReceive(xQueue, &IReceivedValue, xTicksToWait);
         if (IReceivedValue==2)
        {
            xQueueReceive(xQueue, &IReceivedValue, xTicksToWait );
           if (IReceivedValue==0)
            {
              xQueueReceive(xQueue, &IReceivedValue, xTicksToWait );
              if (IReceivedValue==1)
              {
                xQueueReceive(xQueue, &IReceivedValue, xTicksToWait);
                if (IReceivedValue==3)
                {
                  //işlem tamam
                  Serial.println( "Şifre Doğru.\r\n" );
                  digitalWrite(7,HIGH);
                  vTaskDelay(3000/ portTICK_PERIOD_MS);
                  digitalWrite(7,LOW);
                  Serial.println( "Kapı Kapandı, Tekrar Şifre Giriniz.\r\n" );
                  xQueueReset(xQueue);
                }
                else
                {
                   Serial.println( "Şifre Yanlış.\r\n" );
                   xQueueReset(xQueue);
                }
              }
              else
              {
                Serial.println( "Şifre Yanlış.\r\n" );
                xQueueReset(xQueue);
              }
            }
            else
            {
              Serial.println( "Şifre Yanlış.\r\n" );
              xQueueReset(xQueue);
            }
        }
        else
        {
          Serial.println( "Şifre Yanlış.\r\n" );
          xQueueReset(xQueue);
        }
        
      }
    
     
     taskYIELD();
  }
}
