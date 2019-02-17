/*
Derrick Simeon
Feb 16, 2019
*/

#ifndef _FANCY_PRINT_H
#define _FANCY_PRINT_H

extern void printTitle(char *pStr);

extern void delay(float seconds);

extern int passHexString(int (*pfnPrint)(char *), void *pSrc, int nChars);

extern void setStartTime(void);

extern float getElapsedTime(void);

extern void printElapsedTime(void);

extern int printTimestamped(char *pStr);

#endif