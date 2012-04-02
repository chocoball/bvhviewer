#include <QMatrix4x4>
#include <QDebug>
#include "cglview.h"

CGLView::CGLView(QWidget *parent) :
	QGLWidget(parent)
{
	m_pBvh = NULL ;
	m_pressButton = 0 ;
	setMouseTracking(true) ;
}

void CGLView::initializeGL()
{
	glClearColor(0.5, 0.5, 1, 0) ;
	glEnable(GL_DEPTH_TEST) ;
	glPointSize(32) ;
}

void CGLView::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h) ;

	glMatrixMode(GL_PROJECTION) ;
	QMatrix4x4 m ;
	m.perspective(65, (double)w/(double)h, 1, 1000) ;
	glLoadMatrixd(m.data());
	glMatrixMode(GL_MODELVIEW) ;

	qDebug() << "glError" << glGetError() ;
}

void CGLView::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glMatrixMode(GL_MODELVIEW) ;
	m_cam.setMatrix();

	drawGrid() ;

	if ( !m_pBvh ) {
		return ;
	}

	CBvhNode *pRoot = m_pBvh->getRoot() ;
	drawBvh(pRoot) ;
}

void CGLView::mousePressEvent(QMouseEvent *event)
{
	switch ( event->button() ) {
		case Qt::LeftButton:
			m_pressButton = Qt::LeftButton ;
			break ;
		case Qt::RightButton:
			m_pressButton = Qt::RightButton ;
			break ;
		default:
			return ;
	}

	m_oldMousePos = event->pos() ;
	updateGL();
	event->accept();
}

void CGLView::mouseMoveEvent(QMouseEvent *event)
{
	switch ( m_pressButton ) {
		case Qt::LeftButton:
			m_cam.rotate(event->pos() - m_oldMousePos);
			break ;
		case Qt::RightButton:
			break ;
		default:
			return ;
	}

	m_oldMousePos = event->pos() ;
	updateGL();
}

void CGLView::mouseReleaseEvent(QMouseEvent *)
{
	m_pressButton = 0 ;
}

void CGLView::drawBvh(CBvhNode *pNode)
{
	QMatrix4x4 m = pNode->getMatrix() ;

	for ( int i = 0 ; i < pNode->childCount() ; i ++ ) {
		glPushMatrix();
		glMultMatrixd(m.data());

		QVector3D v = pNode->child(i)->getOffset() ;

		glBegin(GL_LINES) ;
		glVertex3f(0, 0, 0) ;
		glVertex3f(v.x(), v.y(), v.z()) ;
		glEnd() ;

		glPopMatrix();

		drawBvh(pNode->child(i)) ;
	}
}

void CGLView::drawGrid()
{
	const int gridNum = 10 ;
	const int gridSize = 10 ;
	const int len = gridSize * gridNum ;
	for ( int i = 0 ; i < gridNum ; i ++ ) {
		glBegin(GL_LINES) ;
		glVertex3f(-len / 2, 0, i*gridSize - len/2) ;
		glVertex3f(len / 2, 0, i*gridSize - len/2) ;
		glEnd() ;

		glBegin(GL_LINES) ;
		glVertex3f(i*gridSize - len/2, 0, -len / 2) ;
		glVertex3f(i*gridSize - len/2, 0, len / 2) ;
		glEnd() ;
	}
}




