#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "40641114S.h"

int main()
{
    int32_t i, j;
    //計分
    for(i = 0; i < 10; i++)
    {
	point[i] = 0;
    }
    //牌組
    for(i = 0; i < 104; i++)
    {
        card[i] = 0;
    }
    for(i = 0; i < 10; i++)
    {
	for(j = 0; j < 10; j++)
	{
            card1[i][j] = 0;
	}
    }

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 5; j++)
	{
  	    table[i][j] = 0;
	}
    }     
    printf("welcome to take6! game\n");
    printf("choose computer level(0~3): ");
    int32_t level, flag2 = 0;
    scanf("%d", &level);
    while(level > 3 || level < 0)
    {
	if(level == 5487)
	{
	    flag2 = 1;
	}
	printf("choose computer level(0~3): ");
    	scanf("%d", &level);
    }
    printf("computer number(1~9): ");
    int32_t computer_num;
    scanf("%d", &computer_num);
    while(computer_num > 9 || computer_num < 1)
    {
	printf("computer number(1~9): ");
    	scanf("%d", &computer_num);
    }
    //洗牌
    rand_card(card);

    //發牌
    int32_t temp;
    int32_t check3[104] = {0};
    for(i = 0; i < 10; i++)
    {
	for(j = 0; j < 10; j++)
	{
	    srand ( time(NULL) ); 
            temp = rand() % 104;
	    while(check3[temp] == 1)
	    {
		temp = rand() % 104;
	    }
	    check3[temp] = 1;
	    card1[i][j] = card[temp];
	}
    }
    //sort
    if(level == 1 || level == 2)
    {
    	sort_card(card1, computer_num+1);
    }
    else
    {
	sort_card(card1, 1);
    }


    //放4張牌到桌上
    for(i = 0; i < 4; i++)
    {
    	srand ( time(NULL) ); 
        temp = rand() % 104;
        while(check3[temp] == 1)
	{
	    temp = rand() % 104;
	}
	check3[temp] = 1;
	table[i][0] = card[temp];
    }  
    int32_t count = 0;
    int32_t check[104] = {0};
    int32_t check1[10] = {0};
    int32_t check2[104] = {0};
    int32_t choose;
    int32_t temp1;
    int32_t temp2[10] = {0};

    printf("***************************************\n");
    do
    {
    	int32_t tag = 0, flag = 0;
    	int32_t table_choose[4] = {0};
    	int32_t table_size[4] = {0};
	int32_t point_min = 105, temp_point_min = 0, temp_point_min_i = 0;
	int32_t min = 105;
	int32_t temp_min = 105, temp_i = 0;
	int32_t card_small_to_big[10][2] = {0};
	
	//印出現在的戰況 分數和牌桌
	printf_table(point, table, computer_num, count);
	//找4排的最後一張牌
	int32_t t_choose = 0;
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
	//電腦出牌
	if(level != 3)
	{
	    temp1 = computer_choose(card1 ,check1, level, computer_num, table, 0);
	    check1[temp1] = 1;	
	}
	if(level == 3)
	{
	    for(i = 1; i <= computer_num; i++)
	    {
	    	temp2[i] = computer_choose(card1 ,check2, level, computer_num, table, i);
		check2[temp2[i]] = 1;
		//printf("%d\n", temp2[i]);
	    }
	}

	if(flag2 == 1)
	{
	    if(level != 3)
	    {
	    	for(i = 1; i <= computer_num; i++)
	    	{
	       	    printf("computer[%d] choose: %d\n", i, card1[i][temp1]);
	    	}
	    }
	    if(level == 3)
	    {
	    	for(i = 1; i <= computer_num; i++)
	    	{
	       	    printf("computer[%d] choose: %d\n", i, temp2[i]);
	    	}		
	    }
	}
	//自己出牌
	while(tag == 0)
	{
	    printf("my cards:\n");
	    //印出手排
	    for(i = 0; i < 10; i++)
	    {
	    	if(check[card1[0][i]] != 1)
	    	{
		    printf("%d ", card1[0][i]);
	    	}
	    }
	    printf("\n");
	    printf("choose one card: ");
	    scanf("%d", &choose);
	    for(i = 0; i < 10; i++)
	    {
	    	if(card1[0][i] == choose)
	    	{
		    check[card1[0][i]] = 1;
		    tag = 1;
	        }
	    }	
	    if(tag == 0)
	    {
		printf("error\n");
	    }
	}
	tag = 0;

	if(flag2 != 1)
	{
	    if(level != 3)
	    {
	    	for(i = 1; i <= computer_num; i++)
	    	{
	    	    printf("computer[%d] choose: %d\n", i, card1[i][temp1]);
	    	}
	    }
	    if(level == 3)
	    {
	    	for(i = 1; i <= computer_num; i++)
	    	{
	       	    printf("computer[%d] choose: %d\n", i, temp2[i]);
	    	}		
	    }
	}
	card_small_to_big[0][0] = choose;
	card_small_to_big[0][1] = 0;
	if(level != 3)
	{
	    for(i = 1; i <= computer_num; i++)
	    {
	    	card_small_to_big[i][0] = card1[i][temp1];
	    	card_small_to_big[i][1] = i;
	    }
	}
	if(level == 3)
	{
	    for(i = 1; i <= computer_num; i++)
	    {
	    	card_small_to_big[i][0] = temp2[i];
	    	card_small_to_big[i][1] = i;
	    }
	}
	//電腦和玩家的排比大小
	sort(card_small_to_big, computer_num+1);
/*
	for(i = 0; i <= computer_num; i++)
	{
	    printf("%d: %d\n", card_small_to_big[i][1], card_small_to_big[i][0]);
	}	
*/
	for(i = 0; i <= computer_num; i++)
	{
	    temp_i = putcard(card_small_to_big[i][0], table_choose);
	    //比場上的牌還要小
	    if(temp_i == -1)
	    {
		int32_t table_i;
		//找出要選那一排
		if(card_small_to_big[i][1] == 0)
		{
		    int32_t choose_row;
    		    for(i = 0; i < 4; i++)
    		    {
        		for(j = 0; j < 5; j++)
        		{
   	    		    printf("%d ", table[i][j]);	
			}	
        		printf("\n");
    		    }
		    printf("choose one row(0~3): ");
		    scanf("%d", &choose_row);	
		    while(choose_row > 3 || choose_row < 0)
		    {
			printf("choose one row(0~3): ");
			scanf("%d", &choose_row);
		    }
		    for(j = 0; j < 5; j++)
		    {
		    	point[0] += point_add(table[choose_row][j]);
		    }	
		    table[choose_row][0] = card_small_to_big[i][0];
	            //牌面上最右邊的牌變成 card_small_to_big[i][0]
	            table_choose[choose_row] = card_small_to_big[i][0];
		    for(j = 1; j < 5; j++)
		    {
		    	table[choose_row][j] = 0;
		    }
		    table_size[choose_row] = 0;	    
		}
		else
		{
		    table_i = flag_0(table);
		    for(j = 0; j < 5; j++)
		    {
		    	point[card_small_to_big[i][1]] += point_add(table[table_i][j]);
		    }
		
		    table[table_i][0] = card_small_to_big[i][0];
	            //牌面上最右邊的牌變成 card_small_to_big[i][0]
	            table_choose[table_i] = card_small_to_big[i][0];
		    for(j = 1; j < 5; j++)
		    {
		    	table[table_i][j] = 0;
		    }
		    table_size[table_i] = 0;
		}
	    }
	    else
	    {
	    	//牌面上最右邊的牌變成 card1[temp1]
	    	table_choose[temp_i] = card_small_to_big[i][0];
	    	//確定有沒有到6張牌
	    	if(table_size[temp_i] + 1 == 5)
	    	{
		    for(j = 0; j < 5; j++)
		    {
		    	point[card_small_to_big[i][1]] += point_add(table[temp_i][j]);
		    }
	 	    table[temp_i][0] = card_small_to_big[i][0];
		    for(j = 1; j < 5; j++)
		    {
		    	table[temp_i][j] = 0;
		    }
		    table_size[temp_i] = 0;
	    	}
	    	else
	    	{
		    table[temp_i][table_size[temp_i]+1] = card_small_to_big[i][0];
		    table_size[temp_i]++;
	    	}
	    }
	}


	printf("***************************************\n");
  	count++;
	if(count == 10)
	{
	    printf_table(point, table, computer_num, count);
	    
    	    int32_t again = 0;
	    printf("Do you want to play again(0~1): ");
	   
	    scanf("%d", &again);
	    while(again < 0 || again > 1)
	    {
		printf("Do you want to play again(0~1): ");
		scanf("%d", &again);
	    }
	    if(again == 0)
	    {
		//判斷誰贏
		who_win(point, computer_num);
	    }
	    if(again == 1)
	    {
		count = 0;
		printf("Do you want to init points(0~1)? ");
		int32_t again_point = 0;
		scanf("%d", &again_point);
	    	while(again < 0 || again > 1)
	    	{
		    printf("Do you want to init points(0~1)? ");
		    scanf("%d", &again_point);
	    	}
		if(again_point == 1)
		{
    		    for(i = 0; i < 10; i++)
    		    {
		    	point[i] = 0;
    		    }
		}
    		//牌組
    		for(i = 0; i < 104; i++)
    		{
        	    card[i] = 0;
    		}
    		for(i = 0; i < 10; i++)
    		{
		    for(j = 0; j < 10; j++)
		    {
            		card1[i][j] = 0;
		    }
    		}

    		for(i = 0; i < 4; i++)
    		{
        	    for(j = 0; j < 5; j++)
		    {
  	    		table[i][j] = 0;
		    }
    		}   
    		printf("choose computer level(0~3): ");
    		scanf("%d", &level);
    		while(level > 3 || level < 0)
    		{
		    if(level == 5487)
		    {
	    		flag2 = 1;
		    }
		    printf("choose computer level(0~3): ");
    		    scanf("%d", &level);
    	   	}
    		printf("computer number(1~9): ");
    		scanf("%d", &computer_num);
    		while(computer_num > 9 || computer_num < 1)
    		{
		    printf("computer number(1~9): ");
    		    scanf("%d", &computer_num);
    		}
    		//洗牌
    		rand_card(card);

    		//發牌
		for(i = 0; i < 104; i++)
		{
    		    check2[i] = 0;
		}
    		for(i = 0; i < 10; i++)
    		{
		    for(j = 0; j < 10; j++)
		    {
	    		srand ( time(NULL) ); 
            		temp = rand() % 104;
	    		while(check2[temp] == 1)
	    		{
			    temp = rand() % 104;
	    		}
	    		check2[temp] = 1;
	    		card1[i][j] = card[temp];
		    }
    		}
    		//sort
    		if(level == 1 || level == 2)
    		{
    		    sort_card(card1, computer_num+1);
    	   	}
    		else
    		{
		    sort_card(card1, 1);
    		}


    		//放4張牌到桌上
    		for(i = 0; i < 4; i++)
    		{
    		    srand ( time(NULL) ); 
        	    temp = rand() % 104;
        	    while(check2[temp] == 1)
		    {
		    	temp = rand() % 104;
		    }
		    check2[temp] = 1;
		    table[i][0] = card[temp];
    		}  
		for(i = 0; i < 104; i++)
		{
		    check[i] = 0;
		}
		for(i = 0; i < 10; i++)
		{
		    check1[i] = 0;
		}
		for(i = 0; i < 104; i++)
		{
		    check2[i] = 0;
		}
  
	    }
	}

    }while(count != 10);
    printf("***************************************\n");

    return 0;
}
