#include "cbvhmodel.h"

CBvhModel::CBvhModel(QObject *parent) :
	QAbstractItemModel(parent)
{
	m_pRoot = new CBvhItem(NULL) ;
}

CBvhModel::~CBvhModel()
{
	if ( m_pRoot ) {
		delete m_pRoot ;
	}
}

QVariant CBvhModel::data(const QModelIndex &index, int role) const
{
	CBvhItem *p = getItem(index) ;
	if ( p ) {
		return p->data(role) ;
	}
	return QVariant() ;
}

int CBvhModel::rowCount(const QModelIndex &parent) const
{
	CBvhItem *p = getItem(parent) ;
	if ( p ) {
		return p->childCount() ;
	}
	return 0 ;
}

int CBvhModel::columnCount(const QModelIndex &parent) const
{
Q_UNUSED(parent)
	return 1 ;
}

Qt::ItemFlags CBvhModel::flags(const QModelIndex &index) const
{
	if ( !index.isValid() ) {
		return Qt::ItemIsEnabled ;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}

bool CBvhModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
Q_UNUSED(index)
Q_UNUSED(value)
Q_UNUSED(role)

	return false ;
}

bool CBvhModel::insertRows(int row, int count, const QModelIndex &parent)
{
	beginInsertRows(parent, row, row+count-1) ;

	CBvhItem *p = getItem(parent) ;
	p->insertChild(row, new CBvhItem(p)) ;

	endInsertRows();
	return true ;
}

bool CBvhModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row+count-1) ;

	CBvhItem *p = getItem(parent) ;
	p->removeChild(p->child(row)) ;

	endRemoveRows();
	return true ;
}

QModelIndex CBvhModel::index(int row, int column, const QModelIndex &parent) const
{
	if ( !hasIndex(row, column, parent) ) { return QModelIndex() ; }

	CBvhItem *p = getItem(parent) ;
	CBvhItem *pChild = p->child(row) ;
	if ( pChild ) {
		return createIndex(row, column, pChild) ;
	}
	return QModelIndex() ;
}

QModelIndex CBvhModel::parent(const QModelIndex &child) const
{
	if ( !child.isValid() ) { return QModelIndex() ; }
	CBvhItem *c = static_cast<CBvhItem *>(child.internalPointer()) ;
	CBvhItem *p = c->parent() ;
	if ( p == m_pRoot || c == m_pRoot ) { return QModelIndex() ; }
	return createIndex(p->getIndex().row(), 0, p) ;
}

QModelIndex CBvhModel::insertItem(int row, CBvhNode *pNode, const QModelIndex &parent)
{
	insertRows(row, 1, parent) ;

	QModelIndex index = this->index(row, 0, parent) ;
	CBvhItem *p = getItem(index) ;
	p->setIndex(index) ;
	p->setNode(pNode) ;
	return index ;
}

void CBvhModel::resetItem()
{
	if ( m_pRoot ) {
		delete m_pRoot ;
	}
	m_pRoot = new CBvhItem(NULL) ;
}

void CBvhModel::setBvh(CBvh &bvh)
{
	CBvhNode *pRoot = bvh.getRoot() ;
	QModelIndex index = insertItem(0, pRoot, QModelIndex()) ;
	makeTree(index, pRoot) ;
}

CBvhItem *CBvhModel::getItem(const QModelIndex &index) const
{
	CBvhItem *p = m_pRoot ;
	if ( index.isValid() ) {
		p = static_cast<CBvhItem *>(index.internalPointer()) ;
	}
	return p ;
}

void CBvhModel::makeTree(QModelIndex index, CBvhNode *pNode)
{
	for ( int i = 0 ; i < pNode->childCount() ; i ++ ) {
		QModelIndex childIndex = insertItem(i, pNode->child(i), index) ;
		makeTree(childIndex, pNode->child(i)) ;
	}
}




