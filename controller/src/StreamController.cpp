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

#include "StreamController.h"

#include "util/SerialCommUtils.h"
#include "LightBar.h"


namespace lichtlein {

	void StreamController::init(LightBar* light_bar) {
		this->light_bar = light_bar;
	}


	void StreamController::update(uint32_t dt) {
		if (stream_layer) {
			// disable the layer, if no color information was received for some time
			if ((last_signal += dt) >= 1000) {
				disable();
			}
		}
	}


	void StreamController::readColorStreamFromSerial() {
		auto* layer        = getOrCreateLayer();
		auto  layer_colors = layer->getLightBar()->getLightCount();

		uint16_t num_colors;
		readSerial(&num_colors);

		for(uint16_t i=0; i<num_colors; i++) {
			if (i < layer_colors) {
				auto* color = layer->getColorRawPtr(i);
				readSerial(&color->r);
				readSerial(&color->g);
				readSerial(&color->b);
			}
			else {
				// skip data
				Serial.read();
				Serial.read();
				Serial.read();
			}
		}

		resetLastSignal();
	}


	Layer* StreamController::getOrCreateLayer() {
		if (stream_layer == nullptr) {
			stream_layer = light_bar->acquireLayer(100);
		}

		return stream_layer;
	}


	void StreamController::disable() {
		if (stream_layer) {
			light_bar->freeLayer(stream_layer);
			stream_layer = nullptr;
		}
	}


	void StreamController::resetLastSignal() {
		this->last_signal = 0;
	}

}
