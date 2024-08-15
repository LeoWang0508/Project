#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#define N 15
#define same_u_i same(row + dx[u] * i, col + dy[u] * i, p[row][col])//u方向i距離的點是否同色
#define OutOrNotEmpty (!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //出了棋盤或者非空格點 
 
int p[N + 2][N + 2]; //0空1黑2白  1●2○ -1▲-2△
int s = 0, ais = 1, s0;//s是輪到誰下,s=1,2，s=1是ai下，s=2是玩家，s=s0是黑方下，否則是白方下
bool is_end = false;
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; 
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//（dx,dy）是8個方向向量
int manu[2][300], manukey = 0;//棋譜 
int t = 0, flag = 0;

int out(int i, int j)//打印棋盤 
{
    if (p[i][j] == 1)return printf("●");
    if (p[i][j] == 2)return printf("○");
    if (p[i][j] == -1)return printf("▲");
    if (p[i][j] == -2)return printf("△");
    return printf("* ");

}
 
void DrawBoard()//打印整個遊戲界面
{
    system("cls");
    int row = 0, col = 0, keyr = 0, keyc = 0;
    char alpha = 'A';
    printf("\n   ");
    printf("準備下第%d手\n\n     ", t);
    for (col = 1; col <= N; col++)printf("%c ", alpha++);
    for (row = N; row >= 1; row--)
    {
        printf("\n   %2d", row);
        for (col = 1; col <= N; col++)
        {
            out(row, col);
            if (p[row][col] < 0)keyr = row, keyc = col;
        }
        printf("%d", row);
    }
    alpha = 'A';
    printf("\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);
    printf("\n\n");
    if (s0 == ais)printf("  AI執黑，玩家執白\n");
    else if (s0 == 3) printf("  玩家1執黑，玩家2執白\n");
    else printf("  AI執白，玩家執黑\n");
    alpha = 'A';
    if (keyr)printf("  最後落子位置：%c%d\n", alpha + keyc - 1, keyr);

}
 
void init()//遊戲開局初始化
{
    system("color f0");
    printf("\n\n  遊戲開始");
    printf("\n\n  輸入1或者2或者3進行選擇\n  1，AI執黑先行\n  2，玩家執黑先行\n  3，玩家打玩家\n  ");
    scanf("%d", &s);
    if (s != 1 && s != 2 && s != 3)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//以空格包圍棋盤	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}
 
bool inboard(int row, int col)//判斷(row,col)是否在棋盤內 
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}
 
int same(int row, int col, int key)//判斷2個棋子是否同色
{
    if (!inboard(row, col))return false;
    return (p[row][col] == key || p[row][col] + key == 0);
}
 
int num(int row, int col, int u)//坐標（row,col），方向向量u，返回該方向有多少連續同色棋子
{
    int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
    if (ref == 0)return 0;
    while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
    return sum;
}
 
int live4(int row, int col)//落子成活4的數量
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)//4個方向，判斷每個方向是否落子就成活4
    {
        int sumk = 1;
        for (i = 1; same_u_i; i++)sumk++;
        if(OutOrNotEmpty)continue;
        for (i = -1; same_u_i; i--)sumk++;
        if(OutOrNotEmpty)continue;
        if (sumk == 4)sum++;
    }
    return sum;
}
 
int cheng5(int row, int col)//成5點的數量
{
    int sum = 0, i, u;
    for (u = 0; u < 8; u++)//8個成五點的方向
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)
        {
            if (!same_u_i)//該方向的第一個不同色的點，超出邊界或者對方棋子或空格
            {
                if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;//該方向的第一不不同色的點是對方棋子,沒有成五點 
                flag = false;
            }
            sumk++;
        }
        if (!inboard(row + dx[u] * --i, col + dy[u] * i))continue;//該方向的第一不不同色的點是對方棋子,沒有成五點
        for (i = -1; same_u_i; i--)sumk++;
        if (sumk == 4)sum++;
    }
    return sum;
}
 
