#pragma once
#include <cstdio>
#include <iostream>					
#include <fstream>						
#include <vector>							//	container Vector
#include <utility>							//	container Pair
#include <thread>
#include <chrono>
#include <algorithm>
#include <Windows.h>
#include <random>
//////////////////////////////////
#define BoardWidth	19
#define BoardHeight 19

#define Black		'B'
#define White		'W'
#define Blank		0
#define STAR		100						//	�鵹 �˸�
#define HEART		101						//	�浹 �˸�
//////////////////////////////////
//	<< Rules >>
//	Odd Turn	-> Black
//	Even Turn	-> White
//////////////////////////////////
typedef enum {
	d_Hori,
	d_Vert,
	d_LBRT,
	d_LTRB,
	a_Hori,
	a_Vert,
	a_LBRT,
	a_LTRB
}AI_WAY;

typedef struct _RockData {
	char style{ Blank };
	int max{ 0 };
}RockData;								//	�� ���κ� ���ӵ� ������ �����ϱ� ���� �ڷ���

typedef struct _Rock {
	int w{ 0 };
	int b{ 0 };
	bool blank{ false };
}RockCount;								//	���ӵ� ���� ���� �ڷ���

typedef struct _BoardManager {
	char** arrayData{ NULL };			//	���� ������
	RockData* cntHori_Data{ NULL };		//	���� ���Ӱ���
	RockData* cntVert_Data{ NULL };		//	������ ���Ӱ���
	RockData* cntLBRT_Data{ NULL };		//	'��'���� �缱�� ���Ӱ���
	RockData* cntLTRB_Data{ NULL };		//	'��'���� �缱�� ���Ӱ���
	int turnb = 1;						//	��
	int turnw = 1;
}BoardManager;

void Count(BoardManager* bm, const std::vector<std::pair<int, int>>& v);
void ClearRockCount(RockCount& rc);
void ClearInputBuffer(void);
template <class Iter>
void CountHori(BoardManager * bm, Iter p);
template <class Iter>
void CountVert(BoardManager * bm, Iter p);
template <class Iter>
void CountLTRB(BoardManager * bm, Iter p);
template <class Iter>
void CountLBRT(BoardManager * bm, Iter p);
void Allocate(BoardManager* bm);
void InsertCoord_AI_W(BoardManager * bm, std::vector<std::pair<int, int>>& v, int* x, int* y);
void InsertCoord_AI_B(BoardManager * bm, std::vector<std::pair<int, int>>& v, int* x, int* y);
void Initiate(BoardManager* bm, std::vector<std::pair<int, int>>& v);
void Allocate(BoardManager* bm)		//	Dynamic Allocation for save & count data of Omok
{
	//	two-dimensional Dynamic Allocation

	//	DataArray
	bm->arrayData = (char**)malloc(sizeof(char*)*BoardHeight);
	for (int i = 0; i < BoardHeight; ++i) {
		bm->arrayData[i] = (char*)malloc(sizeof(char)*BoardWidth);
	}

	//	CountData - Diagonal LTRB
	bm->cntLTRB_Data = (RockData*)malloc(sizeof(RockData)*(BoardHeight + BoardWidth - 1));

	//	CountData - Diagonal LBRT
	bm->cntLBRT_Data = (RockData*)malloc(sizeof(RockData)*(BoardHeight + BoardWidth - 1));

	//	CountData - Horizontal
	bm->cntHori_Data = (RockData*)malloc(sizeof(RockData)*BoardHeight);

	//	CountData - Vertical
	bm->cntVert_Data = (RockData*)malloc(sizeof(RockData)*BoardHeight);

}
void Initiate(BoardManager* bm, std::vector<std::pair<int, int>>& v)											//	�ʱ�ȭ
{
	/* ���� �Լ�. �迭������ ������ �ʱ�ȸ��Ų��. �� ������ �Ҵ���� �����Ѵ�. */
	Allocate(bm);

	//	make board empty
	for (int i = 0; i < BoardHeight; ++i) {
		for (int j = 0; j < BoardWidth; ++j) {
			bm->arrayData[i][j] = Blank;
		}
	}
	//	clear countdata - Diagonal LBRT
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		bm->cntLBRT_Data[i].max = 0;
		bm->cntLBRT_Data[i].style = Blank;
	}
	//	clear countdata - Diagonal LTRB 
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		bm->cntLTRB_Data[i].max = 0;
		bm->cntLTRB_Data[i].style = Blank;
	}
	//	clear countdata - Horizontal
	for (int i = 0; i < BoardHeight; ++i) {
		bm->cntHori_Data[i].max = 0;
		bm->cntHori_Data[i].style = Blank;
	}
	//	clear countdata - Vertical
	for (int i = 0; i < BoardWidth; ++i) {
		bm->cntVert_Data[i].max = 0;
		bm->cntVert_Data[i].style = Blank;
	}
}
void Count(BoardManager* bm, const std::vector<std::pair<int, int>>& v)		//	������
{
	/*
	���ÿ� ���� ���� ������ ������� ���� ���� ���ٺ��ϱ� �߻��ϴ� �����ִ� ������ ���߿� ���� �δ� ��������
	�ǵ�ġ �ʰ� �� ������ '��������'���� �������� ������ �߻��ؼ� ù ��° �õ��� ���� ���� �����͸� �Լ� ȣ�� ���� ��� ���׸�
	�ʱ�ȭ ���ַ��� �ߴ�. (������ ���� �ٽ� ���ϱ�)
	������ �ǵ��Ѵ�� �ذ���� �ʾҰ�, ���� ������ �����ϵ�, ����� ������⿡ �ӽ� ���尪�� �ּ� �� ���尪�� �� �� ū ���� �־�°� ���?
	*/
	//	clear countdata - Diagonal LBRT
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		bm->cntLBRT_Data[i].max = 0;
		bm->cntLBRT_Data[i].style = Blank;
	}
	//	clear countdata - Diagonal LTRB 
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		bm->cntLTRB_Data[i].max = 0;
		bm->cntLTRB_Data[i].style = Blank;
	}
	//	clear countdata - Horizontal
	for (int i = 0; i < BoardHeight; ++i) {
		bm->cntHori_Data[i].max = 0;
		bm->cntHori_Data[i].style = Blank;
	}
	//	clear countdata - Vertical
	for (int i = 0; i < BoardWidth; ++i) {
		bm->cntVert_Data[i].max = 0;
		bm->cntVert_Data[i].style = Blank;
	}
	for (auto p = v.begin(); p != v.end(); ++p) { // ���� ������ ��� ���� ���ؼ� �ľ��Ѵ�. �� ���⾿.
		CountHori(bm, p);
		CountVert(bm, p);
		CountLTRB(bm, p);
		CountLBRT(bm, p);
		//	�˻� ��
	}
}
void ClearInputBuffer(void)			//	���������
{
	/* scanf�� ���๮���� ���ۿ��� fflush �������� �ʱ� ������ ���Ƿ� ���� �Լ��̴�. */
	while (getchar() != '\n');
}

