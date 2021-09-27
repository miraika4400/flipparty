//=============================================================================
//
// �w���|���S���w�b�_ [orderpolygon.cpp]
// Author : �R�c�@�ˑ�
//
//=============================================================================

//******************************
// �C���N���[�h
//******************************
#include "orderPolygon.h"
#include "manager.h"
#include "resource_texture.h"
#include "billboard.h"

//******************************
// �}�N����`
//******************************
#define ODER_POLYGON_LEFT_POS D3DXVECTOR3(50.0f,35.0f,100.0f)	//���̃|���S���̈ʒu
#define ODER_POLYGON_RIGHT_POS D3DXVECTOR3(-50.0f,35.0f,100.0f)	//�E�̃|���S���̈ʒu
#define ODER_POLYGON_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)			//�|���S���̃T�C�Y

D3DXVECTOR3 pos[CFlipper::FLIPPER_TYPE_MAX] =
{
	ODER_POLYGON_LEFT_POS,ODER_POLYGON_RIGHT_POS
};
//******************************
// �ÓI�����o�ϐ��錾
//******************************
bool COrderPolygon::m_bUse = true;

//******************************
// �R���X�g���N�^
//******************************
COrderPolygon::COrderPolygon():CScene(CScene::OBJTYPE_UI)
{
	//�����o�ϐ��̃N���A
	ZeroMemory(&m_Order, sizeof(m_Order));
}

//******************************
// �f�X�g���N�^
//******************************
COrderPolygon::~COrderPolygon()
{
}

//******************************
// �N���G�C�g
//******************************
COrderPolygon * COrderPolygon::Crate(void)
{
	//�w���|���S���N���X�̃|�C���^�ϐ�
	COrderPolygon *pOrderPolygon = NULL;

	//�C���X�^���X����
	pOrderPolygon = new COrderPolygon;

	if (pOrderPolygon)
	{
		//����������
		pOrderPolygon->Init();
	}

	return pOrderPolygon;
}

//******************************
// ����������
//******************************
HRESULT COrderPolygon::Init(void)
{
	for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
	{
		//���E�̃|���S���𐶐�
		m_Order[nCntPoygon].pOrderBillboard = CBillboard::Create(pos[nCntPoygon], ODER_POLYGON_SIZE);
		m_Order[nCntPoygon].bIsDraw = false;
	}
	
	m_bUse = true;

	return S_OK;
}

//******************************
// �I������
//******************************
void COrderPolygon::Uninit(void)
{
	for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
	{
		//���E�̃|���S�����폜
		if (m_Order[nCntPoygon].pOrderBillboard)
		{
			//�I������
			m_Order[nCntPoygon].pOrderBillboard->Uninit();

			//�������폜
			delete m_Order[nCntPoygon].pOrderBillboard;

			//�������̃N���A
			m_Order[nCntPoygon].pOrderBillboard = NULL;
		}
	}

	//���g�̍폜
	Release();
}

//******************************
// �X�V����
//******************************
void COrderPolygon::Update(void)
{
}

//******************************
// �`�揈��
//******************************
void COrderPolygon::Draw(void)
{
	if (m_bUse)
	{
		for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
		{
			if (m_Order[nCntPoygon].bIsDraw)
			{
				//���E�̃|���S���𐶐�
				m_Order[nCntPoygon].pOrderBillboard->Draw();
			}
		}
	}
}

//******************************
// �`��Z�b�g����
//******************************
void COrderPolygon::SetDraw(CFlipper::FLIPPER_TYPE flipperState, CFlipper::FLIPPER_STATE state)
{
	//����̏ꍇ
	if (flipperState == CFlipper::FLIPPER_TYPE_LEFT)
	{
		m_Order[CFlipper::FLIPPER_TYPE_LEFT].bIsDraw = true;
		m_Order[CFlipper::FLIPPER_TYPE_RIGHT].bIsDraw = false;

		if (state == CFlipper::FLIPPERSTATE_UP)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_UP));
		}
		else if (state == CFlipper::FLIPPERSTATE_DOWN)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_DOWN));
		}
		
	}
	//�E��̏ꍇ
	else if (flipperState == CFlipper::FLIPPER_TYPE_RIGHT)
	{
		m_Order[CFlipper::FLIPPER_TYPE_LEFT].bIsDraw = false;
		m_Order[CFlipper::FLIPPER_TYPE_RIGHT].bIsDraw = true;

		if (state == CFlipper::FLIPPERSTATE_UP)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_UP));
		}
		else if (state == CFlipper::FLIPPERSTATE_DOWN)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_DOWN));
		}
	}
}
