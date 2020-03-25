/*
 * MessageQueue.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#include "MessageQueue.h"

MessageQueue::MessageQueue(unsigned int maxLength) {
	this->maxLength = maxLength;
}

MessageQueue::~MessageQueue() {
	// TODO Auto-generated destructor stub
}

void MessageQueue::postMessage(std::string text){
	messages.push_back(text);
	if (messages.size() > maxLength) {
		messages.pop_front();
	}
}

void MessageQueue::postError(std::string text){
	postMessage("ERROR: " + text);
}

void MessageQueue::render(TextureLoader& textureLoader){
	int r = 0;
	for (auto it = messages.begin(); it != messages.end(); it++) {
		auto messageTexture = textureLoader.getTextureFromText(*it);
		messageTexture->render(0, r);
		r += messageTexture->getHeight();
	}
}

void MessageQueue::saveState(std::ofstream& out) {

}

void MessageQueue::loadState(std::ifstream& in) {

}
