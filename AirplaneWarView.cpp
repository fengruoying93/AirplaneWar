
// AirplaneWarView.cpp : CAirplaneWarView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN() //���
	ON_WM_TIMER()	//��ʱ��
	ON_WM_CREATE() //���ڴ���
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CAirplaneWarView ����/����

CAirplaneWarView::CAirplaneWarView()
{
	// TODO: �ڴ˴���ӹ������

}

CAirplaneWarView::~CAirplaneWarView()
{
}

BOOL CAirplaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//bkg.LoadBitmap(IDB_BITMAP1);
	return CView::PreCreateWindow(cs);
}

int CAirplaneWarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  �ڴ������ר�õĴ�������
	//PlaySound(_T("res\\youxi.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//ѭ�����ű�������
	this->SetTimer(1, 100, NULL);//����һ����ʱ��
	int x_num = 50;
	for (int i = 0; i < 5; i++)
	{
		xiaodiji[i].plane_x += x_num;//��ʼʱ��С�ɻ��ĺ��������30
		x_num += 50;
		xiaodiji[i].plane_y -= x_num;//��ʼʱ��С�ɻ������������30�����ӳٳ��ֵ�Ч��
	}
 
	int num = 0;
	for (int j2 = 0;j2 < 30;j2++)
	{
		zidan[j2].plane_y -= (num+20);//��ʼʱ���ӵ������������25�����ӳٳ��ֵ�Ч��
		zidan[j2].plane_x = zhanji.plane_x + 35;//�ӵ��ĺ�������ս�������м�
		num += 50;
	}
	img_bkg = Image::FromFile(_T("res//bkg.png"));
	return 0;
}