void ClearRockCount(RockCount& rc)
{
	/* ���Ӽ� �������� �ʱ�ȭ���ش�.*/
	rc.w = 0;
	rc.b = 0;
	rc.blank = false;
}

template <class Iter>
void CountHori(BoardManager * bm, Iter p)
{
	//	�ݺ��� p�� �Ѿ�� ���� ����ǥ���̱� ������, �ε����� ġȯ��Ű���� -1�� ���ش�.
	RockCount rc;
	// ����� ���� ���� �� ����
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	�鵹�� ��
		//	�������
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i - j] == Black) {
						rc.w = 0;
						goto stop;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == HEART
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == STAR) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1][(*p).second - 1 + i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i - j] == Black || (*p).second - 1 + i - j == 0) {
							rc.w = 0;
							goto stop;
						}
					}
				}
				break;
			}
		}
	stop:
		if ((*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.b) {
			bm->cntHori_Data[(*p).first - 1].max = rc.b;
			bm->cntHori_Data[(*p).first - 1].style = Black;
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.w) {
			bm->cntHori_Data[(*p).first - 1].max = rc.w;
			bm->cntHori_Data[(*p).first - 1].style = White;
		}
		ClearRockCount(rc);
		++rc.w;
		//	�������
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i + j] == Black) {
						rc.w = 0;
						goto stop2;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == HEART
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == STAR) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1][(*p).second - 1 - i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i + j] == Black || (*p).second - 1 - i + j == BoardWidth - 1) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
				break;
			}
		}
	stop2:
		if ((*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.b) {
			bm->cntHori_Data[(*p).first - 1].max = rc.b;
			bm->cntHori_Data[(*p).first - 1].style = Black;
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.w) {
			bm->cntHori_Data[(*p).first - 1].max = rc.w;
			bm->cntHori_Data[(*p).first - 1].style = White;
		}
	}
	else {
		//	�浹�� ��
		//	�������
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i - j] == White) {
						rc.b = 0;
						goto stop3;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == HEART
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == STAR) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1][(*p).second - 1 + i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i - j] == White || (*p).second - 1 + i - j == 0) {
							rc.b = 0;
							goto stop3;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 + i] == Black) {
				++rc.b;
			}
		}
	stop3:
		if ((*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 + j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 - j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.b) {
			bm->cntHori_Data[(*p).first - 1].max = rc.b;
			bm->cntHori_Data[(*p).first - 1].style = Black;
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.w) {
			bm->cntHori_Data[(*p).first - 1].max = rc.w;
			bm->cntHori_Data[(*p).first - 1].style = White;
		}
		//	�������
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i + j] == White) {
						rc.b = 0;
						goto stop4;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == HEART
				|| bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == STAR) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1][(*p).second - 1 - i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i + j] == White || (*p).second - 1 - i + j == BoardWidth - 1) {
							rc.b = 0;
							goto stop4;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1][(*p).second - 1 - i] == Black) {
				++rc.b;
			}
		}
	stop4:
		if ((*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 + j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1][(*p).second - 1 - j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.b) {
			bm->cntHori_Data[(*p).first - 1].max = rc.b;
			bm->cntHori_Data[(*p).first - 1].style = Black;
		}
		if (bm->cntHori_Data[(*p).first - 1].max <= rc.w) {
			bm->cntHori_Data[(*p).first - 1].max = rc.w;
			bm->cntHori_Data[(*p).first - 1].style = White;
		}
	}
}

