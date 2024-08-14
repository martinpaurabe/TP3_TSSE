/************************************************************************************************
Copyright 2024, Testing de Software en Sistemas Embebidos
Facultad de Ingenieria
Universidad de Buenos Aires

Copyright (c) 2023, Martin Paura Bersan <mpb39212@gmail.comr>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef UNIT_THREADCOMPORTH
#define UNIT_THREADCOMPORTH

/** @file Unit_TreadComPort.h
 ** @brief Declaración de las funciones para el manejo del puerto de comunicación
 **/


/* === Headers files inclusions ================================================================ */
#include <time.h>
#include "Unit_ComPort.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
//---------------------------------------------------------------------------
#define ADQ_TIMEOUT      1               // Tiempo de espera para reinciar el parser si no llegan datos
#define SEC_TO_DOUBLE(T) ((T) / 86400.0) // T: Tiempo en segundos

//---------------------------------------------------------------------------
#define ERR_PUERTO 0x01
#define TIMEOUT    0x02

/* === Public data type declarations =========================================================== */
typedef struct {
    uint16_t ComErr;
    int16_t CantBytesRead;
    time_t Tiempo;
    uint8_t EstSciRv;
    uint8_t rxBuf[DIM_ADQ];
    uint8_t rxCantBytes;
    uint8_t rxParser;

} TThreadComPort;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Función para inicializar el puerto de comunicación y el protocolo de bajo nivel
 * 
 * @return int32_t devuelve 0 si se pudo abrir el puerto 1 si hubo un error
 */
int32_t ThreadComPort_Init(void);


/**
 * @brief Funcion para inicializar la tarea de manejo del puerto de comunicación
 * 
 */
int8_t ThreadComPort_Update(void);


/**
 * @brief Función para consultar el estado de las banderas de eventos internos ocurridos
 * 
 * @return uint8_t Devuelve el estado de los errores ocurridos segun flags definidos en este documento
 */
uint8_t ThreadComPort_Error(void) ;

/**
 * @brief Funcion para reiniciar el estado del parser de comunicación
 * 
 */
void ThreadComPort_Rst(void);

/**
 * @brief Función para finalizar el puerto de comunicación y el protocolo de bajo nivel
 * 
 * @return int32_t devuelve 0 si se pudo cerrar el puerto, 1 si hubo un error
 */
int32_t ThreadComPort_End(void);


/**
 * @brief Funcion a definir por el usuario encargada de manejar los datos recibidos en capas superiores
 * 
 * @param buf Puntero al buffer donde se encuentran los datos recibidos
 */
extern void sciDataReceived(BYTE * buf);


/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* UNIT_THREADCOMPORTH */


