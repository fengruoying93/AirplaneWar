
// AirplaneWarView.cpp : CAirplaneWarView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AirplaneWar.h"
#endif

#include "AirplaneWarDoc.h"
#include "AirplaneWarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAirplaneWarView

IMPLEMENT_DYNCREATE(CAirplaneWarView, CView)

BEGIN_MESSAGE_MAP(CAirplaneWarView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN() //左键
	ON_WM_TIMER()	//计时器
	ON_WM_CREATE() //窗口创建
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CAirplaneWarView 构造/析构

CAirplaneWarView::CAirplaneWarView()
{
	// TODO: 在此处添加构造代码

}

CAirplaneWarView::~CAirplaneWarView()
{
}

BOOL CAirplaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//bkg.LoadBitmap(IDB_BITMAP1);
	return CView::PreCreateWindow(cs);
}

int CAirplaneWarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此添加您专用的创建代码
	//PlaySound(_T("res\\youxi.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//循环播放背景音乐
	this->SetTimer(1, 100, NULL);//设置一个定时器
	int x_num = 50;
	for (int i = 0; i < 5; i++)
	{
		xiaodiji[i].plane_x += x_num;//开始时，小飞机的横坐标相隔30
		x_num += 50;
		xiaodiji[i].plane_y -= x_num;//开始时，小飞机的纵坐标相隔30，起到延迟出现的效果
	}
 
	int num = 0;
	for (int j2 = 0;j2 < 30;j2++)
	{
		zidan[j2].plane_y -= (num+20);//开始时，子弹的纵坐标相隔25，起到延迟出现的效果
		zidan[j2].plane_x = zhanji.plane_x + 35;//子弹的横坐标在战机的正中间
		num += 50;
	}
	img_bkg = Image::FromFile(_T("res//bkg.png"));
	return 0;
}

// CAirplaneWarView 绘制
void CAirplaneWarView::OnDraw(CDC* pDC)
{
	CAirplaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

#if 0
	BITMAP bmp;
    bkg.GetBitmap(&bmp); //获取图片大小信息
    //CDC dcCompatible;
    m_cacheDC.CreateCompatibleDC(pDC);
    m_cacheDC.SelectObject(bkg);
    
    CRect rect;
    GetClientRect(&rect);
    pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&m_cacheDC,0,0,
                    bmp.bmWidth,bmp.bmHeight,SRCCOPY);

#endif

}

void CAirplaneWarView::GameRunDraw()
{
	HDC hdc = ::GetDC(m_hWnd);
	CDC *cDC = CClientDC::FromHandle(hdc);   //获得当前窗口的DC   
	CRect rect;
	GetClientRect(rect);
	RectF m_rect(0, 0, 450, 600);
#if 1
	CDC m_dcMemory;   //双缓冲DC
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(cDC, rect.Width(), rect.Height());
	m_dcMemory.CreateCompatibleDC(cDC);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc()); //构造对象
	gh.Clear(Color::White); //清除背景
	gh.ResetClip();

	gh.DrawImage(img_bkg, rect.left, rect.top, rect.Width(), rect.Height()); //绘制背景
	//gh.DrawImage(img, m_rect);

	RefreshPlane(cDC, &gh); //绘制飞机
	
	BitBlt(hdc, 0, 0, rect.Width(), rect.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	
	cDC->DeleteDC();
	
#endif
	
	return;
}

