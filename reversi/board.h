#pragma once
#include "direction.h"

#define ROWS 8//מספר השורות
#define COLS 8//מספר עמודות

// ערכי צבעים
#define REDD   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
// ENUM מסוג PLAYER שמכיל ערכים מסוימים
typedef enum {BLUE ,RED , EMPTY,  VALID} Player;

//מערך הלוח משחק שמכיל שחקנים מסוג PLAYER
typedef Player Board[ROWS+2][COLS+2];

//תנאי כניסה: מוכנס לוח
//תנאי יציאה: הפונקציה תאתחל את הלוח ותכניס אותו למצב ההתחלתי
void InitBoard(Board board);

//תנאי כניסה: מוכנס לוח
//תנאי יציאה: הפונקציה מדפיסה את הלוח
void PrintBoard(Board board);

//תנאי כניסה: מוכנס לוח
//תנאי יציאה: מוחזר האם הלוח מלא בשחקנים
int BoardFull(Board board);

//תנאי כניסה: מוכנס לוח
//תנאי יציאה: הפונקציה מחזירה את השחקן עם כמות הכלים הגבוהה ביותר
Player CheckWinner(Board board);

//תנאי כניסה: מוכנס לוח
//תנאי יציאה: הפונקציה תאפס את כל המקומות שמוגדרים כזמינים לריקים
void CleanValid(Board board);

//תנאי כניסה: מוכנס לוח, מערך כיוונים, שחקן נוכחי, שורה ועמודה
//תנאי יציאה: הפונקציה תבנה באופן רקורסיבי גשר החל מהמיקום שהוכנס 
void Build(Board board, Directions dirc, Player player, int row, int col);

//תנאי כניסה:מוכנס לוח, מערך כיוונים,שחקן נוכחי,שורה,עמודה ומונה
//תשתמש לבניית גשר BUILD תנאי יציאה: זוהי הפוקנציה הרקורסיבית שבה המחלקה 
int Move(Board board, Place vec, Player player, int row, int col, int counter);

//תנאי כניסה: מוכנס לוח ,מערך כיוונים ושחקן נוכחי
//תנאי יציאה: הפונקציה מוצאת מיקומים זמינים שאפשריים לבניית גשר ומציגה אותם למשתמש
int PrintVaild(Board board, Directions dirc, Player player);

//תנאי כניסה: מוכנס לוח,מערך כיוונים,שחקן נוכחי,שורה , עמודה,ומונה
//(מופעלת על ידי PRINTVALID)	תנאי יציאה: זו היא הפונקציה הרקורסיבית שמשמשת להצגת מיקומים זמינים לבניית גשרים 
int SearchForBridge(Board board, Place vec, Player player, int row, int col, int counter);