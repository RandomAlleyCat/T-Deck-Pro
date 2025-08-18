#include "Arduino.h"
#include "esp_sleep.h"
#include "ui_deckpro_port.h"
#include "factory.h"
#include "utilities.h"

void ui_disp_full_refr(void)
{
    disp_full_refr();
}

void ui_shutdown_on(void)
{
    PPM.shutdown();
    Serial.println("Shutdown .....");
}

void ui_sleep_on(void)
{
    Serial.println("Sleep .....");
    esp_light_sleep_start();
}
