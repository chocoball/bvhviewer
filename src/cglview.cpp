#include <QDebug>
#include "cglview.h"

CGLView::CGLView(QWidget *parent) :
	QGLWidget(parent)
{
	m_pBvh = NULL ;
}

void CGLView::initializeGL()
{
	glClearColor(0.5, 0.5, 1, 0) ;
	glEnable(GL_DEPTH_TEST) ;
	glPointSize(10) ;
}

void CGLView::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h) ;

	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glFrustum(0, w, 0, -h, -1000.0f, 1000.0f) ;
	glMatrixMode(GL_MODELVIEW) ;
}

void CGLView::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	if ( !m_pBvh ) {
		return ;
	}

	CBvhNode *pRoot = m_pBvh->getRoot() ;
	drawBvh(pRoot) ;
}

void CGLView::drawBvh(CBvhNode *pNode)
{
}



