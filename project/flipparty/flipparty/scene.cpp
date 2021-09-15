//=================================================
//
//    scene�N���X�̏���[scene.cpp]
//    Author:���V ����
//
//=================================================

//***********************************
// �C���N���[�h
//***********************************
#include "scene.h"
#include "scene2d.h"
#include "debug_log.h"

//***********************************
//�ÓI�����o�ϐ��錾
//***********************************
//CScene *CScene::m_apScene[MAX_SCENE] = {};
CScene * CScene::m_pTop[PRIORITY_NUM] = {};  // �擪
CScene * CScene::m_pCur[PRIORITY_NUM] = {};  // �Ō�
int CScene::m_nIDAll = 0;

//===================================
// �R���X�g���N�^
//===================================
CScene::CScene(int nPriority)
{
	// �v���C�I���e�B�̐ݒ�
	m_nPriority = nPriority;

	// �����t���O������
	m_bReleasFlag = false;

	if (m_pTop[m_nPriority] == NULL)
	{// �ŏ�����̎�

	 // �ŏ��ɃI�u�W�F�N�g�Ɏ���������
		m_pTop[m_nPriority] = this;

		// �v���r���[��NULL�N���A
		m_pPrev = NULL;
	}
	if (m_pCur[m_nPriority] == NULL)
	{// �Ōオ��̎�

	 // �Ō�ɃI�u�W�F�N�g�Ɏ���������
		m_pCur[m_nPriority] = this;

		// �l�N�X�g��NULL�N���A
		m_pNext = NULL;

	}
	else
	{
		// ��O�̃|�C���^���̍X�V
		m_pPrev = m_pCur[m_nPriority];
		// �J�����g�|�C���^�̎��̃|�C���^�Ɏ�������
		m_pCur[m_nPriority]->m_pNext = this;
		// �J�����g�|�C���^�������ɍX�V
		m_pCur[m_nPriority] = this;
		// �l�N�X�g��NULL�N���A
		m_pNext = NULL;
	}

	// ID�̐ݒ�
	m_nNumID = m_nIDAll;
	m_nIDAll++;
}
//===================================
// �f�X�g���N�^
//===================================
CScene::~CScene()
{

}

//====================================
// ���ׂďI������
//====================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// �l�N�X�g�̕ۑ�
			CScene*pSave = pScene->m_pNext;
			// �I������
			pScene->Uninit();
			// ���X�g���Ȃ��Ȃ���
			pScene->ReConnection();
			// �I�u�W�F�N�g�̍폜
			delete pScene;
			// �l�N�X�g�̏���n��
			pScene = pSave;
		}
	}
}

//====================================
// ���ׂčX�V
//====================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// �l�N�X�g�̕ۑ�
			CScene*pSave = pScene->m_pNext;

			// ���S�t���O�`�F�b�N
			if (!pScene->m_bReleasFlag)
			{
				// �I������
				pScene->Update();
			}
			// �l�N�X�g�̏���n��
			pScene = pSave;
		}
	}

	// ���Ńt���O�̃`�F�b�N
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		// �l�N�X�g�̕ۑ�
		CScene*pScene = m_pTop[nCntPriority];

		while (pScene)
		{
			CScene*pNext = pScene->m_pNext;

			// �t���O�������Ă���
			if (pScene->m_bReleasFlag)
			{
				// ���X�g���Ȃ��Ȃ���
				pScene->ReConnection();
				// �I������
				delete pScene;
			}
			// �l�N�X�g�̏��ɍX�V����
			pScene = pNext;
		}
	}
}

//====================================
// ���ׂĕ`��
//====================================
void CScene::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// �l�N�X�g�̕ۑ�
			CScene*pSave = pScene->m_pNext;
			// ���S�t���O�`�F�b�N
			if (!pScene->m_bReleasFlag)
			{
				// �I������
				pScene->Draw();
			}
			// �l�N�X�g�̏���n��
			pScene = pSave;
		}
	}
}

//====================================
// �v���C�I���e�B�̕ύX
//====================================
void CScene::SetPriority(const int nPriority)
{
	ReConnection();

	// �v���C�I���e�B�̐ݒ�
	m_nPriority = nPriority;

	if (m_pTop[m_nPriority] == NULL)
	{// �ŏ�����̎�

	 // �ŏ��ɃI�u�W�F�N�g�Ɏ���������
		m_pTop[m_nPriority] = this;

		// �v���r���[��NULL�N���A
		m_pPrev = NULL;
	}
	if (m_pCur[m_nPriority] == NULL)
	{// �Ōオ��̎�

	 // �Ō�ɃI�u�W�F�N�g�Ɏ���������
		m_pCur[m_nPriority] = this;

		// �l�N�X�g��NULL�N���A
		m_pNext = NULL;

	}
	else
	{
		// ��O�̃|�C���^���̍X�V
		m_pPrev = m_pCur[m_nPriority];
		// �J�����g�|�C���^�̎��̃|�C���^�Ɏ�������
		m_pCur[m_nPriority]->m_pNext = this;
		// �J�����g�|�C���^�������ɍX�V
		m_pCur[m_nPriority] = this;
		// �l�N�X�g��NULL�N���A
		m_pNext = NULL;
	}
}

//====================================
//�������̔j��
//====================================
void CScene::Release(void)
{
	// �����t���O�𗧂Ă�
	m_bReleasFlag = true;
}

//====================================
// ���X�g�̍Đڑ�
//====================================
void CScene::ReConnection(void)
{
	// �l�N�X�g�̏����Ȃ���
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	// �v���r���[�̏����Ȃ���
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}

	if (m_pTop[m_nPriority] == this && m_pCur[m_nPriority] == this)
	{// �������擪���Ōゾ������
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}
	else if (m_pTop[m_nPriority] == this)
	{// ������m_nPriority��
		m_pTop[m_nPriority] = m_pNext;
		if (m_pTop[m_nPriority] != NULL)
		{
			m_pTop[m_nPriority]->m_pPrev = NULL;
		}
	}
	else if (m_pCur[m_nPriority] == this)
	{// �������Ōゾ������
		m_pCur[m_nPriority] = m_pPrev;
		if (m_pCur[m_nPriority] != NULL)
		{
			m_pCur[m_nPriority]->m_pNext = NULL;
		}
	}
}
