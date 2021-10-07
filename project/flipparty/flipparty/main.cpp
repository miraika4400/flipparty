//=============================================================================
//
// ���C������ [main.cpp]
// Author : ���V ����
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include <WinSock2.h>
#include "main.h"
#include "manager.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WINDOW_NAME      "" // �E�C���h�E�̃L���v�V������
#define IS_WINDOW_SCREEN false    // �E�B���h�E���t���X�N���[����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
//CRenderer *g_pRenderer = NULL; // �����_�����O�|�C���^
#ifdef _DEBUG
int					g_nCountFPS = 0;			// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	// ���������[�N������N
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	// �����̏�����
	srand((unsigned)time(NULL));

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		WINDOW_CLASS_NAME,
		NULL
	};

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(WINDOW_CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	CManager *pManager = new CManager;

	if (FAILED(pManager->Init(hInstance, hWnd, IS_WINDOW_SCREEN)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�

												// NULL�`�F�b�N
				if (pManager != NULL)
				{
					// �X�V����
					pManager->Update();

					// �`�揈��
					pManager->Draw();
				}

				//�t���[���J�E���g�A�b�v
				dwFrameCount++;
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(WINDOW_CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	// NULL�`�F�b�N
	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();

		// �������̉��
		delete pManager;
		pManager = NULL;

	}

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
//=============================================================================
// FPS�̎擾
//=============================================================================
int GetFps(void) 
{ 
	return g_nCountFPS; 
}    
#endif // _DEBUG