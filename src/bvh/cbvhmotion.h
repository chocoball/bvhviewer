#ifndef CBVHMOTION_H
#define CBVHMOTION_H

#include <QList>

class CBvhMotion {
public:
	CBvhMotion() ;
	~CBvhMotion() ;

	void setFrameNum(int frame) { m_nFrame = frame ; }
	void setFrameTime(float time) { m_fFrameTime = time ; }

	void addFrameData(const QList<float> &datas) { m_motions.append(datas) ; }

private:
	int						m_nFrame ;
	float					m_fFrameTime ;

	QList<QList<float> >	m_motions ;
} ;


#endif // CBVHMOTION_H
