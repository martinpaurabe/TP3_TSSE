#ifndef Unit_ThreadComPortH
#define Unit_ThreadComPortH
//---------------------------------------------------------------------------
#include <time.h>

// My Libraries
#include "Unit_ComPort.h"

//---------------------------------------------------------------------------
#define ADQ_TIMEOUT      1               // Micro Segundos
#define SEC_TO_DOUBLE(T) ((T) / 86400.0) // T: Tiempo en segundos

//---------------------------------------------------------------------------

#define ERR_PUERTO 0x01
#define TIMEOUT    0x02

typedef struct {
    DWORD ComErr;

    DWORD CantBytesRead;
    time_t Tiempo;

    BYTE EstSciRv;

    BYTE rxBuf[DIM_ADQ];
    uint8_t rxCantBytes;
    BYTE rxParser;

} TThreadComPort;

//---------------------------------------------------------------------------
void ThreadComPort_Init(void);
int8_t ThreadComPort_Update(void);
void ThreadComPort_Rst(void);
extern void sciDataReceived(BYTE * buf);

#endif