template<class Iter>
void CountVert(BoardManager * bm, Iter p)
{
	//	�ݺ��� p�� �Ѿ�� ���� ����ǥ���̱� ������, �ε����� ġȯ��Ű���� -1�� ���ش�.
	RockCount rc;
	// ����� ���� ���� �� ����
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	�鵹�� ��
		//	�������
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1] == Black) {
						rc.w = 0;
						goto stop;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1] == Black || (*p).first - 1 + i - j == 0) {
							rc.w = 0;
							goto stop;
						}
					}
				}
				break;
			}
		}
	stop:
		if ((*p).first - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.b) {
			bm->cntVert_Data[(*p).second - 1].max = rc.b;
			bm->cntVert_Data[(*p).second - 1].style = Black;
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.w) {
			bm->cntVert_Data[(*p).second - 1].max = rc.w;
			bm->cntVert_Data[(*p).second - 1].style = White;
		}
		//	�������
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1] == Black) {
						rc.w = 0;
						goto stop2;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1] == Black || (*p).first - 1 - i + j == BoardHeight - 1) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
				break;
			}
		}
	stop2:
		if ((*p).first - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.b) {
			bm->cntVert_Data[(*p).second - 1].max = rc.b;
			bm->cntVert_Data[(*p).second - 1].style = Black;
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.w) {
			bm->cntVert_Data[(*p).second - 1].max = rc.w;
			bm->cntVert_Data[(*p).second - 1].style = White;
		}
	}
	else {
		//	�浹�� ��
		//	�������
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1] == White) {
						rc.b = 0;
						goto stop3;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1] == White || (*p).first - 1 + i - j == 0) {
							rc.b = 0;
							goto stop3;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1] == Black) {
				++rc.b;
			}
		}
	stop3:
		if ((*p).first - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.b) {
			bm->cntVert_Data[(*p).second - 1].max = rc.b;
			bm->cntVert_Data[(*p).second - 1].style = Black;
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.w) {
			bm->cntVert_Data[(*p).second - 1].max = rc.w;
			bm->cntVert_Data[(*p).second - 1].style = White;
		}
		//	�������
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1] == White) {
						rc.b = 0;
						goto stop4;
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1] == White || (*p).first - 1 - i + j == BoardHeight - 1) {
							rc.b = 0;
							goto stop4;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1] == Black) {
				++rc.b;
			}
		}
	stop4:
		if ((*p).first - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.b) {
			bm->cntVert_Data[(*p).second - 1].max = rc.b;
			bm->cntVert_Data[(*p).second - 1].style = Black;
		}
		if (bm->cntVert_Data[(*p).second - 1].max <= rc.w) {
			bm->cntVert_Data[(*p).second - 1].max = rc.w;
			bm->cntVert_Data[(*p).second - 1].style = White;
		}
	}
}

template<class Iter>
void CountLTRB(BoardManager * bm, Iter p)
{
	//	�ݺ��� p�� �Ѿ�� ���� ����ǥ���̱� ������, �ε����� ġȯ��Ű���� -1�� ���ش�.
	RockCount rc;
	// �ٹ��� ���� ���� �� ����
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	�鵹�� ��
		//	�������
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardHeight - 1 || (*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 + i - j] == Black || ((*p).first - 1 + i - j == -1 || (*p).second - 1 + i - j == -1)) {
							rc.w = 0;
							goto stop;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 + i - j] == Black || ((*p).first - 1 + i - j == 0 || (*p).second - 1 + i - j == 0)) {
							rc.w = 0;
							goto stop;
						}
					}
				}
				break;
			}
		}
	stop:
		if ((*p).first - 1 == 0 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.b) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.b;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = Black;
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.w) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.w;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = White;
		}
		//	�������
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0 || (*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 - i + j] == Black || ((*p).first - 1 - i + j == BoardHeight || (*p).second - 1 - i + j == BoardWidth)) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 - i + j] == Black || ((*p).first - 1 - i + j == BoardHeight - 1 || (*p).second - 1 - i + j == BoardWidth - 1)) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
				break;
			}
		}
	stop2:
		if ((*p).first - 1 == 0 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.b) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.b;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = Black;
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.w) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.w;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = White;
		}
	}
	else {
		//	�浹�� ��
		//	�������
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardHeight - 1 || (*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 + i - j] == White || ((*p).first - 1 + i - j == -1 || (*p).second - 1 + i - j == -1)) {
							rc.b = 0;
							goto stop3;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 + i - j] == White || ((*p).first - 1 + i - j == 0 || (*p).second - 1 + i - j == 0)) {
							rc.b = 0;
							goto stop3;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 + i] == Black) {
				++rc.b;
			}
		}
	stop3:
		if ((*p).first - 1 == 0 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 + j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 - j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.b) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.b;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = Black;
		}
		if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.w) {
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.w;
			bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = White;
		}
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0 || (*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 - i + j] == White || ((*p).first - 1 - i + j == BoardHeight || (*p).second - 1 - i + j == BoardWidth)) {
							rc.b = 0;
							goto stop4;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 - i + j] == White || ((*p).first - 1 - i + j == BoardHeight - 1 || (*p).second - 1 - i + j == BoardWidth - 1)) {
							rc.b = 0;
							goto stop4;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 - i] == Black) {
				++rc.b;
			}
		}
	}
