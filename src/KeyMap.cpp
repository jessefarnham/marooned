/*
 * KeyMap.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: jesse
 */

#include "KeyMap.h"
#include <fstream>
#include <iostream>
#include "ControlFSM.h"

using namespace std;

KeyMap::KeyMap(string filename) {
	ifstream in(filename);
	if (in.is_open()){
		string key;
		string eventName;
		while (getline(in, key)){
			getline(in, eventName);
			keyToEventName.insert(make_pair(stoi(key), eventName));
		}
	}
	in.close();
}

string KeyMap::getEventName(SDL_Keycode key) {
	if (key >= '0' && key <= '9'){
		return NUM_KEY_DOWN;
	}
	else if (key == SDLK_LCTRL || key == SDLK_RCTRL){
		return CTRL_DOWN_EVT;
	}
	else if (keyToEventName.count(key % 128)){
		return keyToEventName[key % 128];
	}
	else {
		return "";
	}
}

KeyMap::~KeyMap() {
	// TODO Auto-generated destructor stub
}

