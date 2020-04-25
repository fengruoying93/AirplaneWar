#include "game.h"
#include "stdafx.h"

Plane::Plane(void)
{
}


Plane::~Plane(void)
{
}


Dadiji::Dadiji(void)
{
	//加载图片
	img = Image::FromFile(_T("res//dadiji.png"));
	CString imgPath = _T("res\\dadiji.png");
	m_hero.Load(imgPath);
	//初始化大敌机的位置
	plane_x = 300;
	plane_y = 0;
}


Dadiji::~Dadiji(void)
{
}


Xiaodiji::Xiaodiji(void)
{
	//加载图片
	img = Image::FromFile(_T("res//xiaodiji.png"));
	CString imgPath = _T("res\\xiaodiji.png");
	m_hero.Load(imgPath);
	//初始化小敌机的位置
	plane_x = 30;
	plane_y = 0;
}


Xiaodiji::~Xiaodiji(void)
{
}


Zhanji::Zhanji(void)
{
	//加载战机图片
	img = Image::FromFile(_T("res//zhanji.png"));
	CString imgPath = _T("res\\zhanji.png");
	m_hero.Load(imgPath);
	//加载爆炸图片
	img_boom = Image::FromFile(_T("res//zhanji_boom.png"));
	CString imgPath1 = _T("res\\zhanji_boom.png");
	m_hero1.Load(imgPath1);
	//设定战机的初始位置
	plane_x = 330;
	plane_y = 480;
}


Zhanji::~Zhanji(void)
{
}


Zidan::Zidan(void)
{
	//加载子弹图片
	img = Image::FromFile(_T("res//zidan.png"));
	CString imgPath = _T("res\\zidan.png");
	m_hero.Load(imgPath);
	//加载爆炸图片
	img_boom = Image::FromFile(_T("res//zidan_boom.png"));
	CString imgPath1 = _T("res\\zidan_boom.png");
	m_hero1.Load(imgPath1);
	//设定子弹初始位置
	plane_x = 320;
	plane_y = 600;
}


Zidan::~Zidan(void)
{
}

