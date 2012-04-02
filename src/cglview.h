#ifndef CGLVIEW_H
#define CGLVIEW_H

#include <QGLWidget>
#include <OpenGL.h>
#include "bvh/cbvh.h"

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

	void drawBvh(CBvhNode *pNode) ;

signals:

public slots:

private:
	CBvh		*m_pBvh ;
};

#endif // CGLVIEW_H
