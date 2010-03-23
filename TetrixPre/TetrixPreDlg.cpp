// TetrixPreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TetrixPre.h"
#include "TetrixPreDlg.h"
#include ".\tetrixpredlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "gdiplus.lib")

CStream    scrStream;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTetrixPreDlg �Ի���



CTetrixPreDlg::CTetrixPreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTetrixPreDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrixPreDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PIC, m_pic);
    DDX_Control(pDX, IDC_DBG_VIEW, m_picDbg);
    DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CTetrixPreDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_TEST, OnBnClickedTest)
    ON_BN_CLICKED(IDC_LOAD, OnBnClickedLoad)
    ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
    ON_WM_TIMER()
    ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CTetrixPreDlg ��Ϣ��������
DWORD WINAPI Playtetris(LPVOID pVoid);
BOOL CTetrixPreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	scrStream.AddRef();
    //SetTimer(1,500,NULL);
    //DWORD id;
    //HANDLE hThread = ::CreateThread(NULL,0,Playtetris,this,0,&id);
    //if(hThread){
    //    ::CloseHandle(hThread);
    //}
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CTetrixPreDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTetrixPreDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CTetrixPreDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTetrixPreDlg::OnBnClickedTest()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
    //stream.SeekToBegin();
    //IStream stream;
    //image.Load(_T("E:\\My Programmes\\Tetrix\\JpegTest\\123.jpg"));
    SetTimer(1,500,NULL);
}

void CTetrixPreDlg::OnBnClickedLoad()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
    TCHAR szFilters[]=
        _T("Jpeg Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|All Files (*.*)|*.*||");
    CFileDialog dlg(
        true,_T("*"),_T("*.jpg"),OFN_FILEMUSTEXIST| OFN_HIDEREADONLY|OFN_EXPLORER  ,szFilters,0,0
        );
    if(dlg.DoModal() == IDOK){
        m_image.Load(dlg.GetPathName());
        CDC* pDC = m_pic.GetDC();
        RECT rect;
        m_pic.GetWindowRect(&rect);
        LONG w = rect.right - rect.left;
        LONG h = rect.bottom - rect.top;
        pDC->Rectangle(0,0,w,h);
        m_image.BitBlt(pDC->m_hDC,0,0,w,h,0,0);
        m_pic.ReleaseDC(pDC);
    }
}

void CTetrixPreDlg::OnBnClickedSave()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
    TCHAR szFilters[]=
        _T("Header File (*.h)|*.h|All Files (*.*)|*.*||");
    CFileDialog dlg(
        false,_T("*"),_T("image.h"),OFN_FILEMUSTEXIST| OFN_HIDEREADONLY|OFN_EXPLORER  ,szFilters,0,0
        );
    if(dlg.DoModal() == IDOK){
        const LONG w = m_image.GetWidth();
        const LONG h = m_image.GetHeight();
        CString result;
        CString ts;
        result.Format(_T("#define WIDTH  (%d)\n")
                      _T("#define HEIGHT  (%d)\n")
                      _T("/* RGB Array*/\n")
                      _T("#define  RGB_DATA    \\\n"),w,h);
        for(int row = 0; row<h; row++){
            for(int col=0; col<w;col++){
                COLORREF color = m_image.GetPixel(col,row);
                ts.Format(_T("0x%02X,0x%02X,0x%02X,"),
                GetRValue(color),GetGValue(color),GetBValue(color));
                result += ts;
                if( (col&7) == 7){
                    result += _T("\\\n");
                }
            }
            result += _T("\\\n");
        }
        result += _T("\n");
        FILE* fp = _tfopen(dlg.GetPathName(),_T("w+"));
        ::_ftprintf(fp,result);
        fclose(fp);
    }
}

extern  unsigned char TetrisMap[18*24];
extern  unsigned char scrBuf[19*23];
void CTetrixPreDlg::OnTimer(UINT nIDEvent)
{
    // TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
    // Every 50ms
    //for(int i=0;i<20;i++){
    //    for(int j=0;j<10;j++){
    //        scrBuf[(i+1)*19+j+1] = i+j+1;//TetrisMap[i*18 + j + 4];
    //    }
    //}
    //for(int i=0;i<4;i++){
    //    for(int j=0;j<4;j++){
    //        scrBuf[(i+4)*19+j+13] = i+j+1;
    //    }
    //}
    //m_keyCode = 4;
    //if(GetKeyState(VK_LEFT) & 0xFF00){
    //    m_keyCode = 1;
    //}else if(GetKeyState(VK_RIGHT) & 0xFF00){
    //    m_keyCode = 2;
    //}else if(GetKeyState(VK_UP) & 0xFF00){
    //    m_keyCode = 3;
    //}else if(GetKeyState(VK_DOWN) & 0xFF00){
    //    m_keyCode = 4;
    //}else{
    //    m_keyCode = 0;
    //}
    //Playtetris(this);
    PostMessage(WM_PLAYACTION,4,0);
    CDialog::OnTimer(nIDEvent);

}

LRESULT CTetrixPreDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: �ڴ�����ר�ô����/����û���
    if(WM_PLAYACTION == message){
        m_keyCode = wParam;
        Playtetris(this);
        CImage m_image;
        GenerateJpeg("Hehe.jpg");
        m_image.Load(&scrStream);
        CDC* pDC = m_pic.GetDC();
        RECT rect;
        m_pic.GetWindowRect(&rect);
        LONG w = rect.right - rect.left;
        LONG h = rect.bottom - rect.top;
        pDC->Rectangle(0,0,w,h);
        m_image.BitBlt(pDC->m_hDC,0,0,w,h,0,0);
        m_pic.ReleaseDC(pDC);
    }
    return CDialog::WindowProc(message, wParam, lParam);
}

void CTetrixPreDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
    CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}