#include <random>

#define BOARD_SIZE_2011144024_rev03 19
#define BOARD_MID_2011144024_rev03 9
#define BLACK -1
#define WHITE 1

typedef struct GAME_BOARD_2011144024_rev03 {
	int color;
	int xMax;
	int yMax;
	int uMax;
	int dMax;
	int point;
} GAME_BOARD_2011144024_rev03;

GAME_BOARD_2011144024_rev03 game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03*BOARD_SIZE_2011144024_rev03] = { 0 };

char mode_2011144024_rev03 = '\n';		// A, B, C ,D
int last_stone_x_2011144024_rev03 = -99;
int last_stone_y_2011144024_rev03 = -99;
int player_black_turn_2011144024_rev03 = 0;
int player_white_turn_2011144024_rev03 = 0;

void reset_point_2011144024_rev03() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev03*BOARD_SIZE_2011144024_rev03; i++) {
		game_board_2011144024_rev03[i].point = 0;
	}
}

void took_stone_2011144024_rev03(int inner_x, int inner_y, int type) {
	game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03*inner_y + inner_x].color = type;
}

void catch_mode_2011144024_rev03(int inner_x, int inner_y) {		// East West South North
	if (inner_x < BOARD_MID_2011144024_rev03 && inner_y < BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'A';
	else if (inner_x > BOARD_MID_2011144024_rev03 && inner_y < BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'B';
	else if (inner_x > BOARD_MID_2011144024_rev03 && inner_y > BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'C';
	else if (inner_x < BOARD_MID_2011144024_rev03 && inner_y > BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'D';
	else if (inner_y == BOARD_MID_2011144024_rev03 && inner_x > BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'E';
	else if (inner_y == BOARD_MID_2011144024_rev03 && inner_x < BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'W';
	else if (inner_y > BOARD_MID_2011144024_rev03 && inner_x == BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'S';
	else if (inner_y < BOARD_MID_2011144024_rev03 && inner_x == BOARD_MID_2011144024_rev03) mode_2011144024_rev03 = 'N';
	else mode_2011144024_rev03 = '\n';
}

void second_side_marking_sub_2011144024_rev03(int inner_x, int inner_y, int *target_x, int *target_y, int add_x, int add_y) {
	*target_x = inner_x + add_x;
	*target_y = inner_y + add_y;
}

void second_side_marking_2011144024_rev03(int inner_x, int inner_y, int *target_x, int *target_y) {
	if (mode_2011144024_rev03 == 'A') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 3, 3);
	}
	else if (mode_2011144024_rev03 == 'B') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -3, 3);
	}
	else if (mode_2011144024_rev03 == 'C') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -3, -3);
	}
	else if (mode_2011144024_rev03 == 'D') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 3, -3);
	}
	else if (mode_2011144024_rev03 == 'E') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -3, 0);
	}
	else if (mode_2011144024_rev03 == 'W') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 3, 0);
	}
	else if (mode_2011144024_rev03 == 'S') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, -3);
	}
	else if (mode_2011144024_rev03 == 'N') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, 3);
	}
	else {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, 0);
	}
}

void second_mid_marking_2011144024_rev03(int inner_x, int inner_y, int *target_x, int *target_y) {
	if (mode_2011144024_rev03 == 'A') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, 0);
	}
	else if (mode_2011144024_rev03 == 'B') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, 1);
	}
	else if (mode_2011144024_rev03 == 'C') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -1, 0);
	}
	else if (mode_2011144024_rev03 == 'D') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, -1);
	}
	else if (mode_2011144024_rev03 == 'E') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -2, 0);
	}
	else if (mode_2011144024_rev03 == 'W') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 2, 0);
	}
	else if (mode_2011144024_rev03 == 'S') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, -2);
	}
	else if (mode_2011144024_rev03 == 'N') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, 2);
	}
	else {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, 0);
	}
}

void second_center_marking_2011144024_rev03(int inner_x, int inner_y, int *target_x, int *target_y) {
	if (mode_2011144024_rev03 == 'A') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -1, 0);
	}
	else if (mode_2011144024_rev03 == 'B') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, 1);
	}
	else if (mode_2011144024_rev03 == 'C') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, -1);
	}
	else if (mode_2011144024_rev03 == 'D') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -1, -1);
	}
	else if (mode_2011144024_rev03 == 'E') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -1, 0);
	}
	else if (mode_2011144024_rev03 == 'W') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, 0);
	}
	else if (mode_2011144024_rev03 == 'S') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, -1, 0);
	}
	else if (mode_2011144024_rev03 == 'N') {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 0, 1);
	}
	else {
		second_side_marking_sub_2011144024_rev03(inner_x, inner_y, target_x, target_y, 1, 0);
	}
}

