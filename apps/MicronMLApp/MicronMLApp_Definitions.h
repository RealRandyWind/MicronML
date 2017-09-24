#pragma once

#include "MicronML.h"
#include <QtCore\QString>

using MicronML::CMicronML;

using MicronML::FException;
using MicronML::EExceptionCode;

using MicronML::FData;
using MicronML::FSample;
using MicronML::FCursor;
using MicronML::FDataPoint;

using MicronML::FDataParameters;
using MicronML::FResultParameters;
using MicronML::FProcedureParameters;

using MicronML::FOnSampleEvent;
using MicronML::FOnDataImportEvent;
using MicronML::FOnDataImportDoneEvent;

using MicronML::data_id;
using MicronML::result_id;
using MicronML::procedure_id;
using MicronML::sample_id;
using MicronML::micron_id;

using MicronML::string_t;
using MicronML::real_t;
using MicronML::raw_t;

namespace MicronMLApp
{
	inline string_t rt(QString String) { return String.toLocal8Bit().data(); }
}