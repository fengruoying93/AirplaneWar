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
	//����ͼƬ
	CString imgPath = _T("res\\dadiji.png");
	m_hero.Load(imgPath);
	//��ʼ����л���λ��
	plane_x = 300;
	plane_y = 0;
}


Dadiji::~Dadiji(void)
{
}


Xiaodiji::Xiaodiji(void)
{
	//����ͼƬ
	CString imgPath = _T("res\\xiaodiji.png");
	m_hero.Load(imgPath);
	//��ʼ��С�л���λ��
	plane_x = 30;
	plane_y = 0;
}


Xiaodiji::~Xiaodiji(void)
{
}


Zhanji::Zhanji(void)
{
	//����ս��ͼƬ
	CString imgPath = _T("res\\zhanji.png");
	m_hero.Load(imgPath);
//���ر�ըͼƬ
	CString imgPath1 = _T("res\\zhanji_boom.png");
	m_hero1.Load(imgPath1);
//�趨ս���ĳ�ʼλ��
	plane_x = 330;
	plane_y = 480;
}


Zhanji::~Zhanji(void)
{
}


Zidan::Zidan(void)
{
	//�����ӵ�ͼƬ
	CString imgPath = _T("res\\zidan.png");
	m_hero.Load(imgPath);
//���ر�ըͼƬ
	CString imgPath1 = _T("res\\zidan_boom.png");
	m_hero1.Load(imgPath1);
//�趨�ӵ���ʼλ��
	plane_x = 320;
	plane_y = 600;
}


Zidan::~Zidan(void)
{
}

