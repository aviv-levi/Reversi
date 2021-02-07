#include "direction.h"
#include "board.h"

void InitBoard(Board board)
{
	int i, j;
	for ( i = 0; i < ROWS+2; i++)
	{
		for (j = 0; j < COLS+2; j++)
		{
			board[i][j] = EMPTY; // מרוקן את הלוח
		}
	}
	board[4][4] = RED;
	board[4][5] = BLUE;
	board[5][4] = BLUE;
	board[5][5] = RED;
	//מכניס מצב משחק התחלתי
}
void PrintBoard(Board board)
{
	int i, j;
	//printf("   |");
	for (i = 1; i < COLS+1; i++)
	{
		printf(" %d |" , i);
	}
	putchar('\n');
	for (i = 1; i < ROWS + 1; i++) {
		for (j = 1; j < COLS + 1; j++)
			printf("----");
		printf("\n");
		//printf(" %d |", i);
		//printf("   |");
		for (j = 1; j < COLS + 1; j++) {
			switch (board[i][j])
			{
				case RED:
					printf(REDD " * " RESET);
					break;
				case BLUE:
					printf(BLU " * " RESET);
					break;
				case EMPTY:
					printf("   ");
					break;
				case VALID:
					printf(GRN " * " RESET);
					break;
				}
				printf("|");
		}
		printf("\n");
	}

	for (j = 1; j < COLS + 1; j++)
		printf("----");
	printf("\n");
}

int BoardFull(Board board)
{
	int i, j;
	for (i = 1; i < ROWS + 1; i++)
	{
		for (j = 1; j < COLS + 1; j++)
		{
			if (board[i][j] == EMPTY)
			{
				return 0;//אם יש מיקום ריק הלוח לא מלא
			}
		}
	}
	return 1;
}
Player CheckWinner(Board board)
{
	//לשחקן כחול נוסיף אחד
	//לשחקן אדום נוריד אחד
	int diff = 0, i ,j; // הפרש בין כמות השחקנים מאותחלת לאפס
	for (i = 1; i < ROWS + 1; i++)
	{
		for (j = 1; j < COLS + 1; j++)
		{
			switch (board[i][j])
			{
				case BLUE:
					diff++;
					break;
				case RED:
					diff--;
			}
		}
	}
	if (diff>0) // אם ההפרש גדול מאפס העלנו את ההפרש יותר משהורדנו לכן הכחול ניצח
	{
		return BLUE;
	}
	if (diff<0)
	{
		return RED;
	}
	return EMPTY;
}
void CleanValid(Board board)
{
	int i, j;
	for (i = 1; i < ROWS + 1; i++)
	{
		for (j = 1; j < COLS + 1; j++)
		{
			board[i][j] = (board[i][j] == VALID) ? EMPTY : board[i][j];//אם המיקום מוגדר כזמין נשים בו ריק, אחרת לא נשנה אותו
		}

	}
}


int PrintVaild(Board board, Directions dirc, Player player)
{
	int i, j ,flag = 0; // דגל האם מצאנו גשר
	for (i = 1; i < ROWS + 1; i++)
	{
		for (j = 1; j < COLS + 1; j++)
		{
			if (board[i][j] == EMPTY)
			{
				int t;
				for (t = 0;  t < DIRLEN;  t++)//נלך לכל הכיוונים
				{
					if (SearchForBridge(board, dirc[t], player, i + dirc[t].row, j + dirc[t].col, 0))
					{//אם יש גשר לכיוון ההוא 
						board[i][j] = VALID;//נסמן מיקום כזמין
						flag = 1;//נדליק דגל
					}
				}
			}
		}
		
	}
	PrintBoard(board);//נדפיס לוח
	return flag;
}
void Build(Board board, Directions dirc, Player player,int row,int col)
{
	int i;
	for (i = 0; i < DIRLEN; i++)
	{
		Move(board, dirc[i], player, row + dirc[i].row, col + dirc[i].col, 0);
	}
}
int SearchForBridge(Board board , Place vec,Player player ,  int row , int col , int counter)
{
	if (board[row][col] == EMPTY || board[row][col] == VALID)//אם המיקום ריק הוא כבר נבדק נחזיר שקר
	{
		return 0;
	}
	if (board[row][col] == player)//אם המיקום הוא השחקן הנוכחי
	{
		if (counter == 0)//אם לא עברנו מעל היריב אין גשר
		{
			return 0;//נחזיר שקר
		}
		else
		{
			return 1;//אחרת נחזיר אמת
		}
	}
	//מצב שהנוכחי הוא היריב,נגדיל את המונה ונתקדם בכיוון
	return SearchForBridge(board, vec, player, row + vec.row, col + vec.col , counter+1);
}
int Move(Board board, Place vec, Player player, int row, int col, int counter)
{
	Player other = 1 - player; // ערכי השחקנים הם 0 ו1 ,כדי למצוא יריב נהפוך ערך על ידי 1 מינוס הנוכחי
	//case 0 
	// 1-0 = 1
	//case 1
	// 1-1 = 0
	if (board[row][col] == player) // אם המיקום שווה לנוכחי נחזיר אמת
	{
		return 1;
	}
	if (board[row][col]!=other)//אם המיקום שונה מהיריב נחזיר שקר
	{
		return 0;
	}
	//מה שנשאר כאן זה היריב
	if (Move(board, vec, player, row + vec.row, col + vec.col, counter + 1))//אם התוצאה של ההתקדמות היא אמת הגענו לשחקן הנוכחי ובחזור נשנה את המיקום לשחקן שלנו
	{
		board[row][col] = player; // החזרה אחורה
	}
}