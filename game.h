#pragma once

class Plane
{
public:
	Plane(void);
	~Plane(void);

	virtual void JIDRAW(CDC *cDC) {}

public:
	CImage m_hero;
	int plane_x;//ͼƬ������
	int plane_y;//ͼƬ������
	
};

class Dadiji :
	public Plane
{
public:
	Dadiji(void);
	~Dadiji(void);
	virtual void JIDRAW(CDC *cDC) {  //�趨��л��Ĵ�С
		m_hero.Draw(*cDC, plane_x, plane_y, 100, 100);//ͼƬ�Ŀ�Ϊ100����50
	}
};

class Xiaodiji :
	public Plane
{
public:
	Xiaodiji(void);
	~Xiaodiji(void);

	virtual void JIDRAW(CDC *cDC) {  //�趨С�л��Ĵ�С
		m_hero.Draw(*cDC, plane_x, plane_y, 50, 50);//ͼƬ�Ŀ�Ϊ50����50
	}

};

class Zhanji :
	public Plane
{
public:
	Zhanji(void);
	~Zhanji(void);
	virtual void JIDRAW(CDC *cDC) {  //�趨ս���Ĵ�С
		m_hero.Draw(*cDC, plane_x, plane_y, 80, 80);//ͼƬ�Ŀ�Ϊ50����50
	}
	//���뱬ըЧ������
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 100, 100);//ս�����л���ײ����ɱ�ը״
	}

public:
	CImage m_hero1;

};

class Zidan :
	public Plane
{
public:
	Zidan(void);
	~Zidan(void);
	virtual void JIDRAW(CDC *cDC) {  //�趨С�л��Ĵ�С
		m_hero.Draw(*cDC, plane_x, plane_y, 10, 25);//ͼƬ�Ŀ�Ϊ50����50
	}
	//���뱬ըЧ������
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 50, 50);//ս�����л���ײ����ɱ�ը״
	}
public:
	CImage m_hero1;

};
