////////////////////////////////////////////////////
//
//    Z�l�e�N�X�`���N���X�̏���[Z_Tex.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "z_tex.h"
#include "manager.h"
#include "renderer.h"

//=============================
// �}�N����`
//=============================

//=============================
// �ÓI�����o�ϐ��錾
//=============================

//=============================
// �R���X�g���N�^
//=============================
CZTex::CZTex()
{
	// �ϐ��̃N���A
	m_pZBufTex  = NULL;
	m_pZTexSurf = NULL;
	m_pZTexZBuf = NULL;
}

//=============================
// �f�X�g���N�^
//=============================
CZTex::~CZTex()
{
}

//=============================
// �N���G�C�g
//=============================
CZTex * CZTex::Create(void)
{
	CZTex *pZtex = new CZTex;
	pZtex->Init();

	return pZtex;
}

//=============================
// ����������
//=============================
HRESULT CZTex::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	UINT width;    // ��
	UINT height;   // ��

	LPDIRECT3DSURFACE9 pTmpSf;
	pDevice->GetDepthStencilSurface(&pTmpSf);

	// �f�o�C�X�̐[�x�o�b�t�@�̕��ƍ������擾
	D3DSURFACE_DESC sufDesc;
	pTmpSf->GetDesc(&sufDesc);
	width = sufDesc.Width;
	height = sufDesc.Height;

	pTmpSf->Release();

	// �e�N�X�`���̐���
	D3DXCreateTexture(pDevice, width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pZBufTex);

	m_pZBufTex->GetSurfaceLevel(0, &m_pZTexSurf);
	m_pZTexSurf->GetDesc(&sufDesc);
	width = sufDesc.Width;
	height = sufDesc.Height;

	// �[�x�o�b�t�@�T�[�t�F�C�X�̍쐬
	pDevice->CreateDepthStencilSurface(width, height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &m_pZTexZBuf, NULL);

	return S_OK;
}

//=============================
// �I������
//=============================
void CZTex::Uninit(void)
{
	if (m_pZBufTex != NULL)
	{
		m_pZBufTex->Release();
		m_pZBufTex = NULL;
	}

	if (m_pZTexSurf != NULL)
	{
		m_pZTexSurf->Release();
		m_pZTexSurf = NULL;
	}

	if (m_pZTexZBuf != NULL)
	{
		m_pZTexZBuf->Release();
		m_pZTexZBuf = NULL;
	}
}


//=============================
// �e�N�X�`���������݊J�n
//=============================
void CZTex::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderTarget(0, m_pZTexSurf);
	pDevice->SetDepthStencilSurface(m_pZTexZBuf);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
}

//=============================
// �e�N�X�`���������ݏI��
//=============================
void CZTex::End(void)
{
}
