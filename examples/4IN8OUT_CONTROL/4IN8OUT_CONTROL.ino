#include <M5Stack.h>
#include "MODULE_4IN8OUT.h"

MODULE_4IN8OUT module;

void setup() {
    M5.begin();  // Init M5Stack.  初始化M5Stack
    while (!module.begin(&Wire, 21, 22, MODULE_4IN8OUT_ADDR)) {
        Serial.println("4IN8OUT INIT ERROR");
        M5.Lcd.println("4IN8OUT INIT ERROR");
        delay(1000);
    };
    Serial.println("4IN8OUT INIT SUCCESS");
}

long interval = 0;
bool level    = false;

void loop() {
    for (uint8_t i = 0; i < 4; i++) {
        if (module.getInput(i) == 1) {
            M5.Lcd.fillRect(60 + 60 * i, 0, 25, 25, TFT_BLACK);
            M5.Lcd.fillRect(60 + 60 * i, 0, 25, 25, TFT_BLUE);
        } else {
            M5.Lcd.fillRect(60 + 60 * i, 0, 25, 25, TFT_BLACK);
            M5.Lcd.drawRect(60 + 60 * i, 0, 25, 25, TFT_BLUE);
        }
        M5.Lcd.drawString("IN" + String(i), 40 + 60 * i, 5);
    }
    M5.Lcd.drawString("4IN8OUT MODULE", 60, 80, 4);
    M5.Lcd.drawString("FW VERSION:" + String(module.getVersion()), 70, 120, 4);
    if (millis() - interval > 1000) {
        interval = millis();
        level    = !level;
        for (uint8_t i = 0; i < 8; i++) {
            module.setOutput(i, level);
            if (level) {
                M5.Lcd.fillRect(20 + 35 * i, 200, 25, 25, TFT_BLACK);
                M5.Lcd.fillRect(20 + 35 * i, 200, 25, 25, TFT_GREEN);
            } else {
                M5.Lcd.fillRect(20 + 35 * i, 200, 25, 25, TFT_BLACK);
                M5.Lcd.drawRect(20 + 35 * i, 200, 25, 25, TFT_GREEN);
            }
            M5.Lcd.drawString("OUT" + String(i), 18 + 35 * i, 180);
            delay(50);
        }
    }
    // if (M5.BtnB.wasPressed()) {
    //     if (module.setDeviceAddr(0x66)) {
    //         Serial.println("Update Addr: 0x66");
    //     }
    // }
    // M5.update();
}