stop4:
	if ((*p).first - 1 == 0 || (*p).second - 1 == 0) {
		for (int j = 1; j < 6; ++j) {
			if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 + j == BoardWidth) {
				break;
			}
			if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 + j] == White) {
				rc.b = 0;
				break;
			}
		}
	}
	else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == BoardWidth - 1) {
		for (int j = 1; j < 6; ++j) {
			if ((*p).first - 1 - j == -1 || (*p).second - 1 - j == -1) {
				break;
			}
			if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 - j] == White) {
				rc.b = 0;
				break;
			}
		}
	}
	if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.b) {
		bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.b;
		bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = Black;
	}
	if (bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max <= rc.w) {
		bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].max = rc.w;
		bm->cntLTRB_Data[-((*p).first - 1) + 18 + (*p).second - 1].style = White;
	}
}

template<class Iter>
void CountLBRT(BoardManager * bm, Iter p)
{
	//	�ݺ��� p�� �Ѿ�� ���� ����ǥ���̱� ������, �ε����� ġȯ��Ű���� -1�� ���ش�.
	RockCount rc;
	// �׹��� ���� ���� �� ����
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	�鵹�� ��
		//	����
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardHeight - 1 || (*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 - i + j] == Black || ((*p).first - 1 + i - j == -1 || (*p).second - 1 - i + j == BoardWidth)) {
							rc.w = 0;
							goto stop;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 - i + j] == Black || ((*p).first - 1 + i - j == 0 || (*p).second - 1 - i + j == BoardWidth - 1)) {
							rc.w = 0;
							goto stop;
						}
					}
				}
				break;
			}
		}
	stop:
		if ((*p).first - 1 == 0 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.b) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.b;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = Black;
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.w) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.w;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = White;
		}
		//	����
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0 || (*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 + i - j] == Black || ((*p).first - 1 - i + j == BoardHeight || (*p).second - 1 + i - j == -1)) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] = STAR;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == White) {
				++rc.w;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == Black) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 + i - j] == Black || ((*p).first - 1 - i + j == BoardHeight - 1 || (*p).second - 1 + i - j == 0)) {
							rc.w = 0;
							goto stop2;
						}
					}
				}
				break;
			}
		}
	stop2:
		if ((*p).first - 1 == 0 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 - j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 + j] == Black) {
					rc.w = 0;
					break;
				}
			}
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.b) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.b;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = Black;
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.w) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.w;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = White;
		}
	}
	else {
		//	�浹�� ��
		//	����
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 - i == -1) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 + i == BoardHeight - 1 || (*p).second - 1 - i == 0) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 - i + j] == White || ((*p).first - 1 + i - j == -1 || (*p).second - 1 - i + j == BoardWidth)) {
							rc.b = 0;
							goto stop3;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == Blank
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == STAR
				|| bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;;
				}
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 + i - j > -1 && (*p).second - 1 - i + j < BoardWidth) {
						if (bm->arrayData[(*p).first - 1 + i - j][(*p).second - 1 - i + j] == White || ((*p).first - 1 + i - j == 0 || (*p).second - 1 - i + j == BoardWidth - 1)) {
							rc.b = 0;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 + i][(*p).second - 1 - i] == Black) {
				++rc.b;
			}
		}
	stop3:
		if ((*p).first - 1 == 0 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 - j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 + j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.b) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.b;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = Black;
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.w) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.w;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = White;
		}
		//	����
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 + i == BoardWidth) {	//	����ε������ ���� �ʴ´�.
				break;
			}
			else if ((*p).first - 1 - i == 0 || (*p).second - 1 + i == BoardWidth - 1) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 + i - j] == White || ((*p).first - 1 - i + j == BoardHeight || (*p).second - 1 + i - j == -1)) {
							rc.b = 0;
							goto stop4;
						}
					}
				}
			}
			if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == Blank
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == STAR
				|| bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == HEART) {
				if (!rc.blank) {
					bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] = HEART;
					rc.blank = true;
				}
				else {
					rc.blank = false;
					break;;
				}
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == White) {
				for (int j = 1; j < 6; ++j) {
					if ((*p).first - 1 - i + j < BoardHeight && (*p).second - 1 + i - j > -1) {
						if (bm->arrayData[(*p).first - 1 - i + j][(*p).second - 1 + i - j] == White || ((*p).first - 1 - i + j == BoardHeight - 1 || (*p).second - 1 + i - j == 0)) {
							rc.b = 0;
						}
					}
				}
				break;
			}
			else if (bm->arrayData[(*p).first - 1 - i][(*p).second - 1 + i] == Black) {
				++rc.b;
			}
		}
	stop4:
		if ((*p).first - 1 == 0 || (*p).second - 1 == BoardWidth - 1) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 + j == BoardHeight || (*p).second - 1 - j == -1) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 + j][(*p).second - 1 - j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		else if ((*p).first - 1 == BoardHeight - 1 || (*p).second - 1 == 0) {
			for (int j = 1; j < 6; ++j) {
				if ((*p).first - 1 - j == -1 || (*p).second - 1 + j == BoardWidth) {
					break;
				}
				if (bm->arrayData[(*p).first - 1 - j][(*p).second - 1 + j] == White) {
					rc.b = 0;
					break;
				}
			}
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.b) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.b;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = Black;
		}
		if (bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max <= rc.w) {
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].max = rc.w;
			bm->cntLBRT_Data[-((*p).first - 1) + 36 + -((*p).second - 1)].style = White;
		}
	}
}

