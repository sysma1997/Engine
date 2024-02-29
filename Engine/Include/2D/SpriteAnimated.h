#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "../Engine.h"
#include "../Texture.h"

namespace E2D {
	class SpriteAnimated : public Object {
	private:
		std::vector<Texture> textures;
		float currentTime;

	public:
		int indexTexture;
		float timeChangeTexture;

		SpriteAnimated(std::vector<Texture> textures);

		void draw() override;
	};
}