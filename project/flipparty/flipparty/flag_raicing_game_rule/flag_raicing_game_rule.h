//======================================================
//
//	���グ�Q�[���̏���[flag_raicing_game_rule.h]
//	Author : ���� �r�H
//
//======================================================

//��d�C���N���[�h�h�~
#ifndef _FLAG_RAICING_GAME_RULE_H_
#define _FLAG_RAICING_GAME_RULE_H_

//======================================================
//	�C���N���[�h�t�@�C��
//======================================================
#include "rule_base.h"
#include "flipper.h"

//======================================================
//	�}�N����`
//======================================================


//======================================================
//	�O���O��
//======================================================
class CPolygon;
class CPlayer;
class CCaptain;
class CCamera;
class CTimeLimit;
class CBlind;
class CBillboard;

//======================================================
//	�N���X��`
//======================================================
class CFlagRaicingGame_rule : public CRuleBase
{
public:
	typedef enum
	{
		PLAYER_TRUN = 0,
		CAPTAIN_TRUN,
		TRUN_END
	}TRUN;

	CFlagRaicingGame_rule();
	~CFlagRaicingGame_rule();

	static CFlagRaicingGame_rule* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void FlagJudge(void);					// �v���C���[�ƃL���v�e���̊��グ���ʊ֐�
	void FlagPoint(void);					// �v���C���[�ƃL���v�e���̊����オ���Ă��邩�������Ă��邩�̔��菈���֐�
	bool PlayerFlagJudge(CPlayer *player);	// vector�̒��g�̔�r
	void JudgeRank(void);					// ���ʂ̔���

	static TRUN GetGameLoop(void) { return m_eLoop; }		// �^�[�����̎擾
	static void SetGameLoop(TRUN loop) { m_eLoop = loop; }	// �^�[�����̐ݒ�
	static CBlind *GetBlind(void) { return m_pBlind; }
private:
	// CPlayer�̓��I�z��
	std::vector<CPlayer*> m_playerVector;

	CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�ւ̃|�C���^
	CCamera *m_pCamera;				// �J�����ւ̃|�C���^
	CCaptain *m_pCaptain;			// �L���v�e���̃|�C���^
	static CBlind *m_pBlind;					//�u���C���h�N���X�̃|�C���^

	int m_nRandTime;				// �t���b�O���グ��Ԋu
	int m_nCntTime;					// ���Ԍv�Z
	int m_nTarn;					// �^�[�����̒ǉ�
	int m_nCntInputPlayer;			// �s���ς݂̃v���C���[���J�E���g

	bool m_bPlay;					// �v���C���[�������������Ȃ����̔���
	static TRUN m_eLoop;			// �グ�邩�グ�Ȃ����̔���
	CTimeLimit * m_pTimeLimit;		// �������ԃN���X
};


#endif