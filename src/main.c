/*
Derrick Simeon
Feb 16, 2019
*/

#include "vr_serial.h"
#include "fancy_print.h"

#include <stdio.h>

#define BAUD 57600
#define UART_BPS (BAUD / 10)

static const char MSG1[] = "I like the tuna here.";
static const char MSG2[] = "Bullshit, asshole, nobody likes the tuna here!";

int main(void)
{
  VrSerDev_t *pClientDev, *pServerDev;
  VrSerLine_t *pSerLine;
  
  pClientDev = VR_SERIAL_initDev("client", UART_BPS);
  pServerDev = VR_SERIAL_initDev("server", UART_BPS);
  
  pSerLine = VR_SERIAL_initLine();
  VR_SERIAL_addDev(pSerLine, pClientDev);
//   VR_SERIAL_addDev(pSerLine, pServerDev);
  
  printTitle("Start test!");  
  setStartTime();
  
  VR_SERIAL_devTx(pClientDev, MSG1, sizeof(MSG1) - 1);
  VR_SERIAL_devTx(pClientDev, MSG2, sizeof(MSG2) - 1);
  
  VR_SERIAL_procLineTask(pSerLine, .01f);
  
//   while(1)
//   {
//     delay(.001f);
    
//     VR_SERIAL_procLineTask(pSerLine, .001f);
//   }
  
  printTitle("End test!");
  return 0;
}