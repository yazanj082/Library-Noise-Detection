#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
 String ssid = "";
 String password = "";
const uint16_t port = 4567;
 char * host = "192.168.1.109";
 String ID="";
 bool loop1=true;
 WiFiClient client;
void setup() {
  
 Serial.begin(115200);
 
 client.setNoDelay(true);





 while(loop1){
  if(Serial.available()){
    
     String Recive =  Serial.readString();
        Recive.replace("\n","");
        String s=Recive;
        ssid=getValue(s, '$', 0);
        password=getValue(s, '$', 1);
        ID =getValue(s, '$', 2);
        serialFlush();
        Serial.print(s);
        Serial.print("\n");
        loop1=false;
           
          
  }
  }


 
   WiFi.begin(ssid,password);
 
 // Serial.print("WiFi connected with IP: ");
  //Serial.println(WiFi.localIP());
 
}


void loop() {


  if(Serial.available()){
  //if(true){
        String Recive =  Serial.readString();
        Recive.replace("\n","");
       if(Recive == "0"){
         serialFlush();
        Serial.print("1");
        Serial.print("\n");
        //if(true){
        if (!client.connect(host, port))
  {
   
    delay(1000);}
        
 client.print(ID);
 delay(10000);
    }
    }
          
          }

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}
          
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
