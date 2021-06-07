//=============================================================================
//
// scoreヘッダ [score.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCORE_H_
#define _SCORE_H_

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
#define MAX_SCORE_DIGIT 6  // スコアの最大桁数

//*****************************
//クラス定義
//*****************************

//スコアクラス
class CScore : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CScore();
	~CScore();

	static CScore *Create(void); // クラス生成

	HRESULT Init(void);// 初期化
	void Uninit(void); // 終了
	void Update(void); // 更新
	void Draw(void);   // 描画

	static void AddScore(int nPoint) { m_nScore += nPoint; } // スコア加算
	static int GetScore(void) { return m_nScore; }           // スコアの取得
private:
	//============
	// メンバ変数
	//============
	CNumber* m_apNumber[MAX_SCORE_DIGIT]; // ナンバーポリゴン
	static int m_nScore;                  // スコア

};

#endif