#ifndef CBVHMODEL_H
#define CBVHMODEL_H

#include <QAbstractItemModel>
#include "bvh/cbvh.h"
#include "cbvhitem.h"

class CBvhModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit CBvhModel(QObject *parent = 0);
	~CBvhModel() ;

	QVariant data(const QModelIndex &index, int role) const ;
	int rowCount(const QModelIndex &parent) const ;
	int columnCount(const QModelIndex &parent) const ;
	Qt::ItemFlags flags(const QModelIndex &index) const ;
	bool setData(const QModelIndex &index, const QVariant &value, int role) ;
	bool insertRows(int row, int count, const QModelIndex &parent) ;
	bool removeRows(int row, int count, const QModelIndex &parent) ;
	QModelIndex index(int row, int column, const QModelIndex &parent) const ;
	QModelIndex parent(const QModelIndex &child) const ;

	QModelIndex insertItem(int row, CBvhNode *pNode, const QModelIndex &parent) ;

	void resetItem() ;

	void setBvh(CBvh &bvh) ;

signals:

public slots:

private:
	CBvhItem *getItem(const QModelIndex &index) const ;
	void makeTree(QModelIndex index, CBvhNode *pNode) ;

private:
	CBvhItem		*m_pRoot ;
};

#endif // CBVHMODEL_H
