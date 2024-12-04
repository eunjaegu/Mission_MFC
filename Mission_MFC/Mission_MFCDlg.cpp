
// Mission_MFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Mission_MFC.h"
#include "Mission_MFCDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMissionMFCDlg dialog



CMissionMFCDlg::CMissionMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMissionMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMissionMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMissionMFCDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMissionMFCDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMissionMFCDlg::OnBnClickedBtnOpen)
	ON_EN_CHANGE(IDC_EDIT_COUNT, &CMissionMFCDlg::OnEnChangeEditCount)
	ON_STN_CLICKED(IDC_STATIC_IMAGE, &CMissionMFCDlg::OnStnClickedStaticImage)
	ON_EN_CHANGE(IDC_EDIT_XY, &CMissionMFCDlg::OnEnChangeEditXy)
END_MESSAGE_MAP()


// CMissionMFCDlg message handlers

BOOL CMissionMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMissionMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMissionMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMissionMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//
void CMissionMFCDlg::OnBnClickedBtnDraw()
{
	//�̹��� ũ�� ����
	int nWidth = 640;
	int nHeight = 480;
	int nBPP = 8;

	m_image.Destroy(); // ���� �̹��� ����
	m_image.Create(nWidth, -nHeight, nBPP); // �̹��� ����
	if (nBPP == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	
	// �̹����� ù ���� ����Ʈ�� �����´�.
	int nPitch = m_image.GetPitch();
	
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

		int nRadius = rand() % 50 + 10; // 10~60 ũ�� ����
		int nX = rand() % (nWidth - nRadius * 2);
		int nY = rand() % (nHeight - nRadius * 2);
		int nGray = rand() % 128; // ȸ�� ���� ����(��ο� �迭)
		
		drawCircle(fm, nX, nY, nRadius, nGray);

	UpdateDisplay();
}

// Draw�� �̹��� �����ϱ�
void CMissionMFCDlg::OnBnClickedBtnAction()

{
	// CEdit ��Ʈ�ѿ��� �Էµ� ���� ������
	CString strCount;
	CEdit* pEditCount = (CEdit*)GetDlgItem(IDC_EDIT_COUNT); // CEdit ��Ʈ�� ID�� IDC_EDIT_COUNT�� ���
	pEditCount->GetWindowText(strCount); // �ؽ�Ʈ ��������

	// ���� �Է� ĭ ���� �� �޽��� ���
	if (strCount.IsEmpty()) {
		AfxMessageBox(_T("�Ʒ� ��ĭ�� ���ڸ� �Է����ּ���."));
		return; 
	}

	// �Է°� ���ڷ� ��ȯ
	int m_nCircleCount = _ttoi(strCount); // CString�� int�� ��ȯ

	// ���� ������ŭ �ݺ�
	for (int i = 0; i < m_nCircleCount; i++) {
		// ���� ������ ���� ��ġ, ũ��, ȸ�� ���� ����
		int nRadius = rand() % 50 + 10; // 10~60 ũ�� ����
		int nX = rand() % (m_image.GetWidth() - nRadius * 2);
		int nY = rand() % (m_image.GetHeight() - nRadius * 2);
		int nGray = rand() % 128; // ȸ�� ���� ����(��ο�迭)

		// �� ��ġ ������Ʈ �� ȭ�鿡 ���
		UpdateCirclePosition(nX, nY, nRadius, nGray);

		// ���� �̸� ����(���� �ð�)
		CString strFileName;
		SYSTEMTIME st;
		GetLocalTime(&st);
		strFileName.Format(_T("c:\\image\\save_%04d%02d%02d%02d%02d%02d.bmp"),
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		// �̹��� ����
		m_image.Save(strFileName);

		// �� �׸��� �� ��� ��� (�ִϸ��̼� ȿ��)
		Sleep(1000);
	}
}

// ����� �̹��� �ҷ�����
void CMissionMFCDlg::OnBnClickedBtnOpen()
{
	// ���� ���̾�α׿��� �̹��� ������ �ε��ϰ� OpenCV�� ��ȯ
	cv::Mat matImage;

	// �̹��� ���� �ε� �� openCV�� ��ȯ
	LoadImageFile(matImage);
		
	// �� ã�� �� ���߽�, ��ǥ ã��
	FindCircleXY(matImage);

	// ó���� �̹����� Picture Control�� ������Ʈ
	UpdateImageDlg(matImage);
}

// ȭ�鿡 �̹��� �׸���(�Լ� ����)
void CMissionMFCDlg::UpdateDisplay()
{
	
	// PICTURE CONTROL�� �̹����� ǥ���ϴ� ����
	CStatic* pStaticCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE); // PICTURE CONTROL ��������
	pStaticCtrl->ModifyStyle(0xF, SS_BITMAP);  // PICTURE CONTROL�� ��Ʈ�� ��Ÿ�Ϸ� ����

	// ��Ʈ���� �����Ͽ� PICTURE CONTROL�� �̹��� ǥ��
	HBITMAP hBitmap = m_image;  // CImage ��ü���� HBITMAP�� ���� ������
	pStaticCtrl->SetBitmap(hBitmap); // PICTURE CONTROL�� ��Ʈ�� ����
	Invalidate(); // ���̾�α׸� �ٽ� �׸����� ��û
	
}

// �� ��ġ ������Ʈ �� ȭ�鿡 ���
void CMissionMFCDlg::UpdateCirclePosition(int nX, int nY, int nRadius, int nGray)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// �̹����� ����� ������� ����(�� �����)
	memset(fm, 0xff, nWidth * nHeight); // ����� ������� ����

	// ���ο� ���� �׸���
	drawCircle(fm, nX, nY, nRadius, nGray);

	UpdateDisplay();

}

