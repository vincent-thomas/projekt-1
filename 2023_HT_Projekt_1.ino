#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();


float total_seconds = 0;


float totalAcceleration = 0;

float total;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  if (!accel.begin()) {
    Serial.println("No valid sensor found");
    while (1)
      ;
  }
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
}


void loop() {
  float y = getY();
  float x = getX();
  float z = getZ();

  Serial.println("X: " + String(x) + " y " + String(y) + " z " + String(z));

  // Vinkel X
  int vinkel_x = round(toDeg(atan(x / z)));


  // Serial.println(tan(toRad(vinkel_x)*x));











  // double baseAcceleration = sqrt(pow(x, 2)+pow(y, 2));
  // RtcDateTime currentMoment = Rtc.GetDateTime();

  //  totalAcceleration += baseAcceleration;


  // Serial.println("base: " + String(baseAcceleration) + " Y: " + String(y) + " X: " + String(x) + " Z: " + String(z));

  //total_seconds = millis() / 1000;
  //Serial.println(String(total_seconds) + " " + String(totalAcceleration));



  delay(1000);

  // Serial.println("hastighet " + String(totalAcceleration * total_seconds));
}

int pi = 3.14159265;

float toRad(float deg) {
  return deg * pi / 180;
}

float toDeg(float rad) {
  return rad * 180 / pi;
}

float getX() {
  sensors_event_t event;
  accel.getEvent(&event);
  float cords = event.acceleration.x;
  return cords;
}
float getY() {
  sensors_event_t event;
  accel.getEvent(&event);
  float cords = event.acceleration.y;
  return cords;
}
float getZ() {
  sensors_event_t event;
  accel.getEvent(&event);
  float cords = event.acceleration.z;
  return cords;
}

char *uint64_to_string(uint64_t input) {
  static char result[21] = "";
  // Clear result from any leftover digits from previous function call.
  memset(&result[0], 0, sizeof(result));
  // temp is used as a temporary result storage to prevent sprintf bugs.
  char temp[21] = "";
  char c;
  uint8_t base = 10;

  while (input) {
    int num = input % base;
    input /= base;
    c = '0' + num;

    sprintf(temp, "%c%s", c, result);
    strcpy(result, temp);
  }
  return result;
}

float asin(float c) {

  float out;

  out = ((c + (c * c * c) / 6 + (3 * c * c * c * c * c) / 40 + (5 * c * c * c * c * c * c * c) / 112 +

          (35 * c * c * c * c * c * c * c * c * c) / 1152 + (c * c * c * c * c * c * c * c * c * c * c * 0.022) +

          (c * c * c * c * c * c * c * c * c * c * c * c * c * .0173) + (c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * .0139) +

          (c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * 0.0115) + (c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * c * 0.01)

            ));

  //asin

  if (c >= .96 && c < .97) { out = 1.287 + (3.82 * (c - .96)); }

  if (c >= .97 && c < .98) { out = (1.325 + 4.5 * (c - .97)); }  // arcsin

  if (c >= .98 && c < .99) { out = (1.37 + 6 * (c - .98)); }

  if (c >= .99 && c <= 1) { out = (1.43 + 14 * (c - .99)); }

  return out;
}

float acos(float c)

{
  float out;

  out = asin(sqrt(1 - c * c));

  return out;
}

float atan(float c)

{
  float out;

  out = asin(c / (sqrt(1 + c * c)));

  return out;
}