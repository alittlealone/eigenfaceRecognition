
// MfcOpencvAttDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MfcOpencvAtt.h"
#include "MfcOpencvAttDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMfcOpencvAttDlg �Ի���



CMfcOpencvAttDlg::CMfcOpencvAttDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMfcOpencvAttDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcOpencvAttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEST_STATIC, m_testPicture);
	DDX_Control(pDX, IDC_SHOW_STATIC, m_showPicture);
}

BEGIN_MESSAGE_MAP(CMfcOpencvAttDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHOOSE_BUTTON, &CMfcOpencvAttDlg::OnBnClickedChooseButton)
	ON_BN_CLICKED(IDC_START_BUTTON, &CMfcOpencvAttDlg::OnBnClickedStartButton)
	ON_STN_CLICKED(IDC_SHOW_STATIC, &CMfcOpencvAttDlg::OnStnClickedShowStatic)
END_MESSAGE_MAP()


// CMfcOpencvAttDlg ��Ϣ�������

BOOL CMfcOpencvAttDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMfcOpencvAttDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMfcOpencvAttDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMfcOpencvAttDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcOpencvAttDlg::OnBnClickedChooseButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("ͼ���ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, 0, szFilter, this);
	CString strFilePath;
 
	HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ͼƬ��ʾ�ڶԻ�����  
		strFilePath = fileDlg.GetPathName();
		//LoadBitMap���ܵ����ⲿͼ�񣬱�����LoadImage
		hBmp = (HBITMAP)LoadImage(NULL, strFilePath, IMAGE_BITMAP,
			0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); 
		m_testPicture.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_testPicture��λͼͼƬΪIDB_BITMAP1 

		UpdateWindow();
	}

}


int identify()
{
	return 5;
}

void CMfcOpencvAttDlg::OnBnClickedStartButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString result;
	result.Format(_T("%d"), identify());

	SetDlgItemText(IDC_RESULT_EDIT1, result);

	/*CString imagePath = _T("C:\\Users\\Administrator\\Desktop\\ATT\\s");
	imagePath += result + _T("\\1.bmp");*/
	CString imagePath = _T("./res/1.bmp");
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, imagePath, IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_showPicture.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_testPicture��λͼͼƬΪIDB_BITMAP1

	UpdateWindow();
}

