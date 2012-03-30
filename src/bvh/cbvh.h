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
	CBvhNode *getRoot() { return m_pRootNode ; }

private:
	CBvhNode		*m_pRootNode ;
	CBvhMotion		m_motion ;
} ;

#endif // CBVH_H