int chong4(int row, int col)//沖4的數量
{
    return cheng5(row, col) - live4(row, col) * 2;
}

int live2(int row, int col)//成5點的數量
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)//三連的活三
    {
        int sumk = 1;
        for (i = 1; same_u_i; i++)sumk++;
        if(OutOrNotEmpty)continue;
        i++;
        if(OutOrNotEmpty)flag--;
        for (i = -1; same_u_i; i--)sumk++;
        if(OutOrNotEmpty)continue;
        i--;
        if(OutOrNotEmpty)flag--;
        if (sumk == 2 && flag>0)sum++;
    }
    return sum;
}
int live3(int row, int col)//落子成活3的數量
{
    int key = p[row][col], sum = 0, i, u,flag=2;
    for (u = 0; u < 4; u++)//三連的活三
    {
        int sumk = 1;
        for (i = 1; same_u_i; i++)sumk++;
        if(OutOrNotEmpty)continue;
        i++;
        if(OutOrNotEmpty)flag--;
        for (i = -1; same_u_i; i--)sumk++;
        if(OutOrNotEmpty)continue;
        i--;
        if(OutOrNotEmpty)flag--;
        if (sumk == 3 && flag>0)sum++;
    }
    for (u = 0; u < 8; u++)//8個方向，每個方向最多1個非三連的活三
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)//成活四點的方向
        {
            if (!same_u_i)
            {
                if (flag&&p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
                flag = false;
            }
            sumk++;
        }
        if(OutOrNotEmpty)continue;;
        if (p[row + dx[u] * --i][col + dy[u] * i] == 0)continue;
        for (i = 1; same_u_i; i++)sumk++;
        if(OutOrNotEmpty)continue;;
        if (sumk == 3)sum++;
    }
    return sum;
}

bool end_(int row, int col)//(row,col)處落子之後是否遊戲結束
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_end = true;
    if (is_end)return true;

    return is_end;
}
 
void go(int row, int col)//落下一子
{
    if (s == s0)p[row][col] = -1; //標出最新下的棋
    else p[row][col] = -2;
    if(s==2)
    {	
    	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一個最新棋的標示 
    	{
        	if (i == row && j == col)continue;
        	if (p[i][j] < 0)p[i][j] *= -1;
    	}
	}
    DrawBoard();

    if (end_(row, col))
    {
        if (s == ais)printf("\n  AI勝");
        else printf("\n  玩家勝");
        //Sleep(10000);
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}
 
bool ok(int row, int col)//能否落子
{
    return inboard(row, col) && (p[row][col] == 0);
}


int point(int row, int col)//非負分值
{

    if (end_(row, col))
    {
        is_end = false;
        return 100000;
    }
    int ret, u;
    ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100 + (live2(row,col))*10;
    for (u = 0; u < 8; u++)if (p[row + dx[u]][col + dy[u]])ret++;//無效點0分

    return ret;
}

int AI4(int p3)
{
    int keyp = 1000000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if (!ok(i, j))continue;
        p[i][j] = 3 - s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            p[i][j] = 0;
            continue;
        }
        if (tempp == 100000)
        {
            p[i][j] = 0;
            return -100000;
        }
        p[i][j] = 0;
        if (tempp + p3 * 2 < keyp)keyp = tempp + p3 * 2;//第四層取極大
    }
    return keyp;
}

int AI3(int p2)
{
    int keyp = -1000000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if (!ok(i, j))continue;
        p[i][j] = s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            p[i][j] = 0;
            continue;
        }
        if (tempp == 100000)
        {
            p[i][j] = 0;
            return 100000;
        }
        //tempp = AI4(tempp);
        p[i][j] = 0;
        if (tempp - p2 > keyp)keyp = tempp - p2 ;//第三層取極小大 
    }
    return keyp;
}
 
int AI2()
{
    int keyp = 1000000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if (!ok(i, j))continue;
        p[i][j] = 3 - s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            p[i][j] = 0;
            continue;
        }
        if (tempp == 100000)
        {
            p[i][j] = 0;
            return -100000;
        }
        tempp = AI3(tempp);
        p[i][j] = 0;
        if (tempp < keyp)keyp = tempp;//第二層取極小 
    }
    return keyp;
}

