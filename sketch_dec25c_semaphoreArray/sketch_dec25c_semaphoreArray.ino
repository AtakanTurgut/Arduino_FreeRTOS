/*
İki periyodik görev içeren bir Arduino kodu  geliştirin. Görev 1, tamsayı türünde 1000 elemanlı
bir diziyi depolamak için paylaşılan bir bellek açar ve tüm elemanları 0  olarak başlatır.
Görev 1, 500 milisaniyede bir diziye 1-100 arasında Rastgele oluşturulan yeni bir değer ekler. 
Diğer yandan Görev 2, her 400 milisaniyede bir diziye eklenen değerlerin sayısını sayar ve sayıyı görüntüler.
*/

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xSerialSemaphore;
SemaphoreHandle_t xDataSemaphore;

int sharedArray[1000];

void TaskAddRandomValue(void *pvParameters);
void TaskCountValues(void *pvParameters);

void setup() {
  Serial.begin(9600);
  xSerialSemaphore = xSemaphoreCreateMutex();
  xDataSemaphore = xSemaphoreCreateMutex();

  if ((xSerialSemaphore != NULL) && (xDataSemaphore != NULL)) {
    xTaskCreate(TaskAddRandomValue, "AddRandomValue", 128, NULL, 1, NULL);
    xTaskCreate(TaskCountValues, "CountValues", 128, NULL, 2, NULL);
  }
}

void loop() {
  // Empty. Tasks handle the work.
}

void TaskAddRandomValue(void *pvParameters) {
  for (;;) {
    // Generate a random value between 1 and 100
    int randomValue = random(1, 101);

    // Access shared array with a semaphore
    if (xSemaphoreTake(xDataSemaphore, (TickType_t)5) == pdTRUE) {
      sharedArray[random(0, 1000)] = randomValue;
      xSemaphoreGive(xDataSemaphore);
    }

    vTaskDelay(500);  // Wait for 500 milliseconds
  }
}
int deneme = 1;
void TaskCountValues(void *pvParameters) {
  for (;;) {
    int count = 0;

    // Count values in the shared array with a semaphore
    if (xSemaphoreTake(xDataSemaphore, (TickType_t)5) == pdTRUE) {
      if (count == 0 && deneme == 1) {
        deneme++;
        Serial.println("Number of values in the array: " + String(count));
      }
      for (int i = 0; i < 1000; ++i) {
        if (sharedArray[i] != 0) {
          Serial.println("Number of values: " + String(sharedArray[i]));
          count++;
        }
      }
      xSemaphoreGive(xDataSemaphore);
    }

    // Print the count with a semaphore
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      Serial.println("Number of values in the array: " + String(count));
      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelay(400);  // Wait for 400 milliseconds
  }
}