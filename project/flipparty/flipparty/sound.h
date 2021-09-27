//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************

// �T�E���h�N���X
class CSound
{
public:
	//============
	// ��ԗ�
	//============
	typedef enum
	{
		LABEL_BGM_TITLE = 0,        // �^�C�g��BGM
		LABEL_BGM_TUTORIAL,         // �`���[�g���A��
		LABEL_BGM_FLAG_GAME,        // ���g���Q�[����BGM
		LABEL_BGM_FLY_GAME,         // �A�ŃQ�[����BGM
		LABEL_BGM_REMEMBER_GAME,    // �L���Q�[����BGM
		LABEL_SE_ENTER,             // �G���^�[��
		LABEL_SE_CURSOR,            // �J�[�\����
        LABEL_SE_OK,                // �L���Q�[�������̉�
        LABEL_SE_MISS,              // �L���Q�[���s�����̉�
		LABEL_SE_MISS2,             // �Ԃԁ[
		LABEL_SE_MISS3,             // �Ԃԁ[
		LABEL_SE_MISS4,             // �Ԃԁ[
		LABEL_SE_WARNING,           // �x����
		LABEL_SE_FLIPPER_LEFT1,     // �t���b�p�[��
		LABEL_SE_FLIPPER_LEFT2,     // �t���b�p�[��
		LABEL_SE_FLIPPER_LEFT3,     // �t���b�p�[��
		LABEL_SE_FLIPPER_LEFT4,     // �t���b�p�[��
		LABEL_SE_FLIPPER_RIGHT1,    // �t���b�p�[�E
		LABEL_SE_FLIPPER_RIGHT2,    // �t���b�p�[�E
		LABEL_SE_FLIPPER_RIGHT3,    // �t���b�p�[�E
		LABEL_SE_FLIPPER_RIGHT4,    // �t���b�p�[�E
		LABEL_SE_STAN1,             // stan
		LABEL_SE_STAN2,             // stan
		LABEL_SE_STAN3,             // stan
		LABEL_SE_STAN4,             // stan
		SOUND_LABEL_MAX,            // �T�E���h�ő吔
	}LABEL;

	//============
	// �����o�֐�
	//============
	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);   // ������
	void Uninit(void);         // �I��
	HRESULT Play(LABEL label); // �Đ�
	void Stop(LABEL label);    // ��~
	void Stop(void);           // �Đ����̉��̂��ׂĒ�~
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//============
	// �\���̒�`
	//============
	// �p�����[�^
	typedef struct
	{
		char *pFilename; // �t�@�C����
		int nCntLoop;    // ���[�v�J�E���g
	} SOUNDPARAM;

	//============
	// �����o�ϐ�
	//============
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];             // �p�����[�^

	IXAudio2 *m_pXAudio2;                                    // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;              // �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];   // �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];                    // �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];                     // �I�[�f�B�I�f�[�^�T�C�Y
};
#endif