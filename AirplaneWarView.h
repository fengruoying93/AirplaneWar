
// AirplaneWarView.h : CAirplaneWarView 类的接口
//

#pragma once


class CAirplaneWarView : public CView
{
protected: // 仅从序列化创建
	CAirplaneWarView();
	DECLARE_DYNCREATE(CAirplaneWarView)

	//在view类中加入下面变量：
	Dadiji  dadiji;//大敌机1台
	Xiaodiji   xiaodiji[5];//保持游戏界面有小敌机5台
	Zidan zidan[30];//保持游戏界面有子弹30颗
	Zhanji zhanji;//战机一台
	CBitmap bkg;
	Gdiplus::Image *img_bkg; //Gdi+背景图
	CDC m_cacheDC;   //缓冲DC

// 特性
public:
	CAirplaneWarDoc* GetDocument() const;

// 操作
public:
	void GameRunDraw();
	void RefreshPlane(CDC *pDC, Graphics *gh);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CAirplaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // AirplaneWarView.cpp 中的调试版本
inline CAirplaneWarDoc* CAirplaneWarView::GetDocument() const
   { return reinterpret_cast<CAirplaneWarDoc*>(m_pDocument); }
#endif

