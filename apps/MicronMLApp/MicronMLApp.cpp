// MicronMLApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <QtWidgets\QApplication>
#include "QMicronMLApp.h"

using namespace MicronMLApp;

int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);
	QMicronMLApp MainWindow;
	MainWindow.show();
	return Application.exec();
}