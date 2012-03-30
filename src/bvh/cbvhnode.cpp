#include "cbvhnode.h"

CBvhNode::CBvhNode(const QString &name, CBvhNode *parent) :
	m_name(name),
	m_nChannel(0)
{
	memset(m_channels, -1, sizeof(m_channels)) ;

	if ( parent ) {
		parent->m_childPtrs.append(this) ;
	}
}

CBvhNode::~CBvhNode()
{
	for ( int i = 0 ; i < m_childPtrs.size() ; i ++ ) {
		delete m_childPtrs[i] ;
	}
}

void CBvhNode::setOffset(float x, float y, float z)
{
	m_offsets[0] = x ;
	m_offsets[1] = y ;
	m_offsets[2] = z ;
}

void CBvhNode::addChannel(int channel, int order)
{
	if ( m_nChannel >= kBvhChannelNum ) {
		return ;
	}
	m_channels[m_nChannel][0] = channel ;
	m_channels[m_nChannel][1] = order ;
	m_nChannel ++ ;
}
