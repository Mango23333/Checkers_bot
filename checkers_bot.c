#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

#define BOARD_SIZE 8       // board size
#define ROWS_WITH_PIECES 3 // number of initial rows with pieces
#define CELL_EMPTY '.'     // empty cell character
#define CELL_BPIECE 'b'    // black piece character
#define CELL_WPIECE 'w'    // white piece character
#define CELL_BTOWER 'B'    // black tower character
#define CELL_WTOWER 'W'    // white tower character
#define COST_PIECE 1       // one piece cost
#define COST_TOWER 3       // one tower cost
#define TREE_DEPTH 3       // minimax tree depth
#define COMP_ACTIONS 10    // number of computed actions



#define TRUE 1
#define FALSE 0
#define B_TURN 1
#define W_TURE 0
#define NUM_B 12
#define NUM_W 12
#define WHITE_ROW_MIN 0
#define BLACK_ROW_MIN 5
#define EMPTY_ROW_MIN 3
#define EMPTY_ROW_MAX 5
#define COL_MIN 0
#define EVEN_CHECK 2
#define EVEN_REMAINDER 0

/*different between black source piece and target position's column by move*/
#define DBBSPTCM 1

/*different between black source piece and target position's column by capture*/
#define DBBSPTCC 2

/*different between white source piece and target position's column by move*/
#define DBWSPTCM -1

/*different between white source piece and target position's column by capture*/
#define DBWSPTCC -2

/*difference between board index number and ascii number of board letter*/
#define DBBA 65

/*difference between an integer and it's corresponding ascii number*/
#define DBIA 48

/*difference between row number and index of row number*/
#define DBRI 1

#define ROW_SEPARATOR "+---+---+---+---+---+---+---+---+"
#define LINE_SEPARATOR '|'
#define SECTION_SEPARATOR "====================================="
#define ERRORSOB "ERROR: Source cell is outside of the board."
#define ERRORTOB "ERROR: Target cell is outside of the board."
#define ERRORSE "ERROR: Source cell is empty."
#define ERRORTNE "ERROR: Target cell is not empty."
#define ERRORSOP "ERROR: Source cell holds opponent's piece/tower."
#define ERRORIA "ERROR: Illegal action."

/*for target or source cell, the index of it's column*/
#define CCI 0

/*for target or source cell, the index of it's row*/
#define CRI 1

/*for an input, the source cell's starting index*/
#define LINESS 0

/*for an input, the source cell's ending index*/
#define LINESE 2

/*for an input, the target cell's starting index*/
#define LINETS 3

/*size of each cell*/
#define SOC 2

/*size of a null character*/
#define SONULL 1

#define CELL_MIN "A1"
#define CELL_MAX "H8"

/*index of the row black piece will change to black tower*/
#define BPTTR 0

/*index of the row white piece will change to white tower*/
#define WPTTR 7

/*divide this to find the medium of a number*/
#define MIDDLE_DIVIDER 2

#define ACTION_MAXLEN 5 
#define SPEC_ACTION_LEN 1
#define SPEC_ACTION_IND 0
#define STRING_RES_INDEX 0

/*machine operation indicator*/
#define MOI "***"

#define INITIAL_DEPTH 1

/*next depth is found by adding this*/
#define NEXT_DEPTH 1

/*next turn is found by adding this*/
#define NEXT_TURN 1

#define ACTION 'A'
#define ACTION10 'P'

/*assign this value to variable if the variable will not be used, or just been
initialized.*/
#define NIU -100


/******************************************************************************/
typedef unsigned char board_t[BOARD_SIZE][BOARD_SIZE];
typedef struct operation operation_t;


typedef struct
{
	char source_cci;
	char source_cri;
	char target_cci;
	char target_cri;
}action_t;


struct operation
{
	board_t cu_board;
	action_t action;
	int cu_boardcost;
	operation_t *next;
	operation_t *nextlv;
};


/******************************************************************************/


void board_fill(board_t board, int start, char input_piece, int empty_line);
void board_setup(board_t board);
void print_board(board_t board);
int board_cost(board_t board);
void error_sourceoboard(char source[]);
void error_targetoboard(char target[]);
void error_sourceempty(board_t board, char source[]);
void error_targetnempty(board_t board, char target[]);
void error_sourceop(board_t board, char source[], int cu_turn);
void error_ia(board_t board, char source[], char target[], int cu_turn);
int error_ia_black(board_t board, char source[], char target[]);
int error_ia_white(board_t board, char source[], char target[]);
void board_action_check(board_t board, char source[], char target[], int turn);
void board_actions_change_cells(board_t board, char source[], char target[]);
void board_actions_towerchange(board_t board);
void board_actions_cells(board_t board, char source[], char target[]);
void board_actionsfrominput(board_t board);
void board_operation(board_t board, char line[], int turns);
void board_initial_print(board_t board);
void board_action_print(board_t board, char source[], char target[], int turns,
int is_machine);
operation_t *find_move_wtower_NE(board_t board, int row, int col,
char source[], char target[], operation_t *operats);
operation_t *find_move_wtower_NW(board_t board, int row, int col,
char source[], char target[], operation_t *operats);
operation_t *find_move_white(board_t board, int row, int col, char source[],
char target[], operation_t *operats);
operation_t *find_move_btower_sesw(board_t board, int row, int col, 
char source[], char target[], operation_t *operats);
operation_t *find_move_black(board_t board, int row, int col, char source[],
char target[], operation_t *operats);
operation_t *fill_position(int row, int col, int target_r, int target_c,
char source[], char target[], operation_t *operats, board_t board);
void form_line(char source[], char target[], char line[]);
void board_cpy(board_t ori_board, board_t new_board);
operation_t *fill_operation(char source[], char target[],
operation_t *operation, board_t board);
void fill_all_operations(board_t board, operation_t *operations, int turn);
void tree_create(operation_t *operations, int turn, int cu_depth, int depth);
operation_t *fill_nextlv_operation(void);
operation_t *fill_l0_operation(board_t board);
void self_operation_a(board_t board, int turns);
void find_action(operation_t *operats, char source[], char target[]);
void fill_bcost_td3(operation_t *operats, int turn);
void free_tree_same_lv(operation_t *operats);
void free_tree_depth3(operation_t *operats);
int find_max_boardcost(operation_t *operats, int turn);
void self_operation_p(board_t board, int turns, int amount);


