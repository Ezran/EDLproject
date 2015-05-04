#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define NUM_MENU_OPTS 2

const int LCD_pin = 11; //Pin 12 as LCD connection
int buttonSelect = 6;
int buttonDown = 7;
int buttonUp = 8;
  bool newdata = false;
  int butSelect;  // read input value
  int butDown;  // read input value
  int butUp; // read input value

int menuIndex = 0;
int inUse = LOW;
char* menuOpts[] = {"Trip Mode", "Distance Mode"};
unsigned long start = millis();

TinyGPS gps;
SoftwareSerial LCD_Serial = SoftwareSerial(255, LCD_pin); // RX, TX
SoftwareSerial nss(10, 255);


void setup() {
  Serial.begin(115200);
  LCD_Serial.begin(9600); // Begin serial communication.
  LCD_Serial.write(12); // Clear LCD
  delay(5); // delay after clearing screen
  pinMode(buttonSelect, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonUp, INPUT);
  pinMode(LCD_pin, OUTPUT); // Initialize the digital pin as an output.
  nss.begin(9600); // Communicate at 9600 baud (default for PAM-7Q module)
  Serial.println("Reading GPS");
    LCD_Serial.print("Choose a mode");
}

// Get and process GPS data
void loop() {
  butSelect = digitalRead(buttonSelect);  // read input value
  butDown = digitalRead(buttonDown);  // read input value
  butUp = digitalRead(buttonUp); // read input value
  
  if (inUse == LOW && (butSelect == HIGH || butDown == HIGH || butUp == HIGH)) { //clear on first use
     Serial.println("First use");
     LCD_Serial.write(12);
     LCD_Serial.print(menuOpts[0]);
     inUse = HIGH;
     delay(250);  //debounce delay
   }
   
    else if (butDown == HIGH || butUp == HIGH) {
      Serial.println("Change menu item");
      LCD_Serial.write(12); // Clear LCD
      menuIndex = (menuIndex + 1) % NUM_MENU_OPTS;
      LCD_Serial.print(menuOpts[menuIndex]);
      delay(250);  //debounce delay 
    }
    else if (butSelect == HIGH) {
       Serial.println("Select");
       LCD_Serial.write(12);
       delay(100);
      if (menuIndex == 0) { //------------------ trip mode selected
       LCD_Serial.print("Trip mode selected.");
       delay(1000);
       LCD_Serial.write(12);
       delay(5);
      
       //begin gps code
       tripMode();
      }
       else if (menuIndex == 1) { //------------- distance mode selected
        LCD_Serial.print("Distance mode\n selected.");
        delay(1000);
        LCD_Serial.write(12);
        
        //begin distance gps code
        distMode(); 
      }     
    }
}

void tripMode() {
  float totalDistance = 0;
  float old_lat, old_lon; 
  float new_lat, new_lon;
    
  while(!updateGPS())
      Serial.println("Waiting for init gps data");
  gps.f_get_position(&new_lat,&new_lon);
  
  LCD_Serial.write(12); // Clear LCD
  delay(5);
  LCD_Serial.print("Trip Started");
  delay(2000);
  LCD_Serial.write(12); // Clear LCD
  delay(5);
  LCD_Serial.print("'Select' to end");
  
  for(;;) {
    butSelect = digitalRead(buttonSelect);  // read input value
    while(!updateGPS()){}
      //Serial.println("Waiting for gps data");
      
    old_lat = new_lat; old_lon = new_lon;
    gps.f_get_position(&new_lat, &new_lon);
    
    float delta = TinyGPS::distance_between(old_lat, old_lon, new_lat, new_lon);
    Serial.println(delta);
    Serial.println(totalDistance);
    totalDistance = totalDistance + delta; 
      
      if (butSelect == HIGH){
        LCD_Serial.write(12); // Clear LCD
        delay(5);
      LCD_Serial.println("Total Distance (m)");
      LCD_Serial.print(totalDistance);
      delay(2000);
         while(true){/*end*/}
      }
   }
}

void distMode() {
  while (!updateGPS())
     Serial.println("Waiting for valid start gps data");
  
  float lat1, lon1;
  gps.f_get_position(&lat1, &lon1);
  Serial.println(lat1);
  Serial.println(lon1);
  Serial.println("---------");
  LCD_Serial.print("'Select' to end");
  
  for(;;){
    butSelect = digitalRead(buttonSelect);  // read input value
   
   if (butSelect == HIGH) {
     LCD_Serial.write(12); // Clear LCD
     delay(5);
     float lat2, lon2;
     
     while(!updateGPS())
         Serial.println("Waiting for valid end gps data point");
     
     gps.f_get_position(&lat2, &lon2);
     Serial.println(lat2);
     Serial.println(lon2);
     LCD_Serial.println("Total Distance (m)");
     LCD_Serial.print(TinyGPS::distance_between(lat1, lon1, lat2, lon2)); 
     while(true){/*end*/};
   }
  }
}

//feed gps data if available
bool updateGPS() {
  while (nss.available()){
    if (gps.encode(nss.read()))
      return true;
  }
  return false;
}

// Get and process GPS data
void gpsdump(TinyGPS &gps) {
  float lat1, lon1;
  unsigned long age;
  gps.f_get_position(&lat1, &lon1, &age);
  //Serial.print(flat, 4); Serial.print(", ");
  //Serial.println(flon, 4);
  //  float lat2, lon2;
  //  gps.f_get_position(&lat2, &lon2);
  //  (unsigned long)TinyGPS::distance_between(lat1, lon1, lat2, lon2);
}


/*******************************************************************************
GPS Code
Straight-Line Distance
*******************************************************************************/

//void
//gps.f_get_position(&lat2, &lon2);
//TinyGPS::(distance_Between(lat1, lon1,lat2, lon2)*1.09361);



/*******************************************************************************
GPS Code
Trip Distance
*******************************************************************************/






