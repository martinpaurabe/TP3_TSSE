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

/************************************************************************************************
Requerimientos:
Reconocer el protocolo con SFD-Cantidad de Datos-Datos-EOFCOM
Enviar mensaje de error en caso que el formato de la trama sea incorrecta
Enviar mensaje de error indicando en caso que la cantidad de datos sea menor a 1
Cerrar el puerto y enviar mensaje de error indicando en caso que la cantidad de datos sea mayor a
DIM_ADQ
Llamar a la función void sciDataReceived(BYTE *buf) en caso que se reciba un mensaje válido
El parser del Thread Comm Port se tiene que resetear si no tiene actividad por ADQ_TIMEOUT
*************************************************************************************************/

/************************************************************************************************
Pruebas:


Recibir mensaje con campo "Cantidad de Datos" igual a 0
Recibir mensaje con longitud de datos menor a "Cantidad de Datos"
Recibir mensaje correcto y verificar que llama a la funcion void sciDataReceived(BYTE *buf);
*************************************************************************************************/

/** @file test_led.c
 ** @brief Definicion de las funciones de prueba del proyecto
 **/

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "mock_Unit_ComPort.h"
#include "Unit_ThreadComPort.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
static int rxIndex = 0;
bool sciCalled = false;
/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

int32_t Auxiliar_OpenCommPort(uint32_t Baudios) {
    return 0;
}

void auxiliar_CloseCommPort(void) {
    return;
}; // Cierra la comunicacion

int32_t auxiliar_ReadBytes_sin_dato(void * Buffer, int n) {

    uint8_t msg_seq[] = {SFD, 0, EOFCOM};

    *(uint8_t *)Buffer = msg_seq[rxIndex++];
    rxIndex %= sizeof(msg_seq);
    return 1;
};

int32_t auxiliar_ReadBytes_un_dato(void * Buffer, int n) {

    uint8_t msg_seq[] = {SFD, 1, 1, EOFCOM};

    *(uint8_t *)Buffer = msg_seq[rxIndex++];
    rxIndex %= sizeof(msg_seq);
    return 1;
};

int32_t auxiliar_ReadBytes_buffer_sobrecargado(void * Buffer, int n) {

    uint8_t msg_seq[] = {SFD, DIM_ADQ + 1, 1, SFD};

    *(uint8_t *)Buffer = msg_seq[rxIndex++];
    rxIndex %= sizeof(msg_seq);
    return 1;
};

int32_t auxiliar_ReadBytes_EOFCOM_incorrecto(void * Buffer, int n) {

    uint8_t msg_seq[] = {SFD, 1, 1, SFD};

    *(uint8_t *)Buffer = msg_seq[rxIndex++];
    rxIndex %= sizeof(msg_seq);
    return 1;
};

void sciDataReceived(BYTE * buf) {
    sciCalled = true;
};
/* === Public function implementation ========================================================== */

/**
 * @brief Función que se ejecuta antes de todas las pruebas (Una Sola vez)
 *
 */
void suitsetUp(void) {
    OpenCommPort_fake.custom_fake = Auxiliar_OpenCommPort;
    ThreadComPort_Init();
}

/**
 * @brief Función que se ejecuta antes de cada prueba
 *
 */
void setUp(void) {
    ThreadComPort_Rst();
    rxIndex = 0;
    sciCalled = false;
}

/**
 * @brief Función que se ejecuta despues de cada una de las pruebas
 *
 */
void tearDown(void) {
}

/**
 * @brief Función que se ejecuta al final todas las pruebas (Una sola vez)
 *
 */
void suittearDown(void) {
}

// Recibir el mensaje con el formato esperado y procesarlo correctamente
/**
 * @brief Funcion que evalua se se procesa en forma correcta un mensaje y que el parser cambie de
 * estado correctamente.
 *
 */
