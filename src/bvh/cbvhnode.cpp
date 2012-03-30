#include <QVariant>
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

void CBvhNode::setOffset(double x, double y, double z)
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

void CBvhNode::dump(QString &ret)
{
	ret += "name:" + m_name + "\n" ;
	ret += "offset x:" + QVariant(m_offsets[0]).toString()
			+ " y:" + QVariant(m_offsets[1]).toString()
			+ " z:" + QVariant(m_offsets[2]).toString() + "\n" ;
	ret += "channel num:" + QVariant(m_nChannel).toString() + "\n" ;
	for ( int i = 0 ; i < m_nChannel ; i ++ ) {
		ret += " [" + QVariant(i).toString() + "] " + QVariant(m_channels[i][0]).toString() + " order:" + QVariant(m_channels[i][1]).toString() + "\n" ;
	}
	ret += "\n" ;

	for ( int i = 0 ; i < m_childPtrs.size() ; i ++ ) {
		m_childPtrs[i]->dump(ret) ;
	}
}
