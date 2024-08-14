#ifndef UNIT_DISP_H
#define UNIT_DISP_H
//==============================================================================================================
#include "Def_TipoDatos.h"
#include "Def_BatChargerMonSim.h"
//--------------------------------------------------------------------------------------------------------------

#define NUM_DISP         1

#define MSG_REPLAY_DELAY 900

extern TBatChargeMon BatChargeMon;

void BatChargerMonSim_Init(void);
void sciDataReceived(BYTE * buf);

//==============================================================================================================

#endif // End of UNIT_DISP_H//