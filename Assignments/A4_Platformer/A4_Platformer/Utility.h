#pragma once
 
#define WORLD_WIDTH 800
#define WORLD_HEIGHT 600

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

#define OPENGL_WIDTH 2.66f
#define OPENGL_HEIGHT 2.0f

namespace Utility{

	struct Coordinates{ float x; float y; };

	inline Coordinates convertPixelsToWorld(float x, float y){
		return{ x / RESOLUTION_X, y / RESOLUTION_Y };
	}

	inline Coordinates convertWorldToPixels(float x, float y){
		return{ x * RESOLUTION_X, y * RESOLUTION_Y };
	}

	inline Coordinates convertPixelsToOpenGL(float x, float y){
		return { (x / RESOLUTION_X) * OPENGL_WIDTH - OPENGL_WIDTH / 2.0f, 
			((RESOLUTION_Y - y) / RESOLUTION_Y) - OPENGL_HEIGHT / 2.0f};
	}

	inline Coordinates convertOpenGLToPixels(float x, float y){
		return{ (x + OPENGL_WIDTH / 2.0f) * RESOLUTION_X / OPENGL_WIDTH,
			RESOLUTION_Y - ( (y + OPENGL_HEIGHT / 2.0f) * RESOLUTION_Y / OPENGL_HEIGHT )
		};

	}
}