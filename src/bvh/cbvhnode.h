#ifndef CBVHNODE_H
#define CBVHNODE_H

#include <QStringList>
#include <QMatrix4x4>
#include "cbvhmotion.h"

enum {
	kBvhChannel_Xposition = 0,
	kBvhChannel_Yposition,
	kBvhChannel_Zposition,
	kBvhChannel_Xrotation,
	kBvhChannel_Yrotation,
	kBvhChannel_Zrotation
} ;

#define kBvhChannelNum		6

class CBvhNode {
public:
	CBvhNode(const QString &name, CBvhNode *parent = 0) ;
	~CBvhNode() ;

	void setOffset(double x, double y, double z) ;
	void addChannel(int channel, int order) ;

	void updateMatrix(int frame, CBvhMotion &motion) ;

	void dump(QString &ret) ;

	QString name() { return m_name ; }
	int childCount() { return m_childPtrs.count() ; }
	CBvhNode *child(int index) { return m_childPtrs[index] ; }
	QMatrix4x4 &getMatrix() { return m_mtx ; }

private:
	QString				m_name ;
	double				m_offsets[3] ;
	int					m_nChannel ;
	int					m_channels[kBvhChannelNum][2] ;

	CBvhNode			*m_pParent ;
	QList<CBvhNode *>	m_childPtrs ;

	QMatrix4x4			m_mtx ;
};


#endif // CBVHNODE_H
