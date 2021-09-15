////////////////////////////////////////////////////
//
//    blind�N���X�̏���[blind.cpp]
//    Author:�R�c �ˑ�
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "blind.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//===================================
// �}�N����`
//===================================
#define BLIND_START_POS D3DXVECTOR3(0.0f, 220.0f, -100.0f)	//�J�n���̃u���C���h�̈ʒu
#define BLIND_POS D3DXVECTOR3(0.0f, -20.0f, 0.0f)			//�u���C���h�̈ʒu
#define BLIND_SIZE D3DXVECTOR3(100.0f, 60.0f, 0.0f)			//�u���C���h�̃T�C�Y
#define BLIND_MOVE 5.0f										//�ړ���

//===================================
// �R���X�g���N�^
//===================================
CBlind::CBlind() : CScene3d(OBJTYPE_BG)
{
	m_nTime = 0;
	m_state = BLIND_STATE_MOVE;
	m_nMoveStartTime = 0;
	m_pBlackPolygon = NULL;
}

//===================================
// �f�X�g���N�^
//===================================
CBlind::~CBlind()
{
}

//===================================
// �N���G�C�g�֐�
//===================================
CBlind * CBlind::Create(int nTime, int nStartTime)
{
	// �|�C���^�ϐ�
	CBlind *pBlind = NULL;

	//�C���X�^���X����
	pBlind = new CBlind;

	if (pBlind)
	{
		//����������
		pBlind->Init();
		pBlind->SetTime(nTime);
		pBlind->m_nMoveStartTime = nStartTime;
	}

	return pBlind;
}

//===================================
// ����������
//===================================
HRESULT CBlind::Init(void)
{
	//����������
	CScene3d::Init();

	//�ʒu�̐ݒ�
	SetPos(BLIND_START_POS);

	//�T�C�Y�̐ݒ�
	SetSize(BLIND_SIZE);

	//�`�揇�̐ݒ�
	SetPriority(CScene::OBJTYPE_MOTION);

	//�e�N�X�`���̐ݒ�
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_BLIND));

	//���|���S���̐���
	m_pBlackPolygon = CScene3d::Create(
		D3DXVECTOR3(BLIND_START_POS.x, BLIND_START_POS.y, BLIND_START_POS.z - 1.0f), 
		BLIND_SIZE);
	m_pBlackPolygon->SetPriority(OBJTYPE_BG);


	//���|���S���̐F�ݒ�
	if (m_pBlackPolygon)
	{
		m_pBlackPolygon->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	return S_OK;
}

//===================================
// �I������
//===================================
void CBlind::Uninit(void)
{
	//�I������
	CScene3d::Uninit();
}

//===================================
// �X�V����
//===================================
void CBlind::Update(void)
{
	//�X�V����
	CScene3d::Update();

	if (m_state == BLIND_STATE_MOVE)
	{
		//�ړ��J�n�^�C����菬�����Ȃ�����
		if (m_nTime <= m_nMoveStartTime)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = GetPos();

			//�ړ��ʂ�^����
			pos.y -= BLIND_MOVE;

			//�ړI�̈ʒu�ɓ��B������
			if (pos.y <= BLIND_POS.y)
			{
				//�ʒu���C��
				pos.y = BLIND_POS.y;

				//�ړ�����߂�
				m_state = BLIND_STATE_NORMAL;
			}

			//�ʒu�̐ݒ�
			SetPos(pos);

			//���|���S���̐ݒ�
			if (m_pBlackPolygon)
			{
				m_pBlackPolygon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z - 1.0f));
			}
		}
	}
}

//===================================
// �`�揈��
//===================================
void CBlind::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	//Z�o�b�t�@�ݒ�̕ۑ��p�ϐ�
	DWORD dwCurZTest = 0;
	
	if (m_state == BLIND_STATE_NORMAL)
	{
		//Z�o�b�t�@�̐ݒ���ꎞ�ۑ�
		pDevice->GetRenderState(D3DRS_ZFUNC, &dwCurZTest);

		//�X�e���V���e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x03);				//�X�e���V���o�b�t�@�֔��f����Q�ƒl�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);			//�}�X�N�̐ݒ�i�r�b�g�����Ȃ��悤�Ɏw��j
		pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//0xffffffff�ɂ���
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);		//�X�e���V���e�X�g�̔����K����������悤�Ɏw��

		//�e�X�g�̌��ʂ̑g�ݍ��킹�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//�X�e���V���EZ�e�X�g�Ƃ��Ɏ��s�����ꍇ
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//�X�e���V���̂ݐ��������ꍇ
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//�����Ƃ����������ꍇ
	}

	//�|���S���̕`��
	CScene3d::Draw();

	if (m_state == BLIND_STATE_NORMAL)
	{
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	//�X�e���V���e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, dwCurZTest);		//Z�o�b�t�@�̐ݒ��߂�
	}
}
