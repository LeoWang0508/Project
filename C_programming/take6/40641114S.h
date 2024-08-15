#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int32_t point[10];
//card[0][10] player, other(1~10) computers
int32_t card[104], card1[10][10];
int32_t table[4][5];

void rand_card(int32_t arr[])
{
    srand (time(0));
    int32_t i;
    int32_t check[104] = {0};
    int32_t temp;
    for(i = 0; i < 104; i++)	
    {
	temp = rand() % 105;
	while(check[temp] == 1 || temp == 0)
	{
	    temp = rand() % 105;
	}
	arr[i] = temp;
	check[temp] = 1;
    }
    return;
}
void swap_ab(int32_t *a, int32_t *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_card(int32_t arr[][10], int32_t computer_num)
{
    int i, j, k;
    for(k = 0; k < computer_num; k++)
    {
    	for(i = 0; i < 9; i++)
    	{
	    for(j = i + 1; j < 10; j++)
	    {
	    	if(arr[k][i] > arr[k][j])
	    	{
	    	    swap_ab(&arr[k][i], &arr[k][j]);
	    	}
	    }
    	}
    }
}

void sort(int32_t arr[][2], int32_t n)
{
    int i, j;
    for(i = 0; i < n-1; i++)
    {
	for(j = i + 1; j < n; j++)
	{
	    if(arr[i][0] > arr[j][0])
	    {
	    	swap_ab(&arr[i][0], &arr[j][0]);
		swap_ab(&arr[i][1], &arr[j][1]);
	    }
	}
    }
}

void sort_1d(int32_t arr[], int32_t n)
{
    int i, j;
    for(i = 0; i < n-1; i++)
    {
	for(j = i + 1; j < n; j++)
	{
	    if(arr[i] > arr[j])
	    {
	    	swap_ab(&arr[i], &arr[j]);
	    }
	}
    }
}

int32_t point_add(int32_t num)
{
    int32_t point = 0;
    switch(num)
    {
	case 55:
	    point = 7;
	    break;
	case 11: case 22: case 33: case 44: case 66: case 77: case 88: case 99:
	    point = 5;
	    break;
	case 10: case 20: case 30: case 40: case 50: case 60: case 70: case 80: case 90: case 100:
	    point = 3;
	    break;
	case 5: case 15: case 25: case 35: case 45: case 65: case 75: case 85: case 95:
	    point = 2;
	    break;
	case 0:
	    point = 0;
	    break;
	default:
	    point = 1;
	    break;
    }
    return point;
}


int32_t flag_0(int32_t table_arr[4][5])
{
    int i, j, min_point = 105, point_check = 0, return_i;
    for(i = 0; i < 4; i++)
    {
	point_check = 0;
	for(j = 0; j < 5; j++)
	{
	    point_check += point_add(table_arr[i][j]);
	}
	//printf("%d: %d\n", i, point_check);
	if(point_check < min_point)
	{
	    min_point = point_check;
	    return_i = i;
	}
    }
    return return_i;
}

void printf_table(int32_t point_arr[], int32_t table_arr[4][5], int32_t computer_num, int32_t count)
{
    int i, j;
    printf("turn %d |\n", count);
    printf("--------\n");
    printf("player points: ");
    printf("%d\n", point_arr[0]);
    for(i = 1; i < computer_num + 1; i++)
    {
    	printf("computer[%d] points: ", i);
    	printf("%d\n", point_arr[i]);
    }
    printf("-------------------------\n");
    printf("table:\n");
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 5; j++)
        {
   	    printf("%d ", table_arr[i][j]);	
	}	
        printf("\n");
    }
    printf("-------------------------\n");
}

void who_win(int32_t point_arr[], int32_t computer_num)
{
    int32_t min = 1000000, i, return_i[10] = {0}, count = 0;
    for(i = 0; i < computer_num+1; i++)
    {
	if(min > point_arr[i])
	{
	    min = point_arr[i];
	    return_i[0] = i;
	    count = 1;
	}
	else if(min == point_arr[i])
	{
	    return_i[count] = i;
	    count++;
	}
    }
    for(i = 0; i < count; i++)
    {
    	if(return_i[0] == 0)
    	{
	    printf("player win\n");
   	}
    	else
    	{
	    printf("computer[%d] win\n", return_i[i]);
    	}
    }
}

int32_t putcard(int32_t c_card, int32_t table_choose[])
{
    int32_t i, temp_min, min = 105, temp_i = -1;
    for(i = 0; i < 4; i++)
    {
	temp_min = c_card - table_choose[i];
    	if(temp_min > 0 && temp_min < min)
	{
	    min = temp_min;
	    temp_i = i;
	}
    }    
    return temp_i;
}

