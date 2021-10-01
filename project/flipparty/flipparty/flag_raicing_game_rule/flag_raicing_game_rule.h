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
class CPlayerFlagRaicing;
class CCaptain;
class CCamera;
class CTimeLimit;
class CBlind;
class CPassingPenguin;
class CNumber;

//======================================================
//	�N���X��`
//======================================================
class CFlagRaicingGame_rule : public CRuleBase
{
public:

	//======================================================
	//�Q�[���^�[���̗�
	//======================================================
	typedef enum
	{
		PLAYER_TRUN = 0,	//�v���C���[�̃^�[��
		CAPTAIN_TRUN,		//�L���v�e���̃^�[��
		TRUN_END
	}TRUN;

	//======================================================
	//�H�̃f�[�^
	//======================================================
	typedef struct
	{
		CFlipper::FLIPPER_TYPE type;	//�H�̍��E�̎��
		CFlipper::FLIPPER_STATE state;	//�H�̏��
	}FLIPPER_DATA;

	//======================================================
	//�񓚃f�[�^
	//======================================================
	typedef struct
	{
		std::vector<int> vecPlayerNumber;	//�s���ς݂̃v���C���[�ԍ��ێ��ϐ�
		int nAnswerNum;	//����������
	}ANSWER_DATA;

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
	static CPlayerFlagRaicing *GetPlayer(int playerNum) { return m_pPlayer[playerNum]; }

	static void SetCaptainData(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
	static void SetPlayerData(int nPlayerNum, CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
private:
	
	static CPlayerFlagRaicing *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�ւ̃|�C���^
	CCamera *m_pCamera;				// �J�����ւ̃|�C���^
	CCaptain *m_pCaptain;			// �L���v�e���̃|�C���^
	static CBlind *m_pBlind;					//�u���C���h�N���X�̃|�C���^

	int m_nRandTime;				// �t���b�O���グ��Ԋu
	int m_nCntTime;					// ���Ԍv�Z

	bool m_bPlay;					// �v���C���[�������������Ȃ����̔���
	static TRUN m_eTrun;			// �グ�邩�グ�Ȃ����̔���
	CTimeLimit * m_pTimeLimit;		// �������ԃN���X
	CPassingPenguin *m_pPassingPenguin;	//�ʉ߃y���M���N���X
	static FLIPPER_DATA m_CaptainData;	//�L���v�e���̍s���f�[�^�̕ۑ��ϐ�
	static ANSWER_DATA m_answerData;	//�s���ς݃v���C���[�ԍ��̕ۑ��ϐ�
};


#endif