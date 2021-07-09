//=============================================================================
//
// rule_flyヘッダ[rule_fly.h]
// Author :増澤 未来
//
//=============================================================================
#ifndef _RULE_FLY_GAME_H_
#define _RULE_FLY_GAME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "rule_base.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 前方宣言
//*****************************
class CTimeLimit;
class CFlyGamePlayer;
//*****************************
// クラス定義
//*****************************
// フライゲームルールクラス
class CRuleFly :public CRuleBase
{
public:
	//============
	//メンバ関数
	//============
	CRuleFly();
	~CRuleFly();

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	static CRuleFly *Create(void); // クラス生成
	// プレイヤー取得処理
	static CFlyGamePlayer * GetPlayer(int nPlayerNum) { return m_pPlayer[nPlayerNum]; }
	static bool GetPlayFlag(void) { return m_bPlay; }
private:
	void JudgeRank(void); // 順位判定
	//============
	// メンバ変数
	//============
	CTimeLimit * m_pTimeLimit; // 制限時間クラス
	static bool m_bPlay; // プレイ中フラグ
	static CFlyGamePlayer * m_pPlayer[4];
};


#endif