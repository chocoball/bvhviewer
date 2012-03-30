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

void CBvh::dump(QString &ret)
{
	ret = "CBvhDump\n" ;
	if ( m_pRootNode ) {
		m_pRootNode->dump(ret) ;
	}
}

