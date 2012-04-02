#include "cbvh.h"

CBvh::CBvh() :
	m_pRootNode(NULL),
	m_currFrame(0),
	m_currTime(0.0)
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

void CBvh::update(float delta)
{
	if ( m_motion.getFrame() == 0 ) { return ; }
	if ( m_motion.getFrameTime() <= 0.0f ) { return ; }

	m_currTime += delta ;
	while ( m_currTime > m_motion.getFrameTime() ) {
		m_currFrame ++ ;
		if ( m_currFrame >= m_motion.getFrame() ) {
			m_currFrame = 0 ;
		}
		m_currTime -= m_motion.getFrameTime() ;
	}
	updateMatrix(m_currFrame) ;
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

