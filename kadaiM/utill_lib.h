//多重定義防止
#ifndef __UTILL_LIB_H__
#define __UTILL_LIB_H__

//列挙型用意
enum SORT
{
	DESC,	//昇順
	ASC,	//降順

	NONE,	//無し
};

/*------------------------------------------------------------
//[機能]：汎用バブルソート関数
//[引数]：第1引数：配列のアドレス
//		：第2引数：最大要素番号
------------------------------------------------------------*/
template <class T> void bubble(T *data,int size)
{
	int i = 0,j = 0;
	T temp;
	for(i = 1;i < size;i++)
	{
		for(j = size-1;j >= i;j--)
		{
			if(data[j-1] > data[j])
			{
				temp = data[j-1];
				data[j-1] = data[j];
				data[j] = temp;
			}
		}
	}
}
/*-------------------------------------------------------------------------------------
//[機能]：汎用クイックソート関数
//[引数]：第1引数：配列のアドレス
//		：第2引数：先頭要素番号
//		：第3引数：最後尾要素番号
//		：第4引数：昇順、降順フラグ
-------------------------------------------------------------------------------------*/
template <class T> void QuickSort(T *array,int head,int tail,SORT flag)
{
	if(flag == DESC)
	{
		int forward = 0;	//先頭→最後尾
		int backward = 0;	//最後尾→先頭
		T  pivot;			//軸となる値
		T  tmp;				//入れ替え用

		//前後の探索開始位置と軸になる値を設定
		forward = head;
		backward = tail-1;
		pivot = array[(forward + backward)/2];

		//分割処理開始
		while(true)
		{
			//軸となる値より大きい値が出るまで最後尾を目指す
			while(array[forward] > pivot)
			{
				forward++;
			}
			//軸となる値より小さい値が出るまで先頭を目指す
			while(array[backward] < pivot)
			{
				backward--;
			}
			//お互いが交差したら分割処理を抜ける
			if(forward >= backward)break;
			//両者を進める
			tmp = array[forward];
			array[forward] = array[backward];
			array[backward] = tmp;
			//探索を続ける為に、両者を進める
			forward++;
			backward--;
		}
		//前から辿ってきた指標の現在位置から1つ前を見て、2つ以上の要素があるなら、その範囲で再度分割処理
		if(head < forward -1)
		{
			QuickSort(array,head,forward,DESC);
		}
		//後ろから辿ってきた指標の現在位置から1つ後ろを見て、2つ以上の要素があるなら、その範囲で再度分割処理
		if(tail -1 > backward + 1)
		{
			QuickSort(array,backward +1,tail,DESC);
		}
	}
	else if(flag == ASC)
	{
		int forward = 0;	//先頭→最後尾
		int backward = 0;	//最後尾→先頭
		T  pivot;			//軸となる値
		T  tmp;				//入れ替え用

		//前後の探索開始位置と軸になる値を設定
		forward = head;
		backward = tail-1;
		pivot = array[(forward + backward)/2];

		//分割処理開始
		while(true)
		{
			//軸となる値より大きい値が出るまで最後尾を目指す
			while(array[forward] < pivot)
			{
				forward++;
			}
			//軸となる値より小さい値が出るまで先頭を目指す
			while(array[backward] > pivot)
			{
				backward--;
			}
			//お互いが交差したら分割処理を抜ける
			if(forward >= backward)break;
			//両者を進める
			tmp = array[forward];
			array[forward] = array[backward];
			array[backward] = tmp;
			//探索を続ける為に、両者を進める
			forward++;
			backward--;
		}
		//前から辿ってきた指標の現在位置から1つ前を見て、2つ以上の要素があるなら、その範囲で再度分割処理
		if(head < forward -1)
		{
			QuickSort(array,head,forward,ASC);
		}
		//後ろから辿ってきた指標の現在位置から1つ後ろを見て、2つ以上の要素があるなら、その範囲で再度分割処理
		if(tail -1 > backward + 1)
		{
			QuickSort(array,backward +1,tail,ASC);
		}
	}
	else if(flag == NONE)
	{
		return;
	}
	else
	{
		return;
	}
}
/*----------------------------------------------------------------------------------------------
//[機能]：汎用二分探索関数
//[引数]：第1引数：配列のアドレス
//		：第2引数：探索始点
//		：第3引数：探索終点
//		：第4引数：探索する値
----------------------------------------------------------------------------------------------*/
template <class T> T* BinarySearch(T *array,int head,int tail,T key)
{
	int middle = 0;	//中央要素番号
	//まだ検索範囲が存在するなら、検索を行う
	if(head <= (tail-1))
	{
		//中央の要素番号を定める
		middle = (head + (tail-1))/2;
		//中央の値が目的の値かどうか調べる
		if(key == array[middle])
		{
			return &array[middle];
		}
		//目的の値が中央の値より小さいなら中央の値より左の範囲で再度検索する
		if(key < array[middle])
		{
			return BinarySearch(array,head,middle,key);
		}
		//目的の値が中央の値より大きい値なら中央の値より右の範囲で再度検索する
		if(key > array[middle])
		{
			return BinarySearch(array,middle+1,tail,key);
		}
	}
	//見つからなかった場合はNULLを返す
	return NULL;
}
//=================================================================================
//▼線形補間
//=================================================================================

