#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define PatternNo  6
#define DataWidth  20
#define DataHeight 20
#define UnitNo     DataWidth*DataHeight
#define TimeMax    2

/********************************************************************
  乱数の発生 (Seedの決定)
********************************************************************/
void init_rnd() {
	srand((unsigned int)time(NULL));
}

/********************************************************************
  乱数の発生 (0〜1の乱数)
********************************************************************/
double Random() {
	return((double)rand() / RAND_MAX);
}

/********************************************************************
  出力関数 (ステップ関数)
	引数  net  : 内部状態の値
		  pout : 1時刻前の出力の値
********************************************************************/
int StepFunc(int net, int pout) {

	/* 内部状態(net)の値が0より大きければ  1
	   内部状態(net)の値が0より小さければ  -1
	   内部状態(net)の値が0ならば前の時刻の出力の値(pout) を返す */

	   /*** この部分を自分で書く ***/
	//処理内容は上記のとおり
	if (net > 0) {
		return 1;
	}
	else if (net < 0) {
		return -1;
	}
	else if (net == 0) {
		return pout;
	}
}

/********************************************************************
  パターンの表示
	引数  out[i] :  ニューロンの出力値
********************************************************************/
void display_pattern(int out[UnitNo]) {
	int i;

	/* ニューロンの出力値out[i]が 1ならば ■ を表示
	   ニューロンの出力値out[i]が-1ならば □ を表示
	   DataWidth個分のデータを出力したら改行する    */

	   /*** この部分を自分で書く ***/
	for (i = 0; i < UnitNo; i++) {
		//iをDataWidthで割った余りが0のとき改行する
		if (i % DataWidth == 0) {
			printf("\n");
		}
		if (out[i] == 1) {
			printf(" ■ ");
		}
		else if (out[i] == -1) {
			printf(" □ ");
		}
	}
	printf("\n");
}

/********************************************************************
  学習パターンの読み込み
	引数  PatternID     : パターンの番号
		  fname         : ファイル名
	  pattern[p][i] : 学習パターン
						   (p番目のパターンのi番目の成分)
   ファイル fname のデータを PatternID番目の学習パターンとして
   pattern[PatternID][i]に読み込む
********************************************************************/
void read_pattern(int PatternID, char *fname,
	int pattern[PatternNo][UnitNo]) {
	int i;
	FILE *fp;

	/* ファイル fname をオープン */
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("read_pattern(): Cannot open \"%s\"\n", fname);
		exit(1);
	}

	/* データの読み込み */
	for (i = 0; i < UnitNo; i++) {
		fscanf(fp, "%d", &pattern[PatternID][i]);
	}

	/* ファイルをクローズ */
	fclose(fp);

}


/********************************************************************
  学習パターンの読み込み (読み込むファイルの指定)
	引数  pattern[p][i] : 学習パターン
						   (p番目のパターンのi番目の成分)
********************************************************************/
void read_patterns(int pattern[PatternNo][UnitNo]) {

	/* 0番目のパターンとして crow を読み込む */
	read_pattern(0, "crow", pattern);
	/* 1番目のパターンとして duck を読み込む */
	read_pattern(1, "duck", pattern);
	/* 2番目のパターンとして lion を読み込む */
	read_pattern(2, "lion", pattern);
	/* 3番目のパターンとして monkey を読み込む */
	read_pattern(3, "monkey", pattern);
	/* 4番目のパターンとして mouse を読み込む */
	read_pattern(4, "mouse", pattern);
	/* 5番目のパターンとして penguin を読み込む */
	read_pattern(5, "penguin", pattern);
}

/********************************************************************
  相関学習
	引数  pattern[p][i] : 学習パターン
		  w[i][j]       : 重み
					(ニューロンiとニューロンjの間の重み)
********************************************************************/
void learn_w(int pattern[PatternNo][UnitNo], int w[UnitNo][UnitNo]) {
	int p, i, j;
	/* 学習パターンを用いて重み w[i][j] を決定する。
	   ただし、自分自身への結合 w[i][i] は0とする */

	   /*** この部分を自分で書く ***/
	/*学習パターンをもとに相関行列（重み行列）の生成を行う*/
	//ニューロン数xニューロン数xパターンの数 回だけ実行
	for (p = 0; p < PatternNo; p++) {
		for (i = 0; i < UnitNo; i++) {
			for (j = 0; j < UnitNo; j++) {
				if (i != j) {
					//行列と転置行列の積
					w[i][j] += pattern[p][i] * pattern[p][j];
				}
				else {
					//i=jのとき、つまり自身への結合は無し
					w[i][j] = 0;
				}
			}
		}
	}

}

