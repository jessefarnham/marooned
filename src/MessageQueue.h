/*
 * MessageQueue.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <string>
#include <deque>
#include "TextureLoader.h"

class MessageQueue {
public:
	MessageQueue(unsigned int maxLength);
	void postMessage(std::string text);
	void render(TextureLoader& textureLoader);
	virtual ~MessageQueue();

private:
	std::deque<std::string> messages;
	unsigned int maxLength;
};

#endif /* MESSAGEQUEUE_H_ */
