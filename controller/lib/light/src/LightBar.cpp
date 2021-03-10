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

#include "LightBar.h"
#include "LightBarBuilder.h"


namespace lichtlein {

	LightBar::~LightBar() {
		dispose();
	}


	void LightBar::setup(size_t lights) {
		this->light_count = lights;
		this->final_colors.resize(lights);
	}


	void LightBar::dispose() {
		for(auto& layer : this->layers) {
			delete layer;
		}

		this->layers.clear();
	}


	Layer* LightBar::acquireLayer(uint32_t sort_key) {
		return acquireLayer(nullptr, sort_key);
	}


	Layer* LightBar::acquireLayer(Animator* animator, uint32_t sort_key) {
		auto* layer = new Layer(this, animator, sort_key);
		this->layers.push_back(layer);

		// layers need to be sorted
		sortLayers();

		return layer;
	}


	void LightBar::freeLayer(Layer* layer) {
		// remove the layer from the layers list
		for(auto it=this->layers.begin(); it!=layers.end();) {
			if (*it == layer) {
				it = this->layers.erase(it);
			}
			else {
				++it;
			}
		}

		// finally delete the layer
		delete layer;
	}


	void LightBar::update(uint32_t dt) {
		for(auto& layer : this->layers) {
			// update the layer
			layer->update(dt);

			// copy the layer's color information into the final colors list
			for(size_t i=0; i<this->light_count; i++) {
				this->final_colors[i] = layer->getColors()[i];
			}
		}
	}


	void LightBar::sortLayers() {
		std::sort(
				this->layers.begin(),
				this->layers.end(),
				[](const Layer* a, const Layer* b) -> bool {
					return a->sort_key < b->sort_key;
				}
		);
	}
}