/******************************************************************************/
/******************************************************************************/


int main(int argc, char *argv[])
{
	board_t board;
	board_setup(board);

	/*All operation control*/
	board_actionsfrominput(board);
	return EXIT_SUCCESS; // exit program with the success code
}


/******************************************************************************/


/*This function takes a board_t type board. It operate the board base on input,
and print all the operations.*/
void board_actionsfrominput(board_t board)
{
	int action = 0, i = 0;
	char current, cu_action[ACTION_MAXLEN + SONULL];

	board_initial_print(board);
	while ((current = getchar()) != EOF)
	{
		if (current == '\n')
		{
			cu_action[i] = '\0';
			i = 0;
			action += NEXT_TURN;

			/*Actions from input*/
			if (strlen(cu_action) == ACTION_MAXLEN)
			{
				board_operation(board, cu_action, action);
			}
			/*Machine action*/
			else if(strlen(cu_action) == SPEC_ACTION_LEN)
			{
				/*If input is 'A'*/
				if (cu_action[SPEC_ACTION_IND] == ACTION)
				{
					self_operation_a(board, action);
				}
				/*If input is 'P'*/
				else if (cu_action[SPEC_ACTION_IND] == ACTION10)
				{
					self_operation_p(board, action, COMP_ACTIONS);
				}
			}
			else
			{
				printf("Input not recognised.");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			cu_action[i] = current;
			i++;
		}

	}
}


/*This function takes a board_t type board, an integer turns, and an integer
amount. It will let the algorithm operates the board base on 'amount' of times*/
void self_operation_p(board_t board, int turns, int amount)
{
	int i;
	for (i = 0; i < amount; i++)
	{
		self_operation_a(board, turns);
		turns++;
	}
}


/*This function takes a board_t type board and an integer turns. It will print
out the next action on the board and also change the board. If no action can be
taken, base on the turn, a winner can be announced. The program will exit if
an winner is announced.*/
void self_operation_a(board_t board, int turns)
{
	operation_t *operats;
	char source[SOC + SONULL] = CELL_MIN, target[SOC + SONULL] = CELL_MIN;

	/*Try to find an action*/
	operats = fill_l0_operation(board);
	tree_create(operats, turns, INITIAL_DEPTH, TREE_DEPTH);
	fill_bcost_td3(operats, turns);
	find_action(operats, source, target);
	free_tree_depth3(operats);

	/*An action has been found.*/
	if (strlen(source) == SOC && strlen(target) == SOC)
	{
		board_actions_cells(board, source, target);
		board_action_print(board, source, target, turns, TRUE);
	}
	/*No action is found, a winner can be announced.*/
	else
	{
		if (turns % EVEN_CHECK == EVEN_REMAINDER)
		{
			printf("BLACK WIN!\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("WHITE WIN!\n");
			exit(EXIT_SUCCESS);
		}
	}
}


/*This function takes a pointer of an operation_t type operats and an integer
turn. It will fill the first and second depth of tree with the required board 
cost base on the turn. */
void fill_bcost_td3(operation_t *operats, int turn)
{
	operation_t *templ1, *templ2, *templ3;
	int l1, l2, l3;

	templ1 = operats -> nextlv -> next;
	while (templ1 != NULL)
	{
		templ2 = templ1 -> nextlv -> next;

		while (templ2 != NULL)
		{
			templ3 = templ2 -> nextlv -> next;

			/*find max or min l3*/
			l3 = find_max_boardcost(templ3, turn + NEXT_DEPTH + NEXT_DEPTH);
			if (l3 != NIU)
			{
				templ2 -> cu_boardcost = l3;
			}
			templ2 = templ2 -> next;
		}
		templ2 = templ1 -> nextlv -> next;

		l2 = find_max_boardcost(templ2, turn + NEXT_DEPTH);
		if (l2 != NIU)
		{
			templ1 -> cu_boardcost = l2;
		}
		templ1 = templ1 -> next;
	}
	templ1 = operats -> nextlv -> next;

	l1 = find_max_boardcost(templ1, turn);
	if (l1 != NIU)
	{
		operats -> cu_boardcost = l1;
	}
}


/*This function takes a pointer of an operation_t type operats and an integer
turn. It will base on the turn find the corresponding maximum or minimun board 
cost. It will also return the board cost.*/
int find_max_boardcost(operation_t *operats, int turn)
{
	int max_cost = NIU;

	/*Initialize the cost with the first item of the linked list.*/
	if (operats != NULL)
	{
		max_cost = operats -> cu_boardcost;
	}

	while (operats != NULL)
	{
		/*white's turn, find minimum cost*/
		if (turn % EVEN_CHECK == EVEN_REMAINDER)
		{
			if (operats -> cu_boardcost < max_cost &&
			operats -> cu_boardcost != NIU)
			{
				max_cost = operats -> cu_boardcost;
			}
		}
		/*black's turn, find max cost*/
		else
		{
			if (operats -> cu_boardcost > max_cost)
			{
				max_cost = operats -> cu_boardcost;
			}
		}
		operats = operats -> next;
	}
	return max_cost;
}


/*This function takes a pointer of an operation_t type operats, a string source
and a string target. It will find the required board cost and it's 
corresponding action and store it in source and target. If no action can be
taken, it will only store a NULL character in the string.*/
void find_action(operation_t *operats, char source[], char target[])
{
	operation_t *temp;

	temp = operats -> nextlv -> next;
	while (temp != NULL)
	{
		if (temp -> cu_boardcost == operats -> cu_boardcost)
		{
			break;
		}
		temp = temp -> next;
	}

	if (temp != NULL)
	{
		source[CCI] = temp -> action.source_cci;
		source[CRI] = temp -> action.source_cri;
		source[CRI + SONULL] = '\0';
		target[CCI] = temp -> action.target_cci;
		target[CRI] = temp -> action.target_cri;
		target[CRI + SONULL] = '\0';
	}
	else
	{
		source[CCI] = '\0';
		target[CCI] = '\0';
	}
}


/*This function takes a board_t type board. It will allocate memory for the
root of operation_t with the board. It will return a pointer pointing at the
location storing the root.*/
operation_t *fill_l0_operation(board_t board)
{
    operation_t *operats;

	operats = (operation_t *)malloc(sizeof(*operats));
	board_cpy(board, operats -> cu_board);
	operats -> cu_boardcost = NIU;
	operats -> next = operats -> nextlv = NULL;
	return operats;
}


/*This function takes a pointer to an operation_t type operation, an integer
turn, an integer current_depth, and an integer max depth. It will create a tree
that stores all the possible moves that can be done for the next three steps.*/
void tree_create(operation_t *operations, int turn, int cu_depth, int depth)
{
	operation_t *temp;

	if (cu_depth <= depth)
	{
		temp = fill_nextlv_operation();
		fill_all_operations(operations -> cu_board, temp, turn);
		operations -> nextlv = temp;

		while (temp != NULL)
		{
			tree_create(temp, turn + NEXT_TURN, cu_depth + NEXT_DEPTH, depth);
			temp = temp -> next;
		}

	}
}


/*This function will allocate memory for a next lv operation_t and return the
pointer pointing at the operation_t.*/
operation_t *fill_nextlv_operation(void)
{
	operation_t *operats;

	operats = (operation_t *)malloc(sizeof(*operats));
	operats -> cu_boardcost = NIU;
	operats -> next = operats -> nextlv = NULL;
	return operats;
}


/*This function takes a pointer to an operation_t type operats. It will free 
all the space a depth 3 linked list is taking.*/
void free_tree_depth3(operation_t *operats)
{
	operation_t *temp1, *temp2;

	temp1 = operats -> nextlv;
	temp2 = temp1 -> nextlv;

	while (temp1 != NULL)
	{
		while (temp2 != NULL)
		{
			free_tree_same_lv(temp2 -> nextlv);
			temp2 = temp2 -> next;
		}
		free_tree_same_lv(temp1 -> nextlv);
		temp1 = temp1 -> next;
	}
	free_tree_same_lv(operats -> nextlv);
	free(operats);
}


/*This functino takes a pointer to an operation_t type operats. It will free
all the space current linked list is taking(same level).*/
void free_tree_same_lv(operation_t *operats)
{
	operation_t *next_op;
	if (operats != NULL)
	{
		next_op = operats -> next;
		free(operats);
		free_tree_same_lv(next_op);
	}
}


/*This function takes a board_t type board, a pointer to an operation_t type
operations, an integer turn. It will base on the turn fill the 
operations(linked list) with all possible actions.*/
void fill_all_operations(board_t board, operation_t *operations, int turn)
{
	int i, j;
	char source[SOC + SONULL] = CELL_MIN, target[SOC + SONULL] = CELL_MIN;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			/*reset strings*/
			source[STRING_RES_INDEX] = '\0';
			target[STRING_RES_INDEX] = '\0';

			if (turn % EVEN_CHECK == B_TURN)
			{
				operations = find_move_black(board, i, j, source, target,
				operations);
			}
			else
			{
				operations = find_move_white(board, i, j, source, target,
				operations);
			}
		}
	}
}


