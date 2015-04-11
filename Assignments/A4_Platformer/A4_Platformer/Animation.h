#pragma once

#include "SpriteBase.h"
#include <vector>

using std::vector;

struct Frame{
	float u;
	float v;
	float width;
	float height;
};

class Animation : public SpriteBase{
public:
	Animation(unsigned int textureID, float sheetWidth, float sheetHeight) :SpriteBase(textureID, 0.0f, 0.0f, 1.0f, 1.0f){}
	~Animation(){}

	void addFrame(float u, float v, float width, float height){ frames.push_back({ u, v, width, height }); }
	void addFramePixels(float u, float v, float width, float height){ frames.push_back({u/sheetWidth, v/sheetHeight, width/sheetWidth, height/sheetHeight}); }
	void Draw(size_t frame, float x, float y){
		this->u = frames[frame].u;
		this->v = frames[frame].v;
		this->width = frames[frame].width;
		this->height = frames[frame].height;
		SpriteBase::Draw(x, y);
	}

protected:
	float sheetWidth;
	float sheetHeight;

	vector<Frame> frames;
};