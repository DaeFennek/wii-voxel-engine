/*
 * SwitchToMainMenuCommand.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "SwitchToMainMenuCommand.h"

SwitchToMainMenuCommand::SwitchToMainMenuCommand() {
	// TODO Auto-generated constructor stub

}

SwitchToMainMenuCommand::~SwitchToMainMenuCommand() {
	// TODO Auto-generated destructor stub
}

void SwitchToMainMenuCommand::executeCommand() {
	Controller::getInstance().getSceneHandler()->loadScene( MAIN_MENU_ID  );
}