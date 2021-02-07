#pragma once

#include <stdio.h>

#define DIRLEN 9//אורך מערך הכיוונים

typedef struct
{
	int row;
	int col;

}Place; // מבנה שישמש למערך כיוונים

typedef Place Directions[DIRLEN]; // מערך כיוונים, מערך של מבנים מסוג מיקום,שמכילים ערכי שורה וטור שיעזרו לזוז לכיוון מסוים

// תנאי כניסה: מוכנס מערך כיוונים ריק
//תנאי יציאה: הפונקציה תמלא את מערך הכיוונים
void GetDirections(Directions vec);