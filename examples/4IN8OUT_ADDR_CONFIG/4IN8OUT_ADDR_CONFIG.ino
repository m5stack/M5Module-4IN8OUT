
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

void loop() {
    M5.Lcd.drawString("4IN8OUT MODULE", 60, 80, 4);
    M5.Lcd.drawString("FW VERSION:" + String(module.getVersion()), 70, 120, 4);
    M5.Lcd.drawString("Click BtnB Update Addr to 0x66", 60, 160, 2);
    if (M5.BtnB.wasPressed()) {
        if (module.setDeviceAddr(0x66)) {
            Serial.println("Update Addr: 0x66");
            M5.Lcd.drawString("Update Addr: 0x66 success", 60, 200, 2);
        }
    }
    M5.update();
}
