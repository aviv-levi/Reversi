#include "direction.h"


void GetDirections(Directions vec)
{
	//אתחול מערך כיוונים
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			Place p;
			p.row = i;
			p.col = j;
			//המרה של מיקום דו מימדי למיקום בחד מימדי והכנסה של השחקן
			vec[(i + 1) * 3 + j + 1 ] = p; 
		}
	}
}

