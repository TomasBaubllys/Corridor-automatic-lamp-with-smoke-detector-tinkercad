/*
Author: Tomas Baublys
*/

#include <Adafruit_NeoPixel.h>

#define PHOTO_RES_THRESHOLD_VAL 200
#define SMOKE_DET_THRESHOLD_VAL 110
#define DELAY 500
#define NUM_OF_LEDS 12
#define LED_ALARM_R 255
#define LED_ALARM_G 0
#define LED_ALARM_B 0
#define LED_ON_R 255
#define LED_ON_G 255
#define LED_ON_B 200

#define PHOTO_RES_PIN A5
#define SMOKE_DETECTOR_PIN A1
#define PIR_SENSOR_PIN 7
#define P_BUZZER_PIN 2
#define LED_RING_PIN 6

int photo_res_val = 0;
int pir_sensor_val = 0;
int smoke_detector_val = 0;

Adafruit_NeoPixel ring(NUM_OF_LEDS, LED_RING_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  	Serial.begin(9600);
  	pinMode(PIR_SENSOR_PIN, INPUT);
	pinMode(P_BUZZER_PIN, OUTPUT);
	pinMode(LED_RING_PIN, OUTPUT);
  	ring.begin();
  	ring.show();
}

void loop()
{
	photo_res_val = analogRead(PHOTO_RES_PIN);
  	smoke_detector_val = analogRead(SMOKE_DETECTOR_PIN);
  	pir_sensor_val = digitalRead(PIR_SENSOR_PIN);
    	
  	if(smoke_detector_val >= SMOKE_DET_THRESHOLD_VAL){	
		// Serial.println("RED Light and buzzer should be on");
      	tone(P_BUZZER_PIN, 523, DELAY);
        ring.fill(ring.Color(LED_ALARM_R, LED_ALARM_G, LED_ALARM_B), 0, NUM_OF_LEDS);
      	ring.show();
	}
  	else if(photo_res_val <= PHOTO_RES_THRESHOLD_VAL && pir_sensor_val == HIGH) {
  		// Serial.println("Light should be on");
      	ring.fill(ring.Color(LED_ON_R, LED_ON_G, LED_ON_B), 0, NUM_OF_LEDS);
      	ring.show();
    }
  	else {
      	// Serial.println("light should be off");
      	ring.fill(ring.Color(0, 0, 0), 0, NUM_OF_LEDS);
      	ring.show();
    }
  	
  	delay(DELAY);                    
}