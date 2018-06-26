#include <random>

#define BOARD_SIZE_2011144024_rev02 19
#define BOARD_MID_2011144024_rev02 9
#define BLACK -1
#define WHITE 1

typedef struct GAME_BOARD {
	int color;
	int xMax;
	int yMax;
	int uMax;
	int dMax;
	int point;
} GAME_BOARD;

GAME_BOARD game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02*BOARD_SIZE_2011144024_rev02] = {0};

typedef struct VERTEX_2011144024_rev02 {
	int color;
	int locate;		// 19 x col + row, 19y + x
	struct VERTEX_2011144024_rev02 *link;
} VERTEX_2011144024_rev02;

typedef struct LINK_HEAD_2011144024_rev02 {
	VERTEX_2011144024_rev02 *head;
} LINK_HEAD_2011144024_rev02;

LINK_HEAD_2011144024_rev02 *link_head_2011144024_rev02 = NULL;
VERTEX_2011144024_rev02 *now_vertex_2011144024_rev02 = NULL;

int now_x_2011144024_rev02 = -1;
int now_y_2011144024_rev02 = -1;
int now_locate_2011144024_rev02 = -1;
char mode_2011144024_rev02 = '\n';		// A, B, C ,D
int turn_2011144024_rev02 = 0;

void reset_point_2011144024_rev02() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev02*BOARD_SIZE_2011144024_rev02; i++) {
		game_board_2011144024_rev02[i].point = 0;
	}
}

void took_stone_2011144024_rev02() {
	if (turn_2011144024_rev02 % 2) (game_board_2011144024_rev02 + now_locate_2011144024_rev02)->color = BLACK;
	else (game_board_2011144024_rev02 + now_locate_2011144024_rev02)->color = WHITE;
}


void catch_mode_2011144024_rev02(int inner_x, int inner_y) {		// East West South North
	if (inner_x < BOARD_MID_2011144024_rev02 && now_y_2011144024_rev02 < BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'A';
	else if (inner_x > BOARD_MID_2011144024_rev02 && now_y_2011144024_rev02 < BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'B';
	else if (inner_x > BOARD_MID_2011144024_rev02 && now_y_2011144024_rev02 > BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'C';
	else if (inner_x < BOARD_MID_2011144024_rev02 && now_y_2011144024_rev02 > BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'D';
	else if (inner_y == BOARD_MID_2011144024_rev02 && inner_x > BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'E';
	else if (inner_y == BOARD_MID_2011144024_rev02 && inner_x < BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'W';
	else if (inner_y > BOARD_MID_2011144024_rev02 && inner_x == BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'S';
	else if (inner_y < BOARD_MID_2011144024_rev02 && inner_x == BOARD_MID_2011144024_rev02) mode_2011144024_rev02 = 'N';
	else mode_2011144024_rev02 = '\n';
}

void catch_xy_2011144024_rev02(int inner_x, int inner_y) {
	now_x_2011144024_rev02 = inner_x;
	now_y_2011144024_rev02 = inner_y;
}

int xy_toLocate_2011144024_rev02(int inner_x, int inner_y) {
	int result = inner_y * 19 + inner_x;
	return result;
}

void insert_link_2011144024_rev02() {
	if (turn_2011144024_rev02 % 2) {
		VERTEX_2011144024_rev02 *data = (VERTEX_2011144024_rev02 *)malloc(sizeof(VERTEX_2011144024_rev02));
		data->color = BLACK;
		data->locate = now_locate_2011144024_rev02;

		if (link_head_2011144024_rev02 == NULL) {
			link_head_2011144024_rev02 = (LINK_HEAD_2011144024_rev02 *)malloc(sizeof(LINK_HEAD_2011144024_rev02));
			data->link = NULL;
			link_head_2011144024_rev02->head = data;
		}
		else {
			data->link = link_head_2011144024_rev02->head;
			link_head_2011144024_rev02->head = data;
		}
	}
	else {
		VERTEX_2011144024_rev02 *data = (VERTEX_2011144024_rev02 *)malloc(sizeof(VERTEX_2011144024_rev02));
		data->color = WHITE;
		data->locate = now_locate_2011144024_rev02;
		
		data->link = link_head_2011144024_rev02->head;
		link_head_2011144024_rev02->head = data;
	}	
}

void marking_pp_2011144024_rev02(int *inner_x, int *inner_y, int length){
	*inner_x = now_x_2011144024_rev02 + length;
	*inner_y = now_y_2011144024_rev02 + length;
}

void marking_pm_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02 + length;
	*inner_y = now_y_2011144024_rev02 - length;
}

void marking_mm_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02 - length;
	*inner_y = now_y_2011144024_rev02 - length;
}

void marking_mp_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02 - length;
	*inner_y = now_y_2011144024_rev02 + length;
}

void marking_zp_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02;
	*inner_y = now_y_2011144024_rev02 + length;
}

void marking_zm_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02;
	*inner_y = now_y_2011144024_rev02 - length;
}

void marking_pz_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02 + length;
	*inner_y = now_y_2011144024_rev02;
}

void marking_mz_2011144024_rev02(int *inner_x, int *inner_y, int length) {
	*inner_x = now_x_2011144024_rev02 - length;
	*inner_y = now_y_2011144024_rev02;
}

void second_side_marking_2011144024_rev02(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev02 == 'A') {
		marking_pp_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'B') {
		marking_mp_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'C') {
		marking_mm_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'D') {
		marking_pm_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'E') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'W') {
		marking_pz_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'S') {
		marking_zm_2011144024_rev02(inner_x, inner_y, 3);
	}
	else if (mode_2011144024_rev02 == 'N') {
		marking_zp_2011144024_rev02(inner_x, inner_y, 3);
	}
	else {
		marking_pz_2011144024_rev02(inner_x, inner_y, 1);
	}
}

