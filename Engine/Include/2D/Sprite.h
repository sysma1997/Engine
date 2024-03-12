#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "../Texture.h"

namespace E2D {
	class Sprite : public Object {
	private:
		Texture texture;

	public:

		Sprite(Texture texture);

		void draw() override;
	};
}