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

	private:
		CMicronML* API;
		QLabel* Canvas;
		QMenu* DataMenu;
		QAction* ImportDataAction;

		void CreateActions();
		void CreateMenus();

	public slots:
		void ImportData();

	};
}