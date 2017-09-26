#pragma once

#include "MicronML.h"
#include <QtCore\QString>

using namespace MicronML;

namespace MicronMLApp
{
	inline string_t rt(QString String) { return String.toLocal8Bit().data(); }
}