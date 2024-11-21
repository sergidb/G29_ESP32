#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Screen configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64  // Changed to 64 for more vertical space
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Constants
const int pinVN = 39;  // X Axis
const int pinVP = 36;  // Y Axis
const int pinD2 = 2;   // Reverse gear

void setup() {
  Serial.begin(115200);
  pinMode(pinD2, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int yValue = analogRead(pinVN);
  int xValue = analogRead(pinVP);
  int reverseGear = digitalRead(pinD2);

  String selectedGear = getGearPosition(xValue, yValue, reverseGear);
  
  // Update screen
  display.clearDisplay();
  display.setTextSize(4);  // Larger text
  
  // Center the text
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(selectedGear, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;
  
  display.setCursor(x, y);
  display.println(selectedGear);
  display.display();

  delay(50);
}

String getGearPosition(int xValue, int yValue, int reverseGear) {
  if (reverseGear == 1 && xValue > 4000 && yValue < 1000) {
    return "R";
  } else if (xValue < 2000 && yValue > 3500) {
    return "1";
  } else if (xValue < 2000 && yValue < 1000) {
    return "2";
  } else if (xValue > 2100 && xValue < 3800 && yValue > 3500) {
    return "3";
  } else if (xValue > 2100 && xValue < 3800 && yValue < 1000) {
    return "4";
  } else if (xValue > 4000 && yValue > 3500) {
    return "5";
  } else if (xValue > 4000 && yValue < 1000) {
    return "6";
  } else if (yValue > 1000 && yValue < 3500) {
    return "N";
  }
  return "?";
}