void xClear_2011144024_rev03(int inner_x, int inner_y, int type) {
	game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax = 0;
	if (inner_x < BOARD_SIZE_2011144024_rev03 - 1) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) xClear_2011144024_rev03(inner_x + 1, inner_y, type);
	if (inner_x > 0) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) xClear_2011144024_rev03(inner_x - 1, inner_y, type);
}

void yClear_2011144024_rev03(int inner_x, int inner_y, int type) {
	game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax = 0;
	if (inner_y < BOARD_SIZE_2011144024_rev03 - 1) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) yClear_2011144024_rev03(inner_x, inner_y + 1, type);
	if (inner_y > 0) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) yClear_2011144024_rev03(inner_x, inner_y - 1, type);
}

void uClear_2011144024_rev03(int inner_x, int inner_y, int type) {
	game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax = 0;
	if (inner_x > 0 && inner_y < BOARD_SIZE_2011144024_rev03 - 1) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) uClear_2011144024_rev03(inner_x - 1, inner_y + 1, type);
	if (inner_x < BOARD_SIZE_2011144024_rev03 - 1 && inner_y > 0) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) uClear_2011144024_rev03(inner_x + 1, inner_y - 1, type);
}

void dClear_2011144024_rev03(int inner_x, int inner_y, int type) {
	game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax = 0;
	if (inner_x < BOARD_SIZE_2011144024_rev03 - 1 && inner_y < BOARD_SIZE_2011144024_rev03 - 1) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) dClear_2011144024_rev03(inner_x + 1, inner_y + 1, type);
	if (inner_x > 0 && inner_y > 0) if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) dClear_2011144024_rev03(inner_x - 1, inner_y - 1, type);
}

int xEnd_check_2011144024_rev03(int inner_x, int inner_y, int type, int move_x, int move_y) {		// 돌 없으면 1리턴
	int inner_x_add = inner_x + move_x;
	int inner_y_add = inner_y + move_y;
	if (inner_x_add < 0) {
		return -1 * type;
	}
	else if (inner_x_add > BOARD_SIZE_2011144024_rev03 - 1) {
		return -1 * type;
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == type) {
			xEnd_check_2011144024_rev03(inner_x_add, inner_y_add, type, move_x, move_y);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == -1 * type) {
			return -1 * type;		// 끝이 막혀있음
		}
		else return 0;
	}
	return 0;
}

void xBoth_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {		// 돌 없으면 1리턴
	if (xEnd_check_2011144024_rev03(inner_x, inner_y, type, -1, 0) && xEnd_check_2011144024_rev03(inner_x, inner_y, type, 1, 0)) xClear_2011144024_rev03(inner_x, inner_y, type);
}

int yEnd_check_2011144024_rev03(int inner_x, int inner_y, int type, int move_x, int move_y) {		// 돌 없으면 1리턴
	int inner_x_add = inner_x + move_x;
	int inner_y_add = inner_y + move_y;
	if (inner_y_add < 0) {
		return -1 * type;
	}
	else if (inner_y_add > BOARD_SIZE_2011144024_rev03 - 1) {
		return -1 * type;
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == type) {
			yEnd_check_2011144024_rev03(inner_x_add, inner_y_add, type, move_x, move_y);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == -1 * type) {
			return -1 * type;		// 끝이 막혀있음
		}
		else return 0;
	}
	return 0;
}

void yBoth_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {		// 돌 없으면 1리턴
	if (yEnd_check_2011144024_rev03(inner_x, inner_y, type, 0, -1) && yEnd_check_2011144024_rev03(inner_x, inner_y, type, 0, -1)) yClear_2011144024_rev03(inner_x, inner_y, type);
}

int uEnd_check_2011144024_rev03(int inner_x, int inner_y, int type, int move_x, int move_y) {		// 돌 없으면 1리턴
	int inner_x_add = inner_x + move_x;
	int inner_y_add = inner_y + move_y;
	if (inner_x_add > BOARD_SIZE_2011144024_rev03 - 1 || inner_y_add < 0) {
		return -1 * type;
	}
	else if (inner_x_add < 0 || inner_y_add > BOARD_SIZE_2011144024_rev03 - 1) {
		return -1 * type;
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == type) {
			uEnd_check_2011144024_rev03(inner_x_add, inner_y_add, type, move_x, move_y);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == -1 * type) {
			return -1 * type;		// 끝이 막혀있음
		}
		else return 0;
	}
	return 0;
}

