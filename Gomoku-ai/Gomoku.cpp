#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#define N 15
#define same_u_i same(row + dx[u] * i, col + dy[u] * i, p[row][col])//u��Vi�Z�����I�O�_�P��
#define OutOrNotEmpty (!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //�X�F�ѽL�Ϊ̫D�Ů��I 
 
int p[N + 2][N + 2]; //0��1��2��  1��2�� -1��-2��
int s = 0, ais = 1, s0;//s�O����֤U,s=1,2�As=1�Oai�U�As=2�O���a�As=s0�O�¤�U�A�_�h�O�դ�U
bool is_end = false;
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; 
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//�]dx,dy�^�O8�Ӥ�V�V�q
int manu[2][300], manukey = 0;//���� 
int t = 0, flag = 0;

int out(int i, int j)//���L�ѽL 
{
    if (p[i][j] == 1)return printf("��");
    if (p[i][j] == 2)return printf("��");
    if (p[i][j] == -1)return printf("��");
    if (p[i][j] == -2)return printf("��");
    return printf("* ");

}
 
void DrawBoard()//���L��ӹC���ɭ�
{
    system("cls");
    int row = 0, col = 0, keyr = 0, keyc = 0;
    char alpha = 'A';
    printf("\n   ");
    printf("�ǳƤU��%d��\n\n     ", t);
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
    if (s0 == ais)printf("  AI���¡A���a����\n");
    else if (s0 == 3) printf("  ���a1���¡A���a2����\n");
    else printf("  AI���աA���a����\n");
    alpha = 'A';
    if (keyr)printf("  �̫Ḩ�l��m�G%c%d\n", alpha + keyc - 1, keyr);

}
 
void init()//�C���}����l��
{
    system("color f0");
    printf("\n\n  �C���}�l");
    printf("\n\n  ��J1�Ϊ�2�Ϊ�3�i����\n  1�AAI���¥���\n  2�A���a���¥���\n  3�A���a�����a\n  ");
    scanf("%d", &s);
    if (s != 1 && s != 2 && s != 3)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//�H�Ů�]��ѽL	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}
 
bool inboard(int row, int col)//�P�_(row,col)�O�_�b�ѽL�� 
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}
 
int same(int row, int col, int key)//�P�_2�ӴѤl�O�_�P��
{
    if (!inboard(row, col))return false;
    return (p[row][col] == key || p[row][col] + key == 0);
}
 
int num(int row, int col, int u)//���С]row,col�^�A��V�V�qu�A��^�Ӥ�V���h�ֳs��P��Ѥl
{
    int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
    if (ref == 0)return 0;
    while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
    return sum;
}
 
int live4(int row, int col)//���l����4���ƶq
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)//4�Ӥ�V�A�P�_�C�Ӥ�V�O�_���l�N����4
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
 
int cheng5(int row, int col)//��5�I���ƶq
{
    int sum = 0, i, u;
    for (u = 0; u < 8; u++)//8�Ӧ����I����V
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)
        {
            if (!same_u_i)//�Ӥ�V���Ĥ@�Ӥ��P�⪺�I�A�W�X��ɩΪ̹��Ѥl�ΪŮ�
            {
                if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;//�Ӥ�V���Ĥ@�����P�⪺�I�O���Ѥl,�S�������I 
                flag = false;
            }
            sumk++;
        }
        if (!inboard(row + dx[u] * --i, col + dy[u] * i))continue;//�Ӥ�V���Ĥ@�����P�⪺�I�O���Ѥl,�S�������I
        for (i = -1; same_u_i; i--)sumk++;
        if (sumk == 4)sum++;
    }
    return sum;
}
 
int chong4(int row, int col)//�R4���ƶq
{
    return cheng5(row, col) - live4(row, col) * 2;
}

int live2(int row, int col)//��5�I���ƶq
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)//�T�s�����T
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
int live3(int row, int col)//���l����3���ƶq
{
    int key = p[row][col], sum = 0, i, u,flag=2;
    for (u = 0; u < 4; u++)//�T�s�����T
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
    for (u = 0; u < 8; u++)//8�Ӥ�V�A�C�Ӥ�V�̦h1�ӫD�T�s�����T
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)//�����|�I����V
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

