//=============================================================================
//
// thunderヘッダ [thunder.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _THUNDER_H_
#define _THUNDER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//=============================
// 前方宣言
//=============================

//*****************************
//クラス定義
//*****************************

// 雷クラス
class CThunder : public CScene3d
{
public:
	//============
	// メンバ関数
	//============
	CThunder();
	~CThunder();

	static CThunder *Create(D3DXVECTOR3 pos, int nPlayerNum); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:

	int m_nPlayerNum;
	int m_nCntAnim;       // アニメーションカウント
	int m_nAnimX;         // アニメーションX軸
	int m_nAnimY;         // アニメーションY軸
};

#endif