void uBoth_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {		// 돌 없으면 1리턴
	if (uEnd_check_2011144024_rev03(inner_x, inner_y, type, -1, 1) && uEnd_check_2011144024_rev03(inner_x, inner_y, type, 1, -1)) uClear_2011144024_rev03(inner_x, inner_y, type);
}

int dEnd_check_2011144024_rev03(int inner_x, int inner_y, int type, int move_x, int move_y) {		// 돌 없으면 1리턴
	int inner_x_add = inner_x + move_x;
	int inner_y_add = inner_y + move_y;
	if (inner_x_add < 0 || inner_y_add < 0) {
		return -1 * type;
	}
	else if (inner_x_add > BOARD_SIZE_2011144024_rev03 - 1 || inner_y_add > BOARD_SIZE_2011144024_rev03 - 1) {
		return -1 * type;
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == type) {
			dEnd_check_2011144024_rev03(inner_x_add, inner_y_add, type, move_x, move_y);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y_add + inner_x_add].color == -1 * type) {
			return -1 * type;		// 끝이 막혀있음
		}
		else return 0;
	}
	return 0;
}

void dBoth_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {		// 돌 없으면 1리턴
	if (dEnd_check_2011144024_rev03(inner_x, inner_y, type, 1, 1) && dEnd_check_2011144024_rev03(inner_x, inner_y, type, -1, -1)) dClear_2011144024_rev03(inner_x, inner_y, type);

}

void blocked_stone_max_claer_2011144024_rev03(int inner_x, int inner_y, int type) {
	xBoth_max_update_2011144024_rev03(inner_x, inner_y, type);
	yBoth_max_update_2011144024_rev03(inner_x, inner_y, type);
	uBoth_max_update_2011144024_rev03(inner_x, inner_y, type);
	dBoth_max_update_2011144024_rev03(inner_x, inner_y, type);
}

void xUp_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].xMax = max_update;
			xUp_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}	
}

void xDown_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x > 0) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].xMax = max_update;
			xDown_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void x_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x > 0 && inner_x < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax;
			xUp_max_update_2011144024_rev03(inner_x, inner_y, 1, 0, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax);
			xDown_max_update_2011144024_rev03(inner_x, inner_y, -1, 0, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax;
			xUp_max_update_2011144024_rev03(inner_x, inner_y, 1, 0, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax;
			xDown_max_update_2011144024_rev03(inner_x, inner_y, -1, 0, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax);
		}
		else {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax = 1;
		}
	}
}

void yUp_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_y < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].yMax = max_update;
			yUp_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void yDown_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_y > 0) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].yMax = max_update;
			yDown_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void y_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x > 0 && inner_x < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax;
			yUp_max_update_2011144024_rev03(inner_x, inner_y, 0, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax);
			yDown_max_update_2011144024_rev03(inner_x, inner_y, 0, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax;
			yUp_max_update_2011144024_rev03(inner_x, inner_y, 0, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax;
			yDown_max_update_2011144024_rev03(inner_x, inner_y, 0, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax);
		}
		else {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax = 1;
		}
	}
}

void uUp_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x < BOARD_SIZE_2011144024_rev03 - 1 && add_inner_y > 0) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].uMax = max_update;
			uUp_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void uDown_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x > 0 && add_inner_y < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].uMax = max_update;
			uDown_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void u_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x > 0 && inner_x < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 *(inner_y + 1) + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax;
			uUp_max_update_2011144024_rev03(inner_x, inner_y, 1, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax);
			uDown_max_update_2011144024_rev03(inner_x, inner_y, -1, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax;
			uUp_max_update_2011144024_rev03(inner_x, inner_y, 1, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax;
			uDown_max_update_2011144024_rev03(inner_x, inner_y, -1, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax);
		}
		else {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax = 1;
		}
	}
}

