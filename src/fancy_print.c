/*
Derrick Simeon
Feb 16, 2019
*/

#include "fancy_print.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define STR_LEN(str) (sizeof(str) - 1)

void printTitle(char *pStr)
{
  int nChars, idx;
  char *pBorder;
  
  nChars = strlen(pStr) + 4;
  pBorder = malloc(nChars);
  
  for(idx = 0; idx < nChars; idx++)
  {
    pBorder[idx] = '=';
  }
  
  pBorder[idx] = 0;
  
  printf("%s\n| %s |\n%s\n", pBorder, pStr, pBorder);
}

void delay(float seconds)
{
  clock_t end;
  
  end = clock() + (clock_t) (((double) CLOCKS_PER_SEC) * seconds);
  
  while(clock() < end);  
}

int passHexString(int (*pfnPrint)(char *), void *pSrc, int nChars)
{
  int idx;
  char *pHexStr;
  
  pHexStr = malloc((nChars * 2) + 1);
  
  for(idx = 0; idx < nChars; idx++)
  {
    sprintf(&pHexStr[idx * 2], "%.2x", ((unsigned char *) pSrc)[idx] & 0xFF); 
  }
  
  nChars = pfnPrint(pHexStr);
  free(pHexStr);
  
  return nChars;
}

static clock_t m_start = 0;

void setStartTime(void)
{
  m_start = clock();
}

float getElapsedTime(void)
{
  return (float) (clock() - m_start) / (float) CLOCKS_PER_SEC;
}

void printElapsedTime(void)
{
  printf("%.3f\n", getElapsedTime());
}

int printTimestamped(char *pStr)
{
  int idx, idx2, nChars, nCharsNew, nNewLines;
  char *pIndentStr;
  
  nChars = strlen(pStr);
  nNewLines = 0;
  
  // Count the number of newline characters.
  for(idx = 0; idx < nChars; idx++)
  {
    if(pStr[idx] == '\n')
      nNewLines++;
  }
  
  // Calculate number of characters needed to replace newline characters.
  nCharsNew = nChars + (2 * nNewLines) + 1;
  pIndentStr = malloc(nCharsNew);
  idx2 = 0;
  
  for(idx = 0; idx < nChars; idx++)
  {
    if(pStr[idx] != '\n')
    {
      // Copy character directly.
      pIndentStr[idx2] = pStr[idx];
      idx2++;
    }
    else
    {
      // Replace newline character with indent.
      memcpy(&pIndentStr[idx2], "\n> ", STR_LEN("\n> "));
      idx2 += STR_LEN("\n> ");
    }
  }
  
  // Terminate with NULL.
  pIndentStr[idx] = 0;
  
  return printf("%.3f\n> %s\n", getElapsedTime(), pIndentStr);
}