#include <QVariant>
#include <QDebug>
#include "cbvhnode.h"

CBvhNode::CBvhNode(const QString &name, CBvhNode *parent) :
	m_nChannel(0)
{
	m_name = name ;
	memset(m_channels, -1, sizeof(m_channels)) ;

	m_pParent = parent ;
	if ( parent ) {
		parent->m_childPtrs.append(this) ;
	}
}

CBvhNode::~CBvhNode()
{
	qDeleteAll(m_childPtrs) ;
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

void CBvhNode::updateMatrix(int frame, CBvhMotion &motion)
{
	m_mtx.setToIdentity() ;
	m_mtx.translate(m_offsets[0], m_offsets[1], m_offsets[2]) ;

	for ( int i = 0 ; i < m_nChannel ; i ++ ) {
		int ch = m_channels[i][0] ;
		int order = m_channels[i][1] ;

		double data = motion.getFrameData(frame, order) ;
		switch ( ch ) {
			case kBvhChannel_Xposition:
				m_mtx.translate(data, 0, 0) ;
				break ;
			case kBvhChannel_Yposition:
				m_mtx.translate(0, data, 0) ;
				break ;
			case kBvhChannel_Zposition:
				m_mtx.translate(0, 0, data) ;
				break ;
			case kBvhChannel_Xrotation:
				m_mtx.rotate(data, 1, 0, 0) ;
				break ;
			case kBvhChannel_Yrotation:
				m_mtx.rotate(data, 0, 1, 0) ;
				break ;
			case kBvhChannel_Zrotation:
				m_mtx.rotate(data, 0, 0, 1) ;
				break ;
		}
	}
	if ( m_pParent ) {
		m_mtx = m_pParent->m_mtx * m_mtx ;
	}
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
