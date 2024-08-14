#ifndef Unit_ComPortH
#define Unit_ComPortH
//---------------------------------------------------------------------------

// C library headers
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#include <sys/ioctl.h>

// Define my types
#define BYTE  uint8_t
#define DWORD uint16_t

//#define BAUDRATE  921600
#define BAUDRATE 115200
#define DIM_ADQ  128

#define SFD      '#'
#define EOFCOM   255
//---------------------------------------------------------------------------

int32_t OpenCommPort(uint32_t Baudios); // Abre la comunicacion
int32_t CloseCommPort(void);            // Cierra la comunicacion

bool ComAbierto(void);          // Devuelve 1 si hay un puerto abierto
int32_t ComNum(void);           // Devuelve el numero del puerto COM abierto
int32_t BytesDisponibles(void); // Devuelve la cantidad de Bytes en el buffer de entrada
DWORD ComError(void); // Devuelve en una variable de 32 bits los errores del puerto. Luego los flags
                      // de error del dispositivo son borrados.

int32_t GetByte(BYTE * value);                // Lectura un caracter
int32_t ReadBytes(void * Buffer, int32_t n);  // Lectura de n del buffer de entrada
int32_t PutByte(BYTE value);                  // Envio de un caracter
int32_t WriteBytes(void * Buffer, int32_t n); // Escritura de n en el buffer de entrada
bool sendSciMsg(BYTE codigo, void * data, DWORD dataLen);

//---------------------------------------------------------------------------
#endif