//=================================================================================
//線形補間
//=================================================================================
template<class T> T LinearInterpolate(const T& startV,const T& endV,int nowCnt,int maxFlame)
{
	float t=nowCnt/(float)maxFlame;
	return startV*(1-t)+endV*t;
}

//=================================================================================
//物理補間
//=================================================================================
template<class T> T PhyInterpolate(const T& startV,const T& endV,int nowCnt,int ts)
{
	float t=nowCnt/(float)ts;
	T d=endV-startV;
	return startV+2*d*t-d*t*t;
}
//=================================================================================
//3次補間
//=================================================================================
template<class T> T CubicInterpolate(const T& startV,const T& endV,int nowCnt,int ts)
{
	float t=nowCnt/(float)ts;
	T d=endV-startV;
	return startV-2*d*t*t*t+3*d*t*t;
}
//=================================================================================
//三角補間
//=================================================================================
template<class T> T CosInterpolate(const T& startV,const T& endV,int nowCnt,int ts)
{
	float t=nowCnt/(float)ts;
	T d=endV-startV;
	return startV+d*(1-cosf(180*t))/2;	//cosdは「度」用のコサイン
}
//=================================================================================
//スプライン曲線
//=================================================================================
template<class T> T BSplineInterpolate(const T& startP,const T& c1,const T& c2,const T& endP,int nowCnt,int ts)
{
	//始点と終点を含めた制御点の総数
	const int N=4;
	//制御点の配列
	T p[N]={startP,c1,c2,endP};
	//現在時刻t（-1≤t≤N）
	float t=LinearInterpolate(-1.0f,(float)N,nowCnt,ts);
	//重みr,ti=t-i
	float r,ti;
	//現在どの点の寄与か表すインデックス
	int k;
	//現在点
	T m=T();

	//Σi=-2～N+2
	for(int i=-2;i<N+2;i++)
	{
		//インデックス設定
		k=i;
		if(i<0)k=0;	//i=-2,-1ならばi=0番目の点の寄与
		if(i>N-1)k=N-1;	//i=N,N+1ならばi=N番目の点の寄与

		//重みを求める
		ti=t-i;
		r=0;
		if(-2<=ti && ti<=2)
		{
			float d=abs(ti)-2;
			r=-d*d*d/6;
		}
		if(-1<=ti && ti<=1)
		{
			float d=abs(ti);
			r=(3*d*d*d-6*d*d+4)/6;
		}

		//重みをかけて各点の寄与を足し込む
		m+=(p[k]*r);
	}

	return m;
}
//=================================================================================
//ベジェ曲線
//=================================================================================
template<class T> T LinearBezierInterpolate(const T& startP,const T& c1,const T& c2,const T& endP,int nowCnt,int ts)
{
	int N=ts;			//全分割数
	float ni=1/(float)N;		//逆数
	T p(startP),q;			//始点と通常のベジェ曲線を描く点
	float tt=0;			//区間ごとのt
	float x,t=nowCnt/(float)ts;	//汎用変数と通常のt
	float *dd=new float[N+1];	//距離を保持する配列

	//ttは小数なのでintで桁落ちしないためのゲタ
	const int G=1000000;
	//始めの長さは0
	dd[0]=0;
	//パラメータに対するベジェ曲線の距離を合算していく
	for(int i=1;i<N+1;i++)
	{
		//時間での区間を進める
		tt+=ni;
		//ttでの通常のベジェ曲線上の点を得る
		q=BezierCurveInterpolate(startP,c1,c2,endP,tt*ts*G,ts*G);
		//距離を足し込んで保持
		dd[i]=dd[i-1]+Distance(p,q);
		//次の点へ
		p=q;
	}

	//距離の合計(=dd[N])で正規化
	//これでddはdd[0]=0<dd[1]<dd[2]<...<dd[N-1]<dd[N]=1となる
	for(int i=1;i<N+1;i++)
	{
		dd[i]/=dd[N];
	}

	//指定されたtが距離でいうと何番目の区間kにあるかを求める
	int k=0;
	for(int i=0;i<N;i++,k++)
	{
		if(dd[i]<=t && t<=dd[i+1])break;
	}

	//tが区間内のどのあたりにあるかを調べる
	//t=dd[k]ならx=0,t=dd[k+1]ならx=1,0<=x<=1
	x=(t-dd[k])/(dd[k+1]-dd[k]);
	//その割合で線形補間し、区間長をかける
	x=(k*(1-x)+(1+k)*x)*ni;

	delete[] dd;

	//求めたxに基づいてベジェ曲線上の点を返す
	return BezierCurveInterpolate(startP,c1,c2,endP,x*ts*G,ts*G);
}

#endif
