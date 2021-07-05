//=============================================================================
//
// �L���Q�[���̃v���C���[�w�b�_ [player_remember.h]
// Author : AYANO KUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _PLAYER_REMEMBER_H_
#define _PLAYER_REMEMBER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayerRemember : public CPlayer
{
public:
    // �����o�֐�
    CPlayerRemember();
    ~CPlayerRemember();

    static CPlayerRemember* Create(D3DXVECTOR3 pos, int nPlayerNum);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Set�֐�
    void SetIsLoss(bool IsLoss) { m_IsLoss = IsLoss; }

    // Get�֐�
    bool GetIsLoss(void) { return m_IsLoss;}      // �E���������ǂ���
private:
    bool m_IsLoss;        // �E���������ǂ���
};


#endif _PLAYER_REMEMBER_H_