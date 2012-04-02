#include "cbvh.h"

CBvh::CBvh() :
	m_pRootNode(NULL)
{
}

CBvh::~CBvh()
{
	if ( m_pRootNode ) {
		delete m_pRootNode ;
	}
}

void CBvh::makeRoot(const QString &name)
{
	if ( m_pRootNode ) {
		delete m_pRootNode ;
	}
	m_pRootNode = new CBvhNode(name) ;
}

void CBvh::updateMatrix(int frame)
{
	if ( !m_pRootNode ) { return ; }
	updateMatrix(frame, m_pRootNode) ;
}

void CBvh::dump(QString &ret)
{
	ret = "CBvhDump\n" ;
	if ( m_pRootNode ) {
		m_pRootNode->dump(ret) ;
	}
}

void CBvh::updateMatrix(int frame, CBvhNode *pNode)
{
	pNode->updateMatrix(frame, m_motion) ;
	for ( int i = 0 ; i < pNode->childCount() ; i ++ ) {
		updateMatrix(frame, pNode->child(i)) ;
	}
}

