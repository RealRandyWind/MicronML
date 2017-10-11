#pragma once

#include "MicronML.h"
#include <QtCore\QString>
#include <QtCore\QPointF>

using namespace MicronML;

namespace MicronMLApp
{
	inline real_t FromQt(qreal Real) { return static_cast<real_t>(Real); }
	inline string_t FromQt(QString String) { return String.toLocal8Bit().data(); }
	inline FPoint FromQt(QPointF Point) { return FPoint{ FromQt(Point.x()), FromQt(Point.y()), MicronML_ZeroF, MicronML_OneF }; }

	inline QPointF ToQt(FPoint Point) { return QPoint(Point.X, Point.Y); }
	inline QString ToQt(string_t String) { return QString::fromUtf8(String); }
	inline qreal ToQt(real_t Real) { return static_cast<qreal>(Real); }

}