
// UseSScomDllExampleDlg.h : ͷ�ļ�
//

#pragma once

#define WM_RECIVESTRING WM_USER + 100

// CUseSScomDllExampleDlg �Ի���
class CUseSScomDllExampleDlg : public CDialogEx
{
// ����
public:
	CUseSScomDllExampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_USESSCOMDLLEXAMPLE_DIALOG };

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
private:
	BOOL LookForSerialPortOtherFunc(void);
public:
	afx_msg void OnBnClickedButton1();
protected:
	afx_msg LRESULT OnRecivestring(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
private:
	UINT m_RecvNumber;
};