bool end_(int row, int col)//(row,col)�B���l����O�_�C������
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_end = true;
    if (is_end)return true;

    return is_end;
}
 
void go(int row, int col)//���U�@�l
{
    if (s == s0)p[row][col] = -1; //�ХX�̷s�U����
    else p[row][col] = -2;
    if(s==2)
    {	
    	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //�����W�@�ӳ̷s�Ѫ��Х� 
    	{
        	if (i == row && j == col)continue;
        	if (p[i][j] < 0)p[i][j] *= -1;
    	}
	}
    DrawBoard();

    if (end_(row, col))
    {
        if (s == ais)printf("\n  AI��");
        else printf("\n  ���a��");
        //Sleep(10000);
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}
 
bool ok(int row, int col)//��_���l
{
    return inboard(row, col) && (p[row][col] == 0);
}


int point(int row, int col)//�D�t����
{

    if (end_(row, col))
    {
        is_end = false;
        return 100000;
    }
    int ret, u;
    ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100 + (live2(row,col))*10;
    for (u = 0; u < 8; u++)if (p[row + dx[u]][col + dy[u]])ret++;//�L���I0��

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
        if (tempp + p3 * 2 < keyp)keyp = tempp + p3 * 2;//�ĥ|�h�����j
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
        if (tempp - p2 > keyp)keyp = tempp - p2 ;//�ĤT�h�����p�j 
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
        if (tempp < keyp)keyp = tempp;//�ĤG�h�����p 
    }
    return keyp;
}

void AI()
{
    DrawBoard();
    printf("  ����AI�U�A�еy�ԡG ");
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
            }//���İŪK�A�׶}�F�L���I 
            if (tempp == 100000)return go(i, j);
            tempp = AI2();
            p[i][j] = 0;
            if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//�Ĥ@�h�����j
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
    printf("  ����AI�U�A�еy�ԡG ");
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
            if (tempp == 0)       //�ŪK
            {
                p[i][j] = 0;
                continue;
            }
            if (tempp == 100000)return go(i, j);
            tempp = AI2();
            p[i][j] = 0;
            if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//�Ĥ@�h�����j
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
    printf("\n  �¤踨�l��m: ");
    for (i = 0; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    printf("\n  �դ踨�l��m: ");
    for (i = 1; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    //printf("\n%d", manukey);
    Sleep(5000);
}

void player_1()
{
    DrawBoard();
    printf("  ���쪱�a�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ���)�G ");
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
        	printf("���B����U");
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
    	printf("  ���쪱�a�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ��СB��J=1����): ");
    }
    else
    {
    	printf("  ���쪱�a�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ���): ");
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
        	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //�����W�@�ӳ̷s�Ѫ��Х� 
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
        printf("���B����U"); 
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

void go_players(int row, int col)//���U�@�l
{
    if (s == s0)p[row][col] = -1; //�ХX�̷s�U����
    else p[row][col] = -2;

    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //�����W�@�ӳ̷s�Ѫ��Х� 
    {
   	    if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }

    DrawBoard();

    if (end_(row, col))
    {
        if (s == 3)printf("\n  ���a1��");
        else printf("\n  ���a2��");
        //Sleep(10000);
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}

void players_1()
{
    DrawBoard();
    printf("  ���쪱�a1�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ���)�G ");
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
        	printf("���B����U");
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
    	printf("  ���쪱�a1�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ��СB��J=1����)�G ");
    else
    	printf("  ���쪱�a2�U�A�п�J���СA�Ҧp:A15(��J=0�d�ݴ��СB��J=1����)�G ");
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
        	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //�����W�@�ӳ̷s�Ѫ��Х� 
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
        printf("���B����U"); 
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
    	
        		s = 3 - s;//���U�Ѥ�
        		if (t == 225)
        		{
        			printf("\n  ����");
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
    	
        	s = 3 - s;//���U�Ѥ�
        	if (t == 225)
        	{
        		printf("\n  ����");
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
    	printf("\n  �O�_�~��U�@������(�n�~���п�J1): ");	
    	scanf("%d", &start);
    	system("cls");

	}

	   
    return 0;
}

