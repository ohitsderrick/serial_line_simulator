/*
Derrick Simeon
Feb 16, 2019
*/

#ifndef _SERIAL_SIM_H
#define _SERIAL_SIM_H

typedef struct _SerSimPkt_t SerSimPkt_t;
typedef struct _SerSimDev_t SerSimDev_t;
typedef struct _SerSimLine_t SerSimLine_t;

struct _SerSimPkt_t {
  char *pData;
  int nChars;
  SerSimPkt_t *pNext;
};

struct _SerSimDev_t {
  const char *pName;
  int bps;
  SerSimPkt_t *pTxQ;
  SerSimPkt_t *pRxQ;
  SerSimDev_t *pNext;
};

struct _SerSimLine_t {
  SerSimDev_t *pDevList;
  SerSimPkt_t *pPkt;
};

extern SerSimDev_t *SERIAL_SIM_initDev(const char *pName, int bps);

extern int SERIAL_SIM_devTx(SerSimDev_t *pDev, const void *pSrc, int nChars);

extern SerSimLine_t *SERIAL_SIM_initLine(void);

extern void SERIAL_SIM_addDev(SerSimLine_t *pSerLine, SerSimDev_t *pSerDev);

extern void SERIAL_SIM_procLineTask(SerSimLine_t *pLine, float seconds);

#endif
