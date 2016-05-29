/*
 * server_Bombman.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mastanca
 */

#include "server_Bombman.h"

#include "../../../game_engine/physics/server_PhysicObject.h"
#include "../../weapons/server_BombCannon.h"

#define ATTACK_INTERVAL_TICKS 5

Bombman::Bombman(float32 x, float32 y) : Humanoid(BOMBMAN_INITIAL_HP, x, y) {
	currentWeapon = new BombCannon();
}

Bombman::~Bombman() {
}

void Bombman::update() {
	// Shots bombs, jumps and walks
	if (ticksPassed == ATTACK_INTERVAL_TICKS) {
		attack();
		ticksPassed = 0;
	} else if (ticksPassed == 1 || ticksPassed == 3){
		move(MS_JUMP);
	} else if (ticksPassed == 2){
		move(MS_RIGHT);
	} else {
		move(MS_LEFT);
	}
	++ticksPassed;
}
