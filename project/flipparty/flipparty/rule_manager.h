//=============================================================================
//
// rule_managerヘッダ [rule_manager.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RULE_MANAGER_H_
#define _RULE_MANAGER_H_

//*****************************
//インクルード
//*****************************
#include "scene.h"

//=============================
// 前方宣言
//=============================

//*****************************
//マクロ定義
//*****************************
class CRuleBase;
class CPolygon;
//*****************************
//クラス定義
//*****************************

// ルール管理クラス
class CRuleManager : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************
	// ルール列挙
	typedef enum
	{
		RULE_FLAG_RACING = 0, // 旗揚げ
		RULE_FLY,             // フライ
		RULE_REMENBER,        // 記憶
		RULE_MAX
	}RULE_TYPE;

	// フェード状態
	typedef enum
	{
		FADE_NONE = 0, // 何でもない状態
		FADE_IN,       // フェードイン
		FADE_OUT,      // フェードアウト
		FADE_MAX,      // 状態の最大数
	}FADE_STATE;

	//*****************************
	// メンバ関数
	//*****************************
	CRuleManager();
	~CRuleManager();

	static CRuleManager *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	void SetRule(RULE_TYPE ruleNext); //ルールのセット
	void TransitionRule(void);        // ルール遷移
private:

	//*****************************
	// メンバ変数
	//*****************************
	CRuleBase* m_pGameRule;     // ルール
	CPolygon*  m_pFadePolygon;  // フェード用ポリゴン
	RULE_TYPE  m_ruleNext;      // ネクストルール
	FADE_STATE m_fadeState;     // フェード状態
	D3DXCOLOR  m_polygonCol;    // カラー

};

#endif