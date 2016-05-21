/*
 * server_ReceiverWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReceiverWorker.h"

#include <string>

#include "server_ClientProxy.h"
#include "server_InboundMessageInterpreter.h"

ReceiverWorker::ReceiverWorker(ClientProxy* client) : client(client) {}

ReceiverWorker::~ReceiverWorker() {
}

void ReceiverWorker::run() {
	std::string inboundData;
	int messageCode;
	unsigned int messageLength;
	client->receive(messageCode, messageLength, inboundData);
	InboundMessageInterpreter interpreter(messageCode, messageLength, inboundData);
}