/********************************************************************
  パターンの入力
	引数  PatternID     : 入力するパターンの番号
		  pattern[p][i] : 学習パターン
		  input[i]      : 入力パターン
		  NoiseLevel    : ノイズレベル (0〜1)
   pattern[p][i]のに含まれるパターンのうち、PatternID番目の
   パターンを入力パターンとしてinput[i]に読み込む。
   NoiseLevelが0でない場合には、NoiseLevelの値に応じて入力
   パターンを反転させたものをinput[i]とする。
********************************************************************/
void input_pattern(int PatternID, int pattern[PatternNo][UnitNo],
	int input[UnitNo], double NoiseLevel) {
	int i;

	/* pattern[p][i]のに含まれるパターンのうち、PatternID番目の
	   パターンを入力パターンとしてinput[i]に読み込む。
	   NoiseLevel が 0 でない場合には、Random()で乱数を発生させ、
	   Random()の値が NoiseLevel 以下の場合には input[i]の値を反転
	   (1ならば-1に、-1ならば1にする)させる。 */

	   /*** この部分を自分で書く ***/
	for (i = 0; i < UnitNo; i++) {
		//inputにPatternID番目のパターンをすべてコピー
		input[i] = pattern[PatternID][i];
		if (NoiseLevel != 0) {
			//Random関数を呼び出しNoiseLevel以下のときはinput[i]を反転
			if (Random() <= NoiseLevel) {
				if (input[i] == 1) {
					input[i] = -1;
				}
				else if (input[i] == -1) {
					input[i] = 1;
				}
			}
		}
	}
}

/********************************************************************
  パターンの想起
	引数  w[i][j]       : 重み (ニューロンiとニューロンjの間の重み)
		  out[i]        : ニューロンの出力
*********************************************************************/
void calc_output(int w[UnitNo][UnitNo], int out[UnitNo]) {
	int i, j;
	int net;

	for (i = 0; i < UnitNo; i++) {
		/* out[i] の値を計算する */

		/*** この部分を自分で書く ***/
		for (j = 0; j < UnitNo; j++) {
			//内部状態netを計算(行列計算)
			net += w[i][j] * out[j];
		}
		//ニューロンの出力outを決定（StepFunc関数を使用し、内部状態をもとに選定する）
		out[i] = StepFunc(net, out[i-1]);
		net = 0;
	}
	/* 出力パターンを表示する */
	display_pattern(out);
	//getchar(); 
}

/************************************************************
  メインプログラム
************************************************************/
int main(int argc, char *argv[]) {
	int pattern[PatternNo][UnitNo]; /* 学習パターン */
	int w[UnitNo][UnitNo];          /* 重み */
	int out[UnitNo];                /* 出力 */
	int PatternID;                  /* 入力パターンの番号 */
	double NoiseLevel;              /* ノイズレベル */
	int t;

	if (argc != 3) {
		printf("プログラムの使用方法 : \n");
		printf("  ./a.out 入力するパターンの番号(0〜5) ノイズレベル(0〜100)\n");
		exit(1);
	}

	PatternID = atoi(argv[1]);
	NoiseLevel = atof(argv[2]) / 100.0;


	init_rnd();              /* 乱数の初期化 */
	read_patterns(pattern);  /* 学習パターンの読み込み */
	learn_w(pattern, w);      /* 相関学習 */
	input_pattern(PatternID, pattern, out, NoiseLevel); /* パターンの入力 */
	display_pattern(out); /* 入力パターンの表示 */

	/* 想起 */
	for (t = 0; t < TimeMax; t++) {
		calc_output(w, out);
	}

	return 0;
}