void AI()
{
    DrawBoard();
    printf("  輪到AI下，請稍候： ");
    if(t==1)
    {
    	return go(2, 8);
	}
    int i, j;
    int keyp = -1000000, keyi, keyj, tempp;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            if (!ok(i, j))continue;
            p[i][j] = s0;
            tempp = point(i, j);
            if (tempp == 0)
            {
                p[i][j] = 0;
                continue;
            }//高效剪枝，避開了無效點 
            if (tempp == 100000)return go(i, j);
            tempp = AI2();
            p[i][j] = 0;
            if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//第一層取極大
            else if (tempp == keyp)
            {
            	if ((abs(i - 8) + abs(j - 8)) < (abs(keyi - 8) + abs(keyj - 8)))
            	{
            		keyp = tempp, keyi = i, keyj = j;
				}
			}
        }
    }
    
    return go(keyi, keyj);
}

void AI1()
{
    DrawBoard();
    printf("  輪到AI下，請稍候： ");
    if(t==1)
    {
    	return go(2, 8);
	}
    int i, j;
    int keyp = -1000000, keyi, keyj, tempp;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++) 
        {
            if (!ok(i, j))continue;
            p[i][j] = s0;
            tempp = point(i, j);
            if (tempp == 0)       //剪枝
            {
                p[i][j] = 0;
                continue;
            }
            if (tempp == 100000)return go(i, j);
            tempp = AI2();
            p[i][j] = 0;
            if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//第一層取極大
            else if (tempp == keyp)
            {
            	if ((abs(i - 8) + abs(j - 8)) < (abs(keyi - 8) + abs(keyj - 8)))
            	{
            		keyp = tempp, keyi = i, keyj = j;
				}
			}
        }
    }
    
    return go(keyi, keyj);
}