void dUp_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x < BOARD_SIZE_2011144024_rev03 - 1 && add_inner_y > BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].dMax = max_update;
			dUp_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void dDown_max_update_2011144024_rev03(int inner_x, int inner_y, int x_move, int y_move, int type, int max_update) {
	int add_inner_x = inner_x + x_move;
	int add_inner_y = inner_y + y_move;
	if (add_inner_x > 0 && add_inner_y > 0) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * add_inner_y + add_inner_x].dMax = max_update;
			dDown_max_update_2011144024_rev03(add_inner_x, add_inner_y, x_move, y_move, type, max_update);
		}
	}
}

void d_max_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x > 0 && inner_x < BOARD_SIZE_2011144024_rev03 - 1) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 *(inner_y - 1) + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax;
			dUp_max_update_2011144024_rev03(inner_x, inner_y, 1, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax);
			dDown_max_update_2011144024_rev03(inner_x, inner_y, -1, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax;
			dUp_max_update_2011144024_rev03(inner_x, inner_y, 1, 1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax);
		}
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax = 1 + game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax;
			dDown_max_update_2011144024_rev03(inner_x, inner_y, -1, -1, type, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax);
		}
		else {
			game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax = 1;
		}
	}
}

void max_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	x_max_update_2011144024_rev03(inner_x, inner_y, type);
	y_max_update_2011144024_rev03(inner_x, inner_y, type);
	u_max_update_2011144024_rev03(inner_x, inner_y, type);
	d_max_update_2011144024_rev03(inner_x, inner_y, type);
}

void insert_xy_2011144024_rev03(int *inner_x, int *inner_y, int x_source, int y_source) {
	*inner_x = BOARD_MID_2011144024_rev03 + x_source;
	*inner_y = BOARD_MID_2011144024_rev03 + y_source;
}

void third_one_length_marking_2011144024_rev03(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev03 == 'A') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 1, 0);
	}
	else if (mode_2011144024_rev03 == 'B') {
		insert_xy_2011144024_rev03(inner_x, inner_y, -1, 0);
	}
	else if (mode_2011144024_rev03 == 'C') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 0, -1);
	}
	else if (mode_2011144024_rev03 == 'D') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 0, -1);
	}
	else if (mode_2011144024_rev03 == 'E') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 1, 1);
	}
	else if (mode_2011144024_rev03 == 'W') {
		insert_xy_2011144024_rev03(inner_x, inner_y, -1, -1);
	}
	else if (mode_2011144024_rev03 == 'S') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 1, 1);
	}
	else if (mode_2011144024_rev03 == 'N') {
		insert_xy_2011144024_rev03(inner_x, inner_y, 1, -1);
	}
}

void third_two_length_marking_2011144024_rev03(int inner_x, int inner_y, int *target_x, int *target_y) {
	if (mode_2011144024_rev03 == 'A') {
		if (BOARD_MID_2011144024_rev03 - inner_x > BOARD_MID_2011144024_rev03 - inner_y) insert_xy_2011144024_rev03(target_x, target_y, 0, 1);
		else if (BOARD_MID_2011144024_rev03 - inner_x < BOARD_MID_2011144024_rev03 - inner_y) insert_xy_2011144024_rev03(target_x, target_y, 1, 0);
		else insert_xy_2011144024_rev03(target_x, target_y, 1, -1);
	}
	else if (mode_2011144024_rev03 == 'B') {
		if (inner_x - BOARD_MID_2011144024_rev03 > BOARD_MID_2011144024_rev03 - inner_y) insert_xy_2011144024_rev03(target_x, target_y, 0, 1);
		else if (inner_x - BOARD_MID_2011144024_rev03 < BOARD_MID_2011144024_rev03 - inner_y) insert_xy_2011144024_rev03(target_x, target_y, -1, 0);
		else insert_xy_2011144024_rev03(target_x, target_y, -1, -1);
	}
	else if (mode_2011144024_rev03 == 'C') {
		if (inner_x - BOARD_MID_2011144024_rev03 > inner_y - BOARD_MID_2011144024_rev03) insert_xy_2011144024_rev03(target_x, target_y, -1, 0);
		else if (inner_x - BOARD_MID_2011144024_rev03 < inner_y - BOARD_MID_2011144024_rev03) insert_xy_2011144024_rev03(target_x, target_y, 0, -1);
		else insert_xy_2011144024_rev03(target_x, target_y, -1, 1);
	}
	else if (mode_2011144024_rev03 == 'D') {
		if (BOARD_MID_2011144024_rev03 - inner_x > inner_y - BOARD_MID_2011144024_rev03) insert_xy_2011144024_rev03(target_x, target_y, 1, 0);
		else if (BOARD_MID_2011144024_rev03 - inner_x < inner_y - BOARD_MID_2011144024_rev03) insert_xy_2011144024_rev03(target_x, target_y, 0, -1);
		else insert_xy_2011144024_rev03(target_x, target_y, 1, 1);
	}
	else if (mode_2011144024_rev03 == 'E') {
		insert_xy_2011144024_rev03(target_x, target_y, -2, 0);
	}
	else if (mode_2011144024_rev03 == 'W') {
		insert_xy_2011144024_rev03(target_x, target_y, 2, 0);
	}
	else if (mode_2011144024_rev03 == 'S') {
		insert_xy_2011144024_rev03(target_x, target_y, -2, 0);
	}
	else if (mode_2011144024_rev03 == 'N') {
		insert_xy_2011144024_rev03(target_x, target_y, 0, 2);
	}
}