/*This function takes a board_t type board, an integer row, and integer column,
a string source, a string target and an a pointer to operation_t type operats. 
It will try to find all action possible for black checkers. All action will be
recorded in the operats and base on the direction start from North-east and
turn clockwise. It will return a pointer pointing at operats.*/
operation_t *find_move_black(board_t board, int row, int col, char source[],
char target[], operation_t *operats)
{
	int target_r, target_c;

	/*check North-east direction move*/
	if (board[row][col] == CELL_BPIECE || board[row][col] == CELL_BTOWER)
	{
		if (board[row - DBBSPTCM][col + DBBSPTCM] == CELL_EMPTY &&
		(row - DBBSPTCM >= COL_MIN && row - DBBSPTCM < BOARD_SIZE && 
		col + DBBSPTCM >= COL_MIN && col + DBBSPTCM < BOARD_SIZE))
		{
			target_r = row - DBBSPTCM;
			target_c = col + DBBSPTCM;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}

		/*check North-east direction move*/
		if (board[row - DBBSPTCC][col + DBBSPTCC] == CELL_EMPTY &&
		(row - DBBSPTCC >= COL_MIN && row - DBBSPTCC < BOARD_SIZE && 
		col + DBBSPTCC >= COL_MIN && col + DBBSPTCC < BOARD_SIZE))
		{
			if (board[row - (DBBSPTCC / MIDDLE_DIVIDER)]
				[col + (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WPIECE ||
				board[row - (DBBSPTCC / MIDDLE_DIVIDER)]
				[col + (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WTOWER)
			{
				target_r = row - DBBSPTCC;
				target_c = col + DBBSPTCC;
				operats = fill_position(row, col, target_r, target_c, source,
				target, operats, board);
			}
		}

		/*South-east and South-west direction actions can only be done on black
		tower.*/
		if (board[row][col] == CELL_BTOWER)
		{
			operats = find_move_btower_sesw(board, row, col, source, target,
			operats);
		}

		/*check North-west move*/
		if (board[row - DBBSPTCM][col - DBBSPTCM] == CELL_EMPTY &&
		(row - DBBSPTCM >= COL_MIN && row - DBBSPTCM < BOARD_SIZE && 
		col - DBBSPTCM >= COL_MIN && col - DBBSPTCM < BOARD_SIZE))
		{
			target_r = row - DBBSPTCM;
			target_c = col - DBBSPTCM;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}
		
		/*check North_west move*/
		if (board[row - DBBSPTCC][col - DBBSPTCC] == CELL_EMPTY &&
		(row - DBBSPTCC >= COL_MIN && row - DBBSPTCC < BOARD_SIZE && 
		col - DBBSPTCC >= COL_MIN && col - DBBSPTCC < BOARD_SIZE))
		{
			if (board[row - (DBBSPTCC / MIDDLE_DIVIDER)]
				[col - (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WPIECE ||
				board[row - (DBBSPTCC / MIDDLE_DIVIDER)]
				[col - (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WTOWER)
			{
				target_r = row - DBBSPTCC;
				target_c = col - DBBSPTCC;
				operats = fill_position(row, col, target_r, target_c, source,
				target, operats, board);
			}
		}
		
	}
	return operats;
}


/*This function takes a board_t type board, an integer row, and integer column,
a string source, a string target and a pointer to an operation_t type operats. 
It will try to find if the south-east and south-west cell can be operated,
include move and capture. If it can, it will store the action in operats. 
It will return the pointer pointing at operats.*/
operation_t *find_move_btower_sesw(board_t board, int row, int col, 
char source[], char target[], operation_t *operats)
{
	int target_r, target_c;

	/*check South-east direction move*/
	if (board[row + DBBSPTCM][col + DBBSPTCM] == CELL_EMPTY &&
		(row + DBBSPTCM >= COL_MIN && row + DBBSPTCM < BOARD_SIZE && 
		col + DBBSPTCM >= COL_MIN && col + DBBSPTCM < BOARD_SIZE))
	{
		target_r = row + DBBSPTCM;
		target_c = col + DBBSPTCM;
		operats = fill_position(row, col, target_r, target_c, source, target,
        operats, board);
	}

	/*check South-east direction capture*/
	if (board[row + DBBSPTCC][col + DBBSPTCC] == CELL_EMPTY &&
		(row + DBBSPTCC >= COL_MIN && row + DBBSPTCC < BOARD_SIZE && 
		col + DBBSPTCC >= COL_MIN && col + DBBSPTCC < BOARD_SIZE))
	{
		if (board[row + (DBBSPTCC / MIDDLE_DIVIDER)]
			[col + (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WPIECE ||
			board[row + (DBBSPTCC / MIDDLE_DIVIDER)]
			[col + (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WTOWER)
		{
			target_r = row + DBBSPTCC;
			target_c = col + DBBSPTCC;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}
	}

	/*check South-west direction move*/
	if (board[row + DBBSPTCM][col - DBBSPTCM] == CELL_EMPTY &&
		(row + DBBSPTCM >= COL_MIN && row + DBBSPTCM < BOARD_SIZE && 
		col - DBBSPTCM >= COL_MIN && col - DBBSPTCM < BOARD_SIZE))
	{
		target_r = row + DBBSPTCM;
		target_c = col - DBBSPTCM;
		operats = fill_position(row, col, target_r, target_c, source, target,
        operats, board);
	}
	
	/*check South-west direction capture*/
	if (board[row + DBBSPTCC][col - DBBSPTCC] == CELL_EMPTY &&
		(row + DBBSPTCC >= COL_MIN && row + DBBSPTCC < BOARD_SIZE && 
		col - DBBSPTCC >= COL_MIN && col - DBBSPTCC < BOARD_SIZE))
	{
		if (board[row + (DBBSPTCC / MIDDLE_DIVIDER)]
			[col - (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WPIECE ||
			board[row + (DBBSPTCC / MIDDLE_DIVIDER)]
			[col - (DBBSPTCC / MIDDLE_DIVIDER)] == CELL_WTOWER)
		{
			target_r = row + DBBSPTCC;
			target_c = col - DBBSPTCC;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}
	}
	return operats;
}


/*This function takes a board_t type board, an integer row, and integer column,
a string source, a string target and a pointer to an operation_t type operats.
It will try to find all action possible for white checkers. All action will be 
recorded in the operats and base on the direction start from North-east and
turn clockwise. It will return the pointer pointing at operats.*/
operation_t *find_move_white(board_t board, int row, int col, char source[],
char target[], operation_t *operats)
{
	int target_r, target_c;

	/*Only operate on white checkers*/
	if (board[row][col] == CELL_WPIECE || board[row][col] == CELL_WTOWER)
	{
		/*North-east direction action can only be done by white tower.*/
		if (board[row][col] == CELL_WTOWER)
		{
			operats = find_move_wtower_NE(board, row, col, source, target, 
			operats);
		}

		/*check South-east direction move*/
		if (board[row - DBWSPTCM][col - DBWSPTCM] == CELL_EMPTY &&
		(row - DBWSPTCM >= COL_MIN && row - DBWSPTCM < BOARD_SIZE && 
		col - DBWSPTCM >= COL_MIN && col - DBWSPTCM < BOARD_SIZE))
		{
			target_r = row - DBWSPTCM;
			target_c = col - DBWSPTCM;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}

		/*check South-east direction capture*/
		if (board[row - DBWSPTCC][col - DBWSPTCC] == CELL_EMPTY &&
		(row - DBWSPTCC >= COL_MIN && row - DBWSPTCC < BOARD_SIZE && 
		col - DBWSPTCC >= COL_MIN && col - DBWSPTCC < BOARD_SIZE))
		{
			if (board[row - (DBWSPTCC / MIDDLE_DIVIDER)]
				[col - (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BPIECE ||
				board[row - (DBWSPTCC / MIDDLE_DIVIDER)]
				[col - (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BTOWER)
			{
				target_r = row - DBWSPTCC;
				target_c = col - DBWSPTCC;
				operats = fill_position(row, col, target_r, target_c, source,
				target, operats, board);
			}
		}

		/*check South-west direction move*/
		if (board[row - DBWSPTCM][col + DBWSPTCM] == CELL_EMPTY &&
		(row - DBWSPTCM >= COL_MIN && row - DBWSPTCM < BOARD_SIZE && 
		col + DBWSPTCM >= COL_MIN && col + DBWSPTCM < BOARD_SIZE))
		{
			target_r = row - DBWSPTCM;
			target_c = col + DBWSPTCM;
			operats = fill_position(row, col, target_r, target_c, source, 
			target, operats, board);
		}
		
		/*check South-west direction capture*/
		if (board[row - DBWSPTCC][col + DBWSPTCC] == CELL_EMPTY &&
		(row - DBWSPTCC >= COL_MIN && row - DBWSPTCC < BOARD_SIZE && 
		col + DBWSPTCC >= COL_MIN && col + DBWSPTCC < BOARD_SIZE))
		{
			if (board[row - (DBWSPTCC / MIDDLE_DIVIDER)]
				[col + (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BPIECE ||
				board[row - (DBWSPTCC / MIDDLE_DIVIDER)]
				[col + (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BTOWER)
			{
				target_r = row - DBWSPTCC;
				target_c = col + DBWSPTCC;
				operats = fill_position(row, col, target_r, target_c, source,
				target, operats, board);
			}
		}

		/*North-west direction action can only be down by white tower.*/
		if (board[row][col] == CELL_WTOWER)
		{
			operats = find_move_wtower_NW(board, row, col, source, target, 
			operats);
		}
	}
	return operats;
}


/*This function takes a board_t type board, an integer row, and integer column,
a string source, a string target and a pointer to an operation_t type operats. 
It will try to find if the north-west cell can be operated, include move and 
capture. If it can, it will store the action in operats. It will return the 
pointer pointing at operats.*/
operation_t *find_move_wtower_NW(board_t board, int row, int col,
char source[], char target[], operation_t *operats)
{
	int target_r, target_c;

	/*check North-west direction move*/
	if (board[row + DBWSPTCM][col + DBWSPTCM] == CELL_EMPTY &&
		(row + DBWSPTCM >= COL_MIN && row + DBWSPTCM < BOARD_SIZE && 
		col + DBWSPTCM >= COL_MIN && col + DBWSPTCM < BOARD_SIZE))
	{
		target_r = row + DBWSPTCM;
		target_c = col + DBWSPTCM;
		operats = fill_position(row, col, target_r, target_c, source, target,
        operats, board);
	}

	/*check North_west direction capture*/
	if (board[row + DBWSPTCC][col + DBWSPTCC] == CELL_EMPTY &&
		(row + DBWSPTCC >= COL_MIN && row + DBWSPTCC < BOARD_SIZE && 
		col + DBWSPTCC >= COL_MIN && col + DBWSPTCC < BOARD_SIZE))
	{
		if (board[row + (DBWSPTCC / MIDDLE_DIVIDER)]
			[col + (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BPIECE ||
			board[row + (DBWSPTCC / MIDDLE_DIVIDER)]
			[col + (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BTOWER)
		{
			target_r = row + DBWSPTCC;
			target_c = col + DBWSPTCC;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}
	}
	return operats;
}


/*This function takes a board_t type board, an integer row, and integer column,
a string source, a string target and a pointer to an operation_t type operats. 
It will try to find if the north-east cell can be operated, include move and 
capture. If it can, it will store the action in operats. It will return the 
pointer pointing at operats.*/
operation_t *find_move_wtower_NE(board_t board, int row, int col,
char source[], char target[], operation_t *operats)
{
	int target_r, target_c;

	/*check North-east direction move*/
	if (board[row + DBWSPTCM][col - DBWSPTCM] == CELL_EMPTY &&
		(row + DBWSPTCM >= COL_MIN && row + DBWSPTCM < BOARD_SIZE && 
		col - DBWSPTCM >= COL_MIN && col - DBWSPTCM < BOARD_SIZE))
	{
		target_r = row + DBWSPTCM;
		target_c = col - DBWSPTCM;
		operats = fill_position(row, col, target_r, target_c, source, target,
        operats, board);
	}
	
	/*check North-east direction capture*/
	if (board[row + DBWSPTCC][col - DBWSPTCC] == CELL_EMPTY &&
		(row + DBWSPTCC >= COL_MIN && row + DBWSPTCC < BOARD_SIZE && 
		col - DBWSPTCC >= COL_MIN && col - DBWSPTCC < BOARD_SIZE))
	{
		if (board[row + (DBWSPTCC / MIDDLE_DIVIDER)]
			[col - (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BPIECE ||
			board[row + (DBWSPTCC / MIDDLE_DIVIDER)]
			[col - (DBWSPTCC / MIDDLE_DIVIDER)] == CELL_BTOWER)
		{
			target_r = row + DBWSPTCC;
			target_c = col - DBWSPTCC;
			operats = fill_position(row, col, target_r, target_c, source,
			target, operats, board);
		}
	}
	return operats;
}


/*This function takes an integer row, an integer column, an integer target_row,
and integer target_column, a string source, a string target, a pointer to an
operation_t type operats, and a board_t type board. It will fill the strings:
source and target and finally fill them into operation(linked list). It will
return the pointer pointing at operats.*/
operation_t *fill_position(int row, int col, int target_r, int target_c,
char source[], char target[], operation_t *operats, board_t board)
{
	source[CRI] = (row + DBRI + DBIA);
	source[CCI] = (col + DBBA);
	source[CRI + SONULL] = '\0';
	target[CRI] = (target_r + DBRI + DBIA);
	target[CCI] = (target_c + DBBA);
	target[CRI + SONULL] = '\0';
	
	fill_operation(source, target, operats, board);
	return operats;
}


/*This function takes a string source, a string target, a pointer to an 
operation_t type operation and a board_t type board. It will add the new 
operation after the last of the original operation(linked list) base on the
source and target value. It will return the pointer pointing at operation.*/
operation_t *fill_operation(char source[], char target[],
operation_t *operation, board_t board)
{
	operation_t *new, *temp;
	board_t new_board;

	new = (operation_t *)malloc(sizeof(*new));
	new -> action.source_cci = source[CCI];
	new -> action.source_cri = source[CRI];
	new -> action.target_cci = target[CCI];
	new -> action.target_cri = target[CRI];
	board_cpy(board, new_board);
	board_actions_cells(new_board, source, target);
	board_cpy(new_board, new -> cu_board);
	new -> cu_boardcost = board_cost(new -> cu_board);
	new -> next = NULL;

	if (operation -> next == NULL)
	{
		operation -> next = new;
	}
	else
	{
		temp = operation -> next;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = new;
	}
	return operation;
}


/*This function takes two board_t type board and copy the content from the first
board to the second one.*/
void board_cpy(board_t ori_board, board_t new_board)
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			new_board[i][j] = ori_board[i][j];
		}
	}

}


/*this function takes a board_t type board, a character array line and an
integer turn. This function will separate the line to source and target cell
and check if the action is valid. If it is, it will apply the action.*/
void board_operation(board_t board, char line[], int turns)
{
	char source[SOC + SONULL] = CELL_MIN;
	char target[SOC + SONULL] = CELL_MIN;
	int j, i = 0;
	for (j = LINESS; j < strlen(line); j++)
	{
		if (j < LINESE)
		{
			source[j] = line[j];
		}
		else if (j >= LINETS)
		{
			target[i] = line[j];
			i++;
		}
	}
	source[SOC] = target[SOC] = '\0';
	board_action_check(board, source, target, turns % EVEN_CHECK);
	board_actions_cells(board, source, target);
	board_action_print(board, source, target, turns, FALSE);
}


/*This function takes a board_t type board, a character array source, a
character array target, an integer turns and an integer is_machine. It will 
print the current action with required format.*/
void board_action_print(board_t board, char source[], char target[], int turns,
int is_machine)
{
	printf("%s\n", SECTION_SEPARATOR);
	if (is_machine)
	{
		printf("%s ", MOI);
	}
	if (turns % EVEN_CHECK == B_TURN)
	{
		printf("BLACK ACTION #%d: %s-%s\n", turns, source, target);
	}
	else
	{
		printf("WHITE ACTION #%d: %s-%s\n", turns, source, target);
	}
	printf("BOARD COST: %d\n", board_cost(board));
	print_board(board);
}


/*This function takes a board_t type board and print it with required format.
(only use while no operation has been done.)*/
void board_initial_print(board_t board)
{
	printf("BOARD SIZE: %dx%d\n", BOARD_SIZE, BOARD_SIZE);
	printf("#BLACK PIECES: %d\n", NUM_B);
	printf("#WHITE PIECES: %d\n", NUM_W);
	print_board(board);
}


/*This function takes a board_t type board, a character array source and a
character array target. It will do a single move or capture, and change any
cells that satisfy requirement to towers.*/
void board_actions_cells(board_t board, char source[], char target[])
{
	board_actions_change_cells(board, source, target);
	board_actions_towerchange(board);
}


/*This function takes a board_t type board and search for any potential cells
that can be change to towers, and then change them from pieces to towers.*/
void board_actions_towerchange(board_t board)
{
	int row, col;

	/*Any piece that reaches certain row base on their colour will change to
	tower.*/
	for (row = 0; row < BOARD_SIZE; row++)
	{
		if (row == BPTTR)
		{
			for (col = 0; col < BOARD_SIZE; col++)
			{
				if (board[row][col] == CELL_BPIECE)
				{
					board[row][col] = CELL_BTOWER;
				}
			}
		}
		else if (row == WPTTR)
		{
			for (col = 0; col < BOARD_SIZE; col++)
			{
				if (board[row][col] == CELL_WPIECE)
				{
					board[row][col] = CELL_WTOWER;
				}
			}
		}
	}
}


/*This function takes a board_t type board, a character arrray source and a
character array target and change the source to empty cell, change the target
cell to the source(which means a move) or also change the cell between the
source and the target cell to empty(which means a capture)*/
void board_actions_change_cells(board_t board, char source[], char target[])
{
	int s_row = source[CRI];
	int t_row = target[CRI];
	int s_col = source[CCI];
	int t_col = target[CCI];
	int row_diff = s_row - t_row;
	char cu_cell;

	/*case when is only moving*/
	if (row_diff * row_diff == DBBSPTCM * DBBSPTCM)
	{
		cu_cell = board[s_row - (DBIA + DBRI)][s_col - DBBA];
		board[s_row - (DBIA + DBRI)][s_col - DBBA] = CELL_EMPTY;
		board[t_row - (DBIA + DBRI)][t_col - DBBA] = cu_cell;
	}
	/*case when capturing*/
	else
	{
		int col_diff = s_col - t_col;
		int cap_col = s_col - DBBA - (col_diff / MIDDLE_DIVIDER);
		int cap_row = s_row - (DBIA + DBRI) - (row_diff / MIDDLE_DIVIDER);

		cu_cell = board[s_row - (DBIA + DBRI)][s_col - DBBA];
		board[s_row - (DBIA + DBRI)][s_col - DBBA] = CELL_EMPTY;
		board[t_row - (DBIA + DBRI)][t_col - DBBA] = cu_cell;
		board[cap_row][cap_col] = CELL_EMPTY;
	}
}


/*This function takes a board_t type board, character array source, character
array target and integer turn and check them for errors.*/
void board_action_check(board_t board, char source[], char target[], int turn)
{
	error_sourceoboard(source);
	error_targetoboard(target);
	error_sourceempty(board, source);
	error_targetnempty(board, target);
	error_sourceop(board, source, turn);
	error_ia(board, source, target, turn);
}


/*This function takes a character array source and exit the program if it is
outside the range of the board.*/
void error_sourceoboard(char source[])
{
	char s_col = source[CCI];
	char s_row = source[CRI];
	if (s_col < CELL_MIN[CCI] || s_col > CELL_MAX[CCI]
	|| s_row < CELL_MIN[CRI] || s_row > CELL_MAX[CRI])
	{
		printf("%s\n", ERRORSOB);
		exit(EXIT_FAILURE);
	}
}


/*This function takes a character array target and exit the program if it is
outside the range of the board.*/
void error_targetoboard(char target[])
{
	char t_col = target[CCI];
	char t_row = target[CRI];
	if (t_col < CELL_MIN[CCI] || t_col > CELL_MAX[CCI]
	    || t_row < CELL_MIN[CRI] || t_row > CELL_MAX[CRI])
	{
		printf("%s\n", ERRORTOB);
		exit(EXIT_FAILURE);
	}
}


/*This function takes a board_t type board and a character array source and
exit the program if the board is empty at that position.*/
void error_sourceempty(board_t board, char source[])
{
	int row_ori = source[CRI];
	int col_ori = source[CCI];
	int row = row_ori - (DBIA + DBRI);
	int col = col_ori - DBBA;

	if (board[row][col] == CELL_EMPTY)
	{
		printf("%s\n", ERRORSE);
		exit(EXIT_FAILURE);
	}
}


/*This function takes a board_t type board and a character array target and
exit the program if the board is not empty at the target position.*/
void error_targetnempty(board_t board, char target[])
{
	int row_ori = target[CRI];
	int col_ori = target[CCI];
	int row = row_ori - (DBIA + DBRI);
	int col = col_ori - DBBA;

	if (board[row][col] != CELL_EMPTY)
	{
		printf("%s\n", ERRORTNE);
		exit(EXIT_FAILURE);
	}
}


/*This function takes a board_t type board and a character array source and
an integer indicate current turn. It will exit the program if the cell holds
opponent's checker.*/
void error_sourceop(board_t board, char source[], int cu_turn)
{
	int row_ori = source[CRI];
	int col_ori = source[CCI];
	int row = row_ori - (DBIA + DBRI);
	int col = col_ori - DBBA;

	char cu_piece = board[row][col];

	if (cu_turn == B_TURN)
	{
		if (!(cu_piece == CELL_BPIECE || cu_piece == CELL_BTOWER))
		{
			printf("%s\n", ERRORSOP);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (!(cu_piece == CELL_WPIECE || cu_piece == CELL_WTOWER))
		{
			printf("%s\n", ERRORSOP);
			exit(EXIT_FAILURE);
		}
	}
}


/*This function takes a board_t type board, a character array source, a
character array target and an integer indicate current turn. It will exit the
program if an invalid target position is given.*/
void error_ia(board_t board, char source[], char target[], int cu_turn)
{
	int error = FALSE;

	if (cu_turn == B_TURN)
	{
		error += error_ia_black(board, source, target);
	}
	else
	{
		error += error_ia_white(board, source, target);
	}
	if (error)
	{
		printf("%s\n", ERRORIA);
		exit(EXIT_FAILURE);
	}

}


/*This function takes a board_t type board, a character array source and a
character array target. It will exit the program if any invalid target position
is given for black checkers.*/
int error_ia_black(board_t board, char source[], char target[])
{
	int error_found = FALSE;
	int s_row_ori = source[CRI];
	int s_col_ori = source[CCI];
	int t_row_ori = target[CRI];
	int t_col_ori = target[CCI];

	int s_row = s_row_ori - (DBIA + DBRI);
	int s_col = s_col_ori - DBBA;
	int row_diff = s_row_ori - t_row_ori;
	int col_diff = s_col_ori - t_col_ori;
	char cu_piece = board[s_row][s_col];
	
	if (cu_piece == CELL_BPIECE)
	{
		/*Black piece must move upward*/
		if (row_diff < DBBSPTCM)
		{
			error_found = TRUE;
		}
	}

	/*must move at diagonal*/
	if (row_diff * row_diff != col_diff * col_diff)
	{
		error_found = TRUE;
	}

	/*any piece can move a maximum of 2 cells. (As already checked is
	diagonal, only row or column need to be checked.)*/
	if (row_diff * row_diff > DBBSPTCC * DBBSPTCC)
	{
		error_found = TRUE;
	}

	/*when capturing*/	
	if (row_diff == DBBSPTCC)
	{
		int cap_col = s_col_ori - DBBA - (col_diff / MIDDLE_DIVIDER);
		int cap_row = s_row_ori - (DBIA + DBRI) - (row_diff / MIDDLE_DIVIDER);
		char captured_piece = board[cap_row][cap_col];

		if (captured_piece == CELL_EMPTY)
		{
			error_found = TRUE;
		}
		if (!(captured_piece == CELL_WPIECE || captured_piece == CELL_WTOWER))
		{
			error_found = TRUE;
		}
	}
	return error_found;
}


/*This function takes a board_t type board, a character array source and a
character array target. It will exit the program if any invalid target position
is given for white checkers.*/
int error_ia_white(board_t board, char source[], char target[])
{
	int error_found = FALSE;
	int s_row_ori = source[CRI];
	int s_col_ori = source[CCI];
	int t_row_ori = target[CRI];
	int t_col_ori = target[CCI];

	int s_row = s_row_ori - (DBIA + DBRI);
	int s_col = s_col_ori - DBBA;
	int row_diff = s_row_ori - t_row_ori;
	int col_diff = s_col_ori - t_col_ori;
	char cu_piece = board[s_row][s_col];
	
	if (cu_piece == CELL_WPIECE)
	{
		/*white piece must move downward*/
		if (row_diff > DBWSPTCM)
		{
			error_found = TRUE;
		}
	}

	/*must move at diagonal*/
	if (row_diff * row_diff != col_diff * col_diff)
	{
		error_found = TRUE;
	}

	/*any piece can move a maximum of 2 cells. (As already checked is
	diagonal, only row or column need to be checked.)*/
	if (row_diff * row_diff > DBWSPTCC * DBWSPTCC)
	{
		error_found = TRUE;
	}

	/*when capturing*/	
	if (row_diff == DBWSPTCC)
	{
		int cap_col = s_col_ori - DBBA - (col_diff / MIDDLE_DIVIDER);
		int cap_row = s_row_ori - (DBIA + DBRI) - (row_diff / MIDDLE_DIVIDER);
		char captured_piece = board[cap_row][cap_col];
		if (captured_piece == CELL_EMPTY)
		{
			error_found = TRUE;
		}
		if (!(captured_piece == CELL_BPIECE || captured_piece == CELL_BTOWER))
		{
			error_found = TRUE;
		}
	}
	return error_found;
}

/*This function takes a board_t type board as input and return the board cost
of current board.*/
int board_cost(board_t board)
{
	int i, j, cost = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == CELL_BPIECE)
			{
				cost += COST_PIECE;
			}
			else if (board[i][j] == CELL_WPIECE)
			{
				cost -= COST_PIECE;
			}
			else if (board[i][j] == CELL_BTOWER)
			{

				cost += COST_TOWER;
			}
			else if (board[i][j] == CELL_WTOWER)
			{
				cost -= COST_TOWER;
			}
		}
	}
	return cost;
}


/*This function takes a board_t type board as input and print it with required
format.*/
void print_board(board_t board)
{
	int i, j;

	printf("  ");
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("   %c", i + DBBA);
	}

	printf("\n");
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("   %s\n", ROW_SEPARATOR);
		printf(" %d", i + DBRI);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			printf(" %c", LINE_SEPARATOR);
			printf(" %c", board[i][j]);
		}
		printf(" %c\n", LINE_SEPARATOR);
	}

	printf("   %s\n", ROW_SEPARATOR);
}


/*This function takes a board_t type board as input and initialize it with
required variables.*/
void board_setup(board_t board)
{
	board_fill(board, WHITE_ROW_MIN, CELL_WPIECE, FALSE);
	board_fill(board, BLACK_ROW_MIN, CELL_BPIECE, FALSE);
	board_fill(board, EMPTY_ROW_MIN, CELL_EMPTY, TRUE);
}


/*This function takes a board_t type board, the start of input, the required
piece, and whether is filling an empty_line. This function will fill the
board with required cells at required position, or if filling an empty line,
fill two rows with empty variables.*/
void board_fill(board_t board, int start, char input_piece, int empty_line)
{
	int row, col;
	
	if (!empty_line)
	{
		for (row = start; row < (start + ROWS_WITH_PIECES); row++)
		{
			for (col = COL_MIN; col < BOARD_SIZE; col++)
			{
				if (row % EVEN_CHECK == EVEN_REMAINDER)
				{
					if (col % EVEN_CHECK == EVEN_REMAINDER)
					{
						board[row][col] = CELL_EMPTY;
					}
					else
					{
						board[row][col] = input_piece;
					}
				}
				else
				{
					if (col % EVEN_CHECK != EVEN_REMAINDER)
					{
						board[row][col] = CELL_EMPTY;
					}
					else
					{
						board[row][col] = input_piece;
					}
				}
			}
		}
	}

	/*fill empty row*/
	else
	{
		for (row = start; row < EMPTY_ROW_MAX; row++)
		{
			for (col = COL_MIN; col < BOARD_SIZE; col++)
			{
				board[row][col] = CELL_EMPTY;
			}
		}
	}
}
