#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>

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

protected:
	void dragEnterEvent(QDragEnterEvent *) ;
	void dropEvent(QDropEvent *) ;
	
private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