void attack_four_check_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax == 4) {
			if (inner_x != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].point += 10000;
			if (inner_x != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].point += 10000;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax == 4) {
			if (inner_y != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].point += 10000;
			if (inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].point += 10000;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax == 4) {
			if (inner_y != 0 && inner_x != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].point += 10000;
			if (inner_x != 0 && inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].point += 10000;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax == 4) {
			if (inner_y != 0 && inner_x != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].point += 10000;
			if (inner_x != BOARD_SIZE_2011144024_rev03 - 1 && inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].point += 10000;
		}
	}
}

void shield_four_check_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax == 4) {
			if (inner_x != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].point += 9999;
			if (inner_x != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].point += 9999;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax == 4) {
			if (inner_y != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].point += 9999;
			if (inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].point += 9999;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax == 4) {
			if (inner_y != 0 && inner_x != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].point += 9999;
			if (inner_x != 0 && inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].point += 9999;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax == 4) {
			if (inner_y != 0 && inner_x != 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].point += 9999;
			if (inner_x != BOARD_SIZE_2011144024_rev03 - 1 && inner_y != BOARD_SIZE_2011144024_rev03 - 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].point += 9999;
		}
	}
}

int check_between_2011144024_rev03(int A, int B, int type) {
	if (A == type && B == type) return 1;
	return 0;
}

void attack_three_check_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x == 0) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_y < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
	}
	else if (inner_x == BOARD_SIZE_2011144024_rev03 - 1) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_y < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
	}
	else if (inner_y == 0) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_x < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
	}
	else if (inner_y == BOARD_SIZE_2011144024_rev03 - 1) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
		if (inner_x < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1000;}
		}
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1001;}

		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 2) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].xMax == 1) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 2) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 1) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 2) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 1) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 2) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 1) { game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 1002;}
		}
	}
}

void sheild_three_check_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (inner_x == 0) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_y < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
	}
	else if (inner_x == BOARD_SIZE_2011144024_rev03 - 1) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_y < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
	}
	else if (inner_y == 0) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_x < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
	}
	else if (inner_y == BOARD_SIZE_2011144024_rev03 - 1) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev03 - 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
		if (inner_x < BOARD_SIZE_2011144024_rev03 - 5) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 990;
		}
	}
	else {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 991;

		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 2) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].xMax == 1) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 2) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 1) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 2) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 1) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
		}
		if (check_between_2011144024_rev03(game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color, game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 2) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 1) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 992;
		}
	}
}

int center_point_update_2011144024_rev03(int inner_x, int inner_y) {
	int result_x = BOARD_MID_2011144024_rev03 - inner_x;
	int result_y = BOARD_MID_2011144024_rev03 - inner_y;
	result_x = (result_x > 0) ? result_x : -1 * result_x;
	result_y = (result_y > 0) ? result_y : -1 * result_y;

	if (result_x > result_y) {
		return BOARD_MID_2011144024_rev03 - result_x;
	}
	else {
		return BOARD_MID_2011144024_rev03 - result_y;
	}
}

int change_absolute_value_2011144024_rev03(int target) {
	return (target > 0) ? target : -1 * target;
}

void new_three_attack_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].point += 20;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 2].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].point += 20;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].point += 20;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].point += 20;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].point += 20;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].point += 20;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].point += 20;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].point += 20;
	}
}

void new_three_shield_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].xMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].point += 15;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 2].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].point += 15;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].yMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].point += 15;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].point += 15;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].uMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].point += 15;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].point += 15;
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].dMax == 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].point += 15;
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].point += 15;
	}
}

