//=============================================================================
//
// player_flygame�w�b�_ [player_flygame.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_FLYGAME_H_
#define _PLAYER_FLYGAME_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "player.h"
#include "flipper.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************

// �v���C���[�N���X
class CFlyGamePlayer : public CPlayer
{
public:
	// ��
	// ���
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_STAN,
		STATE_MAX
	}STATE;

	// �����o�֐�
	CFlyGamePlayer();
	~CFlyGamePlayer();
	static CFlyGamePlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ��Ԃ̎擾�E�Z�b�g
	STATE GetState(void) { return m_state; }
	void SetState(STATE state) { m_state = state; }

private:
	void Fly(CFlipper::FLIPPER_STATE stateNow, CFlipper::FLIPPER_STATE stateOld); // ��ԏ���
	void ManageState(void);
	void ControllFlipper(void);    // �H�̑���

	// �����o�ϐ�
	float m_fHeightDist; // �����̖ڕW�l
	STATE m_state; // ���
	int m_nCntState;// ��ԃJ�E���g
};

#endif
