#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100

struct Term {
	int type;	// 0: number, else char of op.
	double value;
};

//演算子の優先順位を返す
int rank(char op){
	if(op == '*' || op == '/') return 2;
	if(op == '+' || op == '-') {
		return 1;
	}	
	return 0;
}

//数字を読み込んでevalに積む
void readNumber(int *index, int *ev, struct Term eval[], char line[]){
	char *endptr;
	eval[*ev].type = 0;
	eval[*ev].value = strtod(&line[*index], &endptr);
	*index += endptr - line;
	(*ev)++;
}

//入力行を逆ポーランド記法に変換
void tokenize(struct Term eval[], int *ep, char line[]){
	int op = 0;
	int opRank;
	*ep = 0;
	int sIndex = 0;
	int sLen = strlen(line);
	char opStack[N];
	int opIndex = 0;
	while(sIndex < sLen){
		if('0' <= line[sIndex] && line[sIndex] <= '9'){
			readNumber(&sIndex, ep, eval, line);
			printf("%lf,", eval[*ep - 1].value);
			continue;
		}
		op = line[sIndex];
		opRank = rank(op);
		if(opRank){
			for(;;){
				if(opIndex == 0 || rank(opStack[opIndex - 1]) < opRank){
					break;
				}
				eval[(*ep)++].type = opStack[--opIndex];
				printf("%c,", eval[*ep - 1].type);
			}
			opStack[opIndex++] = op;
		}
		sIndex++;
	}
	//読みきったら、operatorの残りをevalに積む
	for(;;){
		if(opIndex == 0){
			break;
		}
		eval[(*ep)++].type = opStack[--opIndex];
		printf("[%c]", eval[*ep - 1].type);
	}
	printf("\n");
}

//逆ポーランド記法の配列の計算
double calculate(struct Term eval[], int ep){
	int i, op, ti = 0;
	struct Term *temp[N];
	for(i = 0; i < ep; i++){
		if(eval[i].type == 0){
			// number
			temp[ti++] = &eval[i];
			continue;
		}
		op = eval[i].type;
		if(op=='+'){
			temp[ti - 2]->value += temp[ti - 1]->value;
		}
		if(op=='-'){
			temp[ti - 2]->value -= temp[ti - 1]->value;
		}
		if(op=='*'){
			temp[ti - 2]->value *= temp[ti - 1]->value;
		}
		if(op=='/'){
			temp[ti - 2]->value /= temp[ti - 1]->value;
		}
		ti--;
	}
	return temp[0]->value;
}

int main(){
	char line[N];
	struct Term eval[N];
	int ep;
	double ans;

	fgets(line, N, stdin);
	tokenize(eval, &ep, line);
	ans = calculate(eval, ep);
	printf("%f\n", ans);

/*	考え方のメモ

	数字か判断
	まわす
	数字だったらスタックにつむeval
　	strtod stodと同じ
	はじめて数字じゃないのかえってくる
	endptrまでよみとばす

	文字がくる
	operator　すたっくの一番上と優先順位比較
	新しいのより優先ジュいい同じか高い　ー＞　evalsたっくに移動
	繰り返す
	
	最後まで到達したら、operatorにのこってるの右からevalにいれてく


	計算にうつる
	逆ポーランド

	左から、数字ならスタックに積む
	演算子ならスタックの上二つにたいして計算
	とりのぞく、結果つむ
	最後までいけばいい

	できるはず？
*/




}
