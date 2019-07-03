/****************************************Copyright (c)****************************************************
**                                                             贺宏宏.
**                                             email:549761222@qq.com
**                                 
**                     该源码可以随意分发，复制和修改但必须保留原作者信息
**---------------------------File Info--------------------------------------------------------------------
** File name:                    2048.cpp
** Last modified Date:     2014-12-05
** Last Version:                0.0.1
** Descriptions:               实现2048游戏的基本功能
**
**--------------------------------------------------------------------------------------------------------
** Created by:                Hehonghong
** Created date:             2014-12-05
** Version:                     0.0.1
** Descriptions:             实现2048游戏的基本功能
**
**--------------------------------------------------------------------------------------------------------
** Modified by:              Hehonghong
** Modified date:           2015-03-15
** Version:                      0.0.2
** Descriptions:             1、某一方向不能移动数据和合并数据时忽略该方向按键，不产生新的数字
**                                  2、优化对游戏结束的判断
**
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ROW 4                                                                      /*  行数                                 */
#define COL ROW                                                                  /*  列数                                 */

#define KEY_UP 72                                                                 /*  方向键'上'的扫描码码值     */
#define KEY_DOWN 80                                                          /*  方向键'下'的扫描码码值     */
#define KEY_LEFT  75                                                             /*  方向键'左'的扫描码码值     */
#define KEY_RIGHT 77                                                           /*  方向键'右'的扫描码码值     */

#define BLANK  0                                                                  /*  空白区域的数字                  */

int g_seed = 0;                                                                      /*  修改随机数种子                  */

/*********************************************************************************************************
** Function name:           Show
** Descriptions:               显示界面
** input parameters:       arr   :保存数据的数组                          
** Returned value:          NONE
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Show(int (*arr)[COL])
{
	system("cls");                                                                    /*  清屏,dos命令                      */
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
		{
			printf("%5d",arr[i][j]);
		}
		printf("\n");
	}
}

/*********************************************************************************************************
** Function name:           MergeLeft
** Descriptions:               向左合并数据，所有的数据向左移动，相邻相同的数字合并成更大的数字
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true:数字合并或位置移动过,false:没有发生改变
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool MergeLeft(int (*arr)[COL])
{
	int index1;                                                                         /*  第一个值的下标                  */
	int index2;                                                                         /*  第二个值的下标                  */
	int i;
	int j;
	int k;
	bool flg = false;                                                                   /*  数字和位置是否有改变          */

	for(i=0;i<ROW;i++)
	{
		index2 = index1 = -1;
		for(j=0;j<COL;j++)                                                        /*  合并相应的值,值的位置不动 */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  查找第一个值                     */
			{
				index1 = j;
				j++;
			}
			if(j<COL && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  查找第二个值                     */
				index2 = j;
			}
			if(index1!=-1 && index2!=-1)                                   /*  查找到两个相同值则合并     */
			{
				if(arr[i][index1] == arr[i][index2])
				{
					arr[i][index1] *= 2;
					arr[i][index2] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  两个值不相同进入下趟查找  */
				{
					index1 = index2;                                               /* 第二个值作为下趟的第一个值*/
					index2 = -1;
				}
			}
		}
	
		for(j=0;j<COL-1;j++)                                                     /* 将非0数据依次移动到最左边 */
		{	
			 index1 = -1;                                                             /* 记录第一个0的下标              */
			for(k=0;k<COL;k++)
			{
				if(arr[i][k]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[i][k]!=BLANK && index1!=-1)                       /*  第一个0后第一个非0的下标 */
				{
					arr[i][index1] = arr[i][k];                                    /*  非0值移到0值的位置           */    
					arr[i][k] = 0;                                                      /*  非0值的位置变成0              */
					flg = true;
					break;                                                               /*  进行下一趟的0和非0查找    */
				} 
			}
		}
	}

	return flg;
}

/*********************************************************************************************************
** Function name:           MergeUp
** Descriptions:               向上合并数据，所有的数据向上移动，相邻相同的数字合并成更大的数字
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true:数字合并或位置移动过,false:没有发生改变
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool MergeUp(int (*arr)[COL])
{
	int index1;                                                                         /*  第一个值的下标                  */
	int index2;                                                                         /*  第二个值的下标                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(j=0;j<COL;j++)                                                             /*  按列的顺序处理数据           */
	{                                                                                         /*  j表示列                             */
		index2 = index1 = -1;
		for(i=0;i<ROW;i++)                                                       /*  合并相应的值,值的位置不动 */
		{
			if(arr[i][j]!=BLANK && index1==-1)                           /*  查找第一个值                     */
			{
				index1 = i;
				i++;
			}
			if(i<ROW && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  查找第二个值                     */
				index2 = i;
			}
			if(index1!=-1 && index2!=-1)                                   /*  查找到两个相同值则合并     */
			{
				if(arr[index1][j] == arr[index2][j])
				{
					arr[index1][j] *= 2;
					arr[index2][j] = BLANK;
					index2 = index1 = -1;
					flg = true;
				}
				else                                                                       /*  两个值不相同进入下趟查找  */
				{
					index1 = index2;                                               /* 第二个值作为下趟的第一个值*/
					index2 = -1;
				}
			}
		}
	
		for(i=0;i<ROW-1;i++)                                                   /* 将非0数据依次移动到最上边 */
		{	
			 index1 = -1;                                                             /* 从上到下第一个0的下标       */
			for(k=0;k<ROW;k++)
			{
				if(arr[k][j]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[k][j]!=BLANK && index1!=-1)                       /*  第一个0后第一个非0的下标 */
				{
					arr[index1][j] = arr[k][j];
					arr[k][j] = 0;
					flg = true;
					break;                                                                /*  进行下一趟的0和非0查找    */
				}
			}
		}
	}

	return flg;
}

