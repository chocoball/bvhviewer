#include <QDebug>
#include "cbvhitem.h"

CBvhItem::CBvhItem(CBvhItem *pParent) :
	m_pParent(pParent),
	m_pBvhNode(NULL)
{

}

CBvhItem::~CBvhItem()
{
	qDeleteAll(m_childPtrs) ;
}

void CBvhItem::insertChild(int row, CBvhItem *p)
{
	m_childPtrs.insert(row, p) ;
}

QVariant CBvhItem::data(int role)
{
	switch ( role ) {
		case Qt::DisplayRole:
		case Qt::EditRole:
			if ( m_pBvhNode ) {
				return m_pBvhNode->name() ;
			}
			break ;
	}
	return QVariant() ;
}

void CBvhItem::removeChild(CBvhItem *p)
{
	int index = m_childPtrs.indexOf(p) ;
	if ( index < 0 ) { return ; }
	m_childPtrs.removeAt(index) ;
	delete p ;
}
