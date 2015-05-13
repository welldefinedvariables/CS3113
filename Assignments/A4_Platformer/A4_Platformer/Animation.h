#pragma once
#include <vector>
#include "SpriteBase.h"

using std::vector;

struct Frame{
	float u;
	float v;
	float width;
	float height;
};

class Animation : public SpriteBase{
public:
	Animation(unsigned int textureID, float sheetWidth, float sheetHeight);
	~Animation();

	void Draw(float elapsed, float x, float y);

	void addFrame(float u, float v, float width, float height){ 
		frames.push_back({ u, v, width, height });
		this->width = width;
		this->height = height;
	}
	void addFramePixels(float u, float v, float width, float height){ addFrame(u / sheetWidth, v / sheetHeight, width / sheetWidth, height / sheetHeight); }
	void setFramesPerSecond(float fps){ this->framesPerSecond = fps; }
	void setFrame(size_t index){
		this->u = frames[index].u;
		this->v = frames[index].v;
		this->width = frames[index].width;
		this->height = frames[index].height;
	}
	void animate(){ done = false; currentIndex = 0; }

protected:
	vector<Frame> frames;
	size_t currentIndex;

	float sheetWidth;
	float sheetHeight;

	float animationElapsed;
	float framesPerSecond;

	float done;
};