void CAirplaneWarView::RefreshPlane(CDC *cDC, Graphics *gh)
{
	if(!cDC)
		return;
	//cDC = &m_cacheDC;
	zhanji.JIDRAW(cDC, gh);//画战机
 
	//子弹
	for (int j1 = 0;j1 < 30;j1++)
	{
		if (zidan[j1].plane_x < dadiji.plane_x+100&& zidan[j1].plane_x >dadiji.plane_x - 100&&zidan[j1].plane_y < dadiji.plane_y+50&& zidan[j1].plane_y >dadiji.plane_y - 50)//判断子弹是否和大战机碰撞
		{
			int xx = dadiji.plane_x;
			int yy = dadiji.plane_y;
			zidan[j1].JIDRAW_Boom(cDC,xx,yy, gh);//若两者产生碰撞，则出现爆炸效果
			zidan[j1].plane_y = zhanji.plane_y - 20;
			zidan[j1].plane_x = zhanji.plane_x + 35;//发生爆炸的子弹，重新回到战机的子弹口
			dadiji.plane_x = rand() % 400;  //大敌机从上面的随机位置重新出现
			while (dadiji.plane_x<20)
				dadiji.plane_x = rand() % 400;
			dadiji.plane_y = 0;
		}
		else if (zidan[j1].plane_y < 0)//如果子弹飞到最高处，重回战机子弹口
		{
			zidan[j1].plane_y = zhanji.plane_y - 20;
			zidan[j1].plane_x = zhanji.plane_x + 35;
		}
		else
		zidan[j1].plane_y = zidan[j1].plane_y-10;//否则，继续上升
		for (int i1 = 0;i1 < 5;i1++)
		{
			if (zidan[j1].plane_x < xiaodiji[i1].plane_x + 50 && zidan[j1].plane_x >xiaodiji[i1].plane_x - 50 && zidan[j1].plane_y <xiaodiji[i1].plane_y + 50 && zidan[j1].plane_y >xiaodiji[i1].plane_y - 50)//判断每台小敌机是否和子弹碰撞
			{
				int xx1 = xiaodiji[i1].plane_x;
				int yy1 = xiaodiji[i1].plane_y;
				xiaodiji[i1].plane_x = rand() % 400;//若碰撞，小敌机重新从上面的随机位置降落
				while (xiaodiji[i1].plane_x<20)
					xiaodiji[i1].plane_x = rand() % 400;
				xiaodiji[i1].plane_y = -30;
			
				zidan[j1].JIDRAW_Boom(cDC, xx1, yy1, gh);//爆炸状态
				zidan[j1].plane_y = zhanji.plane_y - 20;
				zidan[j1].plane_x = zhanji.plane_x + 35;//子弹重新回到战机子弹口
			}
		}
		zidan[j1].JIDRAW(cDC, gh);//画子弹
	}
 
	//小敌机
	for (int j = 0;j < 5;j++)
	{
		if (zhanji.plane_x < xiaodiji[j].plane_x + 50 && zhanji.plane_x >xiaodiji[j].plane_x -50 && zhanji.plane_y < xiaodiji[j].plane_y + 50 && zhanji.plane_y >xiaodiji[j].plane_y - 50)//判断战机是否和小战机碰撞
		{
			int xxx = zhanji.plane_x;
			int yyy = zhanji.plane_y;
			zhanji.JIDRAW_Boom(cDC, xxx, yyy, gh);//若碰撞，发生战机爆炸
			Sleep(500);//停止500ms
			xiaodiji[j].plane_x = rand() % 400;
			while (dadiji.plane_x<20)
				xiaodiji[j].plane_x = rand() % 400;//小敌机重新随机降落
			dadiji.plane_y = 0;
			zhanji.plane_x = 300;
			zhanji.plane_y = 500;//战机回到初始位置
		}
		else if (xiaodiji[j].plane_y > 690)//若小敌机走出游戏界面，则重新随机降落
		{
			xiaodiji[j].plane_x = rand() % 400;
			while(xiaodiji[j].plane_x<20)
				xiaodiji[j].plane_x = rand() % 400;
			xiaodiji[j].plane_y = 0;
		}
		xiaodiji[j].plane_y += 5;//小战机下降
		xiaodiji[j].JIDRAW(cDC, gh);
	}
 
	//大敌机
	if (zhanji.plane_x < dadiji.plane_x + 100 && zhanji.plane_x >dadiji.plane_x - 100 && zhanji.plane_y < dadiji.plane_y + 80 && zhanji.plane_y >dadiji.plane_y - 80)//判断战机是否和大敌机发生碰撞
	{
		int xxx = zhanji.plane_x;
		int yyy = zhanji.plane_y;
		zhanji.JIDRAW_Boom(cDC, xxx, yyy, gh);//若碰撞，战机爆炸，大敌机重新随机降落
		Sleep(500);//停止500ms
		dadiji.plane_x = rand() % 400;
		while (dadiji.plane_x<20)
			dadiji.plane_x = rand() % 400;
		dadiji.plane_y = 0;
		zhanji.plane_x = 300;//战机回到初始位置
		zhanji.plane_y = 500;
	}
	if (dadiji.plane_y < 650)//大敌机下降
		dadiji.plane_y = dadiji.plane_y + 5;
	else
		dadiji.plane_y = 0;//若大飞机飞出游戏界面 ，重新随机降落
	dadiji.JIDRAW(cDC, gh); //画大敌机
	
}

void CAirplaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	CDC *cDC = this->GetDC();   //获得当前窗口的DC   
	CRect rect;
	GetClientRect(rect);
	//cDC->FillSolidRect(rect, RGB(255, 255, 255));
	//InvalidateRect(&rect, FALSE);
	GameRunDraw();
	
	ReleaseDC(cDC);
	CView::OnTimer(nIDEvent);
}

void CAirplaneWarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CString text;
	text.Format(_T("x=%d y=%d"), point.x, point.y);
	AfxGetMainWnd()->SetWindowText(text); 
	//AfxGetApp()->m_pMainWnd->SetWindowText(text);
}

// CAirplaneWarView 打印

BOOL CAirplaneWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAirplaneWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CAirplaneWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CAirplaneWarView 诊断

#ifdef _DEBUG
void CAirplaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CAirplaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAirplaneWarDoc* CAirplaneWarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAirplaneWarDoc)));
	return (CAirplaneWarDoc*)m_pDocument;
}
#endif //_DEBUG


void CAirplaneWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		zhanji.plane_x -= 5;
	} 
	else if(nChar == VK_RIGHT)
	{
		zhanji.plane_x += 5;
	}
	UpdateWindow();
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