// �̹��� ���� ��ǥ ���� ����
BOOL CMissionMFCDlg::valiImagPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));	
}

// �� �׸���
void CMissionMFCDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

// �� �ȿ� �ȼ� �� ���� Ȯ��
bool CMissionMFCDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDit = dX * dX + dY * dY;

	if (dDit < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
}

// Edit Control : ������ �� ���� �Է�
void CMissionMFCDlg::OnEnChangeEditCount()
{
	CString strCount;
	GetDlgItemText(IDC_EDIT_COUNT, strCount);
	m_nCircleCount = _ttoi(strCount); // ���ڿ��� ������ ��ȯ
}

// Picture Control : image ǥ��
void CMissionMFCDlg::OnStnClickedStaticImage()
{
	
}

// Edit Control : Center(x,y), Radius ǥ��
void CMissionMFCDlg::OnEnChangeEditXy()
{

}

// �̹��� ���� �ε� �� openCV�� ��ȯ
bool CMissionMFCDlg::LoadImageFile(cv::Mat& matImage)
{
	// ���� ���̾�α� ��ü ����(���� ���)
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK) {
		CString strFilePath = dlg.GetPathName();
		m_image.Destroy(); // ���� �̹��� ����

		// �̹��� �ҷ�����
		if (m_image.Load(strFilePath) == S_OK) {
			// �̹��� ������ OpenCV �������� ��ȯ
			HBITMAP hBitmap = (HBITMAP)m_image.Detach();
			CImage tempImage;
			tempImage.Attach(hBitmap);

			// �̹����� OpenCV�� Mat ��ü�� ��ȯ
			int width = tempImage.GetWidth();
			int height = tempImage.GetHeight();
			matImage = cv::Mat(height, width, CV_8UC3);
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					COLORREF color = tempImage.GetPixel(x, y);
					matImage.at<cv::Vec3b>(y, x)[0] = GetBValue(color);
					matImage.at<cv::Vec3b>(y, x)[1] = GetGValue(color);
					matImage.at<cv::Vec3b>(y, x)[2] = GetRValue(color);
				}
			}

			return true;
		}
		else {
			AfxMessageBox(_T("�̹��� ������ �ҷ��� �� �����ϴ�."));
			return false;
		}
	}
	return false;
}

