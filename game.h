#pragma once

class Plane
{
public:
	Plane(void);
	~Plane(void);

	virtual void JIDRAW(CDC *cDC) {}

public:
	CImage m_hero;
	int plane_x;//图片横坐标
	int plane_y;//图片轴坐标
	
};

class Dadiji :
	public Plane
{
public:
	Dadiji(void);
	~Dadiji(void);
	virtual void JIDRAW(CDC *cDC) {  //设定大敌机的大小
		m_hero.Draw(*cDC, plane_x, plane_y, 100, 100);//图片的宽为100，高50
	}
};

class Xiaodiji :
	public Plane
{
public:
	Xiaodiji(void);
	~Xiaodiji(void);

	virtual void JIDRAW(CDC *cDC) {  //设定小敌机的大小
		m_hero.Draw(*cDC, plane_x, plane_y, 50, 50);//图片的宽为50，高50
	}

};

class Zhanji :
	public Plane
{
public:
	Zhanji(void);
	~Zhanji(void);
	virtual void JIDRAW(CDC *cDC) {  //设定战机的大小
		m_hero.Draw(*cDC, plane_x, plane_y, 80, 80);//图片的宽为50，高50
	}
	//加入爆炸效果函数
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 100, 100);//战机被敌机碰撞将变成爆炸状
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
	virtual void JIDRAW(CDC *cDC) {  //设定小敌机的大小
		m_hero.Draw(*cDC, plane_x, plane_y, 10, 25);//图片的宽为50，高50
	}
	//加入爆炸效果函数
	virtual void JIDRAW_Boom(CDC *cDC, int x, int y) {
		m_hero1.Draw(*cDC, x, y, 50, 50);//战机被敌机碰撞将变成爆炸状
	}
public:
	CImage m_hero1;

};