void InsertCoord_AI_W(BoardManager * bm, std::vector<std::pair<int, int>>& v, int* x, int* y)
{
	/* �� �κп��� AI ����� �����Ѵ�. ������ �鵹 (�İ�, ���켱����, ���� ���ݼ� �������� ������ ¥���� �Ѵ�.
	*/
	//	<����> : ����ڰ� �浹, AI(?)�� �鵹
	//	�ʿ� �ൿ ::	���Ϳ� emplace_back ��ǥ �о�ֱ�
	//					�� ������Ű��
	//					�� �ڵ����� ����

	int maxblackrock{ 0 };
	int wayselection{ 0 };
	int saveIndex{ 0 };

	//	�鵹�϶�, �浹�� �����Ѵ�.
	for (int i = 0; i < BoardWidth + BoardHeight - 1; ++i) {
		if (bm->cntLTRB_Data[i].style == Black) {
			if (maxblackrock <= bm->cntLTRB_Data[i].max) {
				maxblackrock = bm->cntLTRB_Data[i].max;
				wayselection = d_LTRB;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		if (bm->cntLBRT_Data[i].style == Black) {
			if (maxblackrock <= bm->cntLBRT_Data[i].max) {
				maxblackrock = bm->cntLBRT_Data[i].max;
				wayselection = d_LBRT;
				saveIndex = i;
			}

		}
	}
	for (int i = 0; i < BoardHeight; ++i) {
		if (bm->cntVert_Data[i].style == Black) {
			if (maxblackrock <= bm->cntVert_Data[i].max) {
				maxblackrock = bm->cntVert_Data[i].max;
				wayselection = d_Vert;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardWidth; ++i) {
		if (bm->cntHori_Data[i].style == Black) {
			if (maxblackrock <= bm->cntHori_Data[i].max) {
				maxblackrock = bm->cntHori_Data[i].max;
				wayselection = d_Hori;
				saveIndex = i;
			}
		}
	}
	////////////////////////////////////////////////////////////
	for (int i = 0; i < BoardWidth + BoardHeight - 1; ++i) {
		if (bm->cntLTRB_Data[i].style == White) {
			if (maxblackrock <= bm->cntLTRB_Data[i].max) {
				maxblackrock = bm->cntLTRB_Data[i].max;
				wayselection = a_LTRB;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		if (bm->cntLBRT_Data[i].style == White) {
			if (maxblackrock <= bm->cntLBRT_Data[i].max) {
				maxblackrock = bm->cntLBRT_Data[i].max;
				wayselection = a_LBRT;
				saveIndex = i;
			}

		}
	}
	for (int i = 0; i < BoardHeight; ++i) {
		if (bm->cntVert_Data[i].style == White) {
			if (maxblackrock <= bm->cntVert_Data[i].max) {
				maxblackrock = bm->cntVert_Data[i].max;
				wayselection = a_Vert;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardWidth; ++i) {
		if (bm->cntHori_Data[i].style == White) {
			if (maxblackrock <= bm->cntHori_Data[i].max) {
				maxblackrock = bm->cntHori_Data[i].max;
				wayselection = a_Hori;
				saveIndex = i;
			}
		}
	}
	///////////////////////////////////////////////////////////


	if (wayselection == d_Vert) {
		for (int i = 0; i < BoardHeight; ++i) {
			if (bm->arrayData[i][saveIndex] == HEART) {
				v.emplace_back(i + 1, saveIndex + 1);
				bm->arrayData[i][saveIndex] = White;
				bm->turnw += 1;
				*x = i, *y = saveIndex;
				return;
			}
		}
	}
	else if (wayselection == d_Hori) {
		for (int i = 0; i < BoardWidth; ++i) {
			if (bm->arrayData[saveIndex][i] == HEART) {
				bm->arrayData[saveIndex][i] = White;
				v.emplace_back(saveIndex + 1, i + 1);
				bm->turnw += 1;
				*x = saveIndex, *y = i;
				return;
			}
		}
	}
	else if (wayselection == d_LTRB) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][saveIndex - 18 + i] == HEART) {
					bm->arrayData[0 + i][saveIndex - 18 + i] = White;
					v.emplace_back(i + 1, saveIndex - 18 + i + 1);
					bm->turnw += 1;
					*x = 0 + i, *y = saveIndex - 18 + i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][0 + i] == HEART) {
					bm->arrayData[0 + i][0 + i] = White;
					v.emplace_back(i + 1, i + 1);
					bm->turnw += 1;
					*x = i, *y = i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][0 + i] == HEART) {
					bm->arrayData[18 - saveIndex + i][0 + i] = White;
					v.emplace_back(18 - saveIndex + i + 1, i + 1);
					bm->turnw += 1;
					*x = 18 - saveIndex + i, *y = i;
					return;
				}
			}
		}
	}
	else if (wayselection == d_LBRT) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][36 - saveIndex - i] == HEART) {
					bm->arrayData[0 + i][36 - saveIndex - i] = White;
					v.emplace_back(i + 1, 36 - saveIndex - i + 1);
					bm->turnw += 1;
					*x = i, *y = 36 - saveIndex - i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][saveIndex - i] == HEART) {
					bm->arrayData[0 + i][saveIndex - i] = White;
					v.emplace_back(i + 1, saveIndex - i + 1);
					bm->turnw += 1;
					*x = i, *y = saveIndex - i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][18 - i] == HEART) {
					bm->arrayData[18 - saveIndex + i][18 - i] = White;
					v.emplace_back(18 - saveIndex + i + 1, 18 - i + 1);
					bm->turnw += 1;
					*x = 18 - saveIndex + i, *y = 18 - i;
					return;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	if (wayselection == a_Vert) {
		for (int i = 0; i < BoardHeight; ++i) {
			if (bm->arrayData[i][saveIndex] == STAR) {
				bm->arrayData[i][saveIndex] = White;
				v.emplace_back(i + 1, saveIndex + 1);
				bm->turnw += 1;
				*x = i, *y = saveIndex;
				return;
			}
		}
	}
	else if (wayselection == a_Hori) {
		for (int i = 0; i < BoardWidth; ++i) {
			if (bm->arrayData[saveIndex][i] == STAR) {
				bm->arrayData[saveIndex][i] = White;
				v.emplace_back(saveIndex + 1, i + 1);
				bm->turnw += 1;
				*x = saveIndex, *y = i;
				return;
			}
		}
	}
	else if (wayselection == a_LTRB) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][saveIndex - 18 + i] == STAR) {
					bm->arrayData[0 + i][saveIndex - 18 + i] = White;
					v.emplace_back(i + 1, saveIndex - 18 + i + 1);
					bm->turnw += 1;
					*x = 0 + i, *y = saveIndex - 18 + i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][0 + i] == STAR) {
					bm->arrayData[0 + i][0 + i] = White;
					v.emplace_back(i + 1, i + 1);
					bm->turnw += 1;
					*x = 0 + i, *y = 0 + i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][0 + i] == STAR) {
					bm->arrayData[18 - saveIndex + i][0 + i] = White;
					v.emplace_back(18 - saveIndex + i + 1, i + 1);
					bm->turnw += 1;
					*x = 18 - saveIndex + i, *y = i;
					return;
				}
			}
		}
	}
	else if (wayselection == a_LBRT) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][36 - saveIndex - i] == STAR) {
					bm->arrayData[0 + i][36 - saveIndex - i] = White;
					v.emplace_back(i + 1, 36 - saveIndex - i + 1);
					bm->turnw += 1;
					*x = i, *y = 36 - saveIndex - i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][saveIndex - i] == STAR) {
					bm->arrayData[0 + i][saveIndex - i] = White;
					v.emplace_back(i + 1, saveIndex - i + 1);
					bm->turnw += 1;
					*x = i, *y = saveIndex - i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][18 - i] == STAR) {
					bm->arrayData[18 - saveIndex + i][18 - i] = White;
					v.emplace_back(18 - saveIndex + i + 1, 18 - i + 1);
					bm->turnw += 1;
					*x = 18 - saveIndex + i, *y = 18 - i;
					return;
				}
			}
		}
	}
	//else {
	//	std::random_device rd;
	//	std::default_random_engine dre(rd());
	//	std::uniform_int_distribution<int> uid(0, 18);
	//	int tr = uid(dre);
	//	int tc = uid(dre);
	//	if (bm->arrayData[tr][tc] == Blank || bm->arrayData[tr][tc] == STAR || bm->arrayData[tr][tc] == HEART) {
	//		v.emplace_back(tr, tc);
	//		bm->turn += 1;
	//		return;
	//	}
	//}
}

