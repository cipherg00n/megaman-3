/*
 * server_Spark.cpp
 *
 *  Created on: May 15, 2016
 *      Author: mastanca
 */

#include "server_Spark.h"

Spark::Spark(float32 x, float32 y, int facingPosition) : Projectile(SPARKS_DAMAGE, Projectile::SPARK, x, y, facingPosition) {
}


Spark::~Spark() {
}

int Spark::getTypeForSerialization() {
	return ObstacleViewTypeSpark;
}

