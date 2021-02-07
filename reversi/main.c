#include "board.h"
#include "direction.h"

//AVIV LEVI

void CheckWinAndDisplay(Board board);

//הסבר להחלפת תורות
//case 0 
// 1-0 = 1

//case 1
// 1-1 = 0

int main()                            
{
	time_t t;
	srand((unsigned)time(&t)); //RANDOM נאתחל את ה

	Player current = rand()%2; // השחקן שמתחיל נבחר באופן רנדומלי
	Board board;
	InitBoard(board); // נאתחל לוח
	Directions direvec;
	GetDirections(direvec); // נאתחל מערך כיוונים

	//דגלים האם התור האחרון דולג
	int flagSkipRoundBlue = 0;
	int flagSkipRoundRed = 0;
	printf("\n"  GRN  "Welcome To Reversi!"  RESET  "\n");
	while (!(flagSkipRoundRed && flagSkipRoundBlue)) // כל עוד לא קורה שלשני השחקנים אין תור ברציפות
	{
		if (BoardFull(board)) // אם הלוח מלא,  נבדוק ונציג את המנצח ונסיים את התוכנית
		{
			CheckWinAndDisplay(board);
			return 0;
		}

		int hasbridges = PrintVaild(board, direvec, current); // נדפיס את המקומות האפשריים להנחת השחקן, יוחזר ערך בוליאני האם יש לפחות גשר אחד
		int row, col;
		switch (current)
		{
			case RED:
				if (!hasbridges) // אם אין לפחות גשר אחד
				{
					flagSkipRoundRed = 1;//נדליק דגל דילוג תור
					printf("\n"  REDD  "NO VALID MOVES FOR RED PLAYER!"  RESET  "\n");
					current = 1 - current; // נתקדם לתור של השחקן הבא
					continue; // נדלג ישר לאיטרציה הבאה בלולאה
				}
				else { flagSkipRoundRed = 0;  } // אם ישר גשר,נכבה דגל דילוג תור
				printf("\n"  REDD  "RED TURN , MAKE MOVE (ROW , COL): "  RESET  "\n"); // נקלוט מהשחקו את התור שהוא רוצה לבצע
				printf("\n"  REDD  "ENTER ROW: "  RESET  "\n");
				scanf_s("%d", &row);
				printf("\n"  REDD  "ENTER COL: "  RESET  "\n");
				scanf_s("%d", &col);
				break;
			case BLUE:
				if (!hasbridges) // אותו הסבר כמו לאדום, אין גשר נדליק דגל ונחליף, אם ישר נדליק דגל
				{
					flagSkipRoundBlue = 1;
					current = 1 - current;
					printf("\n"  CYN  "NO VALID MOVES FOR BLUE PLAYER!"  RESET  "\n");
					continue;
				}
				else { flagSkipRoundBlue = 0; }
				printf("\n"  CYN  "BLUE TURN , MAKE MOVE (ROW , COL): "  RESET  "\n");
				printf("\n"  CYN  "ENTER ROW: "  RESET  "\n");
				scanf_s("%d", &row);
				printf("\n"  CYN  "ENTER COL: "  RESET  "\n");
				scanf_s("%d", &col);
				break;
		}

		if (board[row][col] != VALID)//אם המקום הנבחר לא הוגדר כאפשרי לגשר, נחזיר את הלוח לקדמותו ונתקדם בלולאה מבלי לההחליף לשחקן הבא,כך יקבל תור נוסף
		{
			printf("\n"  CYN  "PLACE ISNT VALID , TRY AGAIN"  RESET  "\n");
			CleanValid(board);
			continue;
		}
		CleanValid(board);//אם המקום שנבחר אפשרי, נחזיר לוח לקדמותו ,נבצע את התור,נבנה את הגשר ונחליף לשחקן הבא
		board[row][col] = current;
		Build(board, direvec, current,row,col);

		current = 1 - current;

	}
	//אם המשחק לא נגמר מהלוח מלא בבדיקה הפנימית ויצאנו מהלולאה,זה כנראה כין אין תורות,לכן נבדוק מי מנצח ונציג אותו  
	CheckWinAndDisplay(board);
	return 0;
}


//תנאי כניסה:מוכנס לוח
//תנאי יציאה: הפונקציה בודקת מי המנצח ומציגה אותו על המסך
void CheckWinAndDisplay(Board board)
{
	Player winner = CheckWinner(board);
	switch (winner)
	{
	case BLUE:
		printf("\n"  CYN  "BLUE PLAYER IS THE WINNER!"  RESET  "\n");
		break;
	case RED:
		printf("\n"  REDD  "RED PLAYER IS THE WINNER!"  RESET  "\n");
		break;
	default:
		printf("\n"  GRN  "TIE!"  RESET  "\n");
		break;
	}
}
