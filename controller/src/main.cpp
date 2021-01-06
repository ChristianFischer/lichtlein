#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../lib/light/src/Color.h"


using namespace lichtlein;

static constexpr uint16_t MAX_LIGHTS = 60;

Adafruit_NeoPixel pixels(MAX_LIGHTS, 2);



void setup() {
	pixels.begin();
	pixels.setBrightness(16);
}

void loop() {
	// write your code here
	Color color(0xff0000);

	pixels.fill(color.wrgb, 0, MAX_LIGHTS);
	pixels.show();
}