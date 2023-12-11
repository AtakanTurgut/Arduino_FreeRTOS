#include <Arduino_FreeRTOS.h>

void vGorev1(void *pvParameters);
void vGorev2(void *pvParameters);
void vGorev3(void *pvParameters);
void vGorev4(void *pvParameters);
bool durum = false;

void setup()
{
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  xTaskCreate(vGorev1,
              "Gorev 1",
              100,
              NULL,
              1,
              NULL);
  xTaskCreate(vGorev2,
              "Gorev 2",
              100,
              NULL,
              2,
              NULL);
  xTaskCreate(vGorev3,
              "Gorev 3",
              100,
              NULL,
              3,
              NULL);
  xTaskCreate(vGorev4,
              "Gorev 4",
              100,
              NULL,
              4,
              NULL);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void vGorev1(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    digitalWrite(2, HIGH);

    Serial.println("Görev1");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(2, LOW);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

void vGorev2(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    digitalWrite(3, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(3, HIGH);

    Serial.println("Görev2");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(3, LOW);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void vGorev3(void *pvParameters)
{
  Serial.begin(9600);
  (void)pvParameters;
  for (;;)
  {
    digitalWrite(4, LOW);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    digitalWrite(4, HIGH);

    Serial.println("Görev3");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(4, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vGorev4(void *pvParameters)
{
  Serial.begin(9600);
  (void)pvParameters;
  for (;;)
  {
    digitalWrite(5, LOW);
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    digitalWrite(5, HIGH);

    Serial.println("Görev4");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(5, LOW);
    vTaskDelay(0 / portTICK_PERIOD_MS);
  }
}