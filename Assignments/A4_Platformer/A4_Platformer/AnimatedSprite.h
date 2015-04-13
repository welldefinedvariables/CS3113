#pragma once
#include "Animation.h"


class AnimatedSprite : public Animation{
public:
	AnimatedSprite(unsigned int textureID, float sheetWidth, float sheetHeight);
	~AnimatedSprite();

	void Draw(float elapsed, float x, float y);
	void animate(size_t currentSequence){
		this->currentSequence = currentSequence;
		Animation::animate();
	}

	void addSequence(vector<size_t> sequence){ sequences.push_back(sequence); }

	void enableLooping(){ loop = true; }
	void disableLooping(){ loop = false; }


protected:
	vector<vector<size_t>> sequences;
	size_t currentSequence;
	float loop;
};