void test_rx_msg_Formato_Correcto(void) {

    BytesDisponibles_fake.return_val = 1;
    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_un_dato;
    TEST_ASSERT_EQUAL(1, ThreadComPort_Update()); // recibio en forma correcta el SFD
    TEST_ASSERT_EQUAL(2, ThreadComPort_Update()); // recibió en forma correcta la cantidad
    TEST_ASSERT_EQUAL(3, ThreadComPort_Update()); // recibio la cantidad de datos que correspondia
    TEST_ASSERT_EQUAL(0, ThreadComPort_Update()); // Al final de la trama vino EPFCOM
}

// Recibir mensaje con caracter SFD incorrecto
/**
 * @brief Verifica que ante la llegada de un SDF incorrecto no cambia el estado de parser al
 * siguiente estado
 *
 */
void test_rx_msg_SDF_incorrecto(void) {

    BytesDisponibles_fake.return_val = 1;
    rxIndex = 1; // envió un dato que no SFD
    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_un_dato;
    TEST_ASSERT_EQUAL(0, ThreadComPort_Update()); // no tengo que cambiar el estado del parser
}

// Verificar que luego de ADQ_TIMEOUT el parser se resetea
/**
 * @brief Fuincion que  inicializa la trama pero no la continua. Espera un tiempo para verificar que
 * el parser de comunicación se resetea.
 *
 */
void test_rst_parser_si_no_llegan_datos(void) {

    time_t start_t, end_t;
    double diff_t;

    BytesDisponibles_fake.return_val = 1;
    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_un_dato;
    ThreadComPort_Update(); // inicio una trama para probar que si pasa el
                            // tiempo sin datos se reinicia el parser
    sleep(3 * ADQ_TIMEOUT);
    BytesDisponibles_fake.return_val = 0;
    ThreadComPort_Update();
    TEST_ASSERT_EQUAL(0, ThreadComPort_Update());
    sleep(2 * ADQ_TIMEOUT);
}

// Recibir mensaje con caracter EOFCOM incorrecto
/**
 * @brief
 *
 */
void test_rx_EOFCOM_Incorrecto(void) {

    BytesDisponibles_fake.return_val = 1;

    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_EOFCOM_incorrecto;
    ThreadComPort_Update(); // recibio en forma correcta el SFD
    ThreadComPort_Update(); // recibió en forma correcta la cantidad
    ThreadComPort_Update(); // recibio la cantidad de datos que correspondia
    ThreadComPort_Update(); // Al final de la trama vino EPFCOM
    TEST_ASSERT_FALSE_MESSAGE(sciCalled, "NO ENVIÖ A PROCESAR MENSAJE");
}

// Recibir mensaje con campo "Cantidad de Datos" igual a 0
/**
 * @brief Funcion para probar que verifica bien si la cantidad de datos que ingresan del mensaje es
 * cero
 *
 */
void test_rx_Cant_Datos_cero(void) {
    BytesDisponibles_fake.return_val = 1;
    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_sin_dato;
    TEST_ASSERT_EQUAL(1, ThreadComPort_Update()); // recibio en forma correcta el SFD
    TEST_ASSERT_EQUAL(0, ThreadComPort_Update()); // recibió en forma incorrecta la cantidad
}

// Recibir mensaje con campo "Cantidad de Datos" igual a DIM_ADQ + 1
/**
 * @brief Funcion para probar que verifica bien si la cantidad de datos que es mayor al buffer
 *
 */
void test_rx_Cant_Datos_Maximo(void) {
    BytesDisponibles_fake.return_val = 1;
    ReadBytes_fake.custom_fake = auxiliar_ReadBytes_buffer_sobrecargado;
    CloseCommPort_fake.custom_fake = 0;
    TEST_ASSERT_EQUAL(1, ThreadComPort_Update()); // recibio en forma correcta el SFD
    BytesDisponibles_fake.return_val = DIM_ADQ + 1;
    TEST_ASSERT_EQUAL(-1,
                      ThreadComPort_Update()); // recibió en forma incorrecta la cantidad, verifico
                                               // que envia un error por sobrecarga del buffer
}
/* === End of documentation ==================================================================== */