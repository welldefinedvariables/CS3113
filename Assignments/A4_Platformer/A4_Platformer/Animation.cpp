#include "Animation.h"

Animation::Animation(unsigned int textureID, float sheetWidth, float sheetHeight) :
SpriteBase(textureID), sheetWidth(sheetWidth), sheetHeight(sheetHeight),
animationElapsed(0.0f), framesPerSecond(30.0f), currentIndex(0), done(false){

}

Animation::~Animation(){}

void Animation::Draw(float elapsed, float x, float y){
	if (!done){
		animationElapsed += elapsed;
		if (animationElapsed > 1.0f / framesPerSecond){
			currentIndex++;
			animationElapsed = 0.0f;

			if (currentIndex > frames.size() - 1){
				currentIndex = frames.size() - 1;
				done = true;
			}
		}

		setFrame(currentIndex);
	}
	SpriteBase::Draw(x, y);
}