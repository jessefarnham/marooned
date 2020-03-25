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
#include "Serializable.h"

class MessageQueue : public Serializable {
public:
	MessageQueue(unsigned int maxLength);
	void postMessage(std::string text);
	void postError(std::string text);
	void render(TextureLoader& textureLoader);
	void saveState(std::ofstream& file);
	void loadState(std::ifstream& file);
	virtual ~MessageQueue();

private:
	std::deque<std::string> messages;
	unsigned int maxLength;
};

#endif /* MESSAGEQUEUE_H_ */
