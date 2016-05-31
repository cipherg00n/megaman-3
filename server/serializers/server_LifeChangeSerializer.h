/*
 * server_LifeChangeSerializer.h
 *
 *  Created on: May 31, 2016
 *      Author: mastanca
 */

#ifndef SERVER_SERIALIZERS_SERVER_LIFECHANGESERIALIZER_H_
#define SERVER_SERIALIZERS_SERVER_LIFECHANGESERIALIZER_H_

#include "server_Serializer.h"

class LifeChangeSerializer: public Serializer {
public:
	// Constructor
	LifeChangeSerializer(unsigned int playerId );
	// Destroyer
	virtual ~LifeChangeSerializer();
	// Serialize object
	virtual void serialize();
private:
	// Copy constructor
	LifeChangeSerializer(const LifeChangeSerializer&);
	// Assignment operator
	LifeChangeSerializer& operator=(const LifeChangeSerializer&);
};

#endif /* SERVER_SERIALIZERS_SERVER_LIFECHANGESERIALIZER_H_ */
