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
	ImportDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_D));
	connect(ImportDataAction, SIGNAL(triggered()), this, SLOT(ImportData()));

	ImportResultAction = new QAction(tr("&Import Result"), this);
	ImportResultAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_R));
	connect(ImportResultAction, SIGNAL(triggered()), this, SLOT(ImportResult()));

	ImportProcedureAction = new QAction(tr("&Import Procedure"), this);
	ImportProcedureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_P));
	connect(ImportProcedureAction, SIGNAL(triggered()), this, SLOT(ImportProcedure()));
}

void QMicronMLApp::CreateMenus()
{
	DataMenu = menuBar()->addMenu(tr("&File"));

	DataMenu = menuBar()->addMenu(tr("&Data"));
	DataMenu->addAction(ImportDataAction);

	ResultMenu = menuBar()->addMenu(tr("&Result"));
	ResultMenu->addAction(ImportResultAction);

	ProcedureMenu = menuBar()->addMenu(tr("&Procedure"));
	ProcedureMenu->addAction(ImportProcedureAction);
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

void QMicronMLApp::ImportResult()
{
	FResultParameters Parameters;
	result_id ResultID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, "Import Result", QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportResult(Parameters, &ResultID);
}

void QMicronMLApp::ImportProcedure()
{
	FProcedureParameters Parameters;
	procedure_id ProcedureID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, "Import Procedure", QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportProcedure(Parameters, &ProcedureID);
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
