

/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <Adafruit_NeoPixel.h>
const int NUM_SLIDERS = 5;
#define NUMPIXELS 5
#define PIN 7  
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int analogSliderValues[NUM_SLIDERS];
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobMaster(4,11);
Encoder knobDiscord(2 , 6);
Encoder knobChrome(12,8);
Encoder knobGaming(14,9);
Encoder knobMusic(10, 5);
int Master, Discord, Chrome, Gaming, Music;
int masterMute, discordMute, chromeMute, gamingMute, musicMute;
int masterDebounceTime;
//   avoid using pins with LEDs attached
//buttons: 1, A5, A2, A1, A6
const int masterButton=1;
const int discordButton=A5;
const int chromeButton=A2;
const int gamingButton=A1;
const int musicButton=A6;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 175;    // the debounce time; increase if the output flickers

int masterState=0;
int discordState=0;
int chromeState=0;
int gamingState=0;
int musicState=0;





void setup() {
  
  Serial.begin(9600);
  pinMode(masterButton, INPUT_PULLUP);
  pinMode(discordButton, INPUT_PULLUP);
  pinMode(chromeButton, INPUT_PULLUP);
  pinMode(gamingButton, INPUT_PULLUP);
  pinMode(musicButton, INPUT_PULLUP);
  
analogSliderValues[0]  = 512;
knobMaster.write(51);
analogSliderValues[1] = 512;
knobDiscord.write(51);
analogSliderValues[2] = 512;
knobChrome.write(51);
analogSliderValues[3] = 512;
knobGaming.write(51);
analogSliderValues[4] = 512;
knobMusic.write(51);
pixels.begin();
pixels.clear(); 
masterMute=0;
discordMute=0;
chromeMute=0;
gamingMute=0;
musicMute=0;
}



void loop() {
  
  Master = knobMaster.read();
  Discord = knobDiscord.read();
  Chrome = knobChrome.read();
  Gaming = knobGaming.read();
  Music = knobMusic.read();



checkButtons();
checkEncoders();
sendSliderValues();
//printSliderValues();//debug
pixels.show();   
 

}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}
void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
void checkButtons(){
if (digitalRead(masterButton)==0 && masterState ==0){
masterMute = !masterMute ;
masterState =1;
delay(25);
}
 if (digitalRead(masterButton)==1){
  masterState=0;
 }
if (digitalRead(discordButton)==0 && discordState ==0){
discordMute = !discordMute ;
discordState =1;
delay(25);
}
 if (digitalRead(discordButton)==1){
  discordState=0;
 }
 if (digitalRead(chromeButton)==0 && chromeState ==0){
chromeMute = !chromeMute ;
chromeState =1;
delay(25);
}
 if (digitalRead(chromeButton)==1){
  chromeState=0;
 }
 if (digitalRead(gamingButton)==0 && gamingState ==0){
gamingMute = !gamingMute ;
gamingState =1;
delay(25);
}
 if (digitalRead(gamingButton)==1){
  gamingState=0;
 }
 if (digitalRead(musicButton)==0 && musicState ==0){
musicMute = !musicMute ;
musicState =1;
delay(25);
}
 if (digitalRead(musicButton)==1){
  musicState=0;
 }
}
void checkEncoders(){
      if (Master > 0 && Master < 102 && masterMute==0){
        analogSliderValues[0]=Master*10;
        pixels.setPixelColor(4, pixels.Color(0, 150, 0));
     
    }
    else if (masterMute==0 && (Master > 102 || Master==102)){
        analogSliderValues[0]=102*10;
        knobMaster.write(102);
        pixels.setPixelColor(4, pixels.Color(0, 150, 0));
        
    }
    else if (masterMute==1){
      analogSliderValues[0]=0;
        pixels.setPixelColor(4, pixels.Color(150, 0, 0));
        
    }
    
    else {
        analogSliderValues[0]=0;
        knobMaster.write(0);
        pixels.setPixelColor(4, pixels.Color(150, 0, 0));
        
    }
  
    if (Discord > 0 && (Discord < 102 && discordMute==0)){
        analogSliderValues[1]=Discord*10;
        pixels.setPixelColor(3, pixels.Color(0, 150, 0));
    }
    else if (discordMute==0 && Discord > 102 || Discord==102){
        analogSliderValues[1]=102*10;
        knobDiscord.write(102);
        pixels.setPixelColor(3, pixels.Color(0, 150, 0));
    }
    else if (discordMute==1){
        analogSliderValues[1]=0;
        pixels.setPixelColor(3, pixels.Color(150, 0, 0));
    }
    else {
        analogSliderValues[1]=0;
        knobDiscord.write(0);
        pixels.setPixelColor(3, pixels.Color(150, 0, 0));
    }
    if (chromeMute==0 && Chrome > 0 && Chrome < 102){
        analogSliderValues[2]=Chrome*10;
        pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    }
    else if (chromeMute ==0 && (Chrome > 102 || Chrome==102)){
        analogSliderValues[2]=102*10;
        knobChrome.write(102);
        pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    }
    else if (chromeMute==1){
        analogSliderValues[2]=0;
        pixels.setPixelColor(2, pixels.Color(150, 0, 0));
    }
    else {
        analogSliderValues[2]=0;
        knobChrome.write(0);
        pixels.setPixelColor(2, pixels.Color(150, 0, 0));
    }
        if (gamingMute==0 && Gaming > 0 && Gaming < 102){
        analogSliderValues[3]=Gaming*10;
        pixels.setPixelColor(1, pixels.Color(0, 150, 0));
        
    }
    else if (gamingMute==0 && (Gaming > 102 || Gaming==102)){
        analogSliderValues[3]=102*10;
        knobGaming.write(102);
        pixels.setPixelColor(1, pixels.Color(0, 150, 0));
    }
    else if (gamingMute==1){
        analogSliderValues[3]=0;
        pixels.setPixelColor(1, pixels.Color(150, 0, 0));
    }
    else {
        analogSliderValues[3]=0;
        knobGaming.write(0);
        pixels.setPixelColor(1, pixels.Color(150, 0, 0));
    }
    if (musicMute==0 && Music > 0 && Music < 102){
      analogSliderValues[4]=Music*10;
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
   }
    else if (musicMute ==0 && (Music > 102 || Music==102)){
        analogSliderValues[4]=102*10;
        knobMusic.write(102);
        pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    }
    else if (musicMute==1){
        analogSliderValues[4]=0;
        pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    }
    else {
        analogSliderValues[4]=0;
        knobMusic.write(0);
        pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    }

}
