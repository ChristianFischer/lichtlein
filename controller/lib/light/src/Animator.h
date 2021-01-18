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

#ifndef __CONTROLLER_ANIMATION_H__
#define __CONTROLLER_ANIMATION_H__

#include <stdint.h>


namespace lichtlein {

	class Layer;
	class LightBar;


	/**
	 * The animator is an object to store and manage a single animation.
	 * Each animation has to be attached to a single layer of the light bar
	 * to display it's animation.
	 * There is only one animator per layer, but multiple layers can exist
	 * simultaneously inside the light bar to present different animations
	 * with various priorities at the same time.
	 */
	class Animator
	{
	friend class LightBar;

	protected:
		Animator() = default;

	public:
		virtual ~Animator() = default;

		/**
		 * Updates this layer's content.
		 * @param layer The layer, this animator was assigned to
		 * @param dt    The time passed in milliseconds
		 */
		void update(Layer* layer, uint32_t dt);

	protected:
		/**
		 * Called every time this animator shall update it's content.
		 * @param layer The layer, this animator was assigned to
		 * @param dt    The time passed in milliseconds
		 */
		virtual void onUpdate(Layer* layer, uint32_t dt) = 0;
	};

}

#endif //__CONTROLLER_ANIMATION_H__
