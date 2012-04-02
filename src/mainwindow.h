#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>

#include "cglview.h"
#include "cbvhmodel.h"

#include "bvh/cbvh.h"
#include "bvh/cbvhloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void slot_timerEvent() ;

protected:
	void dragEnterEvent(QDragEnterEvent *) ;
	void dropEvent(QDropEvent *) ;

private:
	Ui::MainWindow	*ui;

	CBvhModel		*m_pModel ;
	CGLView			*m_pGlView ;
	CBvh			m_bvh ;

	QTime			m_oldTime ;
	bool			m_bRead ;
};

#endif // MAINWINDOW_H