void out_manual()
{
    char alpha = 'A';
    int i;
    printf("\n  黑方落子位置: ");
    for (i = 0; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    printf("\n  白方落子位置: ");
    for (i = 1; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    //printf("\n%d", manukey);
    Sleep(5000);
}

void player_1()
{
    DrawBoard();
    printf("  輪到玩家下，請輸入坐標，例如:A15(輸入=0查看棋譜)： ");
    char c = '\n';
    int row = 0, col = 0;
    while (c<'0')scanf("%c%d", &c, &row);
    if (c == '=')
    {
    	if(row==0)
    	{
        	out_manual();
        	return player_1();
        }
    }
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;
    if (col != 1 && col != 2 && col != 14 && col != 15)
    {
    	if (row != 1 && row != 2 && row != 14 && row != 15)
    	{
        	printf("此處不能下");
        	printf("(%c %d)\n", c, col);
        	Sleep(1000);
        	return player_1();    	
    	}
	}

    go(row, col);
}

void player()
{
	
    DrawBoard();
    if(t > 2 && flag == 0)
    {
    	printf("  輪到玩家下，請輸入坐標，例如:A15(輸入=0查看棋譜、輸入=1悔棋): ");
    }
    else
    {
    	printf("  輪到玩家下，請輸入坐標，例如:A15(輸入=0查看棋譜): ");
    }
    flag = 0;
    char c = '\n';
    int row = 0, col = 0;
    while (c<'0')scanf("%c%d", &c, &row);
    if (c == '=')
    {
    	if(row == 0)
    	{
        	out_manual();
        	return player();
        }
        if(row == 1 && t > 2)
        {
        	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一個最新棋的標示 
    		{

				//printf("  %c%d", alpha + manu[1][manukey-3] - 1, manu[0][manukey-3]);

				//printf("  %c%d", alpha + manu[1][manukey-4] - 1  , manu[0][manukey-4]);
				//Sleep(5000);
        		if (p[i][j] < 0)
					p[i][j] = 0;
				flag = 1;

    		}
		}
    }
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;
    if (!ok(row, col) && flag == 0)
    {
        printf("此處不能下"); 
		printf("(%c %d)\n", c, col);      
        Sleep(1000);
        return player();
    }

    if(flag == 1)
    {
    	manukey = manukey - 2;	
    	t = t - 2;
    	if(t == 3)
    	{
    		return player_1();
    	}
    	else
    		return player();
	}
	go(row, col);
}

void go_players(int row, int col)//落下一子
{
    if (s == s0)p[row][col] = -1; //標出最新下的棋
    else p[row][col] = -2;

    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一個最新棋的標示 
    {
   	    if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }

    DrawBoard();

    if (end_(row, col))
    {
        if (s == 3)printf("\n  玩家1勝");
        else printf("\n  玩家2勝");
        //Sleep(10000);
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}

void players_1()
{
    DrawBoard();
    printf("  輪到玩家1下，請輸入坐標，例如:A15(輸入=0查看棋譜)： ");
    char c = '\n';
    int row = 0, col = 0;
    while (c<'0')scanf("%c%d", &c, &row);
    if (c == '=')
    {
    	if(row == 0)
    	{
        	out_manual();
        	return player_1();
        }
    }
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;
    if (col != 1 && col != 2 && col != 14 && col != 15)
    {
    	if (row != 1 && row != 2 && row != 14 && row != 15)
    	{
        	printf("此處不能下");
        	printf("(%c %d)\n", c, row); 
        	Sleep(1000);
        	return player_1();    	
    	}
	}

    go_players(row, col);
}

void players()
{
	

    DrawBoard();
    if (s == 3 &&flag == 0)
    	printf("  輪到玩家1下，請輸入坐標，例如:A15(輸入=0查看棋譜、輸入=1悔棋)： ");
    else
    	printf("  輪到玩家2下，請輸入坐標，例如:A15(輸入=0查看棋譜、輸入=1悔棋)： ");
    flag = 0;
    char c = '\n';
    int row = 0, col = 0;
    while (c<'0')scanf("%c%d", &c, &row);
    if (c == '=')
    {
    	if(row == 0)
    	{
        	out_manual();
        	return players();
        }
        if(row == 1)
        {
        	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一個最新棋的標示 
    		{
        		if (i == row && j == col)continue;
        		if (p[i][j] < 0)p[i][j] = 0;
        		flag = 1;
    		}
		}
    }
    
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;

    if (!ok(row, col) && flag == 0)
    {
        printf("此處不能下"); 
		printf("(%c %d)\n", c, col);      
        Sleep(1000);
        return players();
    }
    if (flag == 1)
    {
    	manukey = manukey - 1;
    	t = t - 1;
    	s = 3 - s;
    	if(t == 3)
    	{
    		return players_1();
    	}
    	else
    		return players();
	}
    go_players(row, col);
	
}


int main()
{
	int start = 1; 
	
	
	while (start == 1)
	{
		init();
		t = 0;
		if (s == 3)
		{
			while (!is_end)
			{
    			t += 1;
				if(t==1)
				{
					players_1();
				}
				else
				{
        			players();
    			}
    	
        		s = 3 - s;//換下棋方
        		if (t == 225)
        		{
        			printf("\n  平手");
        			is_end = true;
				}	
			}
		}
    	while (!is_end)
    	{
    		
    		t += 1;
			if(t==1)
			{
				if (s == ais)AI();
        		else player_1();
        		
			}
			else
			{
        		if (s == ais)AI();
        		else player();
        		
    		}
    	
        	s = 3 - s;//換下棋方
        	if (t == 225)
        	{
        		printf("\n  平手");
        		is_end = true;
			}
    	}
    	
    	out_manual();
    	printf("\n");
		s = 0;
		ais = 1;
		is_end = false;
		manukey = 0;
    	start = 0;
    	printf("\n  是否繼續下一場比賽(要繼續比請輸入1): ");	
    	scanf("%d", &start);
    	system("cls");

	}

	   
    return 0;
}

