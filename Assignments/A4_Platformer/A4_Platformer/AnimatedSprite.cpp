#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(unsigned int textureID, float sheetWidth, float sheetHeight)
	:Animation(textureID, sheetWidth, sheetHeight), currentSequence(0), loop(false){}
AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::Draw(float elapsed, float x, float y){
	if (loop && done){
		animate(currentSequence);
	}
	if (!done && currentSequence < sequences.size()){
		animationElapsed += elapsed;
		if (animationElapsed > 1.0f / framesPerSecond){
			currentIndex++;
			animationElapsed = 0.0f;

			if (currentIndex > sequences[currentSequence].size() - 1){
				currentIndex = sequences[currentSequence].size() - 1;
				done = true;
			}
		}
		setFrame(sequences[currentSequence][currentIndex]);
	}
	SpriteBase::Draw(x, y);

}