void InsertCoord_AI_B(BoardManager * bm, std::vector<std::pair<int, int>>& v, int* x, int* y)
{
	/* �� �κп��� AI ����� �����Ѵ�. ������ �鵹 (�İ�, ���켱����, ���� ���ݼ� �������� ������ ¥���� �Ѵ�.
	*/
	//	�ʿ� �ൿ ::	���Ϳ� emplace_back ��ǥ �о�ֱ�
	//					�� ������Ű��
	//					�� �ڵ����� ����

	int maxblackrock{ 0 };
	int wayselection{ 0 };
	int saveIndex{ 0 };


	//	�鵹�϶�, �浹�� �����Ѵ�.
	for (int i = 0; i < BoardWidth + BoardHeight - 1; ++i) {
		if (bm->cntLTRB_Data[i].style == White) {
			if (maxblackrock <= bm->cntLTRB_Data[i].max) {
				maxblackrock = bm->cntLTRB_Data[i].max;
				wayselection = d_LTRB;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		if (bm->cntLBRT_Data[i].style == White) {
			if (maxblackrock <= bm->cntLBRT_Data[i].max) {
				maxblackrock = bm->cntLBRT_Data[i].max;
				wayselection = d_LBRT;
				saveIndex = i;
			}

		}
	}
	for (int i = 0; i < BoardHeight; ++i) {
		if (bm->cntVert_Data[i].style == White) {
			if (maxblackrock <= bm->cntVert_Data[i].max) {
				maxblackrock = bm->cntVert_Data[i].max;
				wayselection = d_Vert;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardWidth; ++i) {
		if (bm->cntHori_Data[i].style == White) {
			if (maxblackrock <= bm->cntHori_Data[i].max) {
				maxblackrock = bm->cntHori_Data[i].max;
				wayselection = d_Hori;
				saveIndex = i;
			}
		}
	}
	////////////////////////////////////////////////////////////
	for (int i = 0; i < BoardWidth + BoardHeight - 1; ++i) {
		if (bm->cntLTRB_Data[i].style == Black) {
			if (maxblackrock <= bm->cntLTRB_Data[i].max) {
				maxblackrock = bm->cntLTRB_Data[i].max;
				wayselection = a_LTRB;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardHeight + BoardWidth - 1; ++i) {
		if (bm->cntLBRT_Data[i].style == Black) {
			if (maxblackrock <= bm->cntLBRT_Data[i].max) {
				maxblackrock = bm->cntLBRT_Data[i].max;
				wayselection = a_LBRT;
				saveIndex = i;
			}

		}
	}
	for (int i = 0; i < BoardHeight; ++i) {
		if (bm->cntVert_Data[i].style == Black) {
			if (maxblackrock <= bm->cntVert_Data[i].max) {
				maxblackrock = bm->cntVert_Data[i].max;
				wayselection = a_Vert;
				saveIndex = i;
			}
		}
	}
	for (int i = 0; i < BoardWidth; ++i) {
		if (bm->cntHori_Data[i].style == Black) {
			if (maxblackrock <= bm->cntHori_Data[i].max) {
				maxblackrock = bm->cntHori_Data[i].max;
				wayselection = a_Hori;
				saveIndex = i;
			}
		}
	}
	///////////////////////////////////////////////////////////


	if (wayselection == d_Vert) {
		for (int i = 0; i < BoardHeight; ++i) {
			if (bm->arrayData[i][saveIndex] == STAR) {
				v.emplace_back(i + 1, saveIndex + 1);
				bm->arrayData[i][saveIndex] = Black;
				bm->turnb += 1;
				*x = i, *y = saveIndex;
				return;
			}
		}
	}
	else if (wayselection == d_Hori) {
		for (int i = 0; i < BoardWidth; ++i) {
			if (bm->arrayData[saveIndex][i] == STAR) {
				bm->arrayData[saveIndex][i] = Black;
				v.emplace_back(saveIndex + 1, i + 1);
				bm->turnb += 1;
				*x = saveIndex, *y = i;
				return;
			}
		}
	}
	else if (wayselection == d_LTRB) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][saveIndex - 18 + i] == STAR) {
					bm->arrayData[0 + i][saveIndex - 18 + i] = Black;
					v.emplace_back(i + 1, saveIndex - 18 + i + 1);
					bm->turnb += 1;
					*x = 0 + i, *y = saveIndex - 18 + i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][0 + i] == STAR) {
					bm->arrayData[0 + i][0 + i] = Black;
					v.emplace_back(i + 1, i + 1);
					bm->turnb += 1;
					*x = i, *y = i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][0 + i] == STAR) {
					bm->arrayData[18 - saveIndex + i][0 + i] = Black;
					v.emplace_back(18 - saveIndex + i + 1, i + 1);
					bm->turnb += 1;
					*x = 18 - saveIndex + i, *y = i;
					return;
				}
			}
		}
	}
	else if (wayselection == d_LBRT) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][36 - saveIndex - i] == STAR) {
					bm->arrayData[0 + i][36 - saveIndex - i] = Black;
					v.emplace_back(i + 1, 36 - saveIndex - i + 1);
					bm->turnb += 1;
					*x = i, *y = 36 - saveIndex - i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][saveIndex - i] == STAR) {
					bm->arrayData[0 + i][saveIndex - i] = Black;
					v.emplace_back(i + 1, saveIndex - i + 1);
					bm->turnb += 1;
					*x = i, *y = saveIndex - i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][18 - i] == STAR) {
					bm->arrayData[18 - saveIndex + i][18 - i] = Black;
					v.emplace_back(18 - saveIndex + i + 1, 18 - i + 1);
					bm->turnb += 1;
					*x = 18 - saveIndex + i, *y = 18 - i;
					return;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	if (wayselection == a_Vert) {
		for (int i = 0; i < BoardHeight; ++i) {
			if (bm->arrayData[i][saveIndex] == HEART) {
				bm->arrayData[i][saveIndex] = Black;
				v.emplace_back(i + 1, saveIndex + 1);
				bm->turnb += 1;
				*x = i, *y = saveIndex;
				return;
			}
		}
	}
	else if (wayselection == a_Hori) {
		for (int i = 0; i < BoardWidth; ++i) {
			if (bm->arrayData[saveIndex][i] == HEART) {
				bm->arrayData[saveIndex][i] = Black;
				v.emplace_back(saveIndex + 1, i + 1);
				bm->turnb += 1;
				*x = saveIndex, *y = i;
				return;
			}
		}
	}
	else if (wayselection == a_LTRB) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][saveIndex - 18 + i] == HEART) {
					bm->arrayData[0 + i][saveIndex - 18 + i] = Black;
					v.emplace_back(i + 1, saveIndex - 18 + i + 1);
					bm->turnb += 1;
					*x = 0 + i, *y = saveIndex - 18 + i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][0 + i] == HEART) {
					bm->arrayData[0 + i][0 + i] = Black;
					v.emplace_back(i + 1, i + 1);
					bm->turnb += 1;
					*x = 0 + i, *y = 0 + i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][0 + i] == HEART) {
					bm->arrayData[18 - saveIndex + i][0 + i] = Black;
					v.emplace_back(18 - saveIndex + i + 1, i + 1);
					bm->turnb += 1;
					*x = 18 - saveIndex + i, *y = i;
					return;
				}
			}
		}
	}
	else if (wayselection == a_LBRT) {
		if (saveIndex > 18) {
			for (int i = 0; i < 37 - saveIndex; ++i) {
				if (bm->arrayData[0 + i][36 - saveIndex - i] == HEART) {
					bm->arrayData[0 + i][36 - saveIndex - i] = Black;
					v.emplace_back(i + 1, 36 - saveIndex - i + 1);
					bm->turnb += 1;
					*x = i, *y = 36 - saveIndex - i;
					return;
				}
			}
		}
		else if (saveIndex == 18) {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[0 + i][saveIndex - i] == HEART) {
					bm->arrayData[0 + i][saveIndex - i] = Black;
					v.emplace_back(i + 1, saveIndex - i + 1);
					bm->turnb += 1;
					*x = i, *y = saveIndex - i;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < saveIndex + 1; ++i) {
				if (bm->arrayData[18 - saveIndex + i][18 - i] == HEART) {
					bm->arrayData[18 - saveIndex + i][18 - i] = Black;
					v.emplace_back(18 - saveIndex + i + 1, 18 - i + 1);
					bm->turnb += 1;
					*x = 18 - saveIndex + i, *y = 18 - i;
					return;
				}
			}
		}
	}
	//else {
	//	std::random_device rd;
	//	std::default_random_engine dre(rd());
	//	std::uniform_int_distribution<int> uid(0, 18);
	//	int tr = uid(dre);
	//	int tc = uid(dre);
	//	if (bm->arrayData[tr][tc] == Blank || bm->arrayData[tr][tc] == STAR || bm->arrayData[tr][tc] == HEART) {
	//		v.emplace_back(tr, tc);
	//		bm->turn += 1;
	//		return;
	//	}
	//}
}



