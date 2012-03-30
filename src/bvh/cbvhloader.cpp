#include <QTextStream>
#include "cbvhloader.h"

CBvhLoader::CBvhLoader()
{
}

bool CBvhLoader::load(QFile *pFile, CBvh &bvh)
{
	QTextStream stream(pFile) ;
	int state = 0 ;

	m_channelOrder = 0 ;

	while ( 1 ) {
		QString line = stream.readLine() ;
		if ( line.isNull() ) { break ; }
		if ( line.isEmpty() ) { continue ; }

		QStringList strs = line.split(QRegExp("\\s+"), QString::SkipEmptyParts) ;

		if ( strs[0] == "HIERARCHY" ) { state = 1 ; continue ; }
		else if ( strs[0] == "MOTION" ) { state = 2 ; continue ; }

		switch ( state ) {
			case 1:		// hierarchy
				if ( strs[0] == "ROOT" ) {
					bvh.makeRoot(strs[1]) ;
					CBvhNode *pRoot = bvh.getRoot() ;
					if ( !loadNode(pRoot, stream) ) { return false ; }
				}
				break ;
			case 2:		// motion
				break ;
		}
	}
	return true ;
}
