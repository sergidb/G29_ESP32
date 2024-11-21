#include <BleGamepad.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Screen configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Constants for pins
const int pinVN = 39;  // X Axis
const int pinVP = 36;  // Y Axis
const int pinD2 = 2;   // Reverse gear

// BLE Gamepad configuration
BleGamepad bleGamepad("G29 shifter", "DIGIT4L", 100);

// Add these defines after the others
#define BT_ICON_WIDTH 8
#define BT_ICON_HEIGHT 8

// Global variable to store the last gear sent
String lastGear = "N";

// Define the Bluetooth icon (8x8 pixels)
static const unsigned char PROGMEM bluetooth_icon[] = {
  B00010000,
  B00011000,
  B10010100,
  B01011000,
  B00110100,
  B01011000,
  B10010100,
  B00011000
};

void setup() {
  Serial.begin(115200);
  pinMode(pinD2, INPUT);

  // Initialize the screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialize BLE Gamepad with 7 buttons
  BleGamepadConfiguration config;
  config.setButtonCount(7);
  bleGamepad.begin(&config);
  Serial.println("BLE Gamepad active with name: G29 shifter");
}

void loop() {
  int yValue = analogRead(pinVN);
  int xValue = analogRead(pinVP);
  int reverseGear = digitalRead(pinD2);

  String selectedGear = getGearPosition(xValue, yValue, reverseGear);
  
  // Update BLE buttons if connected
  if (bleGamepad.isConnected()) {
    updateBleButtons(selectedGear);
  }

  // Update the screen
  display.clearDisplay();
  
  // Draw the Bluetooth icon if connected
  if (bleGamepad.isConnected()) {
    display.drawBitmap(2, 2, bluetooth_icon, BT_ICON_WIDTH, BT_ICON_HEIGHT, SSD1306_WHITE);
  }
  
  // Show the gear
  display.setTextSize(4);
  
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

void updateBleButtons(String gear) {
  // If the gear has not changed, do nothing
  if (gear == lastGear) {
    return;
  }
  
  // Release all buttons only if we have changed gear
  for (int i = 1; i <= 7; i++) {
    bleGamepad.release(i);
  }
  
  // Activate the button corresponding to the current gear
  if (gear == "1") bleGamepad.press(1);
  else if (gear == "2") bleGamepad.press(2);
  else if (gear == "3") bleGamepad.press(3);
  else if (gear == "4") bleGamepad.press(4);
  else if (gear == "5") bleGamepad.press(5);
  else if (gear == "6") bleGamepad.press(6);
  else if (gear == "R") bleGamepad.press(7);
  
  bleGamepad.sendReport();
  
  // Update the last gear sent
  lastGear = gear;
}