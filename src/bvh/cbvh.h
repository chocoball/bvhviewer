#ifndef CBVH_H
#define CBVH_H

#include "cbvhnode.h"
#include "cbvhmotion.h"

class CBvh
{
public:
	CBvh() ;
	~CBvh() ;

	void makeRoot(const QString &name) ;
	void update(float delta) ;
	void updateMatrix(int frame) ;

	CBvhNode *getRoot() { return m_pRootNode ; }
	CBvhMotion *getMotion() { return &m_motion ; }

	void dump(QString &ret) ;

private:
	void updateMatrix(int frame, CBvhNode *pNode) ;

private:
	CBvhNode		*m_pRootNode ;
	CBvhMotion		m_motion ;

	int				m_currFrame ;
	float			m_currTime ;
} ;

#endif // CBVH_H
