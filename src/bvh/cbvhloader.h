#ifndef CBVHLOADER_H
#define CBVHLOADER_H

#include <QFile>
#include "cbvh.h"

class CBvhLoader
{
public:
	CBvhLoader();

	bool load(QFile *pFile, CBvh &bvh) ;

private:
	int			m_channelOrder ;
};

#endif // CBVHLOADER_H