void second_mid_marking_2011144024_rev02(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev02 == 'A') {
		marking_pz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'B') {
		marking_zp_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'C') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'D') {
		marking_zm_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'E') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 2);
	}
	else if (mode_2011144024_rev02 == 'W') {
		marking_pz_2011144024_rev02(inner_x, inner_y, 2);
	}
	else if (mode_2011144024_rev02 == 'S') {
		marking_zm_2011144024_rev02(inner_x, inner_y, 2);
	}
	else if (mode_2011144024_rev02 == 'N') {
		marking_zp_2011144024_rev02(inner_x, inner_y, 2);
	}
	else {
		marking_pz_2011144024_rev02(inner_x, inner_y, 1);
	}
}

void second_center_marking_2011144024_rev02(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev02 == 'A') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'B') {
		marking_zp_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'C') {
		marking_pm_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'D') {
		marking_mm_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'E') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'W') {
		marking_pz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'S') {
		marking_mz_2011144024_rev02(inner_x, inner_y, 1);
	}
	else if (mode_2011144024_rev02 == 'N') {
		marking_zp_2011144024_rev02(inner_x, inner_y, 1);
	}
	else {
		marking_pz_2011144024_rev02(inner_x, inner_y, 1);
	}
}

void xClear_2011144024_rev02(int inner_x, int inner_y) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax = 0;
	if (inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax != 0) { xClear_2011144024_rev02(now_x_2011144024_rev02 + 1, inner_y); }
	if (inner_x != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax != 0) { xClear_2011144024_rev02(now_x_2011144024_rev02 - 1, inner_y); }
}

void yClear_2011144024_rev02(int inner_x, int inner_y) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax = 0;
	if (inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax != 0) { yClear_2011144024_rev02(inner_x, inner_y + 1); }
	if (inner_y != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax != 0) { yClear_2011144024_rev02(inner_x, inner_y - 1); }
}

void uClear_2011144024_rev02(int inner_x, int inner_y) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax = 0;
	if (inner_y != BOARD_SIZE_2011144024_rev02 - 1 && inner_x != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax != 0) { uClear_2011144024_rev02(now_x_2011144024_rev02 - 1, inner_y + 1); }
	if (inner_y != 0 && inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax != 0) { uClear_2011144024_rev02(now_x_2011144024_rev02 + 1, inner_y - 1); }
}

void dClear_2011144024_rev02(int inner_x, int inner_y) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax = 0;
	if (inner_y != BOARD_SIZE_2011144024_rev02 - 1 && inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax != 0) { dClear_2011144024_rev02(now_x_2011144024_rev02 + 1, inner_y + 1); }
	if (inner_y != 0 && inner_x != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02].color == game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].color && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax != 0) { dClear_2011144024_rev02(now_x_2011144024_rev02 - 1, inner_y - 1); }
}

void xUnder_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax += 1; if (now_x_2011144024_rev02 - 2 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - 2].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - 2].xMax += 1; if (now_x_2011144024_rev02 - 3 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - 3].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - 3].xMax += 1; if (now_x_2011144024_rev02 - 4 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - 4].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 - 4].xMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 5) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax;
	}
}

void xOver_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax += 1; if (now_x_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 2].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + 2].xMax += 1; if (now_x_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 3].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + 3].xMax += 1; if (now_x_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 4].color != -1 * type) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 + 4].xMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 5) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax;
	}
}

