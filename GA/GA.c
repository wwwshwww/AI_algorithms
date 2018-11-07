/********************************************************************
遺伝的アルゴリズム (サンプルプログラム)
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define POP_SIZE 5   /* 個体数 (必ず奇数に設定) */
#define G_LENGTH 10  /* 個体の遺伝子型のビット数 */
#define MAX_GEN  20  /* 世代数 */
#define M_RATE   0.1 /* 突然変異率 (0〜1) */ 

/********************************************************************
乱数の発生 (Seedの決定)
********************************************************************/
void init_rnd()
{
	srand((unsigned int)time(NULL));
}

/********************************************************************
乱数の発生 (0〜1の乱数)
********************************************************************/
double Random()
{
	return((double)rand() / RAND_MAX);
}

/********************************************************************
遺伝子の初期化
引数 gene[p][i] : 遺伝子pのi番目の成分
********************************************************************/
void init_gene(int gene[POP_SIZE][G_LENGTH])
{
	int p, i;
	double g;

	/* 乱数の初期化 */
	init_rnd();

	/* 遺伝子を初期化  0〜1の乱数を発生し、0.5以上なら1
	0.5未満なら0 */
	printf("<< 初期個体群 >>\n");

	/*** この部分を自分で書く  ***/
	//遺伝子pのi番目の要素を順に見ていき、上記の通りに初期化
	for (p = 0; p < POP_SIZE; p++) {
		for (i = 0; i < G_LENGTH; i++) {
			g = Random();
			if (g >= 0.5) {
				gene[p][i] = 1;
			}
			else if (g < 0.5) {
				gene[p][i] = 0;
			}
		}
	}

}

/********************************************************************
適応度の計算
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
********************************************************************/
void calc_fitness(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
	int p, i;

	/* 適応度の計算 前半の5bitは0 後半の5bitは1 */

	/*** この部分を自分で書く  ***/
	for (p = 0; p < POP_SIZE; p++) {
		fitness[p] = 0;
		for (i = 0; i < G_LENGTH; i++) {
			//適応度を上記の条件に従って計算
			//条件に当てはまればその遺伝子の適応度に1を加算
			if (i < 5 && gene[p][i] == 0) {
				fitness[p] += 1;
			}
			else if (i >= 5 && gene[p][i] == 1) {
				fitness[p] += 1;
			}
		}
	}
}

/**********************************************************************
遺伝子の表示 & 最大適応度・平均適応度の計算 & ファイルへの書き出し
引数 t          : gene[POP_SIZE][G_LENGTH] == 1
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
*fp        : ファイルポインタ
**********************************************************************/
void show_gene(int t, int gene[POP_SIZE][G_LENGTH],
	double fitness[POP_SIZE],
	FILE *fp)
{
	int p, i;
	double avg_fit;  /* 平均適応度  */
	double max_fit;  /* 最大適応度  */

	/* 個体の値、適応度の表示 */

	/*** この部分を自分で書く  ***/
	//個体pの遺伝子とその適応度を出力
	for (p = 0; p < POP_SIZE; p++) {
		printf("[個体]");
		for (i = 0; i < G_LENGTH; i++) {
			printf("%d", gene[p][i]);
		}
		printf("%s%f%s"," [適用度]",fitness[p],"\n");
	}

	/* 平均・最大適応度の計算 */
	
	/*** この部分を自分で書く  ***/	
	for (p = 0; p < POP_SIZE; p++) {
		//（平均適応度）各個体pの適応度を順に加算していき、すべて足し終わったらその値を個体数で割る
		avg_fit += fitness[p];
		if (p == POP_SIZE - 1) {
			avg_fit = avg_fit / (double)POP_SIZE;
		}
		//（最大適応度）現時点でのmax_fitと個体pの適応度を比較し、後者の方が大きければmax_fitをその値に更新する
		if (fitness[p] > max_fit) {
			max_fit = fitness[p];
		}
	}

	/* 平均・最大適応度の表示 */
	printf("平均適応度 : %lf\n", avg_fit);
	printf("最大適応度 : %lf\n", max_fit);

	/* 平均・最大適応度をファイルに書き込む */
	fprintf(fp, "%d %lf %lf\n", t, avg_fit, max_fit);
}

