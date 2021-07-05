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
#define PLAYER_NUM 4

//======================================================
//	�O���O��
//======================================================
class CPolygon;
class CPlayer;
class CCaptain;
class CCamera;

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

	void FlagJudge(void);	// �v���C���[�ƃL���v�e���̊��グ���ʊ֐�
	void FlagPoint(void);	// �v���C���[�ƃL���v�e���̊����オ���Ă��邩�������Ă��邩�̔��菈���֐�
	bool PlayerFlagJudge(CPlayer *player);
	void JudgeRank(void);			// ���ʂ̔���

	static TRUN GetGameLoop(void) { return m_eLoop; }
	static void SetGameLoop(TRUN loop) { m_eLoop = loop; }
private:
	// CPlayer�̓��I�z��
	std::vector<CPlayer*> m_playerVector;

	CPlayer *m_pPlayer[PLAYER_NUM];		// �v���C���[�ւ̃|�C���^
	CCamera *m_pCamera;						// �J�����ւ̃|�C���^
	CCaptain *m_pCaptain;

	int m_nCntTime;
	int m_nPoint;
	int m_nTarn;
	int m_nCntInputPlayer;		// �s���ς݂̃v���C���[���J�E���g

	bool m_bPlay;
	static TRUN m_eLoop;			// �グ�邩�グ�Ȃ����̔���
};


#endif