#ifndef CBVHMOTION_H
#define CBVHMOTION_H

#include <QList>

class CBvhMotion {
public:
	CBvhMotion() ;
	~CBvhMotion() ;

	void setFrameNum(int frame) { m_nFrame = frame ; }
	void setFrameTime(float time) { m_fFrameTime = time ; }

	void addFrameData(const QList<double> &datas) { m_motions.append(datas) ; }

	double getFrameData(int frame, int order) { return m_motions.at(frame).at(order) ; }

private:
	int						m_nFrame ;
	float					m_fFrameTime ;

	QList<QList<double> >	m_motions ;
} ;


#endif // CBVHMOTION_H
