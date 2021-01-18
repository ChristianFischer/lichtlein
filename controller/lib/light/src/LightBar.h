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

#ifndef __CONTROLLER_LIGHTBAR_H__
#define __CONTROLLER_LIGHTBAR_H__

#include "Color.h"
#include "Layer.h"

#include <vector>


namespace lichtlein {

	class LightBarBuilder;


	/**
	 * The LightBar controls an arrangement of multiple lights and manages color information for them.
	 * It's primary reason is to mix color information from various layers, which contain effects
	 * from different sources and transitions between them, into a final set of colors.
	 */
	class LightBar
	{
	private:
		friend class LightBarBuilder;

		LightBar() = default;

		/**
		 * Initializes the light bar.
		 * @param lights The number of lights being controlled by this light bar.
		 */
		void setup(size_t lights);

		/**
		 * Disposes this object's content.
		 */
		void dispose();

	public:
		~LightBar();

		// no copying allowed
		LightBar(const LightBar&) = delete;
		LightBar& operator=(const LightBar&) = delete;

		// default moving
		LightBar(LightBar&&) = default;
		LightBar& operator=(LightBar&&) = default;

	public:
		/**
		 * Get the number of lights controlled by this light bar.
		 */
		size_t getLightCount() const {
			return light_count;
		}

		/**
		 * Get the list of colors to be applied.
		 */
		const std::vector<Color>& getFinalColors() const {
			return final_colors;
		}

	public:
		/**
		 * Acquires a layer to be used for the given animator.
		 * @param animator The animator to play animations on the resulting layer
		 * @param sort_key An integer value to define the sort order
		 * @return The layer which will receive the animator's data
		 */
		Layer* acquireLayer(Animator* animator, uint32_t sort_key);

		/**
		 * Removes the layer from the light bar and deletes the object.
		 * After calling this function, layer cannot be accessed anymore.
		 * @param layer The layer to be deleted
		 */
		void freeLayer(Layer* layer);

		/**
		 * Updates the light bar and all of it's layers and attached animators.
		 * @param dt The time passed in milliseconds
		 */
		void update(uint32_t dt);

	private:
		void sortLayers();

	private:
		size_t              light_count = 0;
		std::vector<Layer*> layers;
		std::vector<Color>  final_colors;
	};

}


#endif //__CONTROLLER_LIGHTBAR_H__
