#pragma once

#define LED_PIN 2

void ledTaskInit();
extern void ledTask(void *pvParameters);
