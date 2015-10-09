//旧型の関数を意図的に使用する為に警告を除外する
#pragma warning (disable:4996)
//　ヘッダーファイルインクルード
#include	<windows.h>
#include	"Joy.h"

//静的メンバ変数初期化
CJoySystem* CJoySystem::m_instance = NULL;

CJoySystem* CJoySystem::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CJoySystem();
	}
	return m_instance;
}
void CJoySystem::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//コンストラクタ
CJoySystem::CJoySystem(){
	
	this->JoyZeroInit();
}
//デストラクタ
CJoySystem::~CJoySystem(){
	
	this->JoyZeroInit();
	
}
//メンバを0で初期化する
void CJoySystem::JoyZeroInit(){
	
	ZeroMemory(&this->m_JoyButtonInfo,sizeof(JOYBUTTONINFO));
	ZeroMemory(&this->m_JoyStickInfo,sizeof(JOYSTICKINFO));
	ZeroMemory(&this->m_JoyButtonRecord,sizeof(JOYRECORD));
	ZeroMemory(&this->m_JoyStickRecord,sizeof(JOYRECORD));
	this->Flag = FALSE;
}

//ジョイパッド初期化
void CJoySystem::JoyInitInfo(void)
{

	JOYINFOEX	joy;
	int			i;

	

	//　ジョイスティックが接続されているかをチェックする為に情報の取得
	ZeroMemory( &joy, sizeof( joy ) );
	joy.dwSize = sizeof( joy );
	joy.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;
	if( joyGetPosEx( JOYSTICKID1, &joy )!=JOYERR_NOERROR )
	{

		//MessageBox( NULL, "ジョイスティックが接続されていません", "Joy Stick Error", MB_OK );
		this->Flag = FALSE;		//　ジョイスティック使用不可能状態
		return;

	} 
	else 
	{

		//　ジョイスティック情報の初期化
		for( i=0 ; i<4 ; i++ )
		{
			this->m_JoyStickInfo[i].now = FALSE;
			this->m_JoyStickInfo[i].past = FALSE;
		}
		//　ボタン情報の初期化
		for( i=0 ; i<32 ; i++ )
		{
			this->m_JoyButtonInfo[i].now = FALSE;
			this->m_JoyButtonInfo[i].past = FALSE;
		}
		this->Flag = TRUE;			//　ジョイスティック使用可能状態

	}
}

//ジョイパッド情報更新
void CJoySystem::JoyUpdateInfo(void){

	JOYINFOEX	joy;
	int			i;

	if( this->Flag)
	{
		//　現在の情報を過去の情報として保存
		//　十字キー
		for( i=0 ; i<4 ; i++ )
		{
			this->m_JoyStickInfo[i].past = this->m_JoyStickInfo[i].now;
		}
		//　ボタン
		for( i=0 ; i<32 ; i++ )
		{
			this->m_JoyButtonInfo[i].past = this->m_JoyButtonInfo[i].now;
		}

		//	初期設定
		ZeroMemory( &joy, sizeof( joy ) );
		joy.dwSize = sizeof( joy );
		joy.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;
		if( joyGetPosEx( JOYSTICKID1, &joy )!=JOYERR_NOERROR )
		{

			MessageBox( NULL, "ジョイスティックが接続されていません", "Joy Stick Error", MB_OK );
			this->Flag = FALSE;

		}
		else
		{

			//　十字キー情報の更新
			//　上
			if( joy.dwYpos<11000 ){
				this->m_JoyStickInfo[0].now = TRUE;
			} else {
				this->m_JoyStickInfo[0].now = FALSE;
			}
			//	下
			if( joy.dwYpos>50000 ){
				this->m_JoyStickInfo[1].now = TRUE;
			} else {
				this->m_JoyStickInfo[1].now = FALSE;
			}
			//　左
			if( joy.dwXpos<11000 ){
				this->m_JoyStickInfo[2].now = TRUE;
			} else {
				this->m_JoyStickInfo[2].now = FALSE;
			}
			//　右
			if( joy.dwXpos>50000 ){
				this->m_JoyStickInfo[3].now = TRUE;
			} else {
				this->m_JoyStickInfo[3].now = FALSE;
			}

			//　ボタン情報の更新
			for( i=0 ; i<32 ; i++ ){
				//　各ビットを０ビット目まで移動しビットが立っているかチェック
				if( ( joy.dwButtons>>i )&0x00000001 ){
					this->m_JoyButtonInfo[i].now = TRUE;
				} else {
					this->m_JoyButtonInfo[i].now = FALSE;
				}
			}
		}
		this->UpdateKeepJoyStkPushInfo();		//  継続入力情報更新
		this->UpdateKeepJoyBtnPushInfo();		//  継続入力情報更新
		this->UpdateDoubleJoyStkPushInfo();		//  連続入力情報更新
		this->UpdateSameJoyStkPushInfo();		//  同時入力情報更新
		this->UpdateDoubleJoyBtnPushInfo();		//  連続入力情報更新
		this->UpdateSameJoyBtnPushInfo();		//  同時入力情報更新
	}
	else
	{
		return;
	}
}

