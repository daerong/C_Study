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
#define STAR		100						//	백돌 알림
#define HEART		101						//	흑돌 알림
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
}RockData;								//	각 라인별 연속돌 정보를 저장하기 위한 자료형

typedef struct _Rock {
	int w{ 0 };
	int b{ 0 };
	bool blank{ false };
}RockCount;								//	연속돌 세기 위한 자료형

typedef struct _BoardManager {
	char** arrayData{ NULL };			//	실제 데이터
	RockData* cntHori_Data{ NULL };		//	수평돌 연속개수
	RockData* cntVert_Data{ NULL };		//	수직돌 연속개수
	RockData* cntLBRT_Data{ NULL };		//	'／'방향 사선돌 연속개수
	RockData* cntLTRB_Data{ NULL };		//	'＼'방향 사선돌 연속개수
	int turnb = 1;						//	턴
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
void Initiate(BoardManager* bm, std::vector<std::pair<int, int>>& v)											//	초기화
{
	/* 시작 함수. 배열값들을 모조리 초기회시킨다. 그 이전에 할당부터 시행한다. */
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
void Count(BoardManager* bm, const std::vector<std::pair<int, int>>& v)		//	돌세기
{
	/*
	스택에 의해 돌이 놓여진 순서대로 연속 수를 세다보니까 발생하는 막혀있는 공간에 나중에 돌을 두는 행위에서
	의도치 않게 돌 갯수가 '비정상적'으로 세어지는 현상이 발생해서 첫 번째 시도로 보드 저장 데이터를 함수 호출 전에 모두 깡그리
	초기화 해주려고 했다. (어차피 돌을 다시 세니까)
	하지만 의도한대로 해결되지 않았고, 돌을 무조건 저장하되, 상향과 하향방향에 임시 저장값을 둬서 그 저장값을 비교 후 큰 값을 넣어보는게 어떨까?
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
	for (auto p = v.begin(); p != v.end(); ++p) { // 현재 놓여진 모든 돌에 대해서 파악한다. 각 방향씩.
		CountHori(bm, p);
		CountVert(bm, p);
		CountLTRB(bm, p);
		CountLBRT(bm, p);
		//	검사 끝
	}
}
void ClearInputBuffer(void)			//	버퍼지우기
{
	/* scanf가 개행문자을 버퍼에서 fflush 시켜주지 않기 때문에 임의로 만든 함수이다. */
	while (getchar() != '\n');
}

void ClearRockCount(RockCount& rc)
{
	/* 연속수 시행결과를 초기화해준다.*/
	rc.w = 0;
	rc.b = 0;
	rc.blank = false;
}

template <class Iter>
void CountHori(BoardManager * bm, Iter p)
{
	//	반복자 p로 넘어온 것은 실좌표계이기 때문에, 인덱스로 치환시키려고 -1을 해준다.
	RockCount rc;
	// →방향 가로 연속 돌 세기
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	백돌일 때
		//	하향방향
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
		//	상향방향
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
		//	흑돌일 때
		//	하향방향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
		//	상향방향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
	//	반복자 p로 넘어온 것은 실좌표계이기 때문에, 인덱스로 치환시키려고 -1을 해준다.
	RockCount rc;
	// ↓방향 세로 연속 돌 세기
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	백돌일 때
		//	하향방향
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight) {	//	경계인덱스라면 재지 않는다.
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
		//	상향방향
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
		//	흑돌일 때
		//	하향방향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight) {	//	경계인덱스라면 재지 않는다.
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
		//	상향방향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
	//	반복자 p로 넘어온 것은 실좌표계이기 때문에, 인덱스로 치환시키려고 -1을 해준다.
	RockCount rc;
	// ↘방향 가로 연속 돌 세기
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	백돌일 때
		//	하향방향
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
		//	상향방향
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
		//	흑돌일 때
		//	하향방향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
			if ((*p).first - 1 - i == -1 || (*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
	//	반복자 p로 넘어온 것은 실좌표계이기 때문에, 인덱스로 치환시키려고 -1을 해준다.
	RockCount rc;
	// ↙방향 가로 연속 돌 세기
	if (bm->arrayData[(*p).first - 1][(*p).second - 1] == White) {
		ClearRockCount(rc);
		++rc.w;
		//	백돌일 때
		//	하향
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
		//	상향
		ClearRockCount(rc);
		++rc.w;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
		//	흑돌일 때
		//	하향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 + i == BoardHeight || (*p).second - 1 - i == -1) {	//	경계인덱스라면 재지 않는다.
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
		//	상향
		ClearRockCount(rc);
		++rc.b;
		for (int i = 1; i < 5; ++i) {
			if ((*p).first - 1 - i == -1 || (*p).second - 1 + i == BoardWidth) {	//	경계인덱스라면 재지 않는다.
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
	/* 이 부분에서 AI 기능을 구현한다. 선행은 백돌 (후공, 방어우선순위, 이후 공격수 점검으로 로직을 짜도록 한다.
	*/
	//	<전제> : 사용자가 흑돌, AI(?)는 백돌
	//	필요 행동 ::	벡터에 emplace_back 좌표 밀어넣기
	//					턴 증가시키기
	//					돌 자동으로 놓기

	int maxblackrock{ 0 };
	int wayselection{ 0 };
	int saveIndex{ 0 };

	//	백돌일때, 흑돌을 판정한다.
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
	/* 이 부분에서 AI 기능을 구현한다. 선행은 백돌 (후공, 방어우선순위, 이후 공격수 점검으로 로직을 짜도록 한다.
	*/
	//	필요 행동 ::	벡터에 emplace_back 좌표 밀어넣기
	//					턴 증가시키기
	//					돌 자동으로 놓기

	int maxblackrock{ 0 };
	int wayselection{ 0 };
	int saveIndex{ 0 };


	//	백돌일때, 흑돌을 판정한다.
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