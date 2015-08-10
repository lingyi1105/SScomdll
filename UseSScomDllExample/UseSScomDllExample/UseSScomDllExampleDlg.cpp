
// UseSScomDllExampleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UseSScomDllExample.h"
#include "UseSScomDllExampleDlg.h"
#include "afxdialogex.h"
#include "Winspool.h"
#include "Windows.h"
#include "SScomdll.h"

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


// CUseSScomDllExampleDlg �Ի���



CUseSScomDllExampleDlg::CUseSScomDllExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUseSScomDllExampleDlg::IDD, pParent)
	, m_RecvNumber(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUseSScomDllExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_RecvNumber);
}

BEGIN_MESSAGE_MAP(CUseSScomDllExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUseSScomDllExampleDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RECIVESTRING, &CUseSScomDllExampleDlg::OnRecivestring)
	ON_BN_CLICKED(IDC_BUTTON2, &CUseSScomDllExampleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUseSScomDllExampleDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CUseSScomDllExampleDlg ��Ϣ�������

BOOL CUseSScomDllExampleDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/*if (!LookForSerialPortOtherFunc()){
		MessageBox("���Ҷ˿ں����쳣��");
	}*/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUseSScomDllExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUseSScomDllExampleDlg::OnPaint()
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
HCURSOR CUseSScomDllExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CUseSScomDllExampleDlg::LookForSerialPortOtherFunc(void)
{
	BOOL retValue = FALSE;
	try{
		CComboBox* pListBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
		int i = 0;
		int nSerialPortNum = 0;
		CString strSerialList[256];
		LPBYTE pBite = NULL;
		DWORD pcdNeeded = 0;
		DWORD pcReturned = 0;

		nSerialPortNum = 0;

		EnumPorts(NULL,2,pBite,0,&pcdNeeded,&pcReturned);
		pBite = new BYTE[pcdNeeded];

		EnumPorts(NULL,2,pBite,pcdNeeded,&pcdNeeded,&pcReturned);
		PORT_INFO_2 *pPort;
		pPort =(PORT_INFO_2*)pBite;
		for(i = 0; i < pcReturned; i++){
			CString str = pPort[i].pPortName;
			if (str.Left(3) == "COM"){
				strSerialList[nSerialPortNum] = str.Left(str.GetLength()-1);
				HANDLE hTestHandle =  CreateFile(strSerialList[nSerialPortNum],GENERIC_READ|GENERIC_WRITE,0,
					NULL,OPEN_EXISTING,NULL,NULL);
				if (hTestHandle != INVALID_HANDLE_VALUE){
					pListBox->AddString(strSerialList[nSerialPortNum]);
					nSerialPortNum++;
					CloseHandle(hTestHandle);
				}
			}
		}
		delete[] pBite;
		retValue = TRUE;
	}
	catch(...){
		retValue = FALSE;
	}
	return retValue;
}


void CUseSScomDllExampleDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_COMBO1,str);
	if (str.GetLength() == 0){
		MessageBox("�����봮�ں�!");
		return;
	}
	//MessageBox(str.GetBuffer(str.GetLength()));
	INT res = Opencom(str.GetBuffer(str.GetLength()),this->m_hWnd,WM_RECIVESTRING);
	if (res != 1){
		MessageBox("�򿪴���ʧ��!");
	}
	//str.Format("%d",res);
	//MessageBox(str.GetBuffer(str.GetLength()));
}


afx_msg LRESULT CUseSScomDllExampleDlg::OnRecivestring(WPARAM wParam, LPARAM lParam)
{
	CHAR* pbuf = (CHAR*)lParam;
	DWORD bufsize = *((DWORD*)wParam);
	UpdateData();
	m_RecvNumber += bufsize;
	UpdateData(FALSE);
	int count = ((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->GetLineCount();
	int nLastLineStart = ((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->LineIndex(count-1);
	int nLastLineEnd = nLastLineStart + ((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->LineLength(nLastLineStart);
	((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->SetSel(nLastLineEnd+1,nLastLineEnd+1);
	((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->ReplaceSel(pbuf);
	((CEdit*)(this->GetDlgItem(IDC_RICHEDIT21)))->PostMessage(WM_VSCROLL,SB_BOTTOM,0);
	return 0;
}


void CUseSScomDllExampleDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (CloseComm() == -1){
		MessageBox("CloseComm Error!!");
	}
}


void CUseSScomDllExampleDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if (str.GetLength() != 0){
		if (WriteComm(str.GetBuffer(str.GetLength()),str.GetLength()) != 1){
			MessageBox("WriteComm Error!");
		}
	}
}
