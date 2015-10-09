//多重定義防止
#ifndef __JOY_H__
#define __JOY_H__


//　マクロ定義
#define JOYMAX		(4)
#define JOY_RECORD_MAX (30)
//　十字キーの各キーを表すマクロ
#define	JOY_UP		(0)		//　上
#define	JOY_DOWN	(1)		//　下
#define	JOY_LEFT	(2)		//　左
#define	JOY_RIGHT	(3)		//　右
//　各ボタンをあらすマクロ
#define	JOY_BTN1	(0)		//　ボタン１
#define	JOY_BTN2	(1)		//　ボタン２
#define	JOY_BTN3	(2)		//　ボタン３
#define	JOY_BTN4	(3)		//　ボタン４
#define	JOY_BTN5	(4)		//　ボタン５
#define	JOY_BTN6	(5)		//　ボタン６
#define	JOY_BTN7	(6)		//　ボタン７
#define	JOY_BTN8	(7)		//　ボタン８
#define	JOY_BTN9	(8)		//　ボタン９
#define	JOY_BTN10	(9)		//　ボタン１０
#define	JOY_BTN11	(10)	//　ボタン１１
#define	JOY_BTN12	(11)	//　ボタン１２
#define	JOY_BTN13	(12)	//　ボタン１３
#define	JOY_BTN14	(13)	//　ボタン１４
#define	JOY_BTN15	(14)	//　ボタン１５
#define	JOY_BTN16	(15)	//　ボタン１６
#define	JOY_BTN17	(16)	//　ボタン１７
#define	JOY_BTN18	(17)	//　ボタン１８
#define	JOY_BTN19	(18)	//　ボタン１９
#define	JOY_BTN20	(19)	//　ボタン２０
#define	JOY_BTN21	(20)	//　ボタン２１
#define	JOY_BTN22	(21)	//　ボタン２２
#define	JOY_BTN23	(22)	//　ボタン２３
#define	JOY_BTN24	(23)	//　ボタン２４
#define	JOY_BTN25	(24)	//　ボタン２５
#define	JOY_BTN26	(25)	//　ボタン２６
#define	JOY_BTN27	(26)	//　ボタン２７
#define	JOY_BTN28	(27)	//　ボタン２８
#define	JOY_BTN29	(28)	//　ボタン２９
#define	JOY_BTN30	(29)	//　ボタン３０
#define	JOY_BTN31	(30)	//　ボタン３１
#define	JOY_BTN32	(31)	//　ボタン３２


//　構造体定義
typedef struct tagJOYSTICKINFO
{		//　ジョイスティックの十字キー構造体
	BOOL	now;	//　現在情報
	BOOL	past;	//　過去情報
}JOYSTICKINFO;
typedef struct tagJOYBUTTONINFO
{	//　ジョイスティックのボタン構造体
	BOOL	now;	//　現在情報
	BOOL	past;	//　過去情報
}JOYBUTTONINFO;
typedef struct tagJOYRECORD
{
	BYTE byKeepPushCount;				// 継続入力カウンタ
	DWORD dwDoublePushFlag;			// 連続入力判定フラグ
	DWORD dwSamePushFlag;				// 同時入力判定フラグ
}JOYRECORD,*LPJOYRECORD;

//ジョイパッド管理用クラス
class CJoySystem
{
protected:
	JOYSTICKINFO	m_JoyStickInfo[4];
	JOYBUTTONINFO	m_JoyButtonInfo[32];
	JOYRECORD		m_JoyStickRecord[JOYMAX];
	JOYRECORD		m_JoyButtonRecord[JOYMAX];
	BOOL			Flag;
	static	CJoySystem*	m_instance;
public:

	CJoySystem();	//コンストラクタ
	~CJoySystem();	//デストラクタ
	static CJoySystem* getInstance();
	static void Release();
	void	JoyZeroInit(void);			//メンバを０で初期化する
	void	JoyInitInfo(void);				//　ジョイスティックの初期化関数
	void	JoyUpdateInfo(void);			//　ジョイスティック情報の更新用関数
	BOOL	GetJoyStkPush( BYTE );		//　十字キーの押した瞬間を調べる関数
	BOOL	GetJoyStkPull( BYTE );		//　十字キーの離した瞬間を調べる関数
	BOOL	GetJoyStkKeep( BYTE );		//　十字キーの押しっぱなしを調べる関数
	BOOL	GetJoyStkFree( BYTE );		//　十字キーの離しっぱなしを調べる関数
	BOOL	GetJoyStkNowInfo( BYTE );	//　十字キーの現在情報の取得を行う関数
	BOOL	GetJoyStkPastInfo( BYTE );	//　十字キーの過去情報の取得を行う関数
	BOOL	GetJoyBtnPush( BYTE );		//　ボタンの押した瞬間を調べる関数
	BOOL	GetJoyBtnPull( BYTE );		//　ボタンの離した瞬間を調べる関数
	BOOL	GetJoyBtnKeep( BYTE );		//　ボタンの押しっぱなしを調べる関数
	BOOL	GetJoyBtnFree( BYTE );		//　ボタンの離しっぱなしを調べる関数
	BOOL	GetJoyBtnNowInfo( BYTE );	//　ボタンの現在情報の取得を行う関数
	BOOL	GetJoyBtnPastInfo( BYTE );	//　ボタンの過去情報の取得を行う関数
	void	UpdateKeepJoyBtnPushInfo();		//  ボタン継続入力情報更新
	void	UpdateKeepJoyStkPushInfo();		//  スティック継続入力情報更新
	void	UpdateDoubleJoyBtnPushInfo();	//ボタン連続入力情報更新
	void	UpdateSameJoyBtnPushInfo();		//ボタン同時入力情報更新
	void    UpdateDoubleJoyStkPushInfo();	//スティック連続入力情報更新
	void	UpdateSameJoyStkPushInfo();		//スティック同時入力情報更新
	BOOL	GetKeepJoyStkPush(BYTE,BYTE);		//  スティック継続入力を調べる
	BOOL	GetKeepJoyBtnPush(BYTE,BYTE);		//  ボタン継続入力を調べる
	BOOL	GetDoubleJoyStkPush(BYTE,BYTE);	//  スティック連続入力を調べる
	BOOL	GetDoubleJoyBtnPush(BYTE,BYTE);	//	ボタン連続入力を調べる
	BOOL	GetSameJoyStkPush(BYTE,BYTE,BYTE);//スティック同時入力を調べる
	BOOL	GetSameJoyBtnPush(BYTE,BYTE,BYTE);//ボタン同時入力を調べる
	BOOL	GetSameJoyPush(BYTE,BYTE,BYTE); //ボタン、スティック同時入力
};
#endif