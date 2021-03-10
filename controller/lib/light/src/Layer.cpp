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

#include "Layer.h"

#include "Animator.h"
#include "LightBar.h"


namespace lichtlein {

	Layer::Layer(LightBar* parent, Animator* animator, uint32_t sort_key) :
		parent(parent),
		animator(animator),
		sort_key(sort_key)
	{
		this->colors.resize(parent->getLightCount());
	}


	void Layer::setColor(size_t index, Color color) {
		this->colors[index] = color;
	}


	void Layer::setColor(size_t index, size_t count, Color color) {
		for(size_t i=index, end=index+count; i<end; i++) {
			this->colors[i] = color;
		}
	}


	const Color& Layer::getColor(size_t index) const {
		return this->colors[index];
	}


	Color* Layer::getColorRawPtr(size_t index) {
		return &(this->colors[index]);
	}


	void Layer::update(uint32_t dt) {
		if (this->animator) {
			this->animator->update(this, dt);
		}
	}
}