void xBoth_max_updata_2011144024_rev02(int type) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax + game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 3) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 3) xClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 - 2].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 + 2].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].xMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax;
}

void yUnder_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 - 2 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 - 3 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 3].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 - 4 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 4].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 5) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax;
	}
}

void yOver_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 3].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax += 1; if (now_y_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 4].color != -1 * type) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 5) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax;
	}
}

void yBoth_max_updata_2011144024_rev02(int type) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax + game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 3) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 3) yClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].yMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax;
}


void uUnder_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax += 1; if (now_x_2011144024_rev02 - 2 != 0 && now_y_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2 - 2].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax += 1; if (now_x_2011144024_rev02 - 3 != 0 && now_y_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 3 - 3].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax += 1; if (now_x_2011144024_rev02 - 4 != 0 && now_y_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 4 - 4].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 5) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax;
	}
}

void uOver_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax += 1; if (now_x_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 - 2 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2 + 2].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax += 1; if (now_x_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 - 3 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 3 + 3].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax += 1; if (now_x_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 - 4 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 4 + 4].color != -1 * type) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 5) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax;
	}
}

void uBoth_max_updata_2011144024_rev02(int type) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax + game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 3) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 3) uClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2 + 2].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2 - 2].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].uMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax;
}

void dUnder_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax += 1;  if (now_x_2011144024_rev02 - 2 != 0 && now_y_2011144024_rev02 - 2 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2 - 2].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax += 1;  if (now_x_2011144024_rev02 - 3 != 0 && now_y_2011144024_rev02 - 3 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 3 - 3].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax += 1;  if (now_x_2011144024_rev02 - 4 != 0 && now_y_2011144024_rev02 - 4 != 0 && game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 4 - 4].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 5) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax;
	}
}

void dOver_max_update_2011144024_rev02(int type) {
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].color == type && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax != 0) {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 1) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax += 1; if (now_x_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 + 2 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2 + 2].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 2) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax += 1; if (now_x_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 + 3 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 3 + 3].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 3) { game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax += 1; if (now_x_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 + 4 != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 4 + 4].color != -1 * type) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 4) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax += 1;
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 5) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);		// 오목 이상이 발생하면 더 이상 관여하지 않음
		game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax;
	}
}

void dBoth_max_updata_2011144024_rev02(int type) {
	game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax + game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 3) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 3) dClear_2011144024_rev02(now_x_2011144024_rev02, now_y_2011144024_rev02);
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 2 - 2].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 2) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 2 + 2].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax >= 1) game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].dMax = game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax;
}

