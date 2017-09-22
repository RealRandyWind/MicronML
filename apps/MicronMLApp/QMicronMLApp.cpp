#include "stdafx.h"
#include "QMicronMLApp.h"
#include "QMicronMLApp.moc"

using namespace MicronMLApp;

QMicronMLApp::QMicronMLApp() :
	API(CMicronML::GetInstance()),
	Canvas(new QLabel())
{
	setCentralWidget(Canvas);
	CreateActions();
	CreateMenus();

	API->UseDefaultExceptionListener();
	API->AddListener(FOnDataImportEvent, QMicronMLApp, this, OnDataImport);
	API->AddListener(FOnDataImportDoneEvent, QMicronMLApp, this, OnDataImportDone);
}

QMicronMLApp::~QMicronMLApp()
{
}

void QMicronMLApp::CreateActions()
{
	ImportDataAction = new QAction(tr("&Import Data"), this);
	ImportDataAction->setShortcut(QKeySequence::Open);
	connect(ImportDataAction, SIGNAL(triggered()), this, SLOT(ImportData()));
}

void QMicronMLApp::CreateMenus()
{
	DataMenu = menuBar()->addMenu(tr("&Data"));
	DataMenu->addAction(ImportDataAction);
}

void QMicronMLApp::ImportData()
{
	FDataParameters Parameters;
	data_id DataID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, "Import Data", QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportData(Parameters, &DataID);
}

void QMicronMLApp::OnDataImport(const FDataParameters Parameters, FData* Data, data_id ID)
{
	if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); }
	QImageReader* ImageReader = new QImageReader(Parameters.File);

	Data->Size = (ImageReader->imageCount() ? ImageReader->imageCount() : MicronML_One);
	Data->Samples = new FSample[Data->Size];
	if (!Data->Samples) { MicronML_Throw_Warning(EExceptionCode::FaildToAllocateSamples); return; }

	for (sample_id SampleID = MicronML_First; SampleID < Data->Size; ++SampleID)
	{
		if (!ImageReader->canRead()) { MicronML_Throw_Warning(EExceptionCode::FaildToImportFile); return; }
		QImage Image = ImageReader->read();
		Image.convertToFormat(QImage::Format_RGBA8888);

		Data->Samples[SampleID].Height = Image.height();
		Data->Samples[SampleID].Width = Image.width();
		Data->Samples[SampleID].Channels = MicronML_One;
		Data->Samples[SampleID].Pointer = Image.bits();
		Data->Samples[SampleID].Time = static_cast<real_t>(SampleID);
		Data->Samples[SampleID].OriginX = MicronML_First;
		Data->Samples[SampleID].OriginY = MicronML_First;
	}

	delete ImageReader;
};

void QMicronMLApp::OnDataImportDone(const FDataParameters Parameters, const FData Data, data_id ID)
{
	MicronML_Throw_Success(EExceptionCode::DataImport);
};

void QMicronMLApp::OnSample(FSample* Sample, FCursor Cursor)
{

};
