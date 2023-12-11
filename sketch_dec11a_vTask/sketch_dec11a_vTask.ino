#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void setup()
{
  xTaskCreate(
      vTask1,
      "Task 1",
      100,
      NULL,
      1,
      NULL);

  xTaskCreate(
      vTask2,
      "Task 2",
      100,
      NULL,
      2,
      NULL);

  vTaskStartScheduler();
}

void loop()
{
}

void vTask1(void *pvParameters)
{
  (void)pvParameters;
  const char *pcTaskName = "Task1 calisti.";
  Serial.begin(9600);
  for (;;)
  {
    Serial.println(pcTaskName);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTask2(void *pvParameters)
{
  (void)pvParameters;
  const char *pcTaskName = "Task2 calisti.";
  Serial.begin(9600);
  for (;;)
  {
    Serial.println(pcTaskName);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
