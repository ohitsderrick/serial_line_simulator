/*
Derrick Simeon
Feb 16, 2019
*/

#include "serial_sim.h"
#include "fancy_print.h"

#include <stdio.h>

#define BAUD 57600
#define UART_BPS (BAUD / 10)

static const char MSG1[] = "I like the tuna here.";
static const char MSG2[] = "Bullshit, asshole, nobody likes the tuna here!";

int main(void)
{
  SerSimDev_t *pClientDev, *pServerDev;
  SerSimLine_t *pSerLine;
  
  pClientDev = SERIAL_SIM_initDev("client", UART_BPS);
  pServerDev = SERIAL_SIM_initDev("server", UART_BPS);
  
  pSerLine = SERIAL_SIM_initLine();
  SERIAL_SIM_addDev(pSerLine, pClientDev);
//   SERIAL_SIM_addDev(pSerLine, pServerDev);
  
  printTitle("Start test!");  
  setStartTime();
  
  SERIAL_SIM_devTx(pClientDev, MSG1, sizeof(MSG1) - 1);
  SERIAL_SIM_devTx(pClientDev, MSG2, sizeof(MSG2) - 1);
  
  SERIAL_SIM_procLineTask(pSerLine, .01f);
  
//   while(1)
//   {
//     delay(.001f);
    
//     SERIAL_SIM_procLineTask(pSerLine, .001f);
//   }
  
  printTitle("End test!");
  return 0;
}
