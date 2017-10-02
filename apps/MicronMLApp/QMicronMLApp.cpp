#include "stdafx.h"
#include "QMicronMLApp.h"
#include "QMicronMLApp.moc"

#define MicronMLApp_Title tr("MicronML")
#define MicronMLApp_ImportDataTitle tr("Import Data")
#define MicronMLApp_ImportResultTitle tr("Import Result")
#define MicronMLApp_ImportProcedureTitle tr("Import Procedure")
#define MicronMLApp_FileTitle tr("File")
#define MicronMLApp_SelectTitle tr("Select")
#define MicronMLApp_ProjectTitle tr("Project")
#define MicronMLApp_ExitTile tr("Exit")
#define MicronMLApp_LabelDataTitle tr("Label Data")
#define MicronMLApp_ExtractMicronsTitle tr("Extract Microns")
#define MicronMLApp_TrainProcedureTitle tr("Train Procedure")
#define MicronMLApp_ValidateProcedureTitle tr("Validate Procedure")
#define MicronMLApp_WindowSize QSize(1080, 720)
#define MicronMLApp_ImageFormat QImage::Format_RGBA8888
#define MicronMLApp_Disabled true
#define MicronMLApp_Visible true
#define MicronMLApp_NotVisible false

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
	ImportDataAction = new QAction(MicronMLApp_ImportDataTitle, this);
	ImportDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
	connect(ImportDataAction, SIGNAL(triggered()), this, SLOT(ImportData()));

	ImportResultAction = new QAction(MicronMLApp_ImportResultTitle, this);
	ImportResultAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	connect(ImportResultAction, SIGNAL(triggered()), this, SLOT(ImportResult()));

	ImportProcedureAction = new QAction(MicronMLApp_ImportProcedureTitle, this);
	ImportProcedureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	connect(ImportProcedureAction, SIGNAL(triggered()), this, SLOT(ImportProcedure()));

	ExitAction = new QAction(MicronMLApp_ExitTile, this);
	ExitAction->setShortcut(QKeySequence::Quit);
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));

	LabelDataAction = new QAction(MicronMLApp_LabelDataTitle, this);
	LabelDataAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_L);
	connect(LabelDataAction, SIGNAL(triggered()), this, SLOT(LabelData()));

	TrainProcedureAction = new QAction(MicronMLApp_TrainProcedureTitle, this);
	TrainProcedureAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_T);
	connect(TrainProcedureAction, SIGNAL(triggered()), this, SLOT(TrainProcedure()));

	ValidateProcedureAction = new QAction(MicronMLApp_ValidateProcedureTitle, this);
	ValidateProcedureAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_V);
	connect(ValidateProcedureAction, SIGNAL(triggered()), this, SLOT(ValidateProcedure()));

	ExtractMicronsAction = new QAction(MicronMLApp_ExtractMicronsTitle, this);
	ExtractMicronsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_E);
	connect(ExtractMicronsAction, SIGNAL(triggered()), this, SLOT(ExtractMicrons()));

	DataActionGroup = new QActionGroup(this);
	DataActionGroup->addAction(LabelDataAction);
	DataActionGroup->setDisabled(MicronMLApp_Disabled);

	ProcedureActionGroup = new QActionGroup(this);
	ProcedureActionGroup->addAction(TrainProcedureAction);
	ProcedureActionGroup->addAction(ValidateProcedureAction);
	ProcedureActionGroup->setDisabled(MicronMLApp_Disabled);

	DataProcedureActionGroup = new QActionGroup(this);
	DataProcedureActionGroup->addAction(ExtractMicronsAction);
	DataProcedureActionGroup->setDisabled(MicronMLApp_Disabled);
}

