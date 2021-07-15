//=============================================================================
//
// tears_managerヘッダ [tears_manager.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TEARS_MANAGER_H_
#define _TEARS_MANAGER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// 前方宣言
//*****************************

//*****************************
//クラス定義
//*****************************

//涙管理クラス
class CTearsManager : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CTearsManager();
	~CTearsManager();

	static CTearsManager *Create(D3DXVECTOR3 pos); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ変数
	//============
	D3DXVECTOR3 m_pos;
	int m_nCntTesrsInterval;  // 涙のインターバルカウント
};

#endif