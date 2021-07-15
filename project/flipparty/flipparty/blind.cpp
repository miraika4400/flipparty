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
#define BLIND_POS D3DXVECTOR3(0.0f, 15.0f, 0.0f)			//�u���C���h�̈ʒu
#define BLIND_SIZE D3DXVECTOR3(100.0f, 60.0f, 0.0f)			//�u���C���h�̃T�C�Y

#define BLIND_MOVE 5.0f										//�ړ���
#define MOVE_START_TIME 20									//�ړ��J�n�^�C��

//===================================
// �R���X�g���N�^
//===================================
CBlind::CBlind()
{
	m_nTime = 0;
	m_state = BLIND_STATE_MOVE;
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
CBlind * CBlind::Create(int nTime)
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
		if (m_nTime <= MOVE_START_TIME)
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
