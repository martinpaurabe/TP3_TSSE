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

/** @file test_led.c
 ** @brief Definicion de las funciones de prueba del proyecto
 **/

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "leds.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
uint16_t puerto_virtual;
/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

/**
 * @brief Función que se ejecuta antes de todas las pruebas (Una Sola vez)
 *
 */
void suitsetUp(void) {
}

/**
 * @brief Función que se ejecuta antes de cada prueba
 *
 */
void setUp(void) {
    leds_init(&puerto_virtual);
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

// Al arrancar el sistema todos los leds tienen que estar apagados.
/**
 * @brief Test 1 = Funcion para testear el funcionamiento del driver de los leds en el arranque
 *
 */
void test_todos_los_leds_deben_arrancar_apagados(void) {
    uint16_t puerto_virtual =
        0xFFFF; // la inicializo en 0xFFFF para poder verificar que apaga todos los leds

    leds_init(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual); // Verifico que haya dejado el puerto en 0x0000
}

/**
 * @brief Test 2 = Despues de arrancar el sistema, con todos los leds apagados, voy a prender un led
 * cualquiera.
 *
 */
void test_prender_un_solo_led(void) {

    // todas las pruebas tienen que arrancar desde el sistema en estado reset y llevarla al estado
    // de prueba (SE ENCARGA SetUP)
    led_turn_on(3); // Cuando diseño las pruebas trato de no pensar en como se van a implementar las
                    // funciones
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual); // recordar que el bit inicializa contando
                                                     // desde 1 por eso el shift es por 2
}

/**
 * @brief Test 3 = Voy a prender un led y volver a apagarlo para ver si se apaga.
 *
 */
void test_prender_y_apagar_led(void) {

    // todas las pruebas tienen que arrancar desde el sistema en estado reset y llevarla al estado
    // de prueba (SE ENCARGA SetUP)
    led_turn_on(
        3); // Cuando diseño las pruebas trato de no pensar en como se van a implementar las
            // funciones recordar que el bit inicializa contando desde 1 por eso el shift es por 2
    led_turn_off(3);                                 // Envio a apagar el Led
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual); // Verifico que el led se apagó
}

/**
 * @brief Test 4 = Prender dos leds, apagar uno, y ver que solo se apaga el que corresponde y que el
 * otro sigue prendido.
 *
 */
void test_prender_dos_leds_y_apagar_un_solo_led(void) {

    // todas las pruebas tienen que arrancar desde el sistema en estado reset y llevarla al estado
    // de prueba (SE ENCARGA SetUP)
    led_turn_on(3);
    led_turn_on(7);
    led_turn_off(3);                                 // Envio a apagar el Led
    TEST_ASSERT_EQUAL_HEX16(1 << 6, puerto_virtual); // Verifico que el led se apagó
}

/**
 * @brief Test 5 = Prender todos los leds juntos.
 *
 */
void test_prender_todos_los_leds_juntos(void) {
    leds_turn_on_all();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

/**
 * @brief Test 6 = Prender y apagar todos los leds juntos.
 *
 */

void test_prender_y_apagar_todos_los_leds_juntos(void) {

    leds_turn_on_all();
    leds_turn_off_all();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

/**
 * @brief Test 7 = Prender un led, voy a consultar el estado y tiene que figurar como prendido
 *
 */
void test_prender_un_led_y_verificar_estado(void) {
    led_turn_on(3);
    TEST_ASSERT_TRUE(led_is_turned_on(3));
}

/**
 * @brief Test 8 = Voy a consultar el estado de un led apagado y tiene que figurar como apagado.
 *
 */
void test_apagar_un_led_y_verificar_estado(void) {
    TEST_ASSERT_FALSE(led_is_turned_on(3));
}

/**
 * @brief Test 9 = Revisar que cada led esté bien mapeados en la memoria.
 *
 */
void test_revisar_leds_correctamente_mapeado_en_memoria(void) {
    int i = 1;
    for (; i <= CANT_LEDS; i++) {
        led_turn_on(i);
        TEST_ASSERT_EQUAL_HEX16(FIRST_BIT << (i - LED_OFFSET),
                                puerto_virtual); // Corrijo el -1
        led_turn_off(i);
    }
}

/* === End of documentation ==================================================================== */