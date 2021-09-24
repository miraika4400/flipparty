//=============================================================================
//
// �w���|���S���w�b�_ [orderpolygon.h]
// Author : �R�c�@�ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef ORDER_POLYGON_H
#define ORDER_POLYGON_H

//*****************************
// �C���N���[�h
//*****************************
#include "scene.h"
#include "flipper.h"

//*****************************
// �O���錾
//*****************************
class CBillboard;

//*****************************
// �N���X��`
//*****************************
class COrderPolygon :public CScene
{
public:
	typedef struct
	{
		CBillboard *pOrderBillboard;
		bool bIsDraw;
	}ORDER;

	COrderPolygon();
	~COrderPolygon();

	static COrderPolygon *Crate(void);	//�N���G�C�g����

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void SetDraw(CFlipper::FLIPPER_TYPE flipperState, CFlipper::FLIPPER_STATE state);		//�`��ݒ菈��
	static void SetUse(bool bUse) { m_bUse = bUse; }

private:
	static bool m_bUse;
	ORDER m_Order[CFlipper::FLIPPER_TYPE_MAX];
};

#endif