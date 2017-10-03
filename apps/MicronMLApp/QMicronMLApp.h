#pragma once

#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtWidgets\QtWidgets>

namespace MicronMLApp
{
	class QMicronMLApp : public QMainWindow
	{
		Q_OBJECT

	public:
		QMicronMLApp();
		~QMicronMLApp();

		void OnDataImport(const FDataParameters Parameters, FData* Data, data_id ID);
		void OnDataImportDone(const FDataParameters Parameters, const FData Data, data_id ID);
		void OnSample(FSample* Sample, FCursor Cursor);
		void OnMicron(FMicron* Micron, FCursor Cursor);

	private:
		CMicronML* API;
		QImageReader* ImageReader;

		QLabel* Canvas;
		QStatusBar* MainStatusBar;

		/* Menus */
		QMenu* FileMenu;
		QMenu* ProjectMenu;
		QMenu* SelectMenu;
		QMenu* ContextMenu;

		/* Actions */
		QActionGroup* ProcedureActionGroup;
		QActionGroup* DataActionGroup;
		QActionGroup* ResultActionGroup;
		QActionGroup* DataProcedureActionGroup;

		QAction* ExitAction;

		QAction* ImportDataAction;
		QAction* ImportResultAction;
		QAction* ImportProcedureAction;

		QAction* LabelDataAction;
		QAction* TrainProcedureAction;
		QAction* ValidateProcedureAction;
		QAction* ExtractMicronsAction;

		void CreateMain();
		void CreateActions();
		void CreateMenus();

		inline raw_t* CopyDataPoints(QImage& Image);

	protected:
#ifndef QT_NO_CONTEXTMENU
		void contextMenuEvent(QContextMenuEvent *Event) override;
#endif

	public slots:
		void ImportData();
		void ImportResult();
		void ImportProcedure();

		void LabelData();
		void TrainProcedure();
		void ValidateProcedure();
		void ExtractMicrons();

	};
}