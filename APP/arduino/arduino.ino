
#include <SPI.h>
#include <SD.h>
File myFile;


int signal=A0;
int red=5;
int yellow=6;
int green=3;
int lvl1=50;
int lvl2=80;
int lvl3=100;
long gtime=0;
long ytime=0;
long rtime=0;
long redGlowTime=0;
int count=0;


void setup() {

  pinMode(signal,INPUT);
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(yellow,OUTPUT);
  // put your setup code here, to run once:


  
  Serial.begin(115200);
if (!SD.begin(10)) {
//Serial.println("initialization failed!");
while (1);
}
myFile = SD.open("conf.txt");
if (myFile) {
//Serial.println("conf.txt:");
// read from the file until there's nothing else in it:

  serialFlush();
  String s=readLine();
 
Serial.print(s);
Serial.print("\n");
 while(true){
      if(Serial.available()){
        String Recive =  Serial.readString();
        Recive.replace("\n","");
      
          serialFlush();
         
           delay(2000);
           
          break;
      }
 }
serialFlush();

// close the file:
myFile.close();
} else {
// if the file didn't open, print an error:
//Serial.println("error opening test.txt");
}

//
}


void loop() {
// nothing happens after setup
if(millis()>gtime){
  
  digitalWrite(green,LOW);
  }
  if(millis()>rtime){
  digitalWrite(red,LOW);
 
  }
   if(millis()>ytime){
 digitalWrite(yellow,LOW);
 
  }
  

int value=analogRead(signal);
 value-=256;
//Serial.println(value);
  if(value>lvl3){
    count++;
   // Serial.println(count);
    //digitalWrite(red,HIGH);
    //rtime=millis()+10000;
    }
     if(value>lvl2){
    digitalWrite(yellow,HIGH);
    ytime=millis()+2000;}
     if(value>lvl1){
    digitalWrite(green,HIGH);
    gtime=millis()+2000;}
    if(redGlowTime+20000>millis()){
      if(count>0){
        digitalWrite(red,HIGH);
        rtime=millis()+10000;
        count=0;
        serialFlush();
        Serial.print("0");
         Serial.print("\n");
          while(true){
      if(Serial.available()){
        String Recive =  Serial.readString();
        Recive.replace("\n","");
      
          serialFlush();
         
           delay(2000);
           
          break;
      }
 }
serialFlush();
       
        
        redGlowTime=millis();
        }
        
      }
      else{ count=0;
      //Serial.println("reset");
        redGlowTime=millis();}
    delay(10);
}


void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}
String readLine() { 
  String received = ""; char ch; while (myFile.available()) {

ch = myFile.read();

if (ch == '\n') { return String(received);

} else {

received += ch; } } return ""; }
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
