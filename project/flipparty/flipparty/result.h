//=============================================================================
//
// resultヘッダ [result.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "rule_base.h"
#include "rule_manager.h"

//*****************************
// 前方宣言
//*****************************
class CPolygon;
class CPlayer;
class CRankUI;

//*****************************
//マクロ定義
//*****************************
#define POINT_1ST 30
#define POINT_2ND 20
#define POINT_3RD 10
#define POINT_4TH 0

//*****************************
//クラス定義
//*****************************

//リザルトクラス
class CResult : public CScene
{
public:
	//============
	// 構造体
	//============
	// リザルトポイント集計用
	typedef struct
	{
		int nMiniGameRank[CRuleManager::RULE_MAX];
		int nPoint;
	}ResultPoint;

	//============
	// メンバ関数
	//============
	CResult();
	~CResult();

	static CResult *Create(void); //クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// 集計ポイントの初期化
	static void ResetResultPoint(void) { ZeroMemory(&m_resultPoint, sizeof(m_resultPoint)); }
	// ミニゲームの順位のセット 引数:ミニゲームの番号,プレイヤー番号,順位
	static void SetMiniGameRank(int nMiniGameNum, int nPlayerNum, int nRank) { m_resultPoint[nPlayerNum].nMiniGameRank[nMiniGameNum] = nRank; }
	
	static ResultPoint GetResultPoint(int nPlayerNum) { return m_resultPoint[nPlayerNum]; }
private:
	// プレイヤーのモーションを変える
	void ChagePlayerMotion(void);
	// 順位の計算
	void CalculationRank(void);
	// 順位の判定 引数:同じ点数の時trueなら同じランクにする
	void JudgePlayerRank(bool bSamePointRank);
	// プレイヤーの位置の調整
	void AdjustPlayerPos(void);
	
	//============
	// メンバ変数
	//============
	static ResultPoint m_resultPoint[MAX_PLAYER_NUM]; // リザルトポイント集計用

	CPlayer * m_apPlayer[MAX_PLAYER_NUM];  // プレイヤーポインタ
	int m_nCntFallTime;                    // プレイヤーがこけるタイミングのカウント用
	int m_nActionRank;                     // コケる等のアクションを起こす順位
	bool m_bShow;                          // 順位発表フラグ
	bool m_bBoard;                         // リザルトボードフラグ
	CRankUI * m_apRankUI[MAX_PLAYER_NUM];  // 順位UI
};

#endif