void new_three_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == type) new_three_attack_making_2011144024_rev03(inner_x, inner_y, type);
	else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == -1 * type) new_three_shield_making_2011144024_rev03(inner_x, inner_y, -1 * type);
}

void empty_space_three_attack_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 21;
		}
	}
}

void empty_space_three_shield_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 1 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x + 2].color == 0 || game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += 19;
		}
	}
}

void empty_space_three_making_2011144024_rev03(int inner_x, int inner_y, int type) {
	empty_space_three_attack_making_2011144024_rev03(inner_x, inner_y, type);
	empty_space_three_shield_making_2011144024_rev03(inner_x, inner_y, -1 * type);
}

void new_shape_making_2011144024_rev03(int inner_x, int inner_y, int x_shift, int y_shift, int type) {
	if (y_shift == 0) {
		if (x_shift == 1 || x_shift == -1) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 1) + inner_x + x_shift].color == 0) {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 2) + inner_x + x_shift].color != -1 * type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 2) + inner_x + x_shift + x_shift].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 20;
				}
			}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 1) + inner_x + x_shift].color == 0) {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 2) + inner_x + x_shift].color != -1 * type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 2) + inner_x + x_shift + x_shift].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 20;
				}
			}
		}
		else if (x_shift == 2 || x_shift == -2) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 1) + inner_x + x_shift].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + (x_shift / 2)].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 10;
			}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 1) + inner_x + x_shift].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + (x_shift / 2)].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 10;
			}
		}
	}
	else if (x_shift == 0) {
		if (y_shift == 1 || y_shift == -1) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 1].color == 0) {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 2].color != -1 * type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + y_shift) + inner_x + x_shift - 2].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 20;
				}
			}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 1].color == 0) {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 2].color != -1 * type && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift + y_shift) + inner_x + x_shift + 2].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 20;
				}
			}
		}
		else if (x_shift == 2 || x_shift == -2) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 1].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 10;
			}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 1].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 10;
			}
		}
		else if (x_shift == y_shift || x_shift == -1 * y_shift) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 2) + inner_x + x_shift * 2].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 3) + inner_x + x_shift * 3].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 2) + inner_x + x_shift * 2].point += 30;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 2) + inner_x].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 2) + inner_x].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift * 2) + inner_x].point += 10;
			}
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift * 2].color == 0) {
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift * 2].point += 25;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift].color != -1 * type) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift * 2].point += 10;
			}
		}
		else {
			if (change_absolute_value_2011144024_rev03(x_shift) > change_absolute_value_2011144024_rev03(x_shift)) {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift / 2].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift / 2].point += 10;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift / 2].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + x_shift / 2].point += 10;
			}
			else {
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x + x_shift].point += 10;
				if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x].color == 0) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift / 2) + inner_x].point += 10;
			}
		}
	}
}

void raise_point_use_XY_2011144024_rev03(int inner_x, int inner_y, int x_shift, int y_shift, int raise, int type) {
	if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift].color == 0) {
		game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift].point += raise;
	}
	else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + y_shift) + inner_x + x_shift].color == type) {
		new_shape_making_2011144024_rev03(inner_x, inner_y, x_shift, y_shift, type);
	}
}

void near_by_same_color_point_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 0, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, -1, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, 0, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, 1, 3, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -1, 8, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, -1, 8, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, 1, 8, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 1, 8, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, -1, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -2, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 2, -1, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, -2, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, -1, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -2, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, 1, 4, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 2, 4, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, 0, 9, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, -2, 9, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 2, 0, 9, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, 2, 9, type);
}

void near_by_other_color_point_update_2011144024_rev03(int inner_x, int inner_y, int type) {
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 0, 2, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, -1, 2, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, 0, 2, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, 1, 2, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -1, 6, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, -1, 6, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, 1, 6, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 1, 6, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, -1, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -2, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 2, -1, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 1, -2, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, -1, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, -2, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, 1, 3, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -1, 2, 3, type);

	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, -2, 0, 7, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, -2, 7, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 2, 0, 7, type);
	raise_point_use_XY_2011144024_rev03(inner_x, inner_y, 0, 2, 7, type);
}

