#include "Unit_ThreadComPort.h"
#include "Unit_ComPort.h"
#include "Unit_Disp.h"
//---------------------------------------------------------------------------

#define ERR_PUERTO 0x01
#define TIMEOUT    0x02

enum { PARSER_PRINC, PARSER_LENGTH, PARSER_DATA, PARSER_EOF };

static TThreadComPort ThreadComPort;
//---------------------------------------------------------------------------

void ThreadComPort_Init(void) {
    OpenCommPort(115200);
    ThreadComPort.rxParser = PARSER_PRINC;
    ThreadComPort.EstSciRv = 0x00;
    ThreadComPort.Tiempo = time(NULL);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

int8_t ThreadComPort_Update(void) {
    DWORD CantBytesReadAnt;
    BYTE Dato;

    ThreadComPort.ComErr = ComError();
    CantBytesReadAnt = ThreadComPort.CantBytesRead;
    ThreadComPort.CantBytesRead = BytesDisponibles();

    if (ThreadComPort.CantBytesRead > DIM_ADQ) {
        CloseCommPort();
        return -1;
    }
    if ((ThreadComPort.rxParser == PARSER_PRINC) ||
        (ThreadComPort.CantBytesRead - CantBytesReadAnt) > 0) {
        ThreadComPort.Tiempo = time(NULL);
    }
    if (difftime(time(NULL), ThreadComPort.Tiempo) >= ADQ_TIMEOUT) {
        ThreadComPort.EstSciRv |= TIMEOUT;
        ThreadComPort.rxParser = PARSER_PRINC;
    }

    if (ThreadComPort.CantBytesRead > 0) {
        switch (ThreadComPort.rxParser) {
        case PARSER_PRINC:
            printf("PARSER_PRINC\r\n");
            ReadBytes(&Dato, 1);
            if (Dato == SFD) {
                ThreadComPort.rxParser = PARSER_LENGTH;
            }

            break;
        case PARSER_LENGTH:
            ReadBytes(&ThreadComPort.rxCantBytes, 1);
            printf("PARSER_LENGTH %d\r\n", ThreadComPort.rxCantBytes);
            if (ThreadComPort.rxCantBytes > 0)
                ThreadComPort.rxParser = PARSER_DATA;
            else
                ThreadComPort.rxParser = PARSER_PRINC;

            break;
        case PARSER_DATA:
            if (ThreadComPort.CantBytesRead >= ThreadComPort.rxCantBytes) {
                printf("PARSER_DATA %d\r\n", ThreadComPort.CantBytesRead);
                ReadBytes(ThreadComPort.rxBuf, ThreadComPort.rxCantBytes);
                ThreadComPort.rxParser = PARSER_EOF;
            }

            break;
        case PARSER_EOF:
            ReadBytes(&Dato, 1);
            if (Dato == EOFCOM) {
                printf("PARSER_EOF OK\r\n");
                sciDataReceived(ThreadComPort.rxBuf);
            } else
                printf("PARSER_EOF %d\r\n", Dato);
            ThreadComPort.rxParser = PARSER_PRINC;

            break;
        }
        ThreadComPort.EstSciRv &= ~ERR_PUERTO;
    } else if (ThreadComPort.CantBytesRead == 0) {
        ThreadComPort.EstSciRv &= ~ERR_PUERTO;
    } else {
        ThreadComPort.EstSciRv |= ERR_PUERTO;
        return -1;
    }

    return ThreadComPort.rxParser;
}
//---------------------------------------------------------------------------

void ThreadComPort_End(void) {
    CloseCommPort();
    ThreadComPort.rxParser = PARSER_PRINC;
}
//---------------------------------------------------------------------------

uint8_t ThreadComPort_Error(void) {
    uint8_t errorState = ThreadComPort.EstSciRv;
    ThreadComPort.EstSciRv = 0x00;
    return errorState;
}
//---------------------------------------------------------------------------

void ThreadComPort_Rst(void) {
    ThreadComPort.rxParser = PARSER_PRINC;
    ThreadComPort.EstSciRv = 0x00;
    ThreadComPort.Tiempo = time(NULL);
}
//---------------------------------------------------------------------------
