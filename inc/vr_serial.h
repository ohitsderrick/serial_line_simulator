/*
Derrick Simeon
Feb 16, 2019
*/

#ifndef _VR_SERIAL_H
#define _VR_SERIAL_H

typedef struct _VrSerPkt_t VrSerPkt_t;
typedef struct _VrSerDev_t VrSerDev_t;
typedef struct _VrSerLine_t VrSerLine_t;

struct _VrSerPkt_t {
  char *pData;
  int nChars;
  VrSerPkt_t *pNext;
};

struct _VrSerDev_t {
  const char *pName;
  int bps;
  VrSerPkt_t *pTxQ;
  VrSerPkt_t *pRxQ;
  VrSerDev_t *pNext;
};

struct _VrSerLine_t {
  VrSerDev_t *pDevList;
  VrSerPkt_t *pPkt;
};

extern VrSerDev_t *VR_SERIAL_initDev(const char *pName, int bps);

extern int VR_SERIAL_devTx(VrSerDev_t *pDev, const void *pSrc, int nChars);

extern VrSerLine_t *VR_SERIAL_initLine(void);

extern void VR_SERIAL_addDev(VrSerLine_t *pSerLine, VrSerDev_t *pSerDev);

extern void VR_SERIAL_procLineTask(VrSerLine_t *pLine, float seconds);

#endif