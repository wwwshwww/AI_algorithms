#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	TRUE		1
#define FALSE		0
#define DATA_SIZE0      2
#define DATA_SIZE       DATA_SIZE0*DATA_SIZE0

/************************************************************************
   問題 (答え) の表示
************************************************************************/
void print_board(int board[DATA_SIZE][DATA_SIZE]) {
	int x, y;

	/* 問題 (答え) (board[y][x]) を表示する。
	   数字がまだ決まっていないところには - を表示する。
	   <表示例>
		  - - 1 - 8 7 - 5 -
		  - 5 - - 3 - - 8 -
		  - - - - - 9 - - 3
		  3 - - - - - 6 - -
		  6 4 - - - - - 7 2
		  - - 5 - - - - - 9
		  7 - - 1 - - - - -
		  - 1 - - 7 - - 2 -
		  - 9 - 8 6 - 5 - -                               */

	/*** この部分を自分で書く ***/
	//縦方向に繰り返す（行）
	for (y = 0; y < DATA_SIZE; y++) {
		//横方向に繰り返す（列）
		for (x = 0; x < DATA_SIZE; x++) {
			if (board[y][x] == 0) {
				//0の代わりに-を表示
				printf(" - ");
			}
			else {
				//すでに値がある場所はその値を表示
				printf(" %d ", board[y][x]);
			}
		}
		printf("\n");
	}

}

/************************************************************************
   問題データの読み込み
************************************************************************/
void read_problem(char *fname, int board[DATA_SIZE][DATA_SIZE]) {
	int x, y;
	FILE *fp;
	
	//ファイルが開けない場合の処理
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("read_problem(): Cannot open \"%s\"\n", fname);
		exit(1);
	}
	
	//ファイルからDATA_SIZE分のデータを取り出してboard[y][x]に代入していく
	for (y = 0; y < DATA_SIZE; y++) {
		for (x = 0; x < DATA_SIZE; x++) {
			fscanf(fp, "%d ", &board[y][x]);
		}
	}
	close(fp);
}

/************************************************************************
  空白マスの検出
	board[*y][*x]から順番にチェックしていき、
	空白マス(0が入っているところ)があれば   TRUE  を返す
		   (x,y)が空白マス
								   なければ FALSE を返す
************************************************************************/
int find_blank(int *x, int *y, int board[DATA_SIZE][DATA_SIZE]) {
	int i, j;

	//縦横繰り返し
	for (; *y < DATA_SIZE; (*y)++, *x = 0) {
		for (; *x < DATA_SIZE; (*x)++) {
			/* board[*y][*x]が0ならば TRUE を返す */
			/*** この部分を自分で書く ***/
			if (board[*y][*x] == 0) {
				return TRUE;
			}
		}
	}
	return  FALSE;
}

/************************************************************************
   問題を解く
************************************************************************/
void solve(int x, int y, int board[DATA_SIZE][DATA_SIZE])
{
	int i;
	int x0, y0; /*検査用*/
	int possible[DATA_SIZE + 1]; /* 1〜9のうちどの数字が使えるか */

	/* 途中経過を表示 */
	printf( "[途中経過]\n" );
	print_board(board); //関数print_boardに現時点でのboardを渡す

	/* 空白のマスがなければ答えを表示する */
	// 関数find_blankからfalseが返ってきたら答えを表示
	if (!find_blank(&x, &y, board)) {
		printf("[答え]\n");
		print_board(board);
		return;
	}

	/* 全て使用可にする */
	for (i = 0; i <= DATA_SIZE; i++) {
		possible[i] = TRUE;
	}

	/* 縦・横方向に boardの値を調べて、すでに使用されている数字は
	   possible を FALSE にする */
	for (i = 0; i < DATA_SIZE; i++) {

		/* 横方向 */
		/*** この部分を自分で書く ***/
		//横軸x0番目の値を調べていき、x番目以外の場所の値を使用済みにする
		for (x0 = 0; x0 < DATA_SIZE; x0++) {
			if (x0 != x) {
				possible[board[y][x0]] = FALSE;
			}
		}

		/* 縦方向 */
		/*** この部分を自分で書く ***/
		//縦軸y0番目の値を調べていき、y番目以外の場所の値を使用済みにする
		for (y0 = 0; y0 < DATA_SIZE; y0++) {
			if (y0 != y) {
				possible[board[y0][x]] = FALSE;
			}
		}
	}

	/* DATA_SIZE0xDATA_SIZE0の枠の中の board の値を調べて、
	  すでに使用されている数字のところは possible を FALSE にする */
	  /*** この部分を自分で書く ***/

	/*代入先がint型（商の端数は切り捨て）のため、yをDATA_SIZE0で割ることで
	　現在どのマス群に属しているかがわかる。（1、2、3など）
	　これを座標に変換するため、割った値にDATA_SIZE0を乗算する。
	　属するマス目の区切りはy/DATA_SIZE0に+1した数値に
	　DATA_SIZE0を乗算した座標（次のマス群との境目）である。 */
	//縦方向
	for (y0 = (y / DATA_SIZE0)*DATA_SIZE0; y0 < ((y / DATA_SIZE0) + 1)*DATA_SIZE0; y0++) {
		//上記のxバージョン（横方向）
		for (x0 = (x / DATA_SIZE0)*DATA_SIZE0; x0 < ((x / DATA_SIZE0) + 1)*DATA_SIZE0; x0++) {
			//所属するマス群で使用されている値をすべて使用済みにする
			if (y0 != y && x0 != x) {
				possible[board[y0][x0]] = FALSE;
			}
		}
	}

	for (i = 1; i <= DATA_SIZE; i++) {
		if (possible[i] == FALSE) {
			continue; //使用済の数字のときは処理をスキップ
		}
		/* i を (x,y)に入れることができるとして探索 */
		board[y][x] = i;
		solve(x, y, board);	/* 再帰呼び出し	*/
		board[y][x] = 0;
	}
}

/************************************************************************
   メインプログラム
************************************************************************/
int main(int argc, char *argv[])
{
	int board[DATA_SIZE][DATA_SIZE];

	if (argc != 2) {
		printf("使用法 : ./a.out 問題ファイル");
	}

	/* 問題の読み込み */
	read_problem(argv[1], board);
	/* 問題の表示 */
	printf("[問題]\n");
	print_board(board);
	/* 問題を解く */
	solve(0, 0, board);

	return 0;
}






