/**
 * Copyright (C) 2021
 * Christian Fischer
 *
 * https://github.com/ChristianFischer/lichtlein
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "animators/ColorLoopAnimator.h"

#include "Color.h"
#include "LightBar.h"
#include "LightBarBuilder.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


using namespace lichtlein;

static constexpr uint16_t MAX_LIGHTS = 60;

Adafruit_NeoPixel pixels(MAX_LIGHTS, 2);

LightBar* light_bar = nullptr;
Animator* animator  = nullptr;



void setup() {
	if (light_bar == nullptr) {
		light_bar = LightBarBuilder()
				.setLightCount(MAX_LIGHTS)
				.finish()
		;
	}

	if (animator == nullptr) {
		animator = ColorLoopAnimator::makeRainbowLoopAnimator();
		light_bar->acquireLayer(animator, 0);
	}

	pixels.begin();
	pixels.setBrightness(16);
}


void loop() {
	uint32_t time = 50;

	light_bar->update(time);
	const auto& colors = light_bar->getFinalColors();

	for(size_t i=0; i<MAX_LIGHTS; i++) {
		pixels.setPixelColor(i, colors[i].wrgb);
	}

	pixels.show();

	delay(time);
}