#include "Animation.h"

Animation::Animation(const char* path) {
	this->path = path;
	nFrame = 1;
	nFrameSpeed = 0;
	nFrameSize = 32;

	texture = Texture::loadTexture(path);
};
Animation::Animation(const char* path, int nFrame, int nFrameSpeed, int nFrameSize) {
	this->path = path;
	this->nFrame = nFrame;
	this->nFrameSpeed = nFrameSpeed;
	this->nFrameSize = nFrameSize;

	texture = Texture::loadTexture(path);
};

