//=============================================================================
//
// sea�w�b�_ [sea.cpp]
// Author : ���V ����
//
//=============================================================================

//******************************
// �C���N���[�h
//******************************
#include "sea.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

//*****************************
// �}�N����`
//*****************************
#define BMP_TEX_PATH     "data/Textures/sea/BMP_water4.png"   // �o���v�}�b�v�e�N�X�`���̃p�X
#define BMP_TEX_PATH2    "data/Textures/sea/BMP_water4.png"   // �o���v�}�b�v�e�N�X�`���̃p�X
#define CUBE_TEX_PATH    "data/Textures/sea/cube_sky.dds"     // �L���[�u�e�N�X�`���̃p�X
#define SHADER_PATH      "data/HLSL/SeaShader.fx"             // HLSL�t�@�C���̃p�X
#define SIZE D3DXVECTOR3(1500.0f,1.0f,1500.0f)

//#define COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)               // �J���[
//#define COLOR D3DXCOLOR(0.3f,0.4f,1.0f,1.0f)             // �J���[

// �L���[�u�e�N�X�`������
#define CUB_RATE_DIRTY  4.0f
#define CUB_RATE_NORMAL 4.0f
#define CUB_RATE_EVENING 6.0f

// �J���[
#define COLOR_DIRTY D3DXCOLOR( 0.5f,0.0f,0.3f,1.0f)   
#define COLOR_NORMAL D3DXCOLOR(0.5f,0.6f,1.0f,1.0f)
#define COLOR_EVENING D3DXCOLOR(1.0f,0.2f,0.1f,1.0f)

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CObject3dShader::Shader CSea::m_shader = {};  // �V�F�[�_�[�\����
LPDIRECT3DTEXTURE9 CSea::m_apBmpTex[2] = {};

//******************************
// �R���X�g���N�^
//******************************
CSea::CSea() :CObject3dShader(OBJTYPE_SEA)
{
	m_fWaveaRate = 0.0f;
	m_fWaveSpeed = 0.0f;
	m_seaType = TYPE_DIRTY;
	m_fHeight = 0.0f;
	m_basePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//******************************
// �f�X�g���N�^
//******************************
CSea::~CSea()
{
}

//******************************
// �N���G�C�g
//******************************
CSea * CSea::Create(const D3DXVECTOR3 pos, const float fWaveSeed, SEA_TYPE seaType)
{
	// �������̊m��
	CSea *pSea;
	pSea = new CSea;

	// �^�C�v�̐ݒ�
	pSea->m_seaType = seaType;
	// ������
	pSea->Init();

	// �e�l�̑���E�Z�b�g
	pSea->SetPos(pos);               // ���W�̃Z�b�g
	pSea->m_basePos = pos;
	pSea->BindTexture(m_apBmpTex[0]);
	pSea->m_fWaveSpeed = fWaveSeed;
	return pSea;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CSea::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// HLSL�t�@�C���̓ǂݍ���
	D3DXCreateEffectFromFile(pDevice, SHADER_PATH, NULL, NULL, 0, NULL, &m_shader.pEffect, NULL);
	// �e�N�j�b�N��
	sprintf(&m_shader.achTechniqueName[0], "%s", "Shader");

	// �L���[�u�e�N�X�`���̐���
	D3DXCreateCubeTextureFromFile(pDevice, CUBE_TEX_PATH, &m_shader.pCubeTex);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BMP_TEX_PATH, &m_apBmpTex[0]);
	D3DXCreateTextureFromFile(pDevice, BMP_TEX_PATH2, &m_apBmpTex[1]);
	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CSea::Unload(void)
{
	if (m_shader.pEffect != NULL)
	{
		m_shader.pEffect->Release();
		m_shader.pEffect = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apBmpTex[nCnt] != NULL)
		{
			m_apBmpTex[nCnt]->Release();
			m_apBmpTex[nCnt] = 0;
		}
	}
}

//******************************
// ����������
//******************************
HRESULT CSea::Init(void)
{
	if (FAILED(CObject3dShader::Init()))
	{
		return E_FAIL;
	}

	// �V�F�[�_�[�̃Z�b�g
	SetShader(m_shader);

	// �^�C�v�ɂ���ĐF����
	switch (m_seaType)
	{
	case TYPE_DIRTY:
		// �F�̐ݒ�@
		SetColor(COLOR_DIRTY);

		break;

	case TYPE_NORMAL:
		SetColor(COLOR_NORMAL);
		break;

	case TYPE_EVENING:
		SetColor(COLOR_EVENING);
		break;
	default:
		break;
	}

	SetSize(SIZE);
	return S_OK;
}

//******************************
// �I������
//******************************
void CSea::Uninit(void)
{
	CObject3dShader::Uninit();
}

//******************************
// �X�V����
//******************************
void CSea::Update(void)
{
	//SetRot(D3DXVECTOR3(0.0001f,0.0f,0.01f));
	m_fWaveaRate += m_fWaveSpeed;

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();
	m_fHeight += 0.02f;
	pos.y = m_basePos.y + sin(m_fHeight)*5.0f;
	SetPos(pos);
}

//******************************
// �`�揈��
//******************************
void CSea::Draw(void)
{
	CObject3dShader::Draw();
}

//******************************
// HLSL�ɒl�𑗂�
//******************************
void CSea::SetShaderValue(void)
{
	D3DXVECTOR3 eye = D3DXVECTOR3(0, 0, -2);
	GetShader().pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	GetShader().pEffect->SetFloatArray("SpecularColor", (float*)&D3DXVECTOR4(1, 1, 1, 1), 4);
	GetShader().pEffect->SetTexture("Tex", m_apBmpTex[0]);
	GetShader().pEffect->SetTexture("TexNormal", m_apBmpTex[0]);
	GetShader().pEffect->SetTexture("TexNormal2", m_apBmpTex[1]);
	GetShader().pEffect->SetTexture("CubeTex", GetShader().pCubeTex);

	float fWave = sinf(m_fWaveaRate);

	if (fWave < 0) fWave *= -1;
	GetShader().pEffect->SetFloat("fWaveRate", fWave);
	GetShader().pEffect->SetFloat("fWaveMove", m_fWaveaRate);

	switch (m_seaType)
	{
	case TYPE_DIRTY:
		// �F�̐ݒ�@
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_DIRTY);
		break;

	case TYPE_NORMAL:
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_NORMAL);
		break;

	case TYPE_EVENING:
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_EVENING);
		break;
	default:
		break;
	}


}
