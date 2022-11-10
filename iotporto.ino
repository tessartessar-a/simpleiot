
#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>

const char* mqtt_server = "192.168.1.5";

WiFiClient espClient;
PubSubClient client(espClient);

int redpin = 13; //select the pin for the red LED
int bluepin =14; // select the pin for the  blue LED
int greenpin =12;// select the pin for the green LED

void blue_on()
{
  digitalWrite(14, HIGH);
  delay(1000);
   
  
}
void blue_off(){ 
  digitalWrite(14, LOW);
  delay(1000);
}

void red_on(){ 
  digitalWrite(13, HIGH);
  delay(1000);

}
void red_off() { 
  digitalWrite(13, LOW);
  delay(1000);
  
}

void green_on(){ 
  digitalWrite(12, HIGH);
  delay(1000);

}
void green_off(){ 
  digitalWrite(12, LOW);
  delay(1000);
}
void setup_wifi() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

}

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) { 
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println( );

  if(topic == "esp8266/14"){ 
    Serial.print("Blue Time");
    if (messageTemp == "1"){ 
      blue_on();
      Serial.print("on");
    }
    else if(messageTemp == "0"){ 
      blue_off();
      Serial.print("off");
    }
  }
    if(topic == "esp8266/13"){ 
    Serial.print("Red Time");
    if (messageTemp == "1"){ 
      red_on();
      Serial.print("on");
    }
    else if(messageTemp == "0"){ 
      red_off();
      Serial.print("off");
    }
  }

    if(topic == "esp8266/12"){ 
    Serial.print("Green Time");
    if (messageTemp == "1"){ 
      green_on();
      Serial.print("on");
    }
    else if(messageTemp == "0"){ 
      green_off();
      Serial.print("off");
    }
  }


  Serial.println();
  
  
  
  
}

void reconnect() { 
  while (!client.connected()){ 
    Serial.print("Attempting MQTT connection....");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("esp8266/13");
      client.subscribe("esp8266/14");
      client.subscribe("esp8266/12");
      client.subscribe("esp8266/2");
      
    }else{ 
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds ");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
//  servo.attach(2); //D4
//  servo.write(0);
  

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() 
{
  if(!client.connected()) { 
    reconnect();
  }
  if(!client.loop())
  client.connect("ESP8266Client");
}
