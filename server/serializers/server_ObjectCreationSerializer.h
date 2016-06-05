/*
 * server_ObjectCreationSerializer.h
 *
 *  Created on: May 30, 2016
 *      Author: mastanca
 */

#ifndef SERVER_SERIALIZERS_SERVER_OBJECTCREATIONSERIALIZER_H_
#define SERVER_SERIALIZERS_SERVER_OBJECTCREATIONSERIALIZER_H_

#include "server_PositionSerializer.h"

class ObjectCreationSerializer: public PositionSerializer {
public:
	// Constructor
	ObjectCreationSerializer(unsigned int objectId, int objectType, float x, float y);
	// Destroyer
	virtual ~ObjectCreationSerializer();
	// Serialize object
	virtual void serialize();
private:
	// Copy constructor
	ObjectCreationSerializer(const ObjectCreationSerializer&);
	// Assignment operator
	ObjectCreationSerializer& operator=(const ObjectCreationSerializer&);
};

#endif /* SERVER_SERIALIZERS_SERVER_OBJECTCREATIONSERIALIZER_H_ */
