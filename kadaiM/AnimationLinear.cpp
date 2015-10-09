//=============================================================================
//
// シーン遷移処理 [AnimationLinear.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//=============================================================
// AnimationLinear.cpp
// 線形補間によるキーフレームアニメーションクラスの実装
//=============================================================
#include "AnimationLinear.h"

//=============================================================
// 実装
//=============================================================
//-------------------------------------------------------------
// デフォルトコンストラクタ
//-------------------------------------------------------------
AnimationLinear::AnimationLinear()
 : m_numKey(0), m_keys(0), m_values(0), m_isLoop(TRUE), m_startTime(0), m_duration(0)
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
AnimationLinear::~AnimationLinear()
{
	if(m_keys != 0) 
	{
		delete[] m_keys;
	}

	if(m_values != 0) 
	{
		delete[] m_values;
	}
}

//---------------------------------------------------------
// キーの生成
// 引数
//		numKey : キーの数
//---------------------------------------------------------
void AnimationLinear::CreateKey(int numKey)
{

	// キーフレーム数の設定
	m_numKey = numKey;

	// 古いデータを削除
	if(m_keys != 0) 
	{
		delete[] m_keys;
	}

	if(m_values != 0) 
	{
		delete[] m_values;
	}

	// 新しい配列の生成
	m_keys   = new float[m_numKey];
	m_values = new float[m_numKey];

}
	
//---------------------------------------------------------
// キーとキーに対応する値の設定
// キーは小さい方から順番に設定すること
// 2度目以降同じインデックスを使用した場合は上書きされる
// 引数
//		index : インデックス, 0 <= index < createKeyで生成したキーの数
//		key   : キー, 0.0f <= key <= 1.0f
//		value : キーに対応する値
//---------------------------------------------------------
void AnimationLinear::SetKeyValue(int index, float key, float value)
{
	//インデックスが0より小さい、または現在のキーの数以上なら何もしない
	if((index < 0) || (index >= m_numKey)) 
	{
		return;
	}

	m_keys[index]	= key;
	m_values[index]	= value;
}

//---------------------------------------------------------
// アニメーションの長さ(キーが0から1まで変化するのにかかる時間)の設定
// 引数
//		duration : 時間(ミリ秒)
//---------------------------------------------------------
void AnimationLinear::SetDuration(DWORD duration)
{
	// アニメーション全体の継続時間をメンバ変数に保存
	m_duration = duration;
}

//---------------------------------------------------------
// アニメーションをループするかどうかの設定
// 引数
//		isLoop : TRUEならループする, FALSEならループしない
//---------------------------------------------------------
void AnimationLinear::SetLoopFlag(DWORD isLoop)
{
	m_isLoop = isLoop;
}

//---------------------------------------------------------
// アニメーション開始時刻の設定
// 引数
//		start : アニメーションの開始時刻(ミリ秒)
//---------------------------------------------------------
void AnimationLinear::SetStartTime(DWORD start)
{
	m_startTime = start;
}

//---------------------------------------------------------
// 時刻に対応する値を取得する
// 引数
//		time   : 時刻(ミリ秒)
//		pValue : 結果を受け取る変数へのポインタ
//		pIsEnd : アニメーション終了判定フラグを受け取る変数へのポインタ, 終了していたらTRUEそうれなければFALSE
// 戻り値
//		値の取得に成功したらTRUE, 失敗したらFALSE
//---------------------------------------------------------
BOOL AnimationLinear::GetValue(DWORD time, float* pValue, BOOL* pIsEnd)
{
	if(pValue == 0) 
	{
		return FALSE;
	}

	if(pIsEnd == 0) 
	{
		return FALSE;
	}

	if(m_numKey <= 0) 
	{
		return FALSE;
	}

	//----------------------------------------
	//アニメーションが終了していたときの処理
	//----------------------------------------
	DWORD	endTime = m_startTime + m_duration;	//終了時刻

	if(!m_isLoop) 
	{	// ループしない場合
		if(time < m_startTime) 
		{ 
			// 時刻が開始時刻よりも小さければ最初の値を返す
			*pValue = m_values[0];
			*pIsEnd = TRUE;
			return TRUE;
		}
		else if(time > endTime) 
		{ 
			// 時刻が終了時刻よりも大きければ最後の値を返す
			*pValue = m_values[m_numKey - 1];
			*pIsEnd = TRUE;
			return TRUE;
		}
	}

	//----------------------------------------
	//アニメーションの計算
	//----------------------------------------
	int		beginIndex;
	int		endIndex;
	float	fraction;
	float	slope;

	// 現在時刻を割合に変換
	fraction = GetFraction(time);
	// 現在時刻にもっとも近い直前のキーフレーム取得
	beginIndex = GetBeginIndex(fraction);
	// 現在時刻にもっとも近い直後のキーフレーム取得
	endIndex = beginIndex + 1;

	// 値の計算
	if(beginIndex < 0) 
	{	// アニメーション開始前
		*pValue = m_values[0];	// 最初のキーフレームの値を返す
	}
	else if(beginIndex >= m_numKey - 1) 
	{	// アニメーション終了後
		*pValue = m_values[m_numKey - 1];	// 最後のキーフレームの値を返す
	}
	else 
	{
		// 傾き（1.0あたりの増減量）を求める
		float diffValue = m_values[endIndex] - m_values[beginIndex];// キーフレーム間の値の差
		float diffTime = m_keys[endIndex] - m_keys[beginIndex];		// キーフレーム間の継続時間
		slope = diffValue / diffTime; 

		// 現在値を求める
		float fPastFromPrev = fraction - m_keys[beginIndex];	// 直前のキーフレームからの経過時間（現在時刻- 直前のキーフレームの時刻）
		*pValue = slope * fPastFromPrev + m_values[beginIndex]; // 現在値の計算
	}

	*pIsEnd = FALSE;

	return TRUE;
}

//---------------------------------------------------------
// 時刻を割合に変換する
// 引数
//		time   : 時刻(ミリ秒)
// 戻り値
//		割合
//---------------------------------------------------------
float AnimationLinear::GetFraction(DWORD time)
{
	DWORD	diffTime;
	float	fraction;

	// 時刻から割合を求める
	if(m_duration == 0) 
	{
		fraction = 1.0f;
	}
	else 
	{
		if(time > m_startTime) 
		{
			//通常処理
			// 現在時刻からスタート時刻を引く
			diffTime = time - m_startTime;
			// ループ対応
			diffTime = diffTime % m_duration;
			//割合の計算
			fraction = (float)diffTime / (float)m_duration;
			//小数部分だけ使用
			fraction = fraction - (int)fraction;
		}
		else 
		{
			//もし、現在時刻が、スタート時刻より小さいとき
			//タイマーが一周してしまったとき発生する
			diffTime = m_startTime - time;
			diffTime = diffTime % m_duration;
			fraction = (float)diffTime / (float)m_duration;
			fraction = 1.0f - (fraction - (int)fraction);
		}
	}

	return fraction;
}

//---------------------------------------------------------
// 割合に対応するインデックスを取得する
// 引数
//		fraction : 割合
// 戻り値
//		配列のインデックス, fractionが登録されているキーより小さければ-1
//---------------------------------------------------------
int AnimationLinear::GetBeginIndex(float fraction)
{
	if(fraction < m_keys[0])
		return -1;

	// 引数に指定された割合とキーフレームの割合を比較する
	int index = 0;
	for(int i = 0; i < m_numKey; i++) 
	{
		// キーフレームより大きくなったら発見
		if(m_keys[i] <= fraction) 
		{
			index = i;
		}
		else 
		{
			break;
		}
	}

	return index;
}