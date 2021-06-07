//=============================================================================
//
// �����_���[�w�b�_ [renderer.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RENDERER_H_
#define _RENDERER_H_

//�C���N���[�h
#include "main.h"

//=============================
//�N���X��`
//=============================

//�����_���[�N���X
class CRenderer
{
public:
	//============
	// �����o�֐�
	//============
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);                     // ������
	void Uninit(void);                                         // �I��
	void Update(void);                                         // �X�V
	void Draw(void);                                           // �`��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; } // �f�o�C�X�̎擾
	int GetDrawCount(void) { return m_nCntDraw; }
private:

#ifdef _DEBUG
	void DrawFPS(void); //FPS���̕\��
#endif

	//============
	// �����o�ϐ�
	//============
	PDIRECT3D9        m_pD3D;       // Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice; // Device�I�u�W�F�N�g(�`��ɕK�v)
	int m_nCntDraw;                 // ��t���[�����̉���ڕ`�揈����
#ifdef _DEBUG
	LPD3DXFONT        m_pFont;      // �t�H���g�ւ̃|�C���^
#endif
};

#endif