//　十字キーの押した瞬間の情報を得る関数
BOOL CJoySystem::GetJoyStkPush( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=4 )	return	FALSE;
		
		//　十字キーを「押した瞬間」を判定
		if( this->m_JoyStickInfo[ byNum ].now==TRUE && this->m_JoyStickInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　十字キーの離した瞬間の情報を得る関数
BOOL CJoySystem::GetJoyStkPull( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=4 )	return	FALSE;
		
		//　十字キーを「離した瞬間」を判定
		if( this->m_JoyStickInfo[ byNum ].now==FALSE && this->m_JoyStickInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　十字キーの押しっぱなしの情報を得る関数
BOOL CJoySystem::GetJoyStkKeep( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=4 )	return	FALSE;
		
		//　十字キーを「押しっぱなし」を判定
		if( this->m_JoyStickInfo[ byNum ].now==TRUE && this->m_JoyStickInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　十字キーの離しっぱなしの情報を得る関数
BOOL CJoySystem::GetJoyStkFree( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=4 )	return	FALSE;
		
		//　十字キーを「離しっぱなし」を判定
		if( this->m_JoyStickInfo[ byNum ].now==FALSE && this->m_JoyStickInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　十字キーの現在情報を得る関数
BOOL CJoySystem::GetJoyStkNowInfo( BYTE byNum ){
	

	if( this->Flag ){

		return	this->m_JoyStickInfo[ byNum ].now;
	}
	
	return	FALSE;

}


//　十字キーの過去情報を得る関数
BOOL CJoySystem::GetJoyStkPastInfo( BYTE byNum ){

	if( this->Flag ){
		return	this->m_JoyStickInfo[ byNum ].past;
	}

	return	FALSE;

}

//　ボタンの押した瞬間の情報を得る関数
BOOL CJoySystem::GetJoyBtnPush( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=32 )	return	FALSE;
		
		//　ボタンを「押した瞬間」を判定
		if( this->m_JoyButtonInfo[ byNum ].now==TRUE && this->m_JoyButtonInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}

//　ボタンの離した瞬間の情報を得る関数
BOOL CJoySystem::GetJoyBtnPull( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=32 )	return	FALSE;
		
		//　ボタンを「離した瞬間」を判定
		if( this->m_JoyButtonInfo[ byNum ].now==FALSE && this->m_JoyButtonInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　ボタンの押しっぱなしの情報を得る関数
BOOL CJoySystem::GetJoyBtnKeep( BYTE byNum ){

	if( this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=32 )	return	FALSE;
		
		//　ボタンを「押しっぱなし」を判定
		if( this->m_JoyButtonInfo[ byNum ].now==TRUE && this->m_JoyButtonInfo[ byNum ].past==TRUE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　ボタンの離しっぱなしの情報を得る関数
BOOL CJoySystem::GetJoyBtnFree( BYTE byNum ){

	if(this->Flag ){
		//　引数の値が要素を超えていたら
		if( byNum>=32 )	return	FALSE;
		
		//　ボタンを「離しっぱなし」を判定
		if( this->m_JoyButtonInfo[ byNum ].now==FALSE && this->m_JoyButtonInfo[ byNum ].past==FALSE ){
			return	TRUE;
		}
	}

	return	FALSE;

}


//　ボタンの現在情報を得る関数
BOOL CJoySystem::GetJoyBtnNowInfo( BYTE byNum ){

	if( this->Flag ){
		return	this->m_JoyButtonInfo[ byNum ].now;
	}
	
	return	FALSE;

}


//　ボタンの過去情報を得る関数
BOOL CJoySystem::GetJoyBtnPastInfo( BYTE byNum ){

	if(this->Flag ){
		return	this->m_JoyButtonInfo[ byNum ].past;
	}

	return	FALSE;
}

//  継続入力情報更新
void CJoySystem::UpdateKeepJoyStkPushInfo(){
	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){

		// 判定対象のキーを押し続けているならカウントアップする
		if(this->GetJoyStkKeep(i)){

			// 限界値に達しているなら、その値で固定する(桁あふれ防止)
			if(this->m_JoyStickRecord[i].byKeepPushCount != 255)this->m_JoyStickRecord[i].byKeepPushCount++;

		}else{	// 判定対象キーが離されたらカウンタをリセットする

			this->m_JoyStickRecord[i].byKeepPushCount = 0;

		}

	}

	return;
}

//  継続入力情報更新
void CJoySystem::UpdateKeepJoyBtnPushInfo(){

	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){

		// 判定対象のキーを押し続けているならカウントアップする
		if(this->GetJoyBtnKeep(i)){

			// 限界値に達しているなら、その値で固定する(桁あふれ防止)
			if(this->m_JoyButtonRecord[i].byKeepPushCount != 255)this->m_JoyButtonRecord[i].byKeepPushCount++;

		}else{	// 判定対象キーが離されたらカウンタをリセットする

			this->m_JoyButtonRecord[i].byKeepPushCount = 0;

		}

	}

	return;
}

//  連続入力情報更新
void CJoySystem::UpdateDoubleJoyStkPushInfo(){

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){

		// 押した瞬間の履歴を１フレーム分ずらす
		this->m_JoyStickRecord[i].dwDoublePushFlag <<= 1;
		
		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetJoyStkPush(i))this->m_JoyStickRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;
}

//  連続入力情報更新
void CJoySystem::UpdateDoubleJoyBtnPushInfo(){

	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){

		// 押した瞬間の履歴を１フレーム分ずらす
		this->m_JoyButtonRecord[i].dwDoublePushFlag <<= 1;
		
		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetJoyBtnPush(i))this->m_JoyButtonRecord[i].dwDoublePushFlag |= 0x1;

	}

	return;
}

//  同時入力情報更新
void CJoySystem::UpdateSameJoyStkPushInfo(){		
	
	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){
	
		// 押した瞬間の入力履歴を１フレーム分ずらす
		this->m_JoyStickRecord[i].dwSamePushFlag <<= 1;

		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetJoyStkPush(i))this->m_JoyStickRecord[i].dwSamePushFlag |= 0x1;

	}

	return;
}

