
// MfcOpencvAttDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMfcOpencvAttDlg �Ի���
class CMfcOpencvAttDlg : public CDialogEx
{
// ����
public:
	CMfcOpencvAttDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCOPENCVATT_DIALOG };

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
	CStatic m_testPicture;
	afx_msg void OnBnClickedChooseButton();
	afx_msg void OnBnClickedStartButton();
	CStatic m_showPicture;
	afx_msg void OnEnChangeResultEdit();
	afx_msg void OnStnClickedShowStatic();
};
