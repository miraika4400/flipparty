//=============================================================================
//
// time_limitヘッダ [time_limit.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TIME_H_
#define _TIME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//前方宣言
//*****************************
class CNumber;

//*****************************
//マクロ定義
//*****************************
#define MAX_TIME_NUM 2 // タイムに必要なナンバーの数

//*****************************
//クラス定義
//*****************************

//タイムクラス
class CTimeLimit : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CTimeLimit();
	~CTimeLimit();

	//static
	static CTimeLimit *Create(int nLimitTime); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// 制限時間の取得
	int GetTimeLimit(void) { return m_nLimitTime; }
	int GetTimeCount(void) { return m_nCntTime; }

	void SetTimeFlag(bool bIsTimeCount) { m_bIsTimeCount = bIsTimeCount; }	//カウントの更新するかどうかの設定
private:
	//============
	// メンバ変数
	//============
	int m_nLimitTime;                  // 制限時間
	CNumber* m_apNumber[MAX_TIME_NUM]; // タイム描画用のポリゴン
	int m_nCntTime;                    // 時間カウント用
	bool m_bIsTimeCount;				//時間をカウントするかどうか
};

#endif