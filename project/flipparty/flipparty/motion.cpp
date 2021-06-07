////////////////////////////////////////////////////
//
//    motion�N���X�̏���[motion.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "motion.h"
#include "debug_log.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************

//******************************
// �R���X�g���N�^
//******************************
CMotion::CMotion() :CScene(OBJTYPE_MOTION)
{
	// �����o�ϐ��̃N���A
	m_pModel = NULL;                              // ���f�����
	m_nNumKey = 0;                                // �L�[�t���[���̐� 
	m_nNumParts = 0;                              // �p�[�c��
	m_bMotion = false;                              // �A�j���[�V�������Ă��邩
	m_bLoop = false;                              // ���[�v���邩
	m_nCntKey = 0;                                // �L�[�J�E���g
	m_nCntFrame = 0;                              // �t���[���J�E���g
	memset(&m_pos, 0, sizeof(m_pos));             // ���W
	memset(&m_rot, 0, sizeof(m_rot));             // ��]
	memset(&m_addPos, 0, sizeof(m_addPos));       // ���W�̉��Z�l
	memset(&m_addRot, 0, sizeof(m_addRot));       // ��]�̉��Z�l
	memset(&m_nNumFrame, 0, sizeof(m_nNumFrame)); // �t���[����
}

//******************************
// �f�X�g���N�^
//******************************
CMotion::~CMotion()
{
}

//******************************
// �N���G�C�g
//******************************
CMotion * CMotion::Create(int nNumParts, const char *pPath, CResourceModel::Model*pModel)
{
	// �������̊m��
	CMotion *pAnimation;
	pAnimation = new CMotion;

	// �����̑��
	pAnimation->m_nNumParts = nNumParts;
	pAnimation->m_pModel = pModel;
	// �A�j���[�V�����̓ǂݍ���
	pAnimation->Load(pPath);
	// ������
	pAnimation->Init();

	return pAnimation;
}


//******************************
// ����������
//******************************
HRESULT CMotion::Init(void)
{
	// �ϐ��̏�����
	m_nCntKey = 0;    // �L�[�J�E���g
	m_nCntFrame = 0;  // �t���[���J�E���g

					  // ���Z�l�̏�����
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		//m_pModel[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_pModel[nCntParts].rot) / (float)m_nNumFrame[m_nCntKey];
	}

	return S_OK;
}

//******************************
// �I������
//******************************
void CMotion::Uninit(void)
{
	Release();
}

//******************************
// �X�V����
//******************************
void CMotion::Update(void)
{
	if (m_bMotion)
	{

		// �t���[���J�E���g��i�߂�
		m_nCntFrame++;
		if (m_nCntFrame >= m_nNumFrame[m_nCntKey])
		{
			m_nCntFrame = 0;
			// �L�[�J�E���g��i�߂�
			m_nCntKey++;

			if (m_nCntKey >= m_nNumKey)
			{// ����I���ă��[�v���Ȃ��Ƃ�
				if (!m_bLoop)
				{
					// �A�j���[�V�����̏I��
					m_bMotion = false;
					return;
				}
				else
				{
					m_nCntKey = 0;
				}
			}

			// ���Z�l�̍X�V
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				if (m_nCntKey == 0)
				{// ��ԍŏ��̃t���[��
					m_addPos[nCntParts] = (m_pos[m_nCntKey][nCntParts] - m_pos[m_nNumKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
					m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_rot[m_nNumKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
				}
				else
				{
					// �O����Ɖ�]���Ȃ��悤����
					if (m_rot[m_nCntKey][nCntParts].y - m_pModel[nCntParts].rot.y > D3DXToRadian(180))
					{
						m_pModel[nCntParts].rot.y += D3DXToRadian(360);
					}
					if (m_rot[m_nCntKey][nCntParts].y - m_pModel[nCntParts].rot.y < D3DXToRadian(-180))
					{
						m_pModel[nCntParts].rot.y -= D3DXToRadian(360);
					}

					m_addPos[nCntParts] = (m_pos[m_nCntKey][nCntParts] - m_pos[m_nCntKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
					m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_pModel[nCntParts].rot) / (float)m_nNumFrame[m_nCntKey];
				}
			}
		}

		// ���Z�l�𑫂�
		for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
		{
			m_pModel[nCntParts].pos += m_addPos[nCntParts];
			m_pModel[nCntParts].rot += m_addRot[nCntParts];
		}
	}
}

//******************************
// �`�揈��
//******************************
void CMotion::Draw(void)
{
}

//******************************
// �A�j���[�V�����̃Z�b�g
//******************************
void CMotion::SetActiveMotion(bool bActive)
{
	//�@�����̑��
	m_bMotion = bActive;
	if (m_bMotion)
	{
		// ������
		Init();
	}
}

void CMotion::Load(const char * pPath)
{
	// �t�@�C���I�[�v��
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{
		// �e�L�X�g�t�@�C���̉��

		// ����̕�������p
		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "MOTIONSET"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "MOTIONSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}
		// "LOOP"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "LOOP") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// �ǂݍ��񂾃��[�v���̊i�[�p
		int nLoop;
		// = ���[�v���邩
		fscanf(pFile, "%*s %d", &nLoop);
		// ���[�v�̔���
		if (nLoop == 1)
		{
			m_bLoop = true;
		}
		else
		{
			m_bLoop = false;
		}

		// "NUM_KEY"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "NUM_KEY") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}
		// = �L�[��
		fscanf(pFile, "%*s %d", &m_nNumKey);
		// �L�[�t���[���������[�v
		for (int nCntKey = 0; nCntKey < m_nNumKey; nCntKey++)
		{
			// "KEYSET"�ǂݍ��ނ܂Ń��[�v
			while (strcmp(chChar, "KEYSET") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}

			// "FRAME"�ǂݍ��ނ܂Ń��[�v
			while (strcmp(chChar, "FRAME") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}
			fscanf(pFile, "%*s %d", &m_nNumFrame[nCntKey]);

			// �p�[�c�������[�v
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				// "KEY"�ǂݍ��ނ܂Ń��[�v
				while (strcmp(chChar, "KEY") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
				// �z��ԍ�
				int nIndex = 0;
				fscanf(pFile, "%*s %*s [ %d ] %*s", &nIndex);
				// ���W
				fscanf(pFile, "%*s %*s %f %f %f", &m_pos[nCntKey][nIndex].x, &m_pos[nCntKey][nIndex].y, &m_pos[nCntKey][nIndex].z);
				// ��]
				fscanf(pFile, "%*s %*s %f %f %f", &m_rot[nCntKey][nIndex].x, &m_rot[nCntKey][nIndex].y, &m_rot[nCntKey][nIndex].z);

				// "END_KEY"�ǂݍ��ނ܂Ń��[�v
				while (strcmp(chChar, "END_KEY") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
			}
		}
		// �t�@�C���N���[�Y
		fclose(pFile);
	}
}
