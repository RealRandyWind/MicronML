#pragma once

#include "MicronML.h"
#include <QtCore\QString>

using MicronML::CMicronML;

using MicronML::FException;
using MicronML::EExceptionCode;

using MicronML::FData;
using MicronML::FSample;
using MicronML::FCursor;

using MicronML::FDataParameters;

using MicronML::FOnSampleEvent;
using MicronML::FOnDataImportEvent;
using MicronML::FOnDataImportDoneEvent;

using MicronML::data_id;
using MicronML::sample_id;

using MicronML::string_t;
using MicronML::real_t;

namespace MicronMLApp
{
	inline string_t rt(QString In) { return In.toLocal8Bit().data(); }
}