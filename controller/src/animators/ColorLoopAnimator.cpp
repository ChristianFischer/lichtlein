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

#include "ColorLoopAnimator.h"

#include "Layer.h"
#include "LightBar.h"


namespace lichtlein {

	static const std::vector<Color> COLOR_TABLE_RAINBOW {
			Color(0x00ff0000),
			Color(0x00ff8000),
			Color(0x00ffff00),
			Color(0x0000ff00),
			Color(0x0000ffff),
			Color(0x000000ff),
	};


	ColorLoopAnimator* ColorLoopAnimator::makeRainbowLoopAnimator() {
		auto* animator = new ColorLoopAnimator();
		animator->setColors(COLOR_TABLE_RAINBOW);

		return animator;
	}


	void ColorLoopAnimator::setColors(const std::vector<Color>& colors) {
		this->color_table = colors;
	}


	void ColorLoopAnimator::setFullLoopTime(uint32_t time) {
		this->full_loop_time = time;
	}


	void ColorLoopAnimator::onUpdate(Layer* layer, uint32_t ms) {
		const size_t light_count = layer->getLightBar()->getLightCount();
		const size_t color_count = this->color_table.size();

		this->offset += ms;
		this->offset %= full_loop_time;

		float loop_offset = 1.0f * this->offset / this->full_loop_time;

		for(size_t i=0; i<light_count; i++) {
			const float position         = (float(i) / light_count) + loop_offset;
			const float rainbow_position = (position * color_count);
			const auto  color_index      = size_t(rainbow_position);
			const float color_offset     = rainbow_position - color_index;
			const Color color1           = this->color_table[(color_index + 0) % color_count];
			const Color color2           = this->color_table[(color_index + 1) % color_count];

			Color c = blend(color1, color2, color_offset);

			layer->setColor(i, c);
		}
	}
}
