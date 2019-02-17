/*
Derrick Simeon
Feb 16, 2019
*/

#include "vr_serial.h"
#include "fancy_print.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static VrSerPkt_t *_initPkt(const void *pSrc, int nChars)
{
  VrSerPkt_t *pPkt;
  
  assert((pSrc != NULL) && (nChars > 0));
  
  pPkt = malloc(sizeof(*pPkt));
  pPkt->pData = malloc(nChars);
  pPkt->idx = 0;
  pPkt->nChars = nChars;
  memcpy(pPkt->pData, pSrc, nChars);
  
  return pPkt;
}

static void deletePkt(VrSerPkt_t **ppPkt)
{
  VrSerPkt_t *pObsPkt;
  
  pObsPkt = *ppPkt;
  *ppPkt = (*ppPkt)->pNxt;
  free(pObsPkt);
}

static int _consumePkt(VrSerPkt_t *pPkt, char *pDst,
  int nChars)
{
  int nConsume;
  
  nConsume = ((pPkt->nChars - pPkt->idx) < nChars) ?
    pPkt->nChars - pPkt->idx : nChars;
  
  memcpy(pDst, &pPkt->pData[pPkt->idx], nConsume);
  pPkt->idx += nConsume;
  
//   if(pPkt-> idx >= pPkt->nChars)
//     deletePkt();
  
  return nChars;
}

VrSerDev_t *VR_SERIAL_initDev(const char *pName, int bps)
{
  VrSerDev_t *pDev;
  
  pDev = malloc(sizeof(*pDev));
  pDev->pName = pName;
  pDev->bps = bps;
  pDev->pTxQ = NULL;
  pDev->pNxt = NULL;
  
  return pDev;
}

int VR_SERIAL_devTx(VrSerDev_t *pDev, const void *pSrc, int nChars)
{
  VrSerPkt_t **ppPktItr;
  
  ppPktItr = &pDev->pTxQ;
  
  while(*ppPktItr != NULL)
  {
    ppPktItr = &(*ppPktItr)->pNxt;
  }
  
  *ppPktItr = _initPkt(pSrc, nChars);

  return nChars;
}

VrSerLine_t *VR_SERIAL_initLine(void)
{
  VrSerLine_t *pLine;
  
  pLine = malloc(sizeof(*pLine));
  pLine->pDevList = NULL;
  
  return pLine;
}

void VR_SERIAL_addDev(VrSerLine_t *pSerLine, VrSerDev_t *pSerDev)
{
  VrSerDev_t **ppDevItr;
  
  ppDevItr = &pSerLine->pDevList;
  
  while(*ppDevItr != NULL)
  {
    ppDevItr = &(*ppDevItr)->pNxt;
  }
  
  *ppDevItr = pSerDev;
}

void VR_SERIAL_procLineTask(VrSerLine_t *pLine, float seconds)
{
  VrSerDev_t **ppDevItr;
  char buf[1024];
  int nChars;
  
  for(ppDevItr = &pLine->pDevList; *ppDevItr != NULL;
    ppDevItr = &(*ppDevItr)->pNxt)
  {
    nChars = (*ppDevItr)->bps * seconds;
    sprintf(buf, "%s tx %i bytes", (*ppDevItr)->pName, nChars);
    printTimestamped(buf);
    
    _consumePkt((*ppDevItr)->pTxQ, buf, nChars);
    
    passHexString(&printTimestamped, buf, nChars);
  }
}