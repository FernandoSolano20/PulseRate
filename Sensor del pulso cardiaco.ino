#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <MCUFRIEND_kbv.h>
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.
MCUFRIEND_kbv tft;

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GRAY 0x8410

const int PulseWire = 8; // PulseSensor PURPLE WIRE connected to ANALOG PIN 8
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

uint16_t version = MCUFRIEND_KBV_H_;

void setup() {
  Serial.begin(9600);
  if (!Serial) delay(5000);    //allow some time for Leonardo
  uint16_t ID = tft.readID();  //
  tft.begin(ID);
  tft.setRotation(1);
  cleanScreen();

  // Pulse rate
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);  
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
    //Print "YouTube!" text
    createTextBpm();
  }
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
  // Serial.print("Preview BPM: " + myBPM); // Print phrase "BPM: "
  if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
    Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: "); // Print phrase "BPM: "
    Serial.println(myBPM); // Print the value inside of myBPM.
    tft.fillRect(40, 120, 200, 60, BLACK); 
    tft.setCursor(40, 130);
    tft.setTextSize(4);
    tft.setTextColor(RED);
    tft.print("BPM: " + String(myBPM)); // Print phrase "BPM: "
  }  
  delay(20);
}

void cleanScreen() {
  int width = tft.width();
  int height = tft.height();
  tft.fillScreen(BLACK);
  //Draw white frame
  tft.drawRect(0, 0, width, height, WHITE);
}

void createTextBpm() {
  tft.setCursor(20, 40);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Monitor del");
  tft.setCursor(20, 80);
  tft.setTextSize(3);
  tft.print("Pulso cardiaco!");
}