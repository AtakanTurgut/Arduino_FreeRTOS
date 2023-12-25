#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).

SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskDigitalRead, (const portCHAR *)"DigitalRead"  // A name just for humans
    ,
    128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 2  // Priority, with 1 being the highest, and 4 being the lowest.
    ,
    NULL);

  xTaskCreate(
    TaskAnalogRead, (const portCHAR *)"AnalogRead", 128  // Stack size
    ,
    NULL, 1  // Priority
    ,
    NULL);
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Görev Tanımları ---------------------*/
/*--------------------------------------------------*/

void TaskDigitalRead(void *pvParameters)  // This is a Task.
{
  uint8_t pushButton = 2;


  pinMode(pushButton, INPUT);

  for (;;) {

    int buttonState = digitalRead(pushButton);

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {

      Serial.println(buttonState);

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelay(1);
  }
}

void TaskAnalogRead(void *pvParameters __attribute__((unused)))  // This is a Task.
{

  for (;;) {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);


    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {

      Serial.println(sensorValue);

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelay(1);
  }
}