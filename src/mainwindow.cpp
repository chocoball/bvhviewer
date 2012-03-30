#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setAcceptDrops(true) ;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->accept() ;
}

void MainWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> url = event->mimeData()->urls() ;

	if ( url.size() > 0 ) {
		QString fileName = url[0].toLocalFile() ;
		QFile file(fileName) ;
		if ( !file.open(QFile::ReadOnly) ) {
			return ;
		}

		CBvh bvh ;
		CBvhLoader bvhLoader ;
		if ( bvhLoader.load(&file, bvh) ) {
			QString str ;
			bvh.dump(str);
			qDebug() << str ;
		}
	}
}
