/****************************************Copyright (c)****************************************************
**                                                             �غ��.
**                                             email:549761222@qq.com
**                                 
**                     ��Դ���������ַ������ƺ��޸ĵ����뱣��ԭ������Ϣ
**---------------------------File Info--------------------------------------------------------------------
** File name:                    2048.cpp
** Last modified Date:     2014-12-05
** Last Version:                0.0.1
** Descriptions:               ʵ��2048��Ϸ�Ļ�������
**
**--------------------------------------------------------------------------------------------------------
** Created by:                Hehonghong
** Created date:             2014-12-05
** Version:                     0.0.1
** Descriptions:             ʵ��2048��Ϸ�Ļ�������
**
**--------------------------------------------------------------------------------------------------------
** Modified by:              Hehonghong
** Modified date:           2015-03-15
** Version:                      0.0.2
** Descriptions:             1��ĳһ�������ƶ����ݺͺϲ�����ʱ���Ը÷��򰴼����������µ�����
**                                  2���Ż�����Ϸ�������ж�
**
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ROW 4                                                                      /*  ����                                 */
#define COL ROW                                                                  /*  ����                                 */

#define KEY_UP 72                                                                 /*  �����'��'��ɨ������ֵ     */
#define KEY_DOWN 80                                                          /*  �����'��'��ɨ������ֵ     */
#define KEY_LEFT  75                                                             /*  �����'��'��ɨ������ֵ     */
#define KEY_RIGHT 77                                                           /*  �����'��'��ɨ������ֵ     */

#define BLANK  0                                                                  /*  �հ����������                  */

int g_seed = 0;                                                                      /*  �޸����������                  */

/*********************************************************************************************************
** Function name:           Show
** Descriptions:               ��ʾ����
** input parameters:       arr   :�������ݵ�����                          
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
	system("cls");                                                                    /*  ����,dos����                      */
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
** Descriptions:               ����ϲ����ݣ����е����������ƶ���������ͬ�����ֺϲ��ɸ��������
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true:���ֺϲ���λ���ƶ���,false:û�з����ı�
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
	int index1;                                                                         /*  ��һ��ֵ���±�                  */
	int index2;                                                                         /*  �ڶ���ֵ���±�                  */
	int i;
	int j;
	int k;
	bool flg = false;                                                                   /*  ���ֺ�λ���Ƿ��иı�          */

	for(i=0;i<ROW;i++)
	{
		index2 = index1 = -1;
		for(j=0;j<COL;j++)                                                        /*  �ϲ���Ӧ��ֵ,ֵ��λ�ò��� */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  ���ҵ�һ��ֵ                     */
			{
				index1 = j;
				j++;
			}
			if(j<COL && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  ���ҵڶ���ֵ                     */
				index2 = j;
			}
			if(index1!=-1 && index2!=-1)                                   /*  ���ҵ�������ֵͬ��ϲ�     */
			{
				if(arr[i][index1] == arr[i][index2])
				{
					arr[i][index1] *= 2;
					arr[i][index2] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  ����ֵ����ͬ�������˲���  */
				{
					index1 = index2;                                               /* �ڶ���ֵ��Ϊ���˵ĵ�һ��ֵ*/
					index2 = -1;
				}
			}
		}
	
		for(j=0;j<COL-1;j++)                                                     /* ����0���������ƶ�������� */
		{	
			 index1 = -1;                                                             /* ��¼��һ��0���±�              */
			for(k=0;k<COL;k++)
			{
				if(arr[i][k]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[i][k]!=BLANK && index1!=-1)                       /*  ��һ��0���һ����0���±� */
				{
					arr[i][index1] = arr[i][k];                                    /*  ��0ֵ�Ƶ�0ֵ��λ��           */    
					arr[i][k] = 0;                                                      /*  ��0ֵ��λ�ñ��0              */
					flg = true;
					break;                                                               /*  ������һ�˵�0�ͷ�0����    */
				} 
			}
		}
	}

	return flg;
}