void max_update_2011144024_rev02() {
	int now_color = (turn_2011144024_rev02 % 2) ? -1 : 1;
	if (now_x_2011144024_rev02 == 0 && now_y_2011144024_rev02 == 0) {
		xOver_max_update_2011144024_rev02(now_color);
		yOver_max_update_2011144024_rev02(now_color);
		dOver_max_update_2011144024_rev02(now_color);
	}
	else if (now_x_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 == 0) {
		xUnder_max_update_2011144024_rev02(now_color);
		yOver_max_update_2011144024_rev02(now_color);
		uUnder_max_update_2011144024_rev02(now_color);
	}
	else if (now_x_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1 && now_y_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1) {
		xUnder_max_update_2011144024_rev02(now_color);
		yUnder_max_update_2011144024_rev02(now_color);
		dUnder_max_update_2011144024_rev02(now_color);
	}
	else if (now_x_2011144024_rev02 == 0 && now_y_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1) {
		xOver_max_update_2011144024_rev02(now_color);
		yUnder_max_update_2011144024_rev02(now_color);
		uOver_max_update_2011144024_rev02(now_color);
	}
	else if (now_y_2011144024_rev02 == 0) {
		xOver_max_update_2011144024_rev02(now_color);
		xUnder_max_update_2011144024_rev02(now_color);
		yOver_max_update_2011144024_rev02(now_color);
		dOver_max_update_2011144024_rev02(now_color);
		uUnder_max_update_2011144024_rev02(now_color);
	}
	else if (now_y_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1) {
		xUnder_max_update_2011144024_rev02(now_color);
		xOver_max_update_2011144024_rev02(now_color);
		yUnder_max_update_2011144024_rev02(now_color);
		dUnder_max_update_2011144024_rev02(now_color);
		uOver_max_update_2011144024_rev02(now_color);
	}
	else if (now_x_2011144024_rev02 == BOARD_SIZE_2011144024_rev02 - 1) {
		xUnder_max_update_2011144024_rev02(now_color);
		yOver_max_update_2011144024_rev02(now_color);
		yUnder_max_update_2011144024_rev02(now_color);
		dUnder_max_update_2011144024_rev02(now_color);
		uUnder_max_update_2011144024_rev02(now_color);
	}
	else if (now_x_2011144024_rev02 == 0) {
		xOver_max_update_2011144024_rev02(now_color);
		yOver_max_update_2011144024_rev02(now_color);
		yUnder_max_update_2011144024_rev02(now_color);
		dOver_max_update_2011144024_rev02(now_color);
		uOver_max_update_2011144024_rev02(now_color);
	}
	else {
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - 1].color == now_color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + 1].color == now_color) xBoth_max_updata_2011144024_rev02(now_color);
		else { xUnder_max_update_2011144024_rev02(now_color); xOver_max_update_2011144024_rev02(now_color); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1].color == now_color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1].color == now_color) yBoth_max_updata_2011144024_rev02(now_color);
		else { yUnder_max_update_2011144024_rev02(now_color); yOver_max_update_2011144024_rev02(now_color); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 + 1].color == now_color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 - 1].color == now_color) dBoth_max_updata_2011144024_rev02(now_color);
		else { uUnder_max_update_2011144024_rev02(now_color); uOver_max_update_2011144024_rev02(now_color); }
		if (game_board_2011144024_rev02[now_locate_2011144024_rev02 - BOARD_SIZE_2011144024_rev02 * 1 - 1].color == now_color && game_board_2011144024_rev02[now_locate_2011144024_rev02 + BOARD_SIZE_2011144024_rev02 * 1 + 1].color == now_color) uBoth_max_updata_2011144024_rev02(now_color);
		else { dUnder_max_update_2011144024_rev02(now_color); dOver_max_update_2011144024_rev02(now_color); }
	}
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax == 0) game_board_2011144024_rev02[now_locate_2011144024_rev02].xMax = 1;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax == 0) game_board_2011144024_rev02[now_locate_2011144024_rev02].yMax = 1;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax == 0) game_board_2011144024_rev02[now_locate_2011144024_rev02].uMax = 1;
	if (game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax == 0) game_board_2011144024_rev02[now_locate_2011144024_rev02].dMax = 1;
}

void insert_xy_2011144024_rev02(int *inner_x, int *inner_y, int x_source, int y_source) {
	*inner_x = BOARD_MID_2011144024_rev02 + x_source;
	*inner_y = BOARD_MID_2011144024_rev02 + y_source;
}

void third_one_length_marking_2011144024_rev02(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev02 == 'A') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 1, 0);
	}
	else if (mode_2011144024_rev02 == 'B') {
		insert_xy_2011144024_rev02(inner_x, inner_y, -1, 0);
	}
	else if (mode_2011144024_rev02 == 'C') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 0, -1);
	}
	else if (mode_2011144024_rev02 == 'D') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 0, -1);
	}
	else if (mode_2011144024_rev02 == 'E') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 1, 1);
	}
	else if (mode_2011144024_rev02 == 'W') {
		insert_xy_2011144024_rev02(inner_x, inner_y, -1, -1);
	}
	else if (mode_2011144024_rev02 == 'S') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 1, 1);
	}
	else if (mode_2011144024_rev02 == 'N') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 1, -1);
	}
}

