#ifndef CBVHLOADER_H
#define CBVHLOADER_H

#include <QFile>
#include <QTextStream>
#include "cbvh.h"

class CBvhLoader
{
public:
	CBvhLoader();

	bool load(QFile *pFile, CBvh &bvh) ;
	bool loadNode(CBvhNode *pNode, QTextStream &stream) ;

private:
	int			m_channelOrder ;
};

#endif // CBVHLOADER_H