/*********************************************************************************************************
** Function name:           MergeUp
** Descriptions:               ���Ϻϲ����ݣ����е����������ƶ���������ͬ�����ֺϲ��ɸ��������
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true:���ֺϲ���λ���ƶ���,false:û�з����ı�
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
	int index1;                                                                         /*  ��һ��ֵ���±�                  */
	int index2;                                                                         /*  �ڶ���ֵ���±�                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(j=0;j<COL;j++)                                                             /*  ���е�˳��������           */
	{                                                                                         /*  j��ʾ��                             */
		index2 = index1 = -1;
		for(i=0;i<ROW;i++)                                                       /*  �ϲ���Ӧ��ֵ,ֵ��λ�ò��� */
		{
			if(arr[i][j]!=BLANK && index1==-1)                           /*  ���ҵ�һ��ֵ                     */
			{
				index1 = i;
				i++;
			}
			if(i<ROW && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  ���ҵڶ���ֵ                     */
				index2 = i;
			}
			if(index1!=-1 && index2!=-1)                                   /*  ���ҵ�������ֵͬ��ϲ�     */
			{
				if(arr[index1][j] == arr[index2][j])
				{
					arr[index1][j] *= 2;
					arr[index2][j] = BLANK;
					index2 = index1 = -1;
					flg = true;
				}
				else                                                                       /*  ����ֵ����ͬ�������˲���  */
				{
					index1 = index2;                                               /* �ڶ���ֵ��Ϊ���˵ĵ�һ��ֵ*/
					index2 = -1;
				}
			}
		}
	
		for(i=0;i<ROW-1;i++)                                                   /* ����0���������ƶ������ϱ� */
		{	
			 index1 = -1;                                                             /* ���ϵ��µ�һ��0���±�       */
			for(k=0;k<ROW;k++)
			{
				if(arr[k][j]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[k][j]!=BLANK && index1!=-1)                       /*  ��һ��0���һ����0���±� */
				{
					arr[index1][j] = arr[k][j];
					arr[k][j] = 0;
					flg = true;
					break;                                                                /*  ������һ�˵�0�ͷ�0����    */
				}
			}
		}
	}

	return flg;
}

/*********************************************************************************************************
** Function name:           MergeRight
** Descriptions:               ���Һϲ����ݣ����е����������ƶ���������ͬ�����ֺϲ��ɸ��������
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true:���ֺϲ���λ���ƶ���,false:û�з����ı�
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
	int index1;                                                                         /*  ��һ��ֵ���±�                  */
	int index2;                                                                         /*  �ڶ���ֵ���±�                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(i=0;i<ROW;i++)   
	{
		index2 = index1 = -1;
		for(j=COL-1;j>=0;j--)                                                    /*  �ϲ���Ӧ��ֵ,ֵ��λ�ò��� */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  ���ҵ�һ��ֵ                     */
			{
				index1 = j;
				j--;
			}
			if(j>=0 && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  ���ҵڶ���ֵ                     */
				index2 = j;
			}
			if(index1!=-1 && index2!=-1)                                   /*  ���ҵ�������ֵͬ��ϲ�     */
			{
				if(arr[i][index1] == arr[i][index2]) 
				{
					arr[i][index1] *= 2;
					arr[i][index2] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  ����ֵ����ͬ�������˲���  */
				{
					index1 = index2;                                               /* �ڶ���ֵ��Ϊ���˵ĵ�һ��ֵ*/
					index2 = -1;
				}
			}
		}
	
		for(j=0;j<COL-1;j++)                                                     /* ����0���������ƶ������ұ� */
		{	                                                                                 /* j��ʾ����                            */
			 index1 = -1;                                                             /* ���ҵ����һ��0���±�        */
			for(k=COL-1;k>=0;k--)                                             /* ���ҵ������                       */
			{
				if(arr[i][k]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[i][k]!=BLANK && index1!=-1)                       /*  ��һ��0���һ����0���±� */
				{
					arr[i][index1] = arr[i][k];
					arr[i][k] = 0;
					flg = true;
					break;                                                                /*  ������һ�˵�0�ͷ�0����    */
				}
			}
		}
	}
	return flg;
}

/*********************************************************************************************************
** Function name:           MergeDown
** Descriptions:               ���ºϲ����ݣ����е����������ƶ���������ͬ�����ֺϲ��ɸ��������
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true:���ֺϲ���λ���ƶ���,false:û�з����ı�
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
	int index1;                                                                         /*  ��һ��ֵ���±�                  */
	int index2;                                                                         /*  �ڶ���ֵ���±�                  */
	int i;
	int j;
	int k;
	bool flg = false;

	for(j=0;j<COL;j++)                                                             /*  ���е�˳��������           */
	{                                                                                        /*  j��ʾ��                              */
		index2 = index1 = -1;
		for(i=ROW-1;i>=0;i--)                                                  /*  �ϲ���Ӧ��ֵ,ֵ��λ�ò��� */
		{
			if(arr[i][j]!=BLANK && index1==-1)                          /*  ���ҵ�һ��ֵ                     */
			{
				index1 = i;
				i--;
			}
			if(i>=0 && arr[i][j]!=BLANK && index1!=-1 && index2==-1)
			{                                                                                /*  ���ҵڶ���ֵ                     */
				index2 = i;
			}
			if(index1!=-1 && index2!=-1)                                   /*  ���ҵ�������ֵͬ��ϲ�     */
			{
				if(arr[index1][j] == arr[index2][j])
				{
					arr[index1][j] *= 2;
					arr[index2][j] = BLANK;
					flg = true;
					index2 = index1 = -1;
				}
				else                                                                       /*  ����ֵ����ͬ�������˲���  */
				{
					index1 = index2;                                               /* �ڶ���ֵ��Ϊ���˵ĵ�һ��ֵ*/
					index2 = -1;
				}
			}
		}
	
		for(i=0;i<ROW-1;i++)                                                   /* ����0���������ƶ������±� */
		{	                                                                                 /* i��ʾ����                            */
			 index1 = -1;                                                             /* ���µ��ϵ�һ��0���±�        */
			for(k=ROW-1;k>=0;k--)                                            /* ���µ��ϱ���                      */ 
			{
				if(arr[k][j]==BLANK && index1==-1)
				{
					index1 = k;
				}
				if(arr[k][j]!=BLANK && index1!=-1)                       /*  ��һ��0���һ����0���±� */
				{
					arr[index1][j] = arr[k][j];
					arr[k][j] = 0;
					flg = true;
					break;                                                                /*  ������һ�˵�0�ͷ�0����    */
				}
			}
		}
	}
	return flg;
}