void third_two_length_marking_2011144024_rev02(int *inner_x, int *inner_y) {
	if (mode_2011144024_rev02 == 'A') {
		if (BOARD_MID_2011144024_rev02 - now_x_2011144024_rev02 > BOARD_MID_2011144024_rev02 - now_y_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 0, 1);
		else if (BOARD_MID_2011144024_rev02 - now_x_2011144024_rev02 < BOARD_MID_2011144024_rev02 - now_y_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 1, 0);
		else insert_xy_2011144024_rev02(inner_x, inner_y, 1, -1);
	}
	else if (mode_2011144024_rev02 == 'B') {
		if (now_x_2011144024_rev02 - BOARD_MID_2011144024_rev02 > BOARD_MID_2011144024_rev02 - now_y_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 0, 1);
		else if (now_x_2011144024_rev02 - BOARD_MID_2011144024_rev02 < BOARD_MID_2011144024_rev02 - now_y_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, -1, 0);
		else insert_xy_2011144024_rev02(inner_x, inner_y, -1, -1);
	}
	else if (mode_2011144024_rev02 == 'C') {
		if (now_x_2011144024_rev02 - BOARD_MID_2011144024_rev02 > now_y_2011144024_rev02 - BOARD_MID_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, -1, 0);
		else if (now_x_2011144024_rev02 - BOARD_MID_2011144024_rev02 < now_y_2011144024_rev02 - BOARD_MID_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 0, -1);
		else insert_xy_2011144024_rev02(inner_x, inner_y, -1, 1);
	}
	else if (mode_2011144024_rev02 == 'D') {
		if (BOARD_MID_2011144024_rev02 - now_x_2011144024_rev02 > now_y_2011144024_rev02 - BOARD_MID_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 1, 0);
		else if (BOARD_MID_2011144024_rev02 - now_x_2011144024_rev02 < now_y_2011144024_rev02 - BOARD_MID_2011144024_rev02) insert_xy_2011144024_rev02(inner_x, inner_y, 0, -1);
		else insert_xy_2011144024_rev02(inner_x, inner_y, 1, 1);
	}
	else if (mode_2011144024_rev02 == 'E') {
		insert_xy_2011144024_rev02(inner_x, inner_y, -2, 0);
	}
	else if (mode_2011144024_rev02 == 'W') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 2, 0);
	}
	else if (mode_2011144024_rev02 == 'S') {
		insert_xy_2011144024_rev02(inner_x, inner_y, -2, 0);
	}
	else if (mode_2011144024_rev02 == 'N') {
		insert_xy_2011144024_rev02(inner_x, inner_y, 0, 2);
	}
}

void attack_four_check_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].xMax == 4) {
			if (inner_x != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].point += 1000;
			if (inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].point += 1000;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].yMax == 4) {
			if (inner_y != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].point += 1000;
			if (inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].point += 1000;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].uMax == 4) {
			if (inner_y != 0 && inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].point += 1000;
			if (inner_x != 0 && inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].point += 1000;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].dMax == 4) {
			if (inner_y != 0 && inner_x != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].point += 1000;
			if (inner_x != BOARD_SIZE_2011144024_rev02 - 1 && inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].point += 1000;
		}
	}
}

void shield_four_check_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].xMax == 4) {
			if (inner_x != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].point += 999;
			if (inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].point += 999;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].yMax == 4) {
			if (inner_y != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].point += 999;
			if (inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].point += 999;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].uMax == 4) {
			if (inner_y != 0 && inner_x != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].point += 999;
			if (inner_x != 0 && inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].point += 999;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].dMax == 4) {
			if (inner_y != 0 && inner_x != 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].point += 999;
			if (inner_x != BOARD_SIZE_2011144024_rev02 - 1 && inner_y != BOARD_SIZE_2011144024_rev02 - 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].point += 999;
		}
	}
}

int check_between_2011144024_rev02(int A, int B, int type) {
	if (A == type && B == type) return 1;
	return 0;
}

int black_three_check_2011144024_rev02(int inner_x, int inner_y, int type) {
	int three_count = -1;
	if (inner_x == 0) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_y < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
	}
	else if (inner_x == BOARD_SIZE_2011144024_rev02 - 1) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_y < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
	}
	else if (inner_y == 0) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_x < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
	}
	else if (inner_y == BOARD_SIZE_2011144024_rev02 - 1) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
		if (inner_x < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		}
	}
	else {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 200; three_count += 1; }
		
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 2) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].xMax == 1) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 2) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 1) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 2) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 1) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 2) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 1) { game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 201; three_count += 1; }
		}
	}
	if (three_count > 0) {
		return 1;
	}
	else {
		return 0;
	}

}

void white_three_check_2011144024_rev02(int inner_x, int inner_y, int type) {

	if (inner_x == 0) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_y < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
	}
	else if (inner_x == BOARD_SIZE_2011144024_rev02 - 1) {
		if (inner_y > 3 && inner_y < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_y > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_y < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
	}
	else if (inner_y == 0) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_x < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
	}
	else if (inner_y == BOARD_SIZE_2011144024_rev02 - 1) {
		if (inner_x > 3 && inner_x < BOARD_SIZE_2011144024_rev02 - 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_x > 4) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
		if (inner_x < BOARD_SIZE_2011144024_rev02 - 5) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		}
	}
	else {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 3 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 198;

		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 2) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].xMax == 1) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 2) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 1) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 2) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 1) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
		}
		if (check_between_2011144024_rev02(game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color, game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color, type)) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 2) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 1) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 199;
		}
	}
}

