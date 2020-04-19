
// AirplaneWarView.h : CAirplaneWarView ��Ľӿ�
//

#pragma once


class CAirplaneWarView : public CView
{
protected: // �������л�����
	CAirplaneWarView();
	DECLARE_DYNCREATE(CAirplaneWarView)

	//��view���м������������
	Dadiji  dadiji;//��л�1̨
	Xiaodiji   xiaodiji[5];//������Ϸ������С�л�5̨
	Zidan zidan[30];//������Ϸ�������ӵ�30��
	Zhanji zhanji;//ս��һ̨
	CBitmap bkg;
	Gdiplus::Image *img_bkg; //Gdi+����ͼ
	CDC m_cacheDC;   //����DC

// ����
public:
	CAirplaneWarDoc* GetDocument() const;

// ����
public:
	void GameRunDraw();
	void RefreshPlane(CDC *pDC, Graphics *gh);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CAirplaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // AirplaneWarView.cpp �еĵ��԰汾
inline CAirplaneWarDoc* CAirplaneWarView::GetDocument() const
   { return reinterpret_cast<CAirplaneWarDoc*>(m_pDocument); }
#endif

