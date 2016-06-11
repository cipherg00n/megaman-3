/*
 * server_MagnetCannon.cpp
 *
 *  Created on: May 10, 2016
 *      Author: mastanca
 */

#include "server_MagnetCannon.h"

#include "../projectiles/server_Magnet.h"

MagnetCannon::MagnetCannon() : Weapon(MAGNET_CANNON_MAX_AMMO) {}


MagnetCannon::~MagnetCannon() {
}

void MagnetCannon::fire(float32 x, float32 y, int facingPosition) {
	if (ammo > 0){
		--ammo;
		new Magnet(x + facingPosition, y);
	}
}

unsigned int MagnetCannon::getMaxAmmo() {
	return MAGNET_CANNON_MAX_AMMO;
}
