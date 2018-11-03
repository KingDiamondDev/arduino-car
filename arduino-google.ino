#include <SPI.h>
#include <WiFi101.h>
#include "Keyboard.h"

char ssid[] = "www.KingDiamondDev.tech"; 
char pass[] = "your wifi password";
int keyIndex = 0;      
int ledPin = 6;
bool val = true;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
  Serial.begin(9600);  
  Keyboard.begin();  
  Serial.print("Start Serial ");
  pinMode(ledPin, OUTPUT); 
  Serial.print("WiFi101 shield: ");
  
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  
  while ( status != WL_CONNECTED) {
    digitalWrite(ledPin, LOW);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                
    digitalWrite(ledPin, HIGH);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();                          
  printWifiStatus();                      
  digitalWrite(ledPin, HIGH);
}

void loop() {
  WiFiClient client = server.available();  

  if (client) {                           
    Serial.println("new client");       
    String currentLine = "";              
    while (client.connected()) 
    {       
      if (client.available()) 
      {           
        char c = client.read();          
        Serial.write(c);                 
        if (c == '\n') 
        {                 

    if (currentLine.length() == 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("OK");
    client.println("<br><br>");
    client.println("<a href=\"/forward\"\"><button>Move Forward </button></a>");
    client.print("<a href=\"/left\"\"><button>Rotate Left </button></a>");
    client.print("<a href=\"/stop\"\"><button>Stop </button></a>");
    client.print("<a href=\"/right\"\"><button>Rotate Right </button></a>");
    client.println("<a href=\"/backward\"\"><button>Move Backward </button></a><br />");
    client.println("</html>");
    client.println();
    break;
          }
     else {   
            currentLine = "";
          }
        }
        else if (c != '\r') {   
          currentLine += c;   
        }
   
        if (currentLine.endsWith("GET /forward")) {
        forward();
        }
        else if (currentLine.endsWith("GET /backward")) {
             backward();
        }
        else if (currentLine.endsWith("GET /stop")) {
             stop();
        }
        else if (currentLine.endsWith("GET /right")) {
          right();         
        }
        else if (currentLine.endsWith("GET /left")) 
        {
          left();       
        }
       
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() 
{

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void forward()
{
digitalWrite(10, HIGH);
digitalWrite(11, LOW);
digitalWrite(12, HIGH);
digitalWrite(13, LOW);
digitalWrite(ledPin, HIGH);
Serial.println(" Moving Forward");

}
void backward()
{
digitalWrite(10, LOW);
digitalWrite(11, HIGH);
digitalWrite(12, LOW);
digitalWrite(13, HIGH);
digitalWrite(ledPin, HIGH);
Serial.println("Moving Backward");
}
void stop()
{
digitalWrite(10, LOW);
digitalWrite(11, LOW);
digitalWrite(12, LOW);
digitalWrite(13, LOW);
digitalWrite(ledPin, LOW);
Serial.println("Stop");
}
void left()
{
digitalWrite(10, HIGH);
digitalWrite(11, LOW);
digitalWrite(12, LOW);
digitalWrite(13, HIGH);
digitalWrite(ledPin, HIGH);
Serial.println(" Rotate Left");
}
void right()
{
digitalWrite(10, LOW);
digitalWrite(11, HIGH);
digitalWrite(12, HIGH);
digitalWrite(13, LOW);
digitalWrite(ledPin, HIGH);
Serial.println(" Rotate Right");
}
