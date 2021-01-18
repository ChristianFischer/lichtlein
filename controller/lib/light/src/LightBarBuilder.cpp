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

#include "LightBarBuilder.h"

namespace lichtlein {

	LightBarBuilder::LightBarBuilder() {
		this->light_bar = new lichtlein::LightBar();
	}


	LightBarBuilder& LightBarBuilder::setLightCount(unsigned int light_count) {
		this->light_count = light_count;
		return *this;
	}


	lichtlein::LightBar* LightBarBuilder::finish() {
		this->light_bar->setup(this->light_count);

		auto* result = this->light_bar;
		this->light_bar = nullptr;

		return result;
	}

}
