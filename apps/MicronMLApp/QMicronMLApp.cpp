#include "stdafx.h"
#include "QMicronMLApp.h"
#include "QMicronMLApp.moc"

#define MicronMLApp_Title tr("MicronML")
#define MicronMLApp_WindowSize QSize(1080, 720)
#define MicronMLApp_ImageFormat QImage::Format_RGBA8888

using namespace MicronMLApp;

QMicronMLApp::QMicronMLApp() :
	API(CMicronML::GetInstance()),
	Canvas(new QLabel(this)),
	ImageReader(new QImageReader())
{
	resize(MicronMLApp_WindowSize);
	setWindowTitle(MicronMLApp_Title);
	setCentralWidget(Canvas);
	
	CreateActions();
	CreateMenus();

	API->UseDefaultExceptionListener();
	API->AddListener(FOnDataImportEvent, QMicronMLApp, this, OnDataImport);
	API->AddListener(FOnDataImportDoneEvent, QMicronMLApp, this, OnDataImportDone);
}

QMicronMLApp::~QMicronMLApp()
{
	delete ImageReader;
}

void QMicronMLApp::CreateActions()
{
	ImportDataAction = new QAction(tr("&Import Data"), this);
	ImportDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D));
	connect(ImportDataAction, SIGNAL(triggered()), this, SLOT(ImportData()));

	ImportResultAction = new QAction(tr("&Import Result"), this);
	ImportResultAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_R));
	connect(ImportResultAction, SIGNAL(triggered()), this, SLOT(ImportResult()));

	ImportProcedureAction = new QAction(tr("&Import Procedure"), this);
	ImportProcedureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P));
	connect(ImportProcedureAction, SIGNAL(triggered()), this, SLOT(ImportProcedure()));
}

void QMicronMLApp::CreateMenus()
{
	FileMenu = menuBar()->addMenu(tr("&File"));
	FileMenu->addAction(ImportDataAction);
	FileMenu->addAction(ImportProcedureAction);
	FileMenu->addAction(ImportResultAction);

	SelectMenu = menuBar()->addMenu(tr("&Select"));
}

void QMicronMLApp::ImportData()
{
	FDataParameters Parameters;
	data_id DataID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, tr("Import Data"), QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportData(Parameters, &DataID);
}

void QMicronMLApp::ImportResult()
{
	FResultParameters Parameters;
	result_id ResultID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, tr("Import Result"), QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportResult(Parameters, &ResultID);
}

void QMicronMLApp::ImportProcedure()
{
	FProcedureParameters Parameters;
	procedure_id ProcedureID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, tr("Import Procedure"), QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportProcedure(Parameters, &ProcedureID);
}

void QMicronMLApp::OnDataImport(const FDataParameters Parameters, FData* Data, data_id ID)
{
	if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); }
	ImageReader->setFileName(Parameters.File);
	/* TODO use typdef uint64 raw_t and Qrgba64*/
	Data->Size = (ImageReader->imageCount() ? ImageReader->imageCount() : MicronML_One);
	Data->Samples = new FSample[Data->Size];
	if (!Data->Samples) { MicronML_Throw_Warning(EExceptionCode::FaildToAllocateSamples); return; }
	for (sample_id SampleID = MicronML_First; SampleID < Data->Size; ++SampleID)
	{
		if (!ImageReader->canRead()) { MicronML_Throw_Warning(EExceptionCode::FaildToImportFile); return; }
		QImage Image = ImageReader->read();

		FSample& Sample = Data->Samples[SampleID];
		Sample.Height = Image.height();
		Sample.Width = Image.width();
		Sample.Channels = MicronML_One;
		Sample.Pointer = CopyDataPoints(Image);
		Sample.Time = static_cast<real_t>(SampleID);
		Sample.OriginX = MicronML_First;
		Sample.OriginY = MicronML_First;
	}

	API->AddListener(FOnSampleEvent, QMicronMLApp, this, OnSample, ID);
};

void QMicronMLApp::OnDataImportDone(const FDataParameters Parameters, const FData Data, data_id ID)
{
	MicronML_Throw_Success(EExceptionCode::DataImport);
	/* Show first Sample, this will fire OnSample Event */
	API->Sample({ ID, 0 });
};

void QMicronMLApp::OnSample(FSample* Sample, FCursor Cursor)
{
	QImage Image(Sample->Pointer, Sample->Width, Sample->Height, MicronMLApp_ImageFormat);
	Canvas->setPixmap(QPixmap::fromImage(Image));
	resize(Image.size());
};


inline raw_t* QMicronMLApp::CopyDataPoints(QImage& Image)
{
	size_t Bytes = Image.byteCount();
	raw_t* To = new raw_t[Bytes];
	raw_t* From = Image.bits();
	for (size_t Index = 0; Index < Bytes; ++Index) { To[Index] = From[Index]; }
	return To;
}