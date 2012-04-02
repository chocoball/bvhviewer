#ifndef CGLVIEW_H
#define CGLVIEW_H

#include <QMouseEvent>
#include <QGLWidget>
#include <OpenGL.h>
#include <QMatrix4x4>
#include "bvh/cbvh.h"

class CCam
{
public:
	CCam()
	{
		m_mtx.lookAt(QVector3D(0, 300, 300),
				 QVector3D(0, 0, 0),
				 QVector3D(0, 1, 0)) ;
	}

	void setMatrix()
	{
		glLoadMatrixd(m_mtx.data());
	}

	void rotate(const QPoint &delta)
	{
		m_mtx.rotate(delta.y()*1, 1, 0, 0) ;
		m_mtx.rotate(delta.x()*1, 0, 1, 0) ;
	}

private:
	QMatrix4x4	m_mtx ;
};

class CGLView : public QGLWidget
{
	Q_OBJECT
public:
	explicit CGLView(QWidget *parent = 0);

	void setBvh(CBvh &bvh) { m_pBvh = &bvh ; }

protected:
	void initializeGL();
	void resizeGL(int w, int h) ;
	void paintGL();

	void mousePressEvent(QMouseEvent *) ;
	void mouseMoveEvent(QMouseEvent *) ;
	void mouseReleaseEvent(QMouseEvent *) ;

	void drawBvh(CBvhNode *pNode) ;
	void drawGrid() ;

signals:

public slots:

private:
	CBvh		*m_pBvh ;
	CCam		m_cam ;
	QPoint		m_oldMousePos ;
	int			m_pressButton ;
};

#endif // CGLVIEW_H