void near_by_point_update_2011144024_rev03(int x, int y, int type) {
	if (x > 2 && x < BOARD_SIZE_2011144024_rev03 - 3 && y > 2 && y < BOARD_SIZE_2011144024_rev03 - 3) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * y + x].color == type) near_by_same_color_point_update_2011144024_rev03(x, y, type);
		else if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * y + x].color == -1 * type) near_by_other_color_point_update_2011144024_rev03(x, y, -1 * type);
	}
}

void point_update_white_2011144024_rev03() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev03; i++) {
		for (int j = 0; j < BOARD_SIZE_2011144024_rev03; j++) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * i + j].color == 0) {
				sheild_three_check_2011144024_rev03(j, i, BLACK);
				attack_three_check_2011144024_rev03(j, i, WHITE);
				empty_space_three_making_2011144024_rev03(j, i, WHITE);
			}
			else {
				attack_four_check_2011144024_rev03(j, i, WHITE);
				shield_four_check_2011144024_rev03(j, i, BLACK);
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * j + i].point += center_point_update_2011144024_rev03(j, i);
				near_by_point_update_2011144024_rev03(j, i, WHITE);
				new_three_making_2011144024_rev03(j, i, WHITE);
			}
		}
	}
}

void escape_foul_black_turn_2011144024_rev03(int inner_x, int inner_y) {
	int foul_count = 0;
	if (inner_x > 1 && inner_x < BOARD_SIZE_2011144024_rev03 - 2 && inner_y > 1 && inner_y < BOARD_SIZE_2011144024_rev03 - 2) {
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == BLACK) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 2].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 2].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color == BLACK) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color == BLACK) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x + 2].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x - 2].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color == BLACK) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 2) + inner_x - 2].color == 0 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 2) + inner_x + 2].color == 0) foul_count += 1;
		}
		if (inner_x > 2 && inner_x < BOARD_SIZE_2011144024_rev03 - 3 && inner_y > 2 && inner_y < BOARD_SIZE_2011144024_rev03 - 3) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 1].xMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x - 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].color == BLACK && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x].yMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 3) + inner_x].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 3) + inner_x].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x + 1].uMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 3) + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 3) + inner_x - 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 1) + inner_x + 1].dMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y + 3) + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].color && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 1) + inner_x - 1].dMax == 2 && game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * (inner_y - 3) + inner_x - 3].color == 0) foul_count += 1;
		}
	}
	if (foul_count > 1) game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * inner_y + inner_x].point += -999999;
}



void point_update_black_2011144024_rev03() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev03; i++) {
		for (int j = 0; j < BOARD_SIZE_2011144024_rev03; j++) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * i + j].color == 0) {
				sheild_three_check_2011144024_rev03(j, i, WHITE);
				attack_three_check_2011144024_rev03(j, i, BLACK);
				empty_space_three_making_2011144024_rev03(j, i, BLACK);
				escape_foul_black_turn_2011144024_rev03(j, i);
			}
			else {
				attack_four_check_2011144024_rev03(j, i, BLACK);
				shield_four_check_2011144024_rev03(j, i, WHITE);
				game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * j + i].point += center_point_update_2011144024_rev03(j, i);
				near_by_point_update_2011144024_rev03(j, i, BLACK);
				new_three_making_2011144024_rev03(j, i, BLACK);
			}
		}
	}
}

void max_point_xy_locate_return_2011144024_rev03(int *target_x, int *target_y) {
	int max_point = -1;
	int x, y;
	for (int i = 0; i < BOARD_SIZE_2011144024_rev03; i++) {
		for (int j = 0; j < BOARD_SIZE_2011144024_rev03; j++) {
			if (game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * i + j].color == 0) {
				if (max_point < game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * i + j].point) {
					max_point = game_board_2011144024_rev03[BOARD_SIZE_2011144024_rev03 * i + j].point;
					x = j;
					y = i;
				}
			}

		}
	}
	*target_x = x;
	*target_y = y;
}

