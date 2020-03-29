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
#include <SDL2/SDL.h>

using namespace std;

class KeyMap {
public:
	KeyMap(string filename);
	virtual ~KeyMap();
	string getEventName(SDL_Keycode key);
private:
	unordered_map<SDL_Keycode, string> keyToEventName;
};

#endif /* KEYMAP_H_ */