void QMicronMLApp::CreateMenus()
{
	FileMenu = menuBar()->addMenu(MicronMLApp_FileTitle);
	FileMenu->addAction(ImportDataAction);
	FileMenu->addAction(ImportProcedureAction);
	FileMenu->addAction(ImportResultAction);
	FileMenu->addSeparator();
	FileMenu->addAction(ExitAction);

	ProjectMenu = menuBar()->addMenu(MicronMLApp_ProjectTitle);
	ProjectMenu->setDisabled(MicronMLApp_Disabled);

	SelectMenu = menuBar()->addMenu(MicronMLApp_SelectTitle);
	SelectMenu->setDisabled(MicronMLApp_Disabled);
}

void QMicronMLApp::ImportData()
{
	FDataParameters Parameters;
	data_id DataID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, MicronMLApp_ImportDataTitle, QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportData(Parameters, &DataID);
}

void QMicronMLApp::ImportResult()
{
	FResultParameters Parameters;
	result_id ResultID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, MicronMLApp_ImportResultTitle, QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportResult(Parameters, &ResultID);
}

void QMicronMLApp::ImportProcedure()
{
	FProcedureParameters Parameters;
	procedure_id ProcedureID = MicronML_None;
	QString FileName = QFileDialog::getOpenFileName(this, MicronMLApp_ImportProcedureTitle, QDir::currentPath());
	if (FileName.isEmpty()) { MicronML_Throw_Warning(EExceptionCode::NullFile); return; }
	Parameters.File = rt(FileName);
	API->ImportProcedure(Parameters, &ProcedureID);
}

void QMicronMLApp::LabelData()
{
	/* start labling routene */
	MicronML_Throw_NotSupported();
}

void QMicronMLApp::TrainProcedure()
{
	/* start collecting parameters and train selected procedure */
	MicronML_Throw_NotSupported();
}

void QMicronMLApp::ValidateProcedure()
{
	/* start collecting parameters and validate selected procedure */
	MicronML_Throw_NotSupported();
}

void QMicronMLApp::ExtractMicrons()
{
	/* start collecting parameters and extract microns */
	MicronML_Throw_NotSupported();
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
		Sample.Dimensions = { static_cast<size_t>(Image.width()),  static_cast<size_t>(Image.height()), MicronML_One };
		Sample.Size = Sample.Dimensions.Width * Sample.Dimensions.Height * Sample.Dimensions.Depth;
		Sample.Channels = { MicronML_One, new size_t[MicronML_One] };
		Sample.Channels.Bits[MicronML_First] = (sizeof(FDataPoint) * MicronML_ByteSize);
		Sample.Pointer = CopyDataPoints(Image);
		Sample.Time = static_cast<real_t>(SampleID);
		Sample.Origin = { MicronML_ZeroF, MicronML_ZeroF, MicronML_ZeroF };
	}

	API->AddListener(FOnSampleEvent, QMicronMLApp, this, OnSample, ID);
};

void QMicronMLApp::OnDataImportDone(const FDataParameters Parameters, const FData Data, data_id ID)
{
	MicronML_Throw_Success(EExceptionCode::DataImport);
	/* Show first Sample, this will fire OnSample Event */
	API->Sample({ECursor::Sample, ID, MicronML_First });
};

void QMicronMLApp::OnSample(FSample* Sample, FCursor Cursor)
{
	QImage Image(Sample->Pointer, static_cast<int>(Sample->Dimensions.Width), static_cast<int>(Sample->Dimensions.Height), MicronMLApp_ImageFormat);
	Canvas->setPixmap(QPixmap::fromImage(Image));
	resize(Image.size());
};

void QMicronMLApp::OnMicron(FMicron* Micron, FCursor Cursor)
{
	/* Redraw if data changed, and highlight activated micron */
	MicronML_Throw_NotSupported();
}

inline raw_t* QMicronMLApp::CopyDataPoints(QImage& Image)
{
	size_t Bytes = Image.byteCount();
	raw_t* To = new raw_t[Bytes];
	raw_t* From = Image.bits();
	for (size_t Index = 0; Index < Bytes; ++Index) { To[Index] = From[Index]; }
	return To;
}