/**********************************************************************
個体番号 p1 と p2 の適応度と遺伝子を交換
引数 p1, p2     : 遺伝子の番号
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void swap_gene(int p1, int p2, int gene[POP_SIZE][G_LENGTH],
	double fitness[POP_SIZE])
{
	int tmp; /*遺伝子値の一時避難先*/
	double f; /*適応度の一時避難先*/
	int i;

	/* 遺伝子型の交換 (遺伝子p1と遺伝子p2の値を入れ替える) */

	/*** この部分を自分で書く  ***/
	//二つの個体p1とp2の遺伝子i番目を順番に入れ替えていく
	for (i = 0; i < G_LENGTH; i++) {
		//一時避難先へ値をコピーし、二体の遺伝子i番目を入れ替える
		tmp = gene[p1][i];
		gene[p1][i] = gene[p2][i];
		gene[p2][i] = tmp;
	}

	/* 適応度の交換 (遺伝子p1と遺伝子p2の適応度の値を入れ替える) */

	/*** この部分を自分で書く  ***/
	//二つの個体p1とp2の適応度を入れ替える
	f = fitness[p1];
	fitness[p1] = fitness[p2];
	fitness[p2] = f;

}

/**********************************************************************
個体番号 p1 の適応度と遺伝子型を p2 にコピー
引数 p1, p2     : 遺伝子の番号
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void copy_gene(int p1, int p2, int gene[POP_SIZE][G_LENGTH],
	double fitness[POP_SIZE])
{
	int i;

	/* 遺伝子のコピー (遺伝子p1を遺伝子p2にコピーする) */

	/*** この部分を自分で書く  ***/
	//遺伝子p1のi番目の値を遺伝子p2にコピーしていく
	for (i = 0; i < G_LENGTH; i++) {
		gene[p2][i] = gene[p1][i];
	}

	/* 適応度のコピー */

	/*** この部分を自分で書く  ***/
	//遺伝子p1の適応度を遺伝子p2の適応度にコピーする
	fitness[p2] = fitness[p1];

}

/**********************************************************************
エリート保存
(最小適応度の個体に最大適応度の個体のデータをコピー)
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void elite(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
	int p, i;
	double max_fitness = fitness[0]; /*比較用の最大適応度（初期値は個体0番目の適応度）*/
	double min_fitness = fitness[0]; /*比較用の最小適応度（初期値は個体0番目の適応度）*/
	int max_p = 0; /*最大適応度個体のindex*/
	int min_p = 0; /*最小適応度個体のindex*/

	/* 最大適応度の個体(max_p)と最小適応度の個体(min_p)を見つける */
	
	/*** この部分を自分で書く  ***/
	//各遺伝子の適応度を順に見ていき、最小適応度、最大適応度の個体をみつける
	for (p = 0; p < POP_SIZE; p++) {
		//最大適応度個体のチェック
		if (fitness[p] > max_fitness) {
			//p番目を最大適応度個体のindex（仮）にセット
			max_p = p;
		}
		//最小適応度個体のチェック
		else if(fitness[p] < min_fitness){
			//p番目を最小適応度個体のindex（仮）にセット
			min_p = p;
		}
	}


	/* 最小適応度の個体に最大適応度の個体をコピー */
	copy_gene(max_p, min_p, gene, fitness);
	/* 最大適応度の個体を0番目に移動 */
	swap_gene(0, max_p, gene, fitness);
}

/**********************************************************************
ルーレット選択
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void reproduction(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
	double sum_of_fitness; /* 個体の適応度の総和 */
	double border;         /* ルーレット上の個体間の境界 */
	double r;              /* ルーレット上の選択位置 */
	int p, i;               /* 選ばれた個体の番号 */
	int num;               /* 0 <= num <= POP_SIZE-1 */
	int new_gene[POP_SIZE][G_LENGTH];

	/* ルーレットの1周分 sum_of_fitness を求める */
	sum_of_fitness = 0.0;
	for (p = 0; p<POP_SIZE; p++) {
		sum_of_fitness += fitness[p];
	}

	/* ルーレットを POP_SIZE 回だけ回して次世代の個体を選ぶ */
	for (p = 1; p<POP_SIZE; p++) {
		/* ルーレットを回して場所を選ぶ
		r : 選ばれた位置 (0 <= r <= sum_of_fitness) */
		r = sum_of_fitness*Random();
		/* 選ばれた場所に該当する個体が何番か調べる
		num : 選ばれた個体の番号 (0 <= num <= POP_SIZE-1) */
		num = 0;
		border = fitness[0]; /* 個体間の境界 */
		//rの値がborderを超えるまで繰り返す（超えたときのnumの値が選ばれた個体の番号）
		while (border<r) {
			num++;
			border += fitness[num];
		}

		/* 遺伝子の代入 */
		//new_geneにp回目のルーレット選択の結果を反映させる
		for (i = 0; i<G_LENGTH; i++) {
			new_gene[p][i] = gene[num][i];
		}
	}

	/* 遺伝子のコピー */
	for (p = 1; p<POP_SIZE; p++) {
		for (i = 0; i<G_LENGTH; i++) {
			//遺伝子p番目をルーレット選択の結果に基づいて変更
			gene[p][i] = new_gene[p][i];
		}
	}
}

