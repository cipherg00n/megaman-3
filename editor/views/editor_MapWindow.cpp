/*
 * MapWindow.cpp
 *
 *  Created on: May 29, 2016
 *      Author: santi
 */

#include "editor_MapWindow.h"

#include "../controllers/editor_EditorController.h"
#include <iostream>
#include <exception>
#include "../models/editor_ObstacleViewContainer.h"

MapWindow::MapWindow() {
	// TODO Auto-generated constructor stub

}

MapWindow::~MapWindow() {
	delete addButtonVector;
}

MapWindow::MapWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), builder(refGlade){
	maximize();

	//Navigation Buttons
	builder->get_widget("savebutton", saveButton);
    builder->get_widget("backbutton", backButton);

    builder->get_widget("blockbutton", blockButton);
    builder->get_widget("needlebutton", needleButton);
    builder->get_widget("ladderbutton", ladderButton);
    builder->get_widget("precipicebutton", precipiceButton);
    builder->get_widget("bosschaimberbutton", bossChamberButton);

    builder->get_widget("megamanspawnbutton", megamanSpawnButton);
    builder->get_widget("bumpyspawnbutton", bumpySpawnButton);
    builder->get_widget("jumpingsniperspawnbutton", jumpingSniperSpawnButton);
    builder->get_widget("metspawnbutton", metSpawnButton);
    builder->get_widget("normalsniperspawnbutton", normalSniperSpawnButton);

    builder->get_widget("lifebutton", lifeButton);
    builder->get_widget("energysmallbutton", energySmallButton);
    builder->get_widget("energybigbutton", energyBigButton);
    builder->get_widget("bigammobutton", bigAmmoButton);
    builder->get_widget("smallammobutton", smallAmmoButton);


    //Window Buttons
    builder->get_widget("scrolledwindow", scrolledWindow);
    builder->get_widget_derived("fixedwindow", fixedWindow);
    builder->get_widget("eventbox", eventBox);


    //Add scrolling effect to event box
    eventBox->add_events(Gdk::BUTTON_PRESS_MASK |
			   Gdk::BUTTON_RELEASE_MASK |
			   Gdk::SCROLL_MASK |
			   Gdk::SMOOTH_SCROLL_MASK |
			   Gdk::POINTER_MOTION_MASK);

    saveButton->signal_clicked().connect(sigc::mem_fun(* this, &MapWindow::saveButtonWasTapped));
    backButton->signal_clicked().connect(sigc::mem_fun(* this, &MapWindow::backButtonWasTapped));


    blockButton->signal_clicked().connect(sigc::mem_fun(* this, &MapWindow::blockButtonWasTapped));
    needleButton->signal_clicked().connect(sigc::mem_fun(* this, &MapWindow::needleButtonWasTapped));
    precipiceButton->signal_clicked().connect(sigc::mem_fun(* this, &MapWindow::precipiceButtonWasTapped));

}

//Signals
void MapWindow::saveButtonWasTapped() {
//	delegate->presentMainWindowWithoutSavingMap();
	std::cout<<"Save button"<<std::endl;
}

void MapWindow::backButtonWasTapped() {
//	delegate->presentMainWindowWithoutSavingMap();
	std::cout<<"Back button"<<std::endl;
}

//Add Buttons
void MapWindow::blockButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeBlock);
}

void MapWindow::needleButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeNeedle);
}

void MapWindow::precipiceButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypePrecipice);
}
void MapWindow::ladderButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeLadder);
}

void MapWindow::bossChamberButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeBossChamberGate);
}

    //Spawns
void MapWindow::megamanSpawnButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeMegaman);
}

void MapWindow::bumpySpawnButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeBumpy);
}

void MapWindow::jumpingSniperSpawnButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeJumpingSnyper);
}

void MapWindow::metSpawnButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeMet);
}

void MapWindow::normalSniperSpawnButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeNormalSnyper);
}


    //Powerups
void MapWindow::lifeButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeLife);
}

void MapWindow::energySmallButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeSmallEnergyCapsule);
}

void MapWindow::energyBigButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeBigEnergyCapsule);
}

void MapWindow::bigAmmoButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeBigAmmoPack);
}

void MapWindow::smallAmmoButtonWasTapped() {
	addDraggingImageWithType(ObstacleViewTypeSmallAmmoPack);
}

void MapWindow::addDraggingImageWithType(ObstacleViewType obstacleViewType) {
	draggingBegin();

	ObstacleViewContainer *obstacleViewContainer = new ObstacleViewContainer(obstacleViewType);
	draggingImage = obstacleViewContainer->getImage();

	fixedWindow->put(*draggingImage, 0, 0);
}

//Events
bool MapWindow::on_button_press_event(GdkEventButton *event) {
	draggingEnd();

	draggingImage = 0;

	int x = event->x;
	int y = event->y;


	std::cout<<x<<y<<std::endl;

	return true;
}

bool MapWindow::on_motion_notify_event(GdkEventMotion* event) {
	int x = event->x;
	int y = event->y;

	std::cout<<"x in event box : "<<x<<"y in event box : "<<y<<std::endl;
	if (draggingImageIsMoving) {
		fixedWindow->move(*draggingImage, x - (x % kObstacleSize), y - (y % kObstacleSize));
	}

	return true;
}

void MapWindow::draggingBegin() {
	draggingImageIsMoving = true;
}

void MapWindow::draggingEnd() {
	draggingImageIsMoving = false;
}