int center_point_update_2011144024_rev02(int inner_x, int inner_y) {
	int result_x = BOARD_MID_2011144024_rev02 - inner_x;
	int result_y = BOARD_MID_2011144024_rev02 - inner_y;
	result_x = (result_x > 0) ? result_x : -1 * result_x;
	result_y = (result_y > 0) ? result_y : -1 * result_y;
	
	if (result_x > result_y) {
		return BOARD_MID_2011144024_rev02 - result_x;
	}
	else {
		return BOARD_MID_2011144024_rev02 - result_y;
	}
}

int change_absolute_value_2011144024_rev02(int target) {
	return (target > 0) ? target : -1 * target;
}

void new_three_attack_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].xMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].point += 20;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 2].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].point += 20;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].yMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].point += 20;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].point += 20;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].uMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].point += 20;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].point += 20;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].dMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].point += 20;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].point += 20;
	}
}

void new_three_shield_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].xMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].point += 15;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 2].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].point += 15;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].yMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].point += 15;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].point += 15;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].uMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].point += 15;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].point += 15;
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].dMax == 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x - 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].point += 15;
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x + 2].color == -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].point += 15;
	}
}

void new_three_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == type) new_three_attack_making_2011144024_rev02(inner_x, inner_y, type);
	else if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == -1 * type) new_three_shield_making_2011144024_rev02(inner_x, inner_y, -1 * type);
}

void empty_space_three_attack_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 21;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 21;
		}
	}
}

void empty_space_three_shield_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 19;
		}
	}
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].dMax == 1 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == type) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x + 2].color == 0 || game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x - 2].color == 0) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += 19;
		}
	}
}

void empty_space_three_making_2011144024_rev02(int inner_x, int inner_y, int type) {
	empty_space_three_attack_making_2011144024_rev02(inner_x, inner_y, type);
	empty_space_three_shield_making_2011144024_rev02(inner_x, inner_y, -1 * type);
}

void new_shape_making_2011144024_rev02(int inner_x, int inner_y, int x_shift, int y_shift, int type) {
	if (y_shift == 0) {
		if (x_shift == 1 || x_shift == -1) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 1) + inner_x + x_shift].color == 0) {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 2) + inner_x + x_shift].color != -1 * type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 2) + inner_x + x_shift + x_shift].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 20;
				}
			}
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 1) + inner_x + x_shift].color == 0) {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 2) + inner_x + x_shift].color != -1 * type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 2) + inner_x + x_shift + x_shift].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 20;
				}
			}
		}
		else if (x_shift == 2 || x_shift == -2) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 1) + inner_x + x_shift].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + (x_shift / 2)].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift - 1) + inner_x + x_shift].point += 10;
			}
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 1) + inner_x + x_shift].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + (x_shift / 2)].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + 1) + inner_x + x_shift].point += 10;
			}
		}
	}
	else if (x_shift == 0) {
		if (y_shift == 1 || y_shift == -1) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 1].color == 0) {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 2].color != -1 * type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + y_shift) + inner_x + x_shift - 2].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 20;
				}
			}
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 1].color == 0) {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 2].color != -1 * type && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift + y_shift) + inner_x + x_shift + 2].color != -1 * type) {	// 막혀있지 않을 경우
					game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 20;
				}
			}
		}
		else if (x_shift == 2 || x_shift == -2) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 1].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift - 1].point += 10;
			}
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 1].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift + 1].point += 10;
			}
		}
		else if (x_shift == y_shift || x_shift == -1 * y_shift) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 2) + inner_x + x_shift * 2].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 3) + inner_x + x_shift * 3].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 2) + inner_x + x_shift * 2].point += 30;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 2) + inner_x].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 2) + inner_x].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift * 2) + inner_x].point += 10;
			}
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift * 2].color == 0) {
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift * 2].point += 25;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift].color != -1 * type) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift * 2].point += 10;
			}
		}
		else {
			if (change_absolute_value_2011144024_rev02(x_shift) > change_absolute_value_2011144024_rev02(x_shift)) {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift / 2].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift / 2].point += 10;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift / 2].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + x_shift / 2].point += 10;
			}
			else {
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x + x_shift].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x + x_shift].point += 10;
				if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x].color == 0) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift / 2) + inner_x].point += 10;
			}
		}
	}
}

void raise_point_use_XY_2011144024_rev02(int inner_x, int inner_y, int x_shift, int y_shift, int raise, int type) {
	if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift].color == 0) {
		game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift].point += raise;
	}
	else if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + y_shift) + inner_x + x_shift].color == type) {
		new_shape_making_2011144024_rev02(inner_x, inner_y, x_shift, y_shift, type);
	}
}

