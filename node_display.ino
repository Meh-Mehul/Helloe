/*
 * This intend to connect to a Wifi Access Point
 * and a rosserial socket server.
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 *
 */
bool firstiter = true;
#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid     = "--your-ssid--"; // <=============================================PUT UR SSID AND PASSWORD HERE
const char* password = "--your-password--";
// Set the rosserial socket server IP address
IPAddress server(192,168,0,1); // <================================================== PUT UR IP HERE
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
void messageCb( const std_msgs::String& msg){
  display.clearDisplay();
  String data = msg.data;
  Serial.println(data);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println(data);
  display.display();
  delay(1000);
  display.clearDisplay();

     // blink the led
}
// ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<std_msgs::String> sub("chatter", messageCb );


void setup()
{
  
  // Use ESP8266 serial to monitor the process
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect the ESP8266 the the wifi AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.subscribe(sub);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Hello world!");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop()
{
  
  if (nh.connected()) {

    if(firstiter){
    Serial.println("Connected");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.println("Connected");
    display.display();
    delay(2000);
    firstiter = false;

    }
    // Say hello
  } else {
    Serial.println("Not Connected");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.println("Not Connected");
    display.display();
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(1000);
}