void WhiteAttack_2011144024_rev03(int *x, int *y)
{
	// 3x3 가능, 4x4 가능, 6목 가능하되 승패 영향x

	player_white_turn_2011144024_rev03 += 1;

	int white_x, white_y;

	if (player_white_turn_2011144024_rev03 == 2) {
		if (last_stone_x_2011144024_rev03 < 3 || last_stone_y_2011144024_rev03 < 3 || last_stone_x_2011144024_rev03 >= BOARD_SIZE_2011144024_rev03 - 3 || last_stone_y_2011144024_rev03 >= BOARD_SIZE_2011144024_rev03 - 3) {
			second_side_marking_2011144024_rev03(last_stone_x_2011144024_rev03, last_stone_y_2011144024_rev03, &white_x, &white_y);
		}
		else if (last_stone_x_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 1 && last_stone_x_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 1 && last_stone_y_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 1 && last_stone_y_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 1) {
			second_center_marking_2011144024_rev03(last_stone_x_2011144024_rev03, last_stone_y_2011144024_rev03, &white_x, &white_y);
		}
		else {
			second_mid_marking_2011144024_rev03(last_stone_x_2011144024_rev03, last_stone_y_2011144024_rev03, &white_x, &white_y);
		}
	}
	else {
		reset_point_2011144024_rev03();
		point_update_white_2011144024_rev03();
		max_point_xy_locate_return_2011144024_rev03(&white_x, &white_y);
	}

	*x = white_x;
	*y = white_y;

	last_stone_x_2011144024_rev03 = white_x;
	last_stone_y_2011144024_rev03 = white_y;

	if (mode_2011144024_rev03 == '\n') catch_mode_2011144024_rev03(white_x, white_y);

	took_stone_2011144024_rev03(white_x, white_y, WHITE);
	max_update_2011144024_rev03(white_x, white_y, WHITE);
	blocked_stone_max_claer_2011144024_rev03(white_x, white_y, WHITE);

}
void WhiteDefence_2011144024_rev03(int x, int y)
{
	//흰돌 1
	//검은돌 -1

	player_white_turn_2011144024_rev03 += 1;

	last_stone_x_2011144024_rev03 = x;
	last_stone_y_2011144024_rev03 = y;

	if (mode_2011144024_rev03 == '\n') catch_mode_2011144024_rev03(x, y);

	took_stone_2011144024_rev03(x, y, BLACK);
	max_update_2011144024_rev03(x, y, BLACK);
	blocked_stone_max_claer_2011144024_rev03(x, y, BLACK);
}
void AttackBlack_2011144024_rev03(int *x, int *y)
{
	// 3x3, 4x4, 6목 불가

	player_black_turn_2011144024_rev03 += 1;

	int black_x, black_y;

	if (player_black_turn_2011144024_rev03 == 1) { black_x = 9; black_y = 9; }
	else if (player_black_turn_2011144024_rev03 == 3) {
		if (last_stone_x_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 1 && last_stone_x_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 1 && last_stone_y_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 1 && last_stone_y_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 1) {
			third_one_length_marking_2011144024_rev03(&black_x, &black_y);
		}
		else if (last_stone_x_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 2 && last_stone_x_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 2 && last_stone_y_2011144024_rev03 >= BOARD_MID_2011144024_rev03 - 2 && last_stone_y_2011144024_rev03 <= BOARD_MID_2011144024_rev03 - 2) {
			third_two_length_marking_2011144024_rev03(last_stone_x_2011144024_rev03, last_stone_y_2011144024_rev03, &black_x, &black_y);
		}
		else {
			reset_point_2011144024_rev03();
			point_update_black_2011144024_rev03();
			max_point_xy_locate_return_2011144024_rev03(&black_x, &black_y);
		}
	}
	else {
		reset_point_2011144024_rev03();
		point_update_black_2011144024_rev03();
		max_point_xy_locate_return_2011144024_rev03(&black_x, &black_y);
	}



	*x = black_x;
	*y = black_y;


	last_stone_x_2011144024_rev03 = black_x;
	last_stone_y_2011144024_rev03 = black_y;

	if (mode_2011144024_rev03 == '\n') catch_mode_2011144024_rev03(black_x, black_y);

	took_stone_2011144024_rev03(black_x, black_y, BLACK);
	max_update_2011144024_rev03(black_x, black_y, BLACK);
	blocked_stone_max_claer_2011144024_rev03(black_x, black_y, BLACK);
}
void DefenceBlack_2011144024_rev03(int x, int y)
{
	//흰돌 1
	//검은돌 -1

	player_black_turn_2011144024_rev03 += 1;


	last_stone_x_2011144024_rev03 = x;
	last_stone_y_2011144024_rev03 = y;

	if (mode_2011144024_rev03 == '\n') catch_mode_2011144024_rev03(x, y);

	took_stone_2011144024_rev03(x, y, WHITE);
	max_update_2011144024_rev03(x, y, WHITE);
	blocked_stone_max_claer_2011144024_rev03(x, y, WHITE);
}