void near_by_same_color_point_update_2011144024_rev02(int inner_x, int inner_y, int type) {
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 0, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, -1, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, 0, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, 1, 3, type);

	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -1, 8, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, -1, 8, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, 1, 8, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 1, 8, type);

	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, -1, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -2, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 2, -1, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, -2, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, -1, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -2, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, 1, 4, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 2, 4, type);
	
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, 0, 9, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, -2, 9, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 2, 0, 9, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, 2, 9, type);
}

void near_by_other_color_point_update_2011144024_rev02(int inner_x, int inner_y, int type) {
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 0, 2, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, -1, 2, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, 0, 2, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, 1, 2, type);

	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -1, 6, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, -1, 6, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, 1, 6, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 1, 6, type);

	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, -1, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -2, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 2, -1, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 1, -2, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, -1, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, -2, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, 1, 3, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -1, 2, 3, type);

	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, -2, 0, 7, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, -2, 7, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 2, 0, 7, type);
	raise_point_use_XY_2011144024_rev02(inner_x, inner_y, 0, 2, 7, type);
}

void near_by_point_update_2011144024_rev02(int x, int y, int type) {
	if (x > 2 && x < BOARD_SIZE_2011144024_rev02 - 3 && y > 2 && y < BOARD_SIZE_2011144024_rev02 - 3) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * y + x].color == type) near_by_same_color_point_update_2011144024_rev02(x, y, type);
		else if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * y + x].color == -1 * type) near_by_other_color_point_update_2011144024_rev02(x, y, -1 * type);
	}
}

void point_update_white_2011144024_rev02() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev02; i++) {
		for (int j = 0;  j< BOARD_SIZE_2011144024_rev02; j++) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].color == 0) {
				white_three_check_2011144024_rev02(j, i, WHITE);
				black_three_check_2011144024_rev02(j, i, BLACK);
				empty_space_three_making_2011144024_rev02(j, i, WHITE);
			}
			else {
				attack_four_check_2011144024_rev02(j, i, WHITE);
				shield_four_check_2011144024_rev02(j, i, BLACK);
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * j + i].point += center_point_update_2011144024_rev02(j, i);
				near_by_point_update_2011144024_rev02(j, i, WHITE);
				new_three_making_2011144024_rev02(j, i, WHITE);
			}
		}
	}
}

void escape_foul_black_turn_2011144024_rev02(int inner_x, int inner_y) {
	int foul_count = 0;
	if (inner_x > 1 && inner_x < BOARD_SIZE_2011144024_rev02 - 2 && inner_y > 1 && inner_y < BOARD_SIZE_2011144024_rev02 - 2) {
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == BLACK) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 2].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 2].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color == BLACK) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color == BLACK) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x + 2].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x - 2].color == 0) foul_count += 1;
		}
		if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color == BLACK) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 2) + inner_x - 2].color == 0 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 2) + inner_x + 2].color == 0) foul_count += 1;
		}
		if (inner_x > 2 && inner_x < BOARD_SIZE_2011144024_rev02 - 3 && inner_y > 2 && inner_y < BOARD_SIZE_2011144024_rev02 - 3) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 1].xMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x - 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].color == BLACK && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 1].xMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x].yMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 3) + inner_x].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x].yMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 3) + inner_x].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x + 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 3) + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 3) + inner_x - 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 1) + inner_x + 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y + 3) + inner_x + 3].color == 0) foul_count += 1;
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].color && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 1) + inner_x - 1].uMax == 2 && game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * (inner_y - 3) + inner_x - 3].color == 0) foul_count += 1;
		}
	}
	if (foul_count > 1) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * inner_y + inner_x].point += -1000;
}

void point_update_black_2011144024_rev02() {
	for (int i = 0; i < BOARD_SIZE_2011144024_rev02; i++) {
		for (int j = 0; j < BOARD_SIZE_2011144024_rev02; j++) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].color == 0) {
				white_three_check_2011144024_rev02(j, i, BLACK);
				if (black_three_check_2011144024_rev02(j, i, WHITE)) game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].point = 0;
				empty_space_three_making_2011144024_rev02(j, i, BLACK);
				escape_foul_black_turn_2011144024_rev02(j, i);
			}
			else {
				attack_four_check_2011144024_rev02(j, i, BLACK);
				shield_four_check_2011144024_rev02(j, i, WHITE);
				game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * j + i].point += center_point_update_2011144024_rev02(j, i);
				near_by_point_update_2011144024_rev02(j, i, BLACK);
				new_three_making_2011144024_rev02(j, i, BLACK);
			}
		}
	}
}

