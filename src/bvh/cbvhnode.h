#ifndef CBVHNODE_H
#define CBVHNODE_H

#include <QStringList>

enum {
	BvhChannle_Xposition = 0,
	BvhChannle_Yposition,
	BvhChannle_Zposition,
	BvhChannle_Xrotation,
	BvhChannle_Yrotation,
	BvhChannle_Zrotation
} ;

#define kBvhChannelNum		6

class CBvhNode {
public:
	CBvhNode(const QString &name, CBvhNode *parent = 0) ;
	~CBvhNode() ;

	void setOffset(float x, float y, float z) ;
	void addChannel(int channel, int order) ;

private:
	QString				m_name ;
	float				m_offsets[3] ;
	int					m_nChannel ;
	int					m_channels[kBvhChannelNum][2] ;

	QList<CBvhNode *>	m_childPtrs ;
};


#endif // CBVHNODE_H
