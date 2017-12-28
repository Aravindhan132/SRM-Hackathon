#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#include <Adafruit_NeoPixel.h>

// Set these to run example.
#define FIREBASE_HOST "aravind-f6735.firebaseio.com"
#define FIREBASE_AUTH "NMlX8yRVc0oXxVzqrEBBReUIxVDEbSKh4ladftRo"
#define WIFI_SSID "Test"
#define WIFI_PASSWORD "123456789"

const int pixelPin = 13;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(25); // 0 ... 255
  strip.show(); // Initialize all pixels to 'off'

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  // Get all entries.
  // TODO: Replace with streaming
  FirebaseObject pixels = Firebase.get("/rgbdata");
  if (Firebase.failed()) {
      Serial.println("Firebase get failed");
      Serial.println(Firebase.error());
      return;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    int pixel = pixels.getInt(String("pixel") + i);
    strip.setPixelColor(i, pixel);
  }
  strip.show();
  delay(200);
}