/*********************************************************************************************************
** Function name:           MergeRight
** Descriptions:               向右合并数据，所有的数据向右移动，相邻相同的数字合并成更大的数字
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true:数字合并或位置移动过,false:没有发生改变
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool MergeRight(int (*arr)[COL])
{
	int index1;                                                                         /*  第一个值的下标                  */
	int index2;                                                                         /*  第二个值的下标                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(i=0;i<ROW;i++)   
	{
		index2 = index1 = -1;
		for(j=COL-1;j>=0;j--)                                                    /*  合并相应的值,值的位置不动 */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  查找第一个值                     */
			{
				index1 = j;
				j--;
			}
			if(j>=0 && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  查找第二个值                     */
				index2 = j;
			}
			if(index1!=-1 && index2!=-1)                                   /*  查找到两个相同值则合并     */
			{
				if(arr[i][index1] == arr[i][index2]) 
				{
					arr[i][index1] *= 2;
					arr[i][index2] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  两个值不相同进入下趟查找  */
				{
					index1 = index2;                                               /* 第二个值作为下趟的第一个值*/
					index2 = -1;
				}
			}
		}
	
		for(j=0;j<COL-1;j++)                                                     /* 将非0数据依次移动到最右边 */
		{	                                                                                 /* j表示趟数                            */
			 index1 = -1;                                                             /* 从右到左第一个0的下标        */
			for(k=COL-1;k>=0;k--)                                             /* 从右到左遍历                       */
			{
				if(arr[i][k]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[i][k]!=BLANK && index1!=-1)                       /*  第一个0后第一个非0的下标 */
				{
					arr[i][index1] = arr[i][k];
					arr[i][k] = 0;
					flg = true;
					break;                                                                /*  进行下一趟的0和非0查找    */
				}
			}
		}
	}
	return flg;
}

/*********************************************************************************************************
** Function name:           MergeDown
** Descriptions:               向下合并数据，所有的数据向下移动，相邻相同的数字合并成更大的数字
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true:数字合并或位置移动过,false:没有发生改变
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool MergeDown(int (*arr)[COL])
{
	int index1;                                                                         /*  第一个值的下标                  */
	int index2;                                                                         /*  第二个值的下标                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(j=0;j<COL;j++)                                                             /*  按列的顺序处理数据           */
	{                                                                                        /*  j表示列                              */
		index2 = index1 = -1;
		for(i=ROW-1;i>=0;i--)                                                  /*  合并相应的值,值的位置不动 */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  查找第一个值                     */
			{
				index1 = i;
				i--;
			}
			if(i>=0 && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  查找第二个值                     */
				index2 = i;
			}
			if(index1!=-1 && index2!=-1)                                   /*  查找到两个相同值则合并     */
			{
				if(arr[index1][j] == arr[index2][j])
				{
					arr[index1][j] *= 2;
					arr[index2][j] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  两个值不相同进入下趟查找  */
				{
					index1 = index2;                                               /* 第二个值作为下趟的第一个值*/
					index2 = -1;
				}
			}
		}
	
		for(i=0;i<ROW-1;i++)                                                   /* 将非0数据依次移动到最下边 */
		{	                                                                                 /* i表示趟数                            */
			 index1 = -1;                                                             /* 从下到上第一个0的下标        */
			for(k=ROW-1;k>=0;k--)                                            /* 从下到上遍历                      */ 
			{
				if(arr[k][j]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[k][j]!=BLANK && index1!=-1)                       /*  第一个0后第一个非0的下标 */
				{
					arr[index1][j] = arr[k][j];
					arr[k][j] = 0;
					flg = true;
					break;                                                                /*  进行下一趟的0和非0查找    */
				}
			}
		}
	}
	return flg;
}

