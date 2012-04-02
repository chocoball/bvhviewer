#ifndef CBVHITEM_H
#define CBVHITEM_H

#include <QList>
#include <QVariant>
#include <QModelIndex>

#include "bvh/cbvhnode.h"

class CBvhItem
{
public:
	CBvhItem(CBvhItem *pParent = 0) ;
	~CBvhItem() ;

	void insertChild(int row, CBvhItem *p) ;

	QVariant data(int role) ;

	void removeChild(CBvhItem *p) ;

	int childCount() { return m_childPtrs.count() ; }
	CBvhItem *child(int row) { return m_childPtrs[row] ; }
	CBvhItem *parent() { return m_pParent ; }

	void setName(const QString &name) { m_name = name ; }
	void setNode(CBvhNode *pNode) { m_pBvhNode = pNode ; }

	void setIndex(const QModelIndex &index) { m_index = index ; }
	QModelIndex getIndex() { return m_index ; }

private:
	CBvhItem			*m_pParent ;
	QList<CBvhItem *>	m_childPtrs ;

	QString				m_name ;
	CBvhNode			*m_pBvhNode ;
	QModelIndex			m_index ;
};

#endif // CBVHITEM_H
