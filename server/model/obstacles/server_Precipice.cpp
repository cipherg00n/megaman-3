/*
 * server_Precipice.cpp
 *
 *  Created on: May 11, 2016
 *      Author: mastanca
 */

#include "server_Precipice.h"

#include "../characters/server_Character.h"

Precipice::Precipice() : Obstacle(PRECIPICE_IS_PASSABLE) {}


Precipice::~Precipice() {
}

void Precipice::haveEffectOn(Character* character) {
	character->decreaseHp(character->getHp());
}
