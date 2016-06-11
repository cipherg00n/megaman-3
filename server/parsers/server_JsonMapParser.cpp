/*
 * server_JsonMapParser.cpp
 *
 *  Created on: Jun 4, 2016
 *      Author: mastanca
 */

#include "server_JsonMapParser.h"

#include <list>

#include "../../common/common_MapConstants.h"
#include "../../common/common_MapViewParser.h"
#include "../../common/rapidjson/document.h"
#include "../../common/rapidjson/rapidjson.h"
#include "../game_engine/server_Engine.h"
#include "../game_engine/server_Player.h"
#include "../model/characters/mobs/server_Bumpy.h"
#include "../model/characters/mobs/server_JumpingSniper.h"
#include "../model/characters/mobs/server_Met.h"
#include "../model/characters/mobs/server_NormalSniper.h"
#include "../model/obstacles/server_Block.h"
#include "../model/obstacles/server_BossChamberGate.h"
#include "../model/obstacles/server_Ladder.h"
#include "../model/obstacles/server_Needle.h"
#include "../model/obstacles/server_Precipice.h"
#include "../model/powerups/server_BigAmmoPack.h"
#include "../model/powerups/server_BigEnergyCapsule.h"
#include "../model/powerups/server_Life.h"
#include "../model/powerups/server_SmallAmmoPack.h"
#include "../model/powerups/server_SmallEnergyCapsule.h"


JsonMapParser::JsonMapParser() {
}

JsonMapParser::~JsonMapParser() {
}

void JsonMapParser::parseDocument(const std::string& name) {
	MapViewParser mapParser;
	rapidjson::Document* document = mapParser.serverMapFromPath(name);
	const rapidjson::Value& mapJson = (*document)[MAP_NAME];

	const rapidjson::Value& obstaclesJson = mapJson[MAPOBSTACLES_NAME];

	for (rapidjson::SizeType i = 0; i < obstaclesJson.Size(); i++) {
		unsigned int x = obstaclesJson[i][X_NAME].GetInt();
		unsigned int y = obstaclesJson[i][Y_NAME].GetInt();
		int type = obstaclesJson[i][TYPE_NAME].GetInt();

		inflateObstacle(type, x, y);
	}
}

void JsonMapParser::inflateObstacle(int type, unsigned int x, unsigned int y) {
	std::list<Player*> playerList;
	switch (type) {
		case ObstacleViewTypeBlock:
			new Block(x, y);
			break;
		case ObstacleViewTypeBossChamberGate:
			new BossChamberGate(x, y);
			break;
		case ObstacleViewTypeLadder:
			new Ladder(x, y);
			break;
		case ObstacleViewTypeNeedle:
			new Needle(x, y);
			break;
		case ObstacleViewTypePrecipice:
			new Precipice(x, y);
			break;
		case ObstacleViewTypeBigAmmoPack:
			new BigAmmoPack(x, y);
			break;
		case ObstacleViewTypeBigEnergyCapsule:
			new BigEnergyCapsule(x, y);
			break;
		case ObstacleViewTypeLife:
			new Life(x, y);
			break;
		case ObstacleViewTypeSmallAmmoPack:
			new SmallAmmoPack(x, y);
			break;
		case ObstacleViewTypeSmallEnergyCapsule:
			new SmallEnergyCapsule(x, y);
			break;
		case ObstacleViewTypeBumpy:
			new Bumpy(x, y);
			break;
		case ObstacleViewTypeJumpingSnyper:
			new JumpingSniper(x, y);
			break;
		case ObstacleViewTypeMet:
			new Met(x, y);
			break;
		case ObstacleViewTypeNormalSnyper:
			new NormalSniper(x, y);
			break;
		case ObstacleViewTypeMegaman:
			playerList = Engine::getInstance().getPlayersList();
			for (std::list<Player*>::iterator it = playerList.begin();
					it != playerList.end(); ++it) {
				(*it)->setMegaman(x, y);
			}
			break;
		default:
			break;
	}
}
