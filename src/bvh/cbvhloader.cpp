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
					if ( !loadNode(pRoot, stream) ) {
						return false ;
					}
				}
				break ;
			case 2:		// motion
				if ( strs[0] == "Frames:" ) {
					bvh.getMotion()->setFrameNum(strs[1].toInt()) ;
				}
				else if ( strs[0] == "Frame" && strs[1] == "Time:" ) {
					bvh.getMotion()->setFrameTime(strs[1].toDouble()) ;
				}
				else {
					QList<double> datas ;
					for ( int i = 0 ; i < strs.size() ; i ++ ) {
						datas.append(strs[i].toDouble()) ;
					}
					if ( datas.size() > 0 ) {
						bvh.getMotion()->addFrameData(datas) ;
					}
				}

				break ;
		}
	}
	return true ;
}

bool CBvhLoader::loadNode(CBvhNode *pNode, QTextStream &stream)
{
	while ( 1 ) {
		QString line = stream.readLine() ;
		if ( line.isNull() ) { break ; }
		if ( line.isEmpty() ) { continue ; }

		QStringList strs = line.split(QRegExp("\\s+"), QString::SkipEmptyParts) ;
		if ( strs[0] == "}" ) { return true ; }

		if ( strs[0] == "OFFSET" ) {
			if ( strs.length() != 4 ) { return false ; }

			double x = strs[1].toDouble() ;
			double y = strs[2].toDouble() ;
			double z = strs[3].toDouble() ;
			pNode->setOffset(x, y, z) ;
		}
		else if ( strs[0] == "CHANNELS" ) {
			int channelNum = strs[1].toInt() ;
			for ( int i = 0 ; i < channelNum ; i ++ ) {
				QString strChannel = strs[2+i] ;
				int nch = -1 ;
				if ( strChannel == "Xposition" ) {
					nch = kBvhChannel_Xposition ;
				}
				else if ( strChannel == "Yposition" ) {
					nch = kBvhChannel_Yposition ;
				}
				else if ( strChannel == "Zposition" ) {
					nch = kBvhChannel_Zposition ;
				}
				else if ( strChannel == "Xrotation" ) {
					nch = kBvhChannel_Xrotation ;
				}
				else if ( strChannel == "Yrotation" ) {
					nch = kBvhChannel_Yrotation ;
				}
				else if ( strChannel == "Zrotation" ) {
					nch = kBvhChannel_Zrotation ;
				}
				if ( nch < 0 ) {
					return false ;
				}
				pNode->addChannel(nch, m_channelOrder) ;
				m_channelOrder ++ ;
			}
		}
		else if ( strs[0] == "JOINT" || strs[0] == "End" ) {
			CBvhNode *pChild = new CBvhNode(strs[1], pNode) ;
			if ( !loadNode(pChild, stream) ) {
				return false ;
			}
		}
	}
	return true ;
}




