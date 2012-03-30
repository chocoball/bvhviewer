#ifndef CBVHNODE_H
#define CBVHNODE_H

#include <QStringList>

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

	void dump(QString &ret) ;

private:
	QString				m_name ;
	double				m_offsets[3] ;
	int					m_nChannel ;
	int					m_channels[kBvhChannelNum][2] ;

	QList<CBvhNode *>	m_childPtrs ;
};


#endif // CBVHNODE_H
