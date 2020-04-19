#pragma once
#include <gdiplus.h>
using namespace Gdiplus;

class Plane
{
public:
	Plane(void);
	~Plane(void);

	virtual void JIDRAW(CDC *cDC) {} //CImage���ư汾
	virtual void JIDRAW(CDC *cDC, Graphics *gh) {} //Gdi+���ư汾

public:
	CImage m_hero;
	Gdiplus::Image *img;
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
	virtual void JIDRAW(CDC *cDC, Graphics *gh) {
		gh->DrawImage(img, plane_x, plane_y, 100, 100);
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
	virtual void JIDRAW(CDC *cDC, Graphics *gh) {
		gh->DrawImage(img, plane_x, plane_y, 50, 50);
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
	virtual void JIDRAW(CDC *cDC, Graphics *gh) {
		gh->DrawImage(img, plane_x, plane_y, 80, 80);
	}
	//���뱬ըЧ������
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 100, 100);//ս�����л���ײ����ɱ�ը״
	}
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y, Graphics *gh) {
		gh->DrawImage(img_boom, x, y, 100, 100);
	}

public:
	CImage m_hero1;
	Gdiplus::Image *img_boom;
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
	virtual void JIDRAW(CDC *cDC, Graphics *gh) {
		gh->DrawImage(img, plane_x, plane_y, 10, 25);
	}
	//���뱬ըЧ������
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 50, 50);//ս�����л���ײ����ɱ�ը״
	}
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y, Graphics *gh) {
		gh->DrawImage(img_boom, x, y, 50, 50);
	}
public:
	CImage m_hero1;
	Gdiplus::Image *img_boom;

};
