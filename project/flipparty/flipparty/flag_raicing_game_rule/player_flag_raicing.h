//=============================================================================
//
// player_flag_raicing�w�b�_ [player_flag_raicing.h]
// Author : �R�c�@�ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_FLAG_RAICING_H_
#define _PLAYER_FLAG_RAICING_H_

//*****************************
// �C���N���[�h
//*****************************
#include "player.h"

class CAddPointDisplay;
class CPlayerFlagRaicing :public CPlayer
{
public:
	CPlayerFlagRaicing();
	~CPlayerFlagRaicing();

	static CPlayerFlagRaicing *Create(D3DXVECTOR3 pos, int nPlayerNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CAddPointDisplay *GetAddPoitDisplay(void) { return m_pAddPointDisplay; }
private:
	void ControllFlipper(void);    // �H�̑���

	CAddPointDisplay *m_pAddPointDisplay;
	bool m_bIsOldLeftJoyPad;	//�O�񍶃X�e�B�b�N���g�p�������ǂ���
	bool m_bIsOldRightJoyPad;	//�O��E�X�e�B�b�N�g�p�������ǂ���
};
#endif // !_PLAYER_FLAG_RAICING_H_