int32_t computer_choose(int32_t card1[][10], int32_t check1[], int32_t mode, int32_t computer_num,\
 			int32_t table_arr[4][5], int32_t now)
{
    int32_t temp = 0, choose = -1;
    int32_t i, j;
    if(mode == 0)
    {
	srand ( time(NULL) ); 
        temp = rand() % 10;
        while(check1[temp] == 1)
        {
            temp = rand() % 10;
    	}
	choose = temp;
    }
    else if(mode == 1)
    {
	temp = 0;
	while(check1[temp] == 1)
	{
	    temp++;
	}
	choose = temp;
    }
    else if(mode == 2)
    {
	temp = 9;
	while(check1[temp] == 1)
	{
	    temp--;
	}
	choose = temp;	
    }

    else if(mode == 3)
    {
	int32_t card_choose[10] = {0};
	int32_t count = 0;
	i = now;
	for(j = 0; j < 10; j++)
	{
	    if(check1[card1[i][j]] != 1)
	    {
	    	card_choose[count] = card1[i][j];
	    	count++;
	    }
	}
	
	sort_1d(card_choose, count);
	int32_t min = 105, temp_min, temp_i = -1;
	
	//找4排的最後一張牌
	int32_t t_choose = 0;
	int32_t table_choose[4] = {0};
	int32_t table_size[4] = {0};
	for(i = 0; i < 4; i++)
	{
	    for(j = 0; j < 5; j++)
	    {
		if(table[i][j] == 0)
		{
		    table_choose[t_choose] = table_arr[i][j-1];
		    table_size[i] = j-1;
		    t_choose++;
		    j = 5;
		}
		else if(j == 4)
		{
		    table_choose[t_choose] = table_arr[i][j];
		    table_size[i] = j;
		    t_choose++;
		    j = 5;		    
		}
	    }
	}
	
	for(i = 0; i < count; i++)
	{
	    for(j = 0; j < 4; j++)
	    {
		if(table_size[j] != 4)
	    	{
		    temp_min = card_choose[i] - table_choose[j];
	            if(temp_min > 0 && temp_min < min)
	 	    {
		    	min = temp_min;
	    		temp_i = i;	    	
		    }	
	    	}
	    }
	}
	choose = card_choose[temp_i];
	//手牌都比場上的還要大或是場上的牌都牌滿了
	if(temp_i == -1)
	{
	    //出最大的牌
	    choose = card_choose[count-1];
	}	
    }

    return choose;
}

int32_t CSIE_ID_CARD[104];
int32_t CSIE_ID_CHECK[104];
int32_t mycard[10];

void CSIE_ID_setup( int32_t id )
{
    int32_t i;
    for(i = 0; i < 104; i++)
    {
	CSIE_ID_CARD[i] = 0;
    }
    for(i = 0; i < 104; i++)
    {
	CSIE_ID_CHECK[i] = 0;
    }    
    for(i = 0; i < 10; i++)
    {
	mycard[i] = 0;
    }
    return;
}
void CSIE_ID_deal( const int32_t card[] )
{
    int32_t i;
    for(i = 0; i < 10; i++)
    {
	mycard[i] = card[i];
    }
    return;  
}
int32_t CSIE_ID_pick( const int32_t table[4][5], const int32_t score[], const int32_t last[], const int32_t card[] )
{	
	int32_t i, j;
	int32_t card_choose[10] = {0};
	int32_t count = 0;
	for(i = 0; i < 10; i++)
	{
	    if(card[i] != -1)
	    {
	    	card_choose[count] = card[i];
	    	count++;
	    }
	}
	
	sort_1d(card_choose, count);

	int32_t min = 105, temp_min, temp_i = -1;
	//找4排的最後一張牌
	int32_t t_choose = 0;
	int32_t table_choose[4] = {0};
	int32_t table_size[4] = {0};
	for(i = 0; i < 4; i++)
	{
	    for(j = 0; j < 5; j++)
	    {
		if(table[i][j] == 0)
		{
		    table_choose[t_choose] = table[i][j-1];
		    table_size[i] = j-1;
		    t_choose++;
		    j = 5;
		}
		else if(j == 4)
		{
		    table_choose[t_choose] = table[i][j];
		    table_size[i] = j;
		    t_choose++;
		    j = 5;		    
		}
	    }
	}
 
	int32_t choose;
	for(i = 0; i < count; i++)
	{
	    for(j = 0; j < 4; j++)
	    {
		if(table_size[j] != 4)
	    	{
		    temp_min = card_choose[i] - table_choose[j];
	            if(temp_min > 0 && temp_min < min)
	 	    {
		    	min = temp_min;
	    		temp_i = i;	    	
		    }	
	    	}
	    }
	}
	choose = card_choose[temp_i];
	//手牌都比場上的還要大或是場上的牌都牌滿了
	if(temp_i == -1)
	{
	    //出最大的牌
	    choose = card_choose[count-1];
	}
	return choose;
}
int32_t CSIE_ID_choose( const int32_t table[4][5], int32_t card )
{
	int32_t i, j, table_i, table_temp[4][5] = {0};
	for(i = 0; i < 4; i++)
	{
	    for(j = 0; j < 5; j++)
	    {
		table_temp[i][j] = table[i][j];
	    }
	}
	table_i = flag_0(table_temp);
	return table_i;

}
