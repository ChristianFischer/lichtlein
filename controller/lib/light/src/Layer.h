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

#ifndef __CONTROLLER_LAYER_H__
#define __CONTROLLER_LAYER_H__

#include "Color.h"

#include <stdint.h>
#include <vector>


namespace lichtlein {

	class Animator;
	class LightBar;


	/**
	 * The layer represents the content of a single animation of a light bar.
	 * Each light bar may contain multiple layers of animations with different priorities,
	 * so there could be for example a layer to display a notification animation on top
	 * of all other layers.
	 */
	class Layer
	{
	friend class LightBar;

	public:
		Layer() = delete;

		// disallow copy & move
		Layer(const Layer&) = delete;
		Layer(Layer&&) = delete;

	public:
		/**
		 * Get the LightBar object, this layer is part of.
		 */
		const LightBar* getLightBar() const {
			return this->parent;
		}

		/**
		 * Get the animator, playing animations on this layer.
		 */
		const Animator* getAnimator() const {
			return this->animator;
		}

		/**
		 * Get the layers sort key.
		 */
		uint32_t getSortKey() const {
			return this->sort_key;
		}

		/**
		 * Get this layer's color information.
		 */
		const std::vector<Color>& getColors() const {
			return this->colors;
		}

	public:
		/**
		 * Set a given color for this layer.
		 * @param index The index of the color to be changed
		 * @param color The color to be set on the given index
		 */
		void setColor(size_t index, Color color);

		/**
		 * Set a given color for this layer.
		 * @param index The first index of the color to be changed
		 * @param count The number of colors to be set
		 * @param color The color to be set on the given index
		 */
		void setColor(size_t index, size_t count, Color color);

		/**
		 * Updates this layer's content.
		 * @param dt The time passed in milliseconds
		 */
		void update(uint32_t dt);

	private:
		Layer(LightBar* parent, Animator* animator, uint32_t sort_key);

		LightBar *const parent;
		Animator *const animator;
		const uint32_t sort_key;

		std::vector<Color> colors;
	};

}

#endif //__CONTROLLER_LAYER_H__