void max_point_xy_locate_return_2011144024_rev02(int *target_x, int *target_y) {
	int max_point = -1;
	int x, y;
	for (int i = 0; i < BOARD_SIZE_2011144024_rev02; i++) {
		for (int j = 0; j < BOARD_SIZE_2011144024_rev02; j++) {
			if (game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].color == 0) {
				if (max_point < game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].point) {
					max_point = game_board_2011144024_rev02[BOARD_SIZE_2011144024_rev02 * i + j].point;
					x = j;
					y = i;
				}
			}
			
		}
	}
	*target_x = x;
	*target_y = y;
}

void WhiteAttack_2011144024_rev02(int *inner_x, int *inner_y)
{
	// 3x3 가능, 4x4 가능, 6목 가능하되 승패 영향x
	max_update_2011144024_rev02();

	turn_2011144024_rev02 += 1;

	int white_x, white_y;

	if (turn_2011144024_rev02 == 2) {
		if (now_x_2011144024_rev02 < 3 || now_y_2011144024_rev02 < 3 || now_x_2011144024_rev02 >= BOARD_SIZE_2011144024_rev02 - 3 || now_x_2011144024_rev02 >= BOARD_SIZE_2011144024_rev02 - 3) {
			second_side_marking_2011144024_rev02(&white_x, &white_y);
		}
		else if (now_x_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 1 && now_x_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 1 && now_y_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 1 && now_y_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 1) {
			second_center_marking_2011144024_rev02(&white_x, &white_y);
		}
		else {
			second_mid_marking_2011144024_rev02(&white_x, &white_y);
		}
	}
	else {
		reset_point_2011144024_rev02();
		point_update_white_2011144024_rev02();
		max_point_xy_locate_return_2011144024_rev02(&white_x, &white_y);
	}

	*inner_x = white_x;
	*inner_y = white_y;
	now_locate_2011144024_rev02 = BOARD_SIZE_2011144024_rev02 * white_y + white_x;

	if (mode_2011144024_rev02 == '\n') catch_mode_2011144024_rev02(white_x, white_y);

	insert_link_2011144024_rev02();		// locate 값 저장
	took_stone_2011144024_rev02();
}
void WhiteDefence_2011144024_rev02(int inner_x, int inner_y)
{
	//흰돌 1
	//검은돌 -1

	turn_2011144024_rev02 += 1;

	catch_xy_2011144024_rev02(inner_x, inner_y);
	now_locate_2011144024_rev02 = xy_toLocate_2011144024_rev02(inner_x, inner_y);
	
	insert_link_2011144024_rev02(); 
	took_stone_2011144024_rev02();
}
void AttackBlack_2011144024_rev02(int *inner_x, int *inner_y)
{
	// 3x3, 4x4, 6목 불가
	if (turn_2011144024_rev02 != 0) max_update_2011144024_rev02();

	turn_2011144024_rev02 += 1;

	int black_x, black_y;

	if (turn_2011144024_rev02 == 1) { now_locate_2011144024_rev02 = 180; black_x = 9; black_y = 9; }
	else if (turn_2011144024_rev02 == 3) {
		if (now_x_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 1 && now_x_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 1 && now_y_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 1 && now_y_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 1) {
			third_one_length_marking_2011144024_rev02(&black_x, &black_y);
		}
		else if (now_x_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 2 && now_x_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 2 && now_y_2011144024_rev02 >= BOARD_MID_2011144024_rev02 - 2 && now_y_2011144024_rev02 <= BOARD_MID_2011144024_rev02 - 2) {
			third_two_length_marking_2011144024_rev02(&black_x, &black_y);
		}
		else {
			reset_point_2011144024_rev02();
			point_update_black_2011144024_rev02();
			max_point_xy_locate_return_2011144024_rev02(&black_x, &black_y);
		}
	}
	else {
		reset_point_2011144024_rev02();
		point_update_black_2011144024_rev02();
		max_point_xy_locate_return_2011144024_rev02(&black_x, &black_y);
	}
	


	*inner_x = black_x;
	*inner_y = black_y;
	now_locate_2011144024_rev02 = BOARD_SIZE_2011144024_rev02 * black_y + black_x;

	insert_link_2011144024_rev02();		// locate 값 저장
	took_stone_2011144024_rev02();
}
void DefenceBlack_2011144024_rev02(int x, int y)
{
	//흰돌 1
	//검은돌 -1

	turn_2011144024_rev02 += 1;
	
	if (mode_2011144024_rev02 == '\n') catch_mode_2011144024_rev02(x, y);
	catch_xy_2011144024_rev02(x, y);
	now_locate_2011144024_rev02 = xy_toLocate_2011144024_rev02(x, y);
	
	insert_link_2011144024_rev02();
	took_stone_2011144024_rev02();
}