/*********************************************************************************************************
** Function name:           IsGameover
** Descriptions:               ��Ϸ�Ƿ�����жϺ���,Ŀǰֻ�Ǽ��жϿ��и��ӵ�����
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true :��Ϸ����,false :��Ϸδ����
**
** Created by:                 hehonghong
** Created Date:             2014-12-05
**-------------------------------------------------------------------------------------------------------
** Modified by:              hehonghong
** Modified date:           2015-03-15
** Descriptions:              ��Ӷ����������Ƿ���ȵ��ж�
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if 0
bool IsGameover(int (*arr)[COL])
{
	int activeCell = 0;                                                               /*ͳ�ƻ�û��������ݵĸ�����*/
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
	return activeCell == 0;                                                       /*  û�п��и�����Ϸ����        */
}
#endif
bool IsGameover(int (*arr)[COL])
{
	int activeCell = 0;                                                               /*ͳ�ƻ�û��������ݵĸ�����*/
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
	if(activeCell != 0)                                                               /*  �п��и�����Ϸ������         */
	{
		return false;
	}
	
	for(i=0;i<ROW-1;i++)                                                        /*  �ж����ڵ������Ƿ���ͬ      */
	{
		for(j=0;j<COL-1;j++)
		{
			if(arr[i][j]==arr[i][j+1] || arr[i][j]==arr[i+1][j])
			{
				return false;
			}
		}
	}

	for(i=0;i<ROW-1;i++)                                                         /*  �ж����һ�����µ������Ƿ���ͬ */               
	{
		if(arr[i][COL-1] == arr[i+1][COL-1])
		{
			return false;
		}
	}

	for(i=0;i<COL-1;i++)                                                          /*  �ж����һ�����ҵ������Ƿ���ͬ */
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
** Descriptions:               �����µ�����
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          true :�ɹ�,false :ʧ��
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
	srand((unsigned int)time(NULL)+ g_seed++);                   /*  �����������                     */
	                                                                                         /*  g_seed��ֹһ���ڲ�����    */
	                                                                                         /*  ������ͬ                            */
	int row = rand()%ROW;                                                     /*  �е��±�                           */   
	int col = rand()%COL;                                                        /*  �е��±�                           */
	int num = 2;                                                                      /*  ����Ĭ��Ϊ2                      */
	if(rand()%5 == 0)                                                               /*  ż����������4                  */
	{
		num = 4;
	}
	while(arr[row][col] != 0)                                                     /*  �ҵ�û�����ݵĸ����±�    */
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
** Descriptions:               ��ȡ���������ֵ
** input parameters:       arr   :�������ݵ�����                          
** Returned value:          �����ֵ��1��,2��,3��,4��
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
		Sleep(100);                                                                /*����ϵͳæ�ȴ�,����CPUʹ����*/
	}
	return 0;
}

/*********************************************************************************************************
** Function name:           MergeNum
** Descriptions:               ���ݷ�����ϲ���Ӧ������
** input parameters:       arr     :�������ݵ�����  
**                                    dirce :����ֵ                      
** Returned value:          true:���ֺϲ���λ���ƶ���,false:û�з����ı�
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
** Descriptions:               ��ʼ��Ϸ
** input parameters:       arr     :�������ݵ�����                      
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
	for(int i=0;i<2;i++)                                                             /*  ��ʼ�����������������    */
	{
		GetNum(arr);
	}

	Show(arr);
}
/*********************************************************************************************************
** Function name:           Run
** Descriptions:               ������Ϸ
** input parameters:       arr     :�������ݵ�����                      
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
	int direc;                                                                             /*  ���淽��ֵ                       */
	while(1)
	{
		direc = GetButton();

		if(!MergeNum(arr,direc))
		{
			continue;
		}

		if(!GetNum(arr))                                                              /*  ��Ϸ����                          */
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

