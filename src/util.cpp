/*
 * util.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#include <cstdlib>
#include "util.h"

namespace util {

	float randFloat(){
	  //from http://forums.codeguru.com/showthread.php?351834-how-do-i-generate-a-random-float-between-0-and-1
	  float scale=RAND_MAX+1.;
	  float base=rand()/scale;
	  float fine=rand()/scale;
	  return base+fine/scale;
	}

}

