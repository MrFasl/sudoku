////空格加入计算
////5.2-5.5s
////fputs

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<time.h>
using namespace std;
#define SUDOKUPATH  "sudoku.txt"
#define QUESPATH "ques.txt"
#define SOLUTIONPATH "solution.txt"
int num = 0;
int settle_flag = 1;
char ques_board[9][9];

void sudoku_generate(int n)
{
	char str[30];
	char line[9] = { '5','1','2','3','4','6','7','8','9' };
	char line1[19] = { '5',' ','1', ' ' ,'2', ' ','3',' ','4', ' ','6',' ','7',' ','8',' ','9','\n','\0' };
	int shift[9] = { 0,6,12,2,8,14,4,10,16 };

	int pos1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,5,3 },{ 4,3,5 },{ 5,4,3 },{ 5,3,4 } };
	int pos2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };


	char final[10][19];
	int i, j, k;
	int flag = 0;

	for (int i = 0; i < 9; i++)//初始值置空格和\0
	{
		for (int j = 0; j < 17; j++)
		{
			final[i][j] = ' ';
		}
		final[i][17] = '\n';
		final[i][18] = '\0';
	}
	final[9][0] = '\n';//第10行只有一个空行
	final[9][1] = '\0';

	//freopen(SUDOKUPATH, "w", stdout);
	FILE *fp = fopen(SUDOKUPATH, "w");

	do//生成第一行
	{
		for (int i = 0; i < 9; i++)
		{
			line1[2 * i] = line[i];
		}
		memcpy(final[0], line1, sizeof(line1));
		for (i = 1; i < 9; i++)//以第一行为基础，生成一个终局
		{
			for (j = 0; j < 18; j += 2)
			{
				final[i][j] = line1[(j + shift[i]) % 18];
			}
		}

		//在一个终局的基础上改变4-6,7-9行的输出顺序即可
		for (i = 0; i < 6; i++)
		{
			for (j = 0; j < 6; j++)
			{
				flag++;
				for (k = 0; k < 3; k++)//前三行
				{
					fputs(final[k], fp);
					//fclose(fp);
					//return;
				}

				for (k = 0; k < 3; k++)//3 4 5行
				{
					fputs(final[pos1[i][k]], fp);
				}
				if (n > 1)
				{
					for (k = 0; k < 3; k++)
					{
						fputs(final[pos2[j][k]], fp);
					}
					fputs(final[9], fp);//输出回车
				}
				else
				{
					for (k = 0; k < 2; k++)
					{
						fputs(final[pos2[j][k]], fp);
					}
					for (k = 0; k < 17; k++)
					{
						fputc(final[pos2[j][3]][k], fp);
					}
				}
				n--;
				if (!n) { fclose(fp); return; }
			}
		}

	} while (next_permutation(line + 1, line + 9));
}


void ques_genetate()
{


	freopen("sudokubase.txt", "r", stdin);
	int pos;
	char str[20];
	pos = 1 + rand() % 1000;
	while (--pos)
	{
		for (int i = 0; i < 10; i++)
			gets_s(str);
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)getchar();
			ques_board[i][j] = getchar();
		}getchar();
	}

	int base[9] = { 0,3,6,27,30,33,54,57,60 };
	int plus[9] = { 0,1,2,9,10,11,18,19,20 };

	for (int k = 0; k < 9; k++)//每个3*3随机掏空2个
	{

		int i, j, hole[2];
		hole[1] = rand() % 9;
		hole[2] = rand() % 9;
		while (hole[1] == hole[2])
		{
			hole[2] = rand() % 9;
		}
		for (int t = 0; t < 2; t++)
		{
			int dot;
			dot = base[k] + plus[hole[t]];
			i = dot / 9;
			j = dot % 9;
			ques_board[i][j] = '0';

		}

	}

	//已经掏空了18个
	int others;
	others = 12 + rand() % 31;//再掏12-41个就可以了
	while (others--)
	{
		int flag = 1;
		while (flag)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;
			if (ques_board[i][j] != '0')continue;

			flag = 0;
			ques_board[i][j] = '0';
		}
	}

	freopen(QUESPATH, "w", stdout);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)putchar(' ');
			putchar(ques_board[i][j]);
		}putchar('\n');
	}

}

int check(int m, int n)
{
	int i, j, k;
	i = m;
	j = n;
	for (k = 0; k < 9; k++)
	{
		if (k != j)//判断行是否满足
		{
			if (ques_board[i][j] == ques_board[i][k])return 0;
		}
		if (k != i)//判断列是否满足
		{
			if (ques_board[i][j] == ques_board[k][j])return 0;
		}
	}
	if (m / 3 == 0)i = 0;
	else if (m / 3 == 1)i = 3;
	else i = 6;

	if (n / 3 == 0)j = 0;
	else if (n / 3 == 1)j = 3;
	else j = 6;

	//int sum = 0;
	for (int c = i; c<i + 3; c++)
		for (int d = j; j < j + 3; j++)
		{
			if (c != m && d != n && ques_board[m][n] == ques_board[c][d])return 0;
		}
	return 1;
}



void settle(int pos)
{
	if (pos == 81)
	{
		settle_flag = 1;
		return;
	}
	int i, j, k;
	i = pos / 9;
	j = pos % 9;

	if (ques_board[i][j] != '0')
	{
		for (k = 1; k <= 9; k++)
		{
			ques_board[i][j] = k + '0';
			if (check(i, j))
			{
				settle(pos + 1);
				//ques_board[i][j] = 0;
			}
			if (settle_flag)return;
			ques_board[i][j] = '0';
		}
	}
	else
	{
		settle(pos + 1);
	}
	if (settle_flag)return;
}

void settle_ques()
{
	char c;
	freopen(QUESPATH, "r", stdin);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			ques_board[i][j] = getchar();
		}
		getchar();
	}
	settle(0);
	freopen(SOLUTIONPATH, "w", stdout);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)putchar(' ');
			putchar(ques_board[i][j]);
		}
		putchar('\n');
	}
}

int main(int argc, char** argv)
{

	int begintime, endtime;
	scanf("%d", &num);
	begintime = clock();
	//freopen("test.txt","w",stdout);
	sudoku_generate(num);
	endtime = clock();	//计时结束
						//freopen("CON", "w", stdout);
	printf("\nRunning Time：%dms\n", endtime - begintime);
	system("pause");
	return 0;
}