// CAirplaneWarView ����
void CAirplaneWarView::OnDraw(CDC* pDC)
{
	CAirplaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

#if 0
	BITMAP bmp;
    bkg.GetBitmap(&bmp); //��ȡͼƬ��С��Ϣ
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
	CDC *cDC = CClientDC::FromHandle(hdc);   //��õ�ǰ���ڵ�DC   
	CRect rect;
	GetClientRect(rect);
	RectF m_rect(0, 0, 450, 600);
#if 1
	CDC m_dcMemory;   //˫����DC
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(cDC, rect.Width(), rect.Height());
	m_dcMemory.CreateCompatibleDC(cDC);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc()); //�������
	gh.Clear(Color::White); //�������
	gh.ResetClip();

	gh.DrawImage(img_bkg, rect.left, rect.top, rect.Width(), rect.Height()); //���Ʊ���
	//gh.DrawImage(img, m_rect);

	RefreshPlane(cDC, &gh); //���Ʒɻ�
	
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
	zhanji.JIDRAW(cDC, gh);//��ս��
 
	//�ӵ�
	for (int j1 = 0;j1 < 30;j1++)
	{
		if (zidan[j1].plane_x < dadiji.plane_x+100&& zidan[j1].plane_x >dadiji.plane_x - 100&&zidan[j1].plane_y < dadiji.plane_y+50&& zidan[j1].plane_y >dadiji.plane_y - 50)//�ж��ӵ��Ƿ�ʹ�ս����ײ
		{
			int xx = dadiji.plane_x;
			int yy = dadiji.plane_y;
			zidan[j1].JIDRAW_Boom(cDC,xx,yy, gh);//�����߲�����ײ������ֱ�ըЧ��
			zidan[j1].plane_y = zhanji.plane_y - 20;
			zidan[j1].plane_x = zhanji.plane_x + 35;//������ը���ӵ������»ص�ս�����ӵ���
			dadiji.plane_x = rand() % 400;  //��л�����������λ�����³���
			while (dadiji.plane_x<20)
				dadiji.plane_x = rand() % 400;
			dadiji.plane_y = 0;
		}
		else if (zidan[j1].plane_y < 0)//����ӵ��ɵ���ߴ����ػ�ս���ӵ���
		{
			zidan[j1].plane_y = zhanji.plane_y - 20;
			zidan[j1].plane_x = zhanji.plane_x + 35;
		}
		else
		zidan[j1].plane_y = zidan[j1].plane_y-10;//���򣬼�������
		for (int i1 = 0;i1 < 5;i1++)
		{
			if (zidan[j1].plane_x < xiaodiji[i1].plane_x + 50 && zidan[j1].plane_x >xiaodiji[i1].plane_x - 50 && zidan[j1].plane_y <xiaodiji[i1].plane_y + 50 && zidan[j1].plane_y >xiaodiji[i1].plane_y - 50)//�ж�ÿ̨С�л��Ƿ���ӵ���ײ
			{
				int xx1 = xiaodiji[i1].plane_x;
				int yy1 = xiaodiji[i1].plane_y;
				xiaodiji[i1].plane_x = rand() % 400;//����ײ��С�л����´���������λ�ý���
				while (xiaodiji[i1].plane_x<20)
					xiaodiji[i1].plane_x = rand() % 400;
				xiaodiji[i1].plane_y = -30;
			
				zidan[j1].JIDRAW_Boom(cDC, xx1, yy1, gh);//��ը״̬
				zidan[j1].plane_y = zhanji.plane_y - 20;
				zidan[j1].plane_x = zhanji.plane_x + 35;//�ӵ����»ص�ս���ӵ���
			}
		}
		zidan[j1].JIDRAW(cDC, gh);//���ӵ�
	}
 
	//С�л�
	for (int j = 0;j < 5;j++)
	{
		if (zhanji.plane_x < xiaodiji[j].plane_x + 50 && zhanji.plane_x >xiaodiji[j].plane_x -50 && zhanji.plane_y < xiaodiji[j].plane_y + 50 && zhanji.plane_y >xiaodiji[j].plane_y - 50)//�ж�ս���Ƿ��Сս����ײ
		{
			int xxx = zhanji.plane_x;
			int yyy = zhanji.plane_y;
			zhanji.JIDRAW_Boom(cDC, xxx, yyy, gh);//����ײ������ս����ը
			Sleep(500);//ֹͣ500ms
			xiaodiji[j].plane_x = rand() % 400;
			while (dadiji.plane_x<20)
				xiaodiji[j].plane_x = rand() % 400;//С�л������������
			dadiji.plane_y = 0;
			zhanji.plane_x = 300;
			zhanji.plane_y = 500;//ս���ص���ʼλ��
		}
		else if (xiaodiji[j].plane_y > 690)//��С�л��߳���Ϸ���棬�������������
		{
			xiaodiji[j].plane_x = rand() % 400;
			while(xiaodiji[j].plane_x<20)
				xiaodiji[j].plane_x = rand() % 400;
			xiaodiji[j].plane_y = 0;
		}
		xiaodiji[j].plane_y += 5;//Сս���½�
		xiaodiji[j].JIDRAW(cDC, gh);
	}
 
	//��л�
	if (zhanji.plane_x < dadiji.plane_x + 100 && zhanji.plane_x >dadiji.plane_x - 100 && zhanji.plane_y < dadiji.plane_y + 80 && zhanji.plane_y >dadiji.plane_y - 80)//�ж�ս���Ƿ�ʹ�л�������ײ
	{
		int xxx = zhanji.plane_x;
		int yyy = zhanji.plane_y;
		zhanji.JIDRAW_Boom(cDC, xxx, yyy, gh);//����ײ��ս����ը����л������������
		Sleep(500);//ֹͣ500ms
		dadiji.plane_x = rand() % 400;
		while (dadiji.plane_x<20)
			dadiji.plane_x = rand() % 400;
		dadiji.plane_y = 0;
		zhanji.plane_x = 300;//ս���ص���ʼλ��
		zhanji.plane_y = 500;
	}
	if (dadiji.plane_y < 650)//��л��½�
		dadiji.plane_y = dadiji.plane_y + 5;
	else
		dadiji.plane_y = 0;//����ɻ��ɳ���Ϸ���� �������������
	dadiji.JIDRAW(cDC, gh); //����л�
	
}

void CAirplaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	CDC *cDC = this->GetDC();   //��õ�ǰ���ڵ�DC   
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

// CAirplaneWarView ��ӡ

BOOL CAirplaneWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CAirplaneWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CAirplaneWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CAirplaneWarView ���

#ifdef _DEBUG
void CAirplaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CAirplaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAirplaneWarDoc* CAirplaneWarView::GetDocument() const // �ǵ��԰汾��������
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
