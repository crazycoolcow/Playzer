#include <Arduino.h>
#include <WiFi.h>
#include <painlessMesh.h>
#include <IRremoteESP8266.h>
#include <IRsend.h> // For sending IR codes (Transmitting ESP32)
#include <IRrecv.h> // For receiving IR codes (Receiving ESP32)
#include "GameMode.h"

#define builtIN 2 // Esp32 built in led
#define testLED 23 // Im using this pin for an led temporaraly
#define triggerPin 13 // Button for triger
#define MESH_SSID "YourMeshSSID"
#define MESH_PASSWORD "YourMeshPassword"
#define MESH_PORT 5555

painlessMesh mesh;

const int IR_SEND_PIN = 4;  // pin for IR LED
const int IR_RECEIVE_PIN = 5; // pin for IR receiver
IRsend irsend(IR_SEND_PIN);  // Set the GPIO to be used to sending a message
IRrecv irReceiver(IR_RECEIVE_PIN); // Set the GPIO to be used to receiving a message
decode_results results;
uint32_t nodeId = mesh.getNodeId(); // Get the Node ID of the current node

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
  // Handle received data (e.g., game commands or scores)
  // Customize this function for your game logic
}

// To check if a button is pressed
bool ButtonPress(int buttonPin, bool buttonState = false){
  static bool prevButtonState = false; // Static variable to retain the previous state

  buttonState = digitalRead(buttonPin);
  if (buttonState && !prevButtonState) { // Button is pressed
    //Serial.println("Button pressed");
    prevButtonState = buttonState;
    return true;
  }
  else {
    prevButtonState = buttonState;
    return false;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(builtIN, OUTPUT); // Pin 2 is the builtin led on esp32
  pinMode(triggerPin, INPUT_PULLUP);

  pinMode(testLED, OUTPUT); // Im using this pin for an led temporaraly

  // Initialize the IR sender and receiver
  irsend.begin();
  irReceiver.enableIRIn();

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(receivedCallback);
  mesh.onNewConnection([](size_t nodeId) {
    Serial.printf("New connection, nodeId = %u\n", nodeId);
  });
}

void loop() {
  if (ButtonPress(triggerPin)){
      irsend.sendNEC(nodeId);
  }
  if (irReceiver.decode(&results)) {
    // Print the received IR code
    Serial.println(results.value);

    // Send a message to the mesh network indicating a hit
    String hitMessage = String(results.value) + "hit" + String(nodeId);
    mesh.sendBroadcast(hitMessage);
    Serial.println(hitMessage);

    digitalWrite(testLED, HIGH); // Again just led for testing
    delay(3000); // I'm not supposed to have delays when painless mesh is running but this is temporary
    digitalWrite(testLED, LOW);

    irReceiver.resume(); // Receive the next value
    mesh.update();
  }
}