/*********************************************************************************************************
** Function name:           IsGameover
** Descriptions:               游戏是否结束判断函数,目前只是简单判断空闲格子的数量
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true :游戏结束,false :游戏未结束
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:              hehonghong
** Modified date:           2015-03-15
** Descriptions:              添加对相邻数字是否相等的判断
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if 0
bool IsGameover(int (*arr)[COL])
{
	int activeCell = 0;                                                               /*统计还没有填充数据的格子数*/
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
		{
			if(arr[i][j] == 0)
			{
				activeCell++;
			}
		}
	}
	return activeCell == 0;                                                       /*  没有空闲格子游戏结束        */
}
#endif
bool IsGameover(int (*arr)[COL])
{
	int activeCell = 0;                                                               /*统计还没有填充数据的格子数*/
	int i;
	int j;
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(arr[i][j] == 0)
			{
				activeCell++;
			}
		}
	}
	if(activeCell != 0)                                                               /*  有空闲格子游戏不结束         */
	{
		return false;
	}
	
	for(i=0;i<ROW-1;i++)                                                        /*  判断相邻的数字是否相同      */
	{
		for(j=0;j<COL-1;j++)
		{
			if(arr[i][j]==arr[i][j+1] || arr[i][j]==arr[i+1][j])
			{
				return false;
			}
		}
	}

	for(i=0;i<ROW-1;i++)                                                         /*  判断最后一列向下的数字是否相同 */               
	{
		if(arr[i][COL-1] == arr[i+1][COL-1])
		{
			return false;
		}
	}

	for(i=0;i<COL-1;i++)                                                          /*  判断最后一行向右的数字是否相同 */
	{
		if(arr[ROW-1][i] == arr[ROW-1][i+1])
		{
			return false;
		}
	}

	return true;
}
/*********************************************************************************************************
** Function name:           GetNum
** Descriptions:               产生新的数字
** input parameters:       arr   :保存数据的数组                          
** Returned value:          true :成功,false :失败
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool GetNum(int (*arr)[COL])
{
	if(IsGameover(arr))
	{
		return false;
	}
	srand((unsigned int)time(NULL)+ g_seed++);                   /*  生成随机种子                     */
	                                                                                         /*  g_seed防止一秒内产生的    */
	                                                                                         /*  数字相同                            */
	int row = rand()%ROW;                                                     /*  行的下标                           */   
	int col = rand()%COL;                                                        /*  列的下标                           */
	int num = 2;                                                                      /*  数字默认为2                      */
	if(rand()%5 == 0)                                                               /*  偶尔产生数字4                  */
	{
		num = 4;
	}
	while(arr[row][col] != 0)                                                     /*  找到没有数据的格子下标    */
	{
		col++;
		if(col == COL)
		{
			row = (row+1)%ROW;
			col = 0;
		}
	}
	arr[row][col] = num;

	return true;
}

/*********************************************************************************************************
** Function name:           GetButton
** Descriptions:               获取到方向键的值
** input parameters:       arr   :保存数据的数组                          
** Returned value:          方向键值，1左,2上,3右,4下
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
int GetButton()
{
	int ch;
	while(1)
	{
		if(_kbhit() != 0)
		{
			ch = _getch();
			if(ch ==  0xE0)
			{
				ch = _getch();
				switch(ch)
				{
				case KEY_LEFT:
					return 1;
				case KEY_UP:
					return 2;
				case KEY_RIGHT:
					return 3;
				case KEY_DOWN:
					return 4;
				default:
					break;
				}
			}
		}
		Sleep(100);                                                                /*避免系统忙等待,降低CPU使用率*/
	}
	return 0;
}

/*********************************************************************************************************
** Function name:           MergeNum
** Descriptions:               根据方向键合并相应的数字
** input parameters:       arr     :保存数据的数组  
**                                    dirce :方向值                      
** Returned value:          true:数字合并或位置移动过,false:没有发生改变
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
bool MergeNum(int (*arr)[COL],int dirce)
{
	bool flg = false;
	switch(dirce)
	{
	case 1:
		flg = MergeLeft(arr);
		break;
	case 2:
		flg = MergeUp(arr);
		break;
	case 3:
		flg = MergeRight(arr);
		break;
	case 4:
		flg = MergeDown(arr);
		break;
	default:
		break;
	}

	return flg;
}

/*********************************************************************************************************
** Function name:           Start
** Descriptions:               开始游戏
** input parameters:       arr     :保存数据的数组                      
** Returned value:          NONE
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Start(int (*arr)[COL])
{
	for(int i=0;i<2;i++)                                                             /*  开始界面必须有两个数字    */
	{
		GetNum(arr);
	}

	Show(arr);
}
/*********************************************************************************************************
** Function name:           Run
** Descriptions:               运行游戏
** input parameters:       arr     :保存数据的数组                      
** Returned value:          NONE
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Run(int (*arr)[COL])
{
	int direc;                                                                             /*  保存方向值                       */
	while(1)
	{
		direc = GetButton();

		if(!MergeNum(arr,direc))
		{
			continue;
		}

		if(!GetNum(arr))                                                              /*  游戏结束                          */
		{
			return;
		}
		Show(arr);

		if(IsGameover(arr))
		{
			return;
		}
	}
}

int main()
{
	int arr[ROW][COL] = {0};

	Start(arr);
	Run(arr);

	printf("Game over!\n");

	return 0;
}

