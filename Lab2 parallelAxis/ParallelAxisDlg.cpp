
// ParallelAxisDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ParallelAxis.h"
#include "ParallelAxisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CParallelAxisDlg 对话框



CParallelAxisDlg::CParallelAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParallelAxisDlg::IDD, pParent)
	, KEEP(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CParallelAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, KEEP);
}

BEGIN_MESSAGE_MAP(CParallelAxisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CParallelAxisDlg::OnBnClickedButtonOpen)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CParallelAxisDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CParallelAxisDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CParallelAxisDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CParallelAxisDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CParallelAxisDlg::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CParallelAxisDlg::OnCbnSelchangeCombo6)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CParallelAxisDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CParallelAxisDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON3, &CParallelAxisDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CParallelAxisDlg 消息处理程序

BOOL CParallelAxisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();  
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ShowWindow(SW_NORMAL);
	//ShowWindow(SW_M);
	InitParallelAxis();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CParallelAxisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CParallelAxisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		MemoryBufferAhead();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CParallelAxisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









/****************************************************************初始化*********************************************************************************/
//初始化参数
void CParallelAxisDlg::InitParallelAxis(){
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_DrawBox); 
	pWnd->GetClientRect(&rect);
	pDC = pWnd->GetDC();  

	Box_W=rect.Width();   
	Box_H=rect.Height();  
	unitnum=5;
	unit=Box_W/unitnum;

	DOWN=false;
	KEEP=false;
	HeightLightColor=RGB(200,0,0);

	{
		Combo[0]=(CComboBox*)GetDlgItem(IDC_COMBO1);
		Combo[1]=(CComboBox*)GetDlgItem(IDC_COMBO2);
		Combo[2]=(CComboBox*)GetDlgItem(IDC_COMBO3);
		Combo[3]=(CComboBox*)GetDlgItem(IDC_COMBO4);
		Combo[4]=(CComboBox*)GetDlgItem(IDC_COMBO5);
		Combo[5]=(CComboBox*)GetDlgItem(IDC_COMBO6);
		for (int i=0;i<6;i++) Combo[i]->ResetContent(); //清空选项
	}

	UpdateData(false);
	InitMemoryBuffer();		
}

//初始化缓冲
void CParallelAxisDlg::InitMemoryBuffer(){
	//定义一个内存设备描述表对象（即后备缓冲区）
	CBitmap MemBitmap; //定义一个位图对象
	MemDC.CreateCompatibleDC(NULL);  //建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）
	MemBitmap.CreateCompatibleBitmap(pDC,Box_W,Box_H);//这时还不能绘图，因为没有位图的设备描述表是不能绘图的,下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//将位图选入到内存设备描述表,只有选入了位图的设备描述表才有地方绘图，画到指定的位图上
	MemDC.FillSolidRect(0,0,Box_W,Box_H,RGB(255,255,255));//先用背景色将位图清除干净，这里我用的是白色作为背景
	Grid();

	CBitmap MemBitmap1; 
	BgDC.CreateCompatibleDC(NULL);  
	MemBitmap1.CreateCompatibleBitmap(pDC,Box_W,Box_H);
	pOldBit=BgDC.SelectObject(&MemBitmap1);
	BgDC.BitBlt(0,0,Box_W,Box_H,&MemDC,0,0,SRCCOPY);

	CBitmap MemBitmap2; 
	SelDC.CreateCompatibleDC(NULL);  
	MemBitmap2.CreateCompatibleBitmap(pDC,Box_W,Box_H);
	pOldBit=SelDC.SelectObject(&MemBitmap2);
	SelDC.FillSolidRect(0,0,Box_W,Box_H,RGB(255,255,255));

	CBitmap MemBitmap3; 
	DC.CreateCompatibleDC(NULL);  
	MemBitmap3.CreateCompatibleBitmap(pDC,Box_W,Box_H);
	pOldBit=DC.SelectObject(&MemBitmap3);
	DC.FillSolidRect(0,0,Box_W,Box_H,RGB(255,255,255));

	//显示
	MemoryBufferAhead();	
}


 //画轴
void CParallelAxisDlg::Grid(){
	CPen pen,*oldpen;
	pen.CreatePen(PS_SOLID, 1,RGB(200,200,200));
	oldpen=MemDC.SelectObject(&pen);

	for (int i=0;i<=unitnum;i++){
		MemDC.MoveTo(unit*i,0);
		MemDC.LineTo(unit*i,Box_H);
	}
	MemDC.MoveTo(0,0);
	MemDC.LineTo(Box_W,0);
	MemDC.MoveTo(0,Box_H-1);
	MemDC.LineTo(Box_W,Box_H-1);
}

//显示
void CParallelAxisDlg::MemoryBufferAhead(){
	DC.BitBlt(0,0,Box_W,Box_H,&MemDC,0,0,SRCCOPY);
	DC.BitBlt(0,0,Box_W,Box_H,&SelDC,0,0,SRCAND);
	pDC->BitBlt(0,0,Box_W,Box_H,&DC,0,0,SRCCOPY);//将后备缓冲区中的图形拷贝到前端缓冲区
}




/******************************************************************文件处理*******************************************************************************/
//打开文件
void CParallelAxisDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("All Files (*.*)|*.*|TXT Files (*.txt)|*.txt|CSV Files (*.csv)|*.csv||"),
        NULL);
    if(dlg.DoModal()==IDOK){
        FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
		FileProcess();
	}
    else
    {
         return;
    }
}

//读取文件
void CParallelAxisDlg::FileProcess(){
	CStdioFile myFile;
	CFileException fileException;
	if(!myFile.Open(FilePathName,CFile::typeText|CFile::modeRead,&fileException)){
		TRACE("Can't open file %s, error = %u/n",FilePathName,fileException.m_cause);
		return;
	}

	myFile.SeekToBegin();

	CString line;
	SampleNum=0;
	AttributeNum=0;
	CStringArray strarr;
	BOOL ex;
	while (true){
		ex=myFile.ReadString(line);
		if (!ex) break;
		SampleNum++;

		AttributeNum=Split(line, ",",strarr);
		int i=SampleNum-1;
		for (int j=0;j<AttributeNum;j++){
			Sample[i][j]=atof(strarr[j]);
		}
	}
	InitDraw();
}

//string分割
int CParallelAxisDlg::Split(CString source, CString ch,CStringArray &strarr){
	CString TmpStr;
	strarr.RemoveAll();
	if(source.IsEmpty() || ch.IsEmpty()) return 0;
	int len=ch.GetLength();
	int findi=0;
	int findn=0;
	int sum=0;
 
	findn=source.Find(ch,findi);
	if (findn!=-1){
		TmpStr=source.Mid(0,findn);
		//TmpStr.Trim();
		strarr.Add(TmpStr);
		findi=findn+len;
		sum++;
	}
	else
	{
		//source.Trim();
		strarr.Add(source);
		sum++;
		return sum;
	}
 
 
	while (findn!=-1)//有发现
	{
			findn=source.Find(ch,findi);
		if (findn!=-1)
		{
			TmpStr=source.Mid(findi,findn-findi);
			//TmpStr.Trim();//去除头尾空格
			strarr.Add(TmpStr);
   
			findi=findn+len;
			sum++;
		}else{
			TmpStr=source.Mid(findi,source.GetLength()-findi);
			//TmpStr.Trim();
			strarr.Add(TmpStr);
   
			sum++;
   
		}
	}
 
	return sum;
}

//初始化读取的数据
void CParallelAxisDlg::InitDraw(){
	for (int i=0;i<6;i++) AttributeShow[i]=i;
	for (int i=0;i<SampleNum;i++) HeightLight[i]=false;

	char s[20];
	for (int i=0;i<6;i++){ 
		Combo[i]->ResetContent();
		for (int j = 0;  j < AttributeNum;  j++)
		{
			sprintf_s(s,"%d:%f",j+1,Sample[0][j]);
			Combo[i]->InsertString( j,s );
		}
		Combo[i]->SetCurSel(i);
	}


	double MM[100][2];
	for (int j=0;j<AttributeNum;j++){
		MM[j][0]=MM[j][1]=Sample[0][j];
		for (int i=1;i<SampleNum;i++){
			MM[j][0]=min(Sample[i][j],MM[j][0]);
			MM[j][1]=max(Sample[i][j],MM[j][1]);
		}
	}

	for (int i=0;i<SampleNum;i++)
		for (int j=0;j<AttributeNum;j++){
			Sample[i][j]=Box_H*(Sample[i][j]-MM[j][0])/(MM[j][1]-MM[j][0]);
		}
	
	DrawSample();
}