//  同時入力情報更新
void CJoySystem::UpdateSameJoyBtnPushInfo(){		
	
	int i = 0;

	// 現在使用しているボタン分の情報更新を行う
	for(i = 0 ; i < JOYMAX ; i++){
	
		// 押した瞬間の入力履歴を１フレーム分ずらす
		this->m_JoyButtonRecord[i].dwSamePushFlag <<= 1;

		// 現在フレームでの対象のキー入力が押した瞬間なら０ビット目にチェックする
		if(this->GetJoyBtnPush(i))this->m_JoyButtonRecord[i].dwSamePushFlag |= 0x1;

	}

	return;
}

//  継続入力を調べる
BOOL CJoySystem::GetKeepJoyStkPush(BYTE byJoyNum,BYTE byWait){

	// エラーチェック
	if(byJoyNum >= JOYMAX ||
	   byWait == 0)return FALSE;

	// 指定したキーが指定したフレーム数継続入力されていたら入力成功
	if(this->m_JoyStickRecord[byJoyNum].byKeepPushCount >= byWait)return TRUE;

	// 入力失敗
	return FALSE;
}
//  継続入力を調べる
BOOL CJoySystem::GetKeepJoyBtnPush(BYTE byJoyNum,BYTE byWait){
	// エラーチェック
	if(byJoyNum >= JOYMAX ||
	   byWait == 0)return FALSE;

	// 指定したキーが指定したフレーム数継続入力されていたら入力成功
	if(this->m_JoyButtonRecord[byJoyNum].byKeepPushCount >= byWait)return TRUE;

	// 入力失敗
	return FALSE;
}
//  連続入力を調べる
BOOL CJoySystem::GetDoubleJoyStkPush(BYTE byJoyNum,BYTE byWait){

	int i = 0;

	// エラーチェック
	if(byJoyNum >= JOYMAX ||byWait <= 1 ||byWait >= JOY_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の連続入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一度目の指定したキーの入力があったかを調べる
		if((this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

			// 一度目の入力があった次のフレームから指定されたフレーム間の入力情報を調べる
			for(i = (i + 1) ; i < byWait ; i++){

				// 指定したフレーム間内に二度目の指定したキーの入力があったかを調べる
				if((this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

					// 二度目の入力があった時点で履歴をリセットする
					this->m_JoyStickRecord[byJoyNum].dwDoublePushFlag = 0;

					// 入力成功
					return TRUE;

				}

			}

			// 二度目の入力がなかったら失敗
			return FALSE;

		}

	}

	// 一度目の入力がなかったら失敗
	return FALSE;
}
//  同時入力を調べる
BOOL CJoySystem::GetSameJoyStkPush(BYTE byJoyNum1,BYTE byJoyNum2,BYTE byWait){

	int i = 0;
	BYTE byPushCheck = 0;			// 同時入力チェック用

	// エラーチェック
	if(byJoyNum1 >= JOYMAX ||
	   byJoyNum2 >= JOYMAX ||
	   byJoyNum1 == byJoyNum2 ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の同時入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyStickRecord[byJoyNum1].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら０ビット目にチェックする
			byPushCheck |= 0x1;

		}

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyStickRecord[byJoyNum2].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら１ビット目にチェックする
			byPushCheck |= 0x2;

		}

	}

	// 両方のキーが入力されているかを調べる
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// 同時入力されていた時点で履歴をリセットする
		this->m_JoyStickRecord[byJoyNum1].dwSamePushFlag = 0;
		this->m_JoyStickRecord[byJoyNum2].dwSamePushFlag = 0;

		// 入力成功
		return TRUE;

	}else{	// 同時入力されていなかったら入力失敗

		return FALSE;

	}
}
//  連続入力を調べる
BOOL CJoySystem::GetDoubleJoyBtnPush(BYTE byJoyNum,BYTE byWait){
	
	int i = 0;

	// エラーチェック
	if(byJoyNum >= JOYMAX ||byWait <= 1 ||byWait >= JOY_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の連続入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一度目の指定したキーの入力があったかを調べる
		if((this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

			// 一度目の入力があった次のフレームから指定されたフレーム間の入力情報を調べる
			for(i = (i + 1) ; i < byWait ; i++){

				// 指定したフレーム間内に二度目の指定したキーの入力があったかを調べる
				if((this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag >> i) & 0x1){

					// 二度目の入力があった時点で履歴をリセットする
					this->m_JoyButtonRecord[byJoyNum].dwDoublePushFlag = 0;

					// 入力成功
					return TRUE;

				}

			}

			// 二度目の入力がなかったら失敗
			return FALSE;

		}

	}

	// 一度目の入力がなかったら失敗
	return FALSE;
}
BOOL CJoySystem::GetSameJoyBtnPush(BYTE byJoyNum1,BYTE byJoyNum2,BYTE byWait){
	//  同時入力を調べる
	int i = 0;
	BYTE byPushCheck = 0;			// 同時入力チェック用

	// エラーチェック
	if(byJoyNum1 >= JOYMAX ||
	   byJoyNum2 >= JOYMAX ||
	   byJoyNum1 == byJoyNum2 ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の同時入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyButtonRecord[byJoyNum1].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら０ビット目にチェックする
			byPushCheck |= 0x1;

		}

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyButtonRecord[byJoyNum2].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら１ビット目にチェックする
			byPushCheck |= 0x2;

		}

	}

	// 両方のキーが入力されているかを調べる
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// 同時入力されていた時点で履歴をリセットする
		this->m_JoyButtonRecord[byJoyNum1].dwSamePushFlag = 0;
		this->m_JoyButtonRecord[byJoyNum2].dwSamePushFlag = 0;

		// 入力成功
		return TRUE;

	}else{	// 同時入力されていなかったら入力失敗

		return FALSE;

	}
}
BOOL CJoySystem::GetSameJoyPush(BYTE byJoyStk,BYTE byJoyBtn,BYTE byWait){
	//  同時入力を調べる
	int i = 0;
	BYTE byPushCheck = 0;			// 同時入力チェック用

	// エラーチェック
	if(byJoyStk >= JOYMAX ||
	   byJoyBtn >= JOYMAX ||
	   byWait == 0 ||
	   byWait > JOY_RECORD_MAX)return FALSE;

	// 指定されたフレーム間の同時入力情報を調べる
	for(i = 0 ; i < byWait ; i++){

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyStickRecord[byJoyStk].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら０ビット目にチェックする
			byPushCheck |= 0x1;

		}

		// 指定したフレーム間内に一つ目のキーの入力があったかを調べる
		if((this->m_JoyButtonRecord[byJoyBtn].dwSamePushFlag >> i) & 0x1){
		
			// 入力があったら１ビット目にチェックする
			byPushCheck |= 0x2;

		}

	}

	// 両方のキーが入力されているかを調べる
	if((byPushCheck & 0x1) && (byPushCheck & 0x2)){

		// 同時入力されていた時点で履歴をリセットする
		this->m_JoyStickRecord[byJoyStk].dwSamePushFlag = 0;
		this->m_JoyButtonRecord[byJoyBtn].dwSamePushFlag = 0;

		// 入力成功
		return TRUE;

	}else{	// 同時入力されていなかったら入力失敗

		return FALSE;

	}
}
