#include <frt.h>

#include <Arduino_FreeRTOS.h>

void vSenderTask( void *pvParameters );
void  vReceiverTask( void *pvParameters );

QueueHandle_t xQueue;


void setup() 
{

  xQueue = xQueueCreate( 5, sizeof( int32_t ) );
  if( xQueue != NULL )
  {

  //BaseType_t türünde değer döndüren görevler  
   xTaskCreate( 
     vReceiverTask
      ,  "vReceiverTask"   // A name just for humans
      ,  128  // Stack size
      ,  NULL
      ,  3  // priority
      ,  NULL );
    xTaskCreate( 
     vSenderTask
      ,  "sender1"   // A name just for humans
      ,  128  // Stack size
      , 100 //parametre değeri
      ,  1  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      , "sender2"   // A name just for humans
      ,  128  // Stack size
      ,   150//parametre
      ,  1  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      , "sender3"   // A name just for humans
      ,  128  // Stack size
      ,  200
      ,  1  // priority
      ,  NULL );
       xTaskCreate( 
     vSenderTask
      ,  "sender4"   // A name just for humans
      ,  128  // Stack size
      ,  1000
      ,  1  // priority
      ,  NULL );
   
   

   
      vTaskStartScheduler();
  }
  else
  {
     Serial.begin(9600);
    Serial.print("Kuyruk oluşmadı");
  }
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
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
  
  //Değişken tanımları
  
  int32_t IValueToSend;
  BaseType_t xStatus;
  IValueToSend=(int32_t) pvParameters;
  Serial.begin(9600);

  for (;;) // 
  {
    xStatus=xQueueSendToBack(xQueue, &IValueToSend, 0); //son parametre bekleme süresidir. 0 doğrudan dönmeyi sağlar.

    if(xStatus!=pdPASS)//if (xStatus==errQUEUE_FUL) //veri yazılmazsa
    {
      Serial.println("Kuyruğa gönderilemedi");
    }
    else
    {
      Serial.print("Gönderilen=");
      Serial.println(IValueToSend);
    }
    taskYIELD();//bekle diğer görevi bekle
  }
}
void vReceiverTask(void *pvParameters)  // This is a task.
{
  
  //Değişken tanımları
  
  int32_t IReceivedValue;
  BaseType_t xStatus;
  const TickType_t xTicksToWait=pdMS_TO_TICKS(1000);
  
  
  
Serial.begin(9600);
  for (;;) // 
  {
    if( uxQueueMessagesWaiting( xQueue ) != 0 )
      {
        Serial.println("Kuyruk boş olmalı");
        
      }
      xStatus = xQueueReceive( xQueue, &IReceivedValue, xTicksToWait );
      if( xStatus == pdPASS )
      {

        Serial.print( "Received = ");
        Serial.println(IReceivedValue);
      }
      else
      {

        Serial.println( "Kuyruktan alınamadı.\r\n" );
      }
     taskYIELD();
  }
}