/*****************************************************************显示********************************************************************************/
//在图上表示数据
void CParallelAxisDlg::DrawSample(){
	MemDC.BitBlt(0,0,Box_W,Box_H,&BgDC,0,0,SRCCOPY);
	for (int i=0;i<SampleNum;i++){
		if (!HeightLight[i]){
			DrawOneSample(i,RGB(200,200,200));
		}
	}


	for (int i=0;i<SampleNum;i++){
		if (HeightLight[i]){
			DrawOneSample(i,HeightLightColor);
		}
	}
	MemoryBufferAhead();
}

//处理单个样本
void CParallelAxisDlg::DrawOneSample(int SampleCode,COLORREF Color){
	CPen pen,*oldpen;
	pen.CreatePen(PS_SOLID, 2,Color);
	oldpen=MemDC.SelectObject(&pen);

	int i=SampleCode;
	for (int s=0;s<5;s++){
		int ja=AttributeShow[s];
		int jb=AttributeShow[s+1];
		MemDC.MoveTo(s*unit,Box_H-Sample[i][ja]);
		MemDC.LineTo((s+1)*unit,Box_H-Sample[i][jb]);
	}
}


/******************************************************************维度选择*******************************************************************************/
//选择当前的显示的维度
void CParallelAxisDlg::SelectAttribute(){
	for (int i=0;i<6;i++) AttributeShow[i]=Combo[i]->GetCurSel();
	DrawSample();
}

void CParallelAxisDlg::OnCbnSelchangeCombo1()
{
	SelectAttribute();
}


void CParallelAxisDlg::OnCbnSelchangeCombo2()
{
	SelectAttribute();
}


void CParallelAxisDlg::OnCbnSelchangeCombo3()
{
	SelectAttribute();
}


void CParallelAxisDlg::OnCbnSelchangeCombo4()
{
	SelectAttribute();
}


void CParallelAxisDlg::OnCbnSelchangeCombo5()
{
	SelectAttribute();
}


void CParallelAxisDlg::OnCbnSelchangeCombo6()
{
	SelectAttribute();
}





/**************************************************************样本高亮选择***********************************************************************************/
void CParallelAxisDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SPoint=point;
	DOWN=true;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CParallelAxisDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	DOWN=false;
	SelDC.FillSolidRect(0,0,Box_W,Box_H,RGB(255,255,255));
	MemoryBufferAhead();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CParallelAxisDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!DOWN) return;

	EPoint=point;
	SelDC.FillSolidRect(0,0,Box_W,Box_H,RGB(255,255,255));
	CRect rect=CRect(SPoint,EPoint);
	rect.OffsetRect(-75,-38);
	SelDC.Rectangle(&rect);

	//找到被选中的轴
	int k=0;
	for (k=0;k<6;k++){
		if (k*unit>=rect.left&&k*unit<rect.right) break;
	}

	if (k!=6){
		int selectedAttr=AttributeShow[k];
		for (int i=0;i<SampleNum;i++){
			double tmp=Box_H-Sample[i][selectedAttr];
			if (tmp>=rect.top&&tmp<=rect.bottom){ 
				HeightLight[i]=true; 	if (KEEP) DrawOneSample(i,HeightLightColor);}
			else HeightLight[i]=false;
		}
		if (!KEEP) DrawSample();

	}
	MemoryBufferAhead();
	CDialogEx::OnMouseMove(nFlags, point);
}





/***************************************************************按键**********************************************************************************/
//选择颜色
void CParallelAxisDlg::OnBnClickedButton2()
{ 
	COLORREF color =RGB(200, 0, 0);
    CColorDialog cdlg(color, CC_FULLOPEN | CC_RGBINIT); // 设置默认颜色
    if(cdlg.DoModal() == IDOK) color = cdlg.GetColor();
	HeightLightColor=color;
}

//KEEP
void CParallelAxisDlg::OnBnClickedCheck1()
{
	UpdateData(true);
}

//清空
void CParallelAxisDlg::OnBnClickedButton3()
{
	for (int i=0;i<SampleNum;i++){
		HeightLight[i]=false; 
	}
	DrawSample();
}