/**********************************************************************
一点交叉
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void crossover(int gene[POP_SIZE][G_LENGTH])
{
	int tmp; /*交換時の一時避難先*/
	int p, i;
	int c_pos;   /* 交叉位置 (1 <= c_pos <= G_LENGTH-1) */

	/* 交叉位置を1〜G_LENGTH-1の範囲でランダムに決め、
	それより後ろを入れ替える。
	gene[1]とgene[2],  gene[3]とgene[4] ... のように親にする */

	/*** この部分を自分で書く  ***/
	//親となる個体として1と2、3と4...と参照するように繰り返す
	for (p = 1; p < POP_SIZE / 2; p+=2) {
		//交叉位置の決定
		c_pos = Random() * (G_LENGTH - 1)+ 1;
		//交叉位置から後ろの遺伝子の要素をすべて入れ替える
		for (i = c_pos; i < G_LENGTH; i++) {
			//親1(p番目)と親2(p+1番目)の遺伝子を交換
			tmp = gene[p][i];
			gene[p][i] = gene[p + 1][i]; 
			gene[p + 1][i] = tmp;
		}
	}

}

/**********************************************************************
二点交叉 (余裕があれば)
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void two_crossover(int gene[POP_SIZE][G_LENGTH])
{
	int p, i;
	int c_pos1, c_pos2;  /* 交叉位置 (1 <= c_pos1,2 <= G_LENGTH-1) */
	int tmp; /*交換時の一時避難先*/

	/* 交叉位置を1〜G_LENGTH-1の範囲でランダムに2つ決め、その間を入れ替える。
	gene[1]とgene[2],  gene[3]とgene[4] ... のように親にする */

	/*** この部分を自分で書く  ***/
	//親となる個体として1と2、3と4...と参照するように繰り返す
	for (p = 1; p < POP_SIZE / 2; p += 2) {
		/*2点の交叉位置を決定する
		c_pos1がc_pos2以上の値にならないように設定*/
		do {
			c_pos1 = Random() * (G_LENGTH - 1)+ 1;
			c_pos2 = Random() * (G_LENGTH - 1)+ 1;
		} while (c_pos1 >= c_pos2);
		//交叉位置c_pos1からc_pos2までの範囲の遺伝子を交換
		for (i = c_pos1; i < c_pos2; i++) {
			//親1(p番目)と親2(p+1番目)の遺伝子を交換
			tmp = gene[p][i];
			gene[p][i] = gene[p + 1][i];
			gene[p + 1][i] = tmp;
		}
	}

}

/**********************************************************************
突然変異
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void mutation(int gene[POP_SIZE][G_LENGTH])
{
	int p, i;

	/* 0〜1の乱数を発生させ、その値が M_RATE 以下ならば
	遺伝子の値をランダムに変える (0ならば1、1ならば0) */

	/*** この部分を自分で書く  ***/
	//エリート以外の遺伝子に突然変異の可能性を付与
	for (p = 1; p < POP_SIZE; p++) {
		//遺伝子の長さだけ繰り返す
		for (i = 0; i < G_LENGTH; i++) {
			//乱数を発生させ、M_RATE以下のとき突然変異
			if (Random() <= M_RATE) {
				//遺伝子pのi番目成分が0のとき1に変化
				if (gene[p][i] == 0) {
					gene[p][i] = 1;
				}
				//遺伝子pのi番目成分が1のとき0に変化
				else {
					gene[p][i] = 0;
				}
			}
		}
	}
}

/**********************************************************************
メインプログラム
**********************************************************************/
int main(int argc, char *argv[])
{
	int gene[POP_SIZE][G_LENGTH];
	double fitness[POP_SIZE];
	int t;
	FILE *fp;

	/* 適応度の変化を記録するファイルのオープン */
	if ((fp = fopen("result.dat", "w")) == NULL) {
		printf("Cannot open \"result.dat\"\n");
		exit(1);
	}

	/* シミュレーション条件の表示 */
	printf("個体数     : %d\n", POP_SIZE);
	printf("遺伝子長   : %d bit\n", G_LENGTH);
	printf("突然変異率 : %lf\n", M_RATE);


	init_gene(gene);              /* 遺伝子の初期化 */
	calc_fitness(gene, fitness);   /* 適応度の計算 */
	show_gene(0, gene, fitness, fp); /* 表示 */

	for (t = 1; t <= MAX_GEN; t++) {
		printf("<< 世代数 : %d >>\n", t);
		elite(gene, fitness);           /* エリート保存 */
		reproduction(gene, fitness);    /* ルーレット選択 */
		crossover(gene);               /* 単純交叉 */
		two_crossover(gene);         /* 二点交叉 */ 
		mutation(gene);                /* 突然変異 */
		calc_fitness(gene, fitness);    /* 適応度の計算 */
		show_gene(t, gene, fitness, fp);  /* 表示 */
	}

	/* ファイルのクローズ */
	fclose(fp);

	return 0;
}
