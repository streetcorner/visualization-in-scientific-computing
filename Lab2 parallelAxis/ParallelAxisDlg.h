
// ParallelAxisDlg.h : ͷ�ļ�
//

#pragma once


// CParallelAxisDlg �Ի���
class CParallelAxisDlg : public CDialogEx
{
// ����
public:
	CParallelAxisDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PARALLELAXIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CDC* pDC; //��ʾ������
	CDC MemDC; //ƽ�������������ݵĻ���
	CDC BgDC; //����
	CDC SelDC; //ѡ�п�Ļ���
	CDC DC; //������ʾ�Ļ���

	int Box_W; //��ʾ������
	int Box_H; //��ʾ����߶�
	int unit; //��Ԫ����=���/��Ԫ��Ŀ
	int unitnum; //��Ԫ��Ŀ5������Ŀ6

	CString FilePathName; //�ļ�·��+�ļ���

	int SampleNum; //��������Ŀ
	int AttributeNum; //���Ե���Ŀ
	double Sample[1000][100]; //����
	BOOL HeightLight[1000]; //�����Ƿ����
	COLORREF HeightLightColor;//��ǰ������ɫ

	int AttributeShow[6];//��ǰ��ʾ��ά��
	CComboBox* Combo[6];//ѡ���������ʾ��һά

	CPoint SPoint;//������㣬����갴������
	CPoint EPoint;//�����յ㣬����긡������
	BOOL DOWN; //�棺����갴��

	BOOL KEEP;//�棺�������еĸ�������

protected:
	void InitParallelAxis(); //��ʼ������
	void InitMemoryBuffer(); //�������Ĵ���
	void MemoryBufferAhead();	//������ǰ�ˣ���ʾ
	void Grid(); //����

	void FileProcess(); //�ļ�����
	int Split(CString source, CString ch,CStringArray &strarr); //��String�ָ�

	void InitDraw(); //�������ݺ�ĳ�ʼ������
	void SelectAttribute(); //ѡ��ǰ����ʾ��ά��
	void DrawSample(); //������������
	void DrawOneSample(int SampleCode,COLORREF Color); //����i������
	
public:
	afx_msg void OnBnClickedButtonOpen();  //���ļ�
	//����ƽ����
	afx_msg void OnCbnSelchangeCombo1();	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo6();
	//������ѡ��
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButton2(); //ѡ�������ɫ��Ĭ�Ϻ�ɫ
	afx_msg void OnBnClickedCheck1(); //KEEP,�������еĸ�������
	afx_msg void OnBnClickedButton3(); //������и���
};
