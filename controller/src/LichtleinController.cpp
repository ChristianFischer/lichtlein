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


#include "LichtleinController.h"

#include "animators/ColorLoopAnimator.h"

#include "Animator.h"
#include "LightBarBuilder.h"


namespace lichtlein {

	LichtleinController::LichtleinController() = default;


	LichtleinController::~LichtleinController() {
		dispose();
	}


	void LichtleinController::init() {
		pixels = new Adafruit_NeoPixel(LIGHT_BAR_LED_COUNT, LIGHT_BAR_PIN);
		pixels->setBrightness(16);
		pixels->begin();

		light_bar = LightBarBuilder()
				.setLightCount(LIGHT_BAR_LED_COUNT)
				.finish()
		;

		animator = ColorLoopAnimator::makeRainbowLoopAnimator();
		light_bar->acquireLayer(animator, 0);
	}


	void LichtleinController::dispose() {
		if (animator) {
			delete animator;
			animator = nullptr;
		}

		if (pixels) {
			delete pixels;
			pixels = nullptr;
		}

		if (light_bar) {
			delete light_bar;
			light_bar = nullptr;
		}
	}


	void LichtleinController::update() {
		uint32_t time = UPDATE_TICK_TIME;

		light_bar->update(time);
		const auto& colors = light_bar->getFinalColors();

		for(size_t i=0; i<LIGHT_BAR_LED_COUNT; i++) {
			pixels->setPixelColor(i, colors[i].wrgb);
		}

		pixels->show();

		delay(time);
	}
}