// �� ã�� �� ���߽�, ��ǥ ã��
void CMissionMFCDlg::FindCircleXY(cv::Mat& matImage)
{
	// �׷��̽����Ϸ� ��ȯ
	cv::Mat gray;
	cv::cvtColor(matImage, gray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);

	// HoughCircles�� �� ã��
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 50, 20, 0, 0);

	// �� �߰� �� �߽� ��ǥ�� ������ ���
	if (circles.size() > 0) {
		for (size_t i = 0; i < circles.size(); i++) {
			cv::Vec3f c = circles[i];
			int x = cvRound(c[0]);
			int y = cvRound(c[1]);
			int radius = cvRound(c[2]);

			// ���� ���� �̹����� �׸���
			cv::circle(matImage, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 2); // �ʷϻ� ��

			// X ����� ũ�⸦ �������� ����Ͽ� ����
			int lineLength = radius / 5; // �������� 1/5 ũ��� X ��� ���� ����

			// ���� �߽ɿ� X ��� �׸���
			cv::line(matImage, cv::Point(x - lineLength, y - lineLength), cv::Point(x + lineLength, y + lineLength), cv::Scalar(0, 0, 255), 2); // �밢��1
			cv::line(matImage, cv::Point(x - lineLength, y + lineLength), cv::Point(x + lineLength, y - lineLength), cv::Scalar(0, 0, 255), 2); // �밢��2

			// ��ǥ�� �ؽ�Ʈ ǥ��
			std::string text = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
			int baseline = 0;
			cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseline);
			cv::Point textOrigin(x - textSize.width / 2, y - textSize.height - 5);
			cv::putText(matImage, text, textOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);

			// ���� �߽ɰ� �������� edit control�� ǥ��
			CString strMessage;
			strMessage.Format(_T("(%d, %d), %d"), x, y, radius);
			SetDlgItemText(IDC_EDIT_XY, strMessage); // ID�� IDC_EDIT_XY�� Edit Control�� �ؽ�Ʈ ǥ��
		}
	}
	else {
		SetDlgItemText(IDC_EDIT_XY, _T("�� �̹߰�"));
	}
}

// ó���� �̹����� Picture Control�� ������Ʈ
void CMissionMFCDlg::UpdateImageDlg(cv::Mat& matImage)
{
	// OpenCV�� ó���� �̹����� �ٽ� CImage ��ü�� ��ȯ
	cv::Mat matImageRGB;
	cv::cvtColor(matImage, matImageRGB, cv::COLOR_BGR2RGB); // OpenCV���� BGR -> RGB�� ��ȯ

	// �̹��� ũ��� ������ CImage�� �°� ����
	CImage tempImage;
	int width = matImage.cols;
	int height = matImage.rows;
	tempImage.Destroy();
	tempImage.Create(width, height, 24); // 24��Ʈ �÷� �̹����� ����

	// �̹����� CImage�� ����
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cv::Vec3b color = matImageRGB.at<cv::Vec3b>(y, x);
			tempImage.SetPixel(x, y, RGB(color[2], color[1], color[0])); // RGB�� ���� ����
		}
	}

	// PICTURE CONTROL ��ü ��������
	CStatic* pStaticCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
	pStaticCtrl->ModifyStyle(0xF, SS_BITMAP);  // PICTURE CONTROL�� ��Ʈ�� ��Ÿ�Ϸ� ���� �� �غ�

	// tempImage���� ��Ʈ�� �ڵ� �и� �� ��ȯ
	HBITMAP hNewBitmap = (HBITMAP)tempImage.Detach();
	pStaticCtrl->SetBitmap(hNewBitmap); // �и��� ��Ʈ�� �ڵ��� PICTURE CONTROL�� ���� �� ǥ��

	Invalidate();  // ������Ʈ�� ���ο� �̹��� ǥ��

}

