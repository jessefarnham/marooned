/*
 * KeyMap.h
 *
 *  Created on: Mar 29, 2020
 *      Author: jesse
 */

#ifndef KEYMAP_H_
#define KEYMAP_H_

#include <string>
#include <unordered_map>

using namespace std;

class KeyMap {
public:
	KeyMap(string filename);
	virtual ~KeyMap();
	string getEventName(char key);
private:
	unordered_map<char, string> keyToEventName;
};

#endif /* KEYMAP_H_ */
