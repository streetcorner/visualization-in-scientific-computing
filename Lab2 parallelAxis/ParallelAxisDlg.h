
// ParallelAxisDlg.h : 头文件
//

#pragma once


// CParallelAxisDlg 对话框
class CParallelAxisDlg : public CDialogEx
{
// 构造
public:
	CParallelAxisDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PARALLELAXIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CDC* pDC; //显示的区域
	CDC MemDC; //平行轴上所有数据的绘制
	CDC BgDC; //背景
	CDC SelDC; //选中框的绘制
	CDC DC; //最终显示的缓冲

	int Box_W; //显示区域宽度
	int Box_H; //显示区域高度
	int unit; //单元长度=宽度/单元数目
	int unitnum; //单元数目5，轴数目6

	CString FilePathName; //文件路径+文件名

	int SampleNum; //样本的数目
	int AttributeNum; //属性的数目
	double Sample[1000][100]; //数据
	BOOL HeightLight[1000]; //样本是否高亮
	COLORREF HeightLightColor;//当前高亮颜色

	int AttributeShow[6];//当前显示的维度
	CComboBox* Combo[6];//选择所在轴表示哪一维

	CPoint SPoint;//矩形起点，或鼠标按下坐标
	CPoint EPoint;//矩形终点，或鼠标浮起坐标
	BOOL DOWN; //真：有鼠标按下

	BOOL KEEP;//真：保持已有的高亮不变

protected:
	void InitParallelAxis(); //初始化参数
	void InitMemoryBuffer(); //缓冲区的创建
	void MemoryBufferAhead();	//拷贝到前端，显示
	void Grid(); //画轴

	void FileProcess(); //文件处理
	int Split(CString source, CString ch,CStringArray &strarr); //将String分割

	void InitDraw(); //输入数据后的初始化操作
	void SelectAttribute(); //选择当前的显示的维度
	void DrawSample(); //画出所有样本
	void DrawOneSample(int SampleCode,COLORREF Color); //画第i条样本
	
public:
	afx_msg void OnBnClickedButtonOpen();  //打开文件
	//六个平行轴
	afx_msg void OnCbnSelchangeCombo1();	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo6();
	//样本的选择
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButton2(); //选择高亮颜色，默认红色
	afx_msg void OnBnClickedCheck1(); //KEEP,保持已有的高亮不变
	afx_msg void OnBnClickedButton3(); //清除所有高亮
};