bool isStart = false;
BoardManager bm;
std::vector<std::pair<int, int>> v;
bool isBlackFirstAttack = false;

//////////////////////////////////////////////////////////////////////////
void WhiteAttack_2013182024(int* x, int *y)
{
	if (!isStart) {
		isStart = true;
		Initiate(&bm,v);
	}
	Count(&bm, v);
	InsertCoord_AI_W(&bm, v, x, y);
}
void WhiteDefence_2013182024(int x, int y)
{
	if (!isStart) {
		isStart = true;
		Initiate(&bm, v);
	}
	bm.arrayData[x][y] = Black;
	bm.turnw += 1;
	v.emplace_back(x + 1, y + 1);
}
void BlackAttack_2013182024(int* x, int *y)
{
	if (!isStart) {
		isStart = true;
		Initiate(&bm, v);
	}
	if (!isBlackFirstAttack) {
		isBlackFirstAttack = true;
		*x = 10, *y = 10;
		return;
	}
	Count(&bm, v);
	InsertCoord_AI_B(&bm, v, x, y);
}
void BlackDefence_2013182024(int x, int y)
{
	if (!isStart) {
		isStart = true;
		Initiate(&bm, v);
	}
	bm.arrayData[x][y] = White;
	bm.turnb += 1;
	v.emplace_back(x + 1, y + 1);
}
//////////////////////////////////////////////////////////////////////////