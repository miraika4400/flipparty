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
#define MAX_POINT_NUM 2

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
class CPassingPenguin;
class CNumber;
class CFlagRaicingGamePolygon;
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

	typedef struct
	{
		CFlipper::FLIPPER_TYPE type;
		CFlipper::FLIPPER_STATE state;
	}FLIPPER_DATA;


	typedef struct
	{
		CFlagRaicingGamePolygon * bPoint[PLAYER_NUM];
	}PLAYER_POINT_VARIABLE;

	CFlagRaicingGame_rule();
	~CFlagRaicingGame_rule();

	static CFlagRaicingGame_rule* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameProcess(void);
	void MiniResultProcess(void);
	void JudgeRank(void);					// ���ʂ̔���

	static TRUN GetGameTrun(void) { return m_eTrun; }		// �^�[�����̎擾
	static void SetGameTrun(TRUN Trun) { m_eTrun = Trun; }	// �^�[�����̐ݒ�
	static CBlind *GetBlind(void) { return m_pBlind; }
	static CPlayer *GetPlayer(int playerNum) { return m_pPlayer[playerNum]; }

	static void SetCaptainData(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
	static void SetPlayerData(int nPlayerNum, CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
private:
	
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�ւ̃|�C���^
	CCamera *m_pCamera;				// �J�����ւ̃|�C���^
	CCaptain *m_pCaptain;			// �L���v�e���̃|�C���^
	static CBlind *m_pBlind;					//�u���C���h�N���X�̃|�C���^
	PLAYER_POINT_VARIABLE m_PlayerPoint;
	CNumber *m_apNumber[MAX_POINT_NUM];

	int m_nRandTime;				// �t���b�O���グ��Ԋu
	int m_nCntTime;					// ���Ԍv�Z
	int m_nCntInputPlayer;			// �s���ς݂̃v���C���[���J�E���g

	bool m_bPlay;					// �v���C���[�������������Ȃ����̔���
	static TRUN m_eTrun;			// �グ�邩�グ�Ȃ����̔���
	CTimeLimit * m_pTimeLimit;		// �������ԃN���X
	CPassingPenguin *m_pPassingPenguin;	//�ʉ߃y���M���N���X
	static FLIPPER_DATA m_CaptainData;	//�L���v�e���̍s���f�[�^�̕ۑ��ϐ�
	static std::vector<int> m_vecPlayerNumber;	//�s���ς݃v���C���[�ԍ��̕ۑ��ϐ�
};


#endif