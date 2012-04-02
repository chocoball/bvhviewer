#include <QDebug>
#include <QSplitter>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_pModel = new CBvhModel(this) ;

	QHBoxLayout *pLayout = new QHBoxLayout(ui->centralWidget) ;
	QSplitter *pSplitter = new QSplitter(ui->centralWidget) ;
	pLayout->addWidget(pSplitter);

	QTreeView *pTreeView = new QTreeView(this) ;
	pTreeView->setModel(m_pModel);
	pTreeView->header()->setHidden(true) ;

	m_pGlView = new CGLView(ui->centralWidget) ;
	m_pGlView->show();

	pSplitter->addWidget(pTreeView) ;
	pSplitter->addWidget(m_pGlView) ;

	ui->centralWidget->setLayout(pLayout) ;

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

		CBvhLoader bvhLoader ;
		if ( bvhLoader.load(&file, m_bvh) ) {
			m_bvh.updateMatrix(0) ;
			m_pModel->resetItem() ;
			m_pModel->setBvh(m_bvh) ;
			m_pGlView->setBvh(m_bvh) ;
		}
	}
}
