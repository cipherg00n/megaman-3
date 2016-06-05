/*
 * editor_main.cpp
 *
 *  Created on: May 14, 2016
 *      Author: santi
 */

#include <gtkmm.h>

#include "views/editor_MainWindow.h"
#include <iostream>
#include <exception>
#include "controllers/editor_EditorController.h"

int main(int argc, char *argv[]) {

	std::cout<<argc<<argv[0]<<std::endl;

	EditorController editorController = EditorController(argc, argv);

	editorController.begin();

	std::cout<<"fin?"<<std::endl;

	return EXIT_SUCCESS;
}

