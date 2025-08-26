#include <WiFi.h>
#include <typeinfo>
#include <string.h>
#include <stdio.h>

// SSID and password for the access point
// Ensure that it's a *secret* password to avoid difficulties during running
// Also ensure that your SSID is *unique*. One way to ensure this is to set it to your XLR8 registration number
// MAKE SURE THAT THE PASSWORD IS AT LEAST 8 DIGITS LONG OR THE CODE WON'T WORK
const char* ssid = "Speedaf";
const char* password = "Llamacool";

// Define a structure to hold IMU (Inertial Measurement Unit) data
typedef struct {
  float gx, gy, gz;
} IMUData;

IMUData myMessage; // Create a variable to store received IMU data
int cmd = 0;       // Initialize motor control command variable
int spd = 0;       // Initialize motor speed variable


// Pin assignments for motor control
const int ENA = 8;
const int ENB = 9;

const int IN1 = 10;
const int IN2 = 11;
const int IN3 = 12;
const int IN4 = 13;

// Create a WiFiServer object for the TCP server
WiFiServer server(80);

// Function to update motor control based on received IMU data
// WRITE YOUR CODE IN THIS FUNCTION
void updateMotorControl() {
  float gx = myMessage.gx;
  float gy = myMessage.gy;
  float gz = myMessage.gz;

  /** Apply Motor Control logic based on IMU data
   * 
   * You can use some cool functions like:
   *    constrain()
   *    map()
   *    atan2()
   */
  Serial.println(gx);
  Serial.println(gy);
  Serial.println(gz);


  // Adjust motor speed thresholds. 
  // Ensure that motor speed stays in the range 0 to 255 for PWM output
   



  // Display motor control information (for debugging)
  


}

// WRITE YOUR CODE IN THIS FUNCTION
void applyMotorControl() {
  switch (cmd) {
    case 1:  // Forward

      break;
    case 2:  // Backward

      break;
    case 3:  // Right

      break;
    case 4:  // Left

      break;
    default:  // Stop

      break;
  }

  // Apply the calculated motor speed to both motors
 

}


// MODIFY ONLY IF YOU'RE CONFIDENT
void setup() {
  // Start Serial for debugging
  Serial.begin(115200);
    // Configure motor control pins as outputs
  /

  // Set up the access point
  Serial.println("Setting up WiFi AP...");
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // Start the server
  server.begin();

  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client is connected");
  }

}


// MODIFY ONLY IF YOU'RE CONFIDENT
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  //if (client) {
    //while (client.connected()) {
      if (client.available()) {
        digitalWrite(LED_BUILTIN, HIGH);
        String request = client.readStringUntil('\r');
        Serial.print("Received data: ");
        //Serial.println(request);
        char chararr[50];
        request.toCharArray(chararr, sizeof(chararr));

        Serial.println(chararr);
        char *res;
        float arr[3];
        int i = 0;

        res = strtok(chararr , " ");
        while(res != NULL){
          Serial.println(res);
          String strr = String(res);
          float val = strr.toFloat();
          Serial.println(val);
          res = strtok(NULL, " ");
          arr[i]= val;
          i++;
        }
        myMessage.gx = arr[0];
        myMessage.gy = arr[1];
        myMessage.gz = arr[2];
        //Serial.println("gx");
        //Serial.println(myMessage.gx);

        // Your functions are being called here
        updateMotorControl();
        applyMotorControl();


        digitalWrite(LED_BUILTIN, LOW);}
      digitalWrite(LED_BUILTIN, LOW);
   // Continuously update and apply motor control
  delay(100); // Delay to control loop speed
}
