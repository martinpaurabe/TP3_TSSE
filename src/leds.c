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

/** @file leds.c
 ** @brief Definicion de las funciones para el manejo de los leds
 **/

/* === Headers files inclusions =============================================================== */
#include "leds.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
static uint16_t * puerto_virtual;

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
static uint16_t led_to_mask(int led) {
    return (FIRST_BIT << (led - LED_OFFSET));
}
/* === Public function implementation ========================================================== */

void leds_init(uint16_t * puerto) {
    puerto_virtual = puerto;
    *puerto_virtual = ALL_LEDS_OFF; // Mínimo código posible para resolver el problema actual
}

void led_turn_on(int led) { // Si la prueba la hago para un led detarminado podria llamar la fucnion
                            // led_turn_on_3(void) y que la misma no tenga parámetros.
    *puerto_virtual |=
        led_to_mask(led); // Inicialmente se tiene que hacer hardcodeado y a
                          // medida que vamos pasando los requerimientos se va complicando, por
                          //  eso es importante ir realizando las pruebas en orden de
                          //  complejidad de los requerimientos (primero los mas sensillos)
}

void led_turn_off(int led) {

    *puerto_virtual &=
        ~led_to_mask(led); // Inicialmente se tiene que hacer hardcodeado y
                           // a medida que vamos pasando los requerimientos se va complicando,
                           //  por eso es importante ir realizando las pruebas en orden de
                           //  complejidad de los requerimientos (primero los mas sensillos)
}

void leds_turn_on_all(void) {
    *puerto_virtual = ALL_LEDS_ON; // Mínimo código posible para resolver el problema actual
}

void leds_turn_off_all(void) {
    *puerto_virtual = ALL_LEDS_OFF; // Mínimo código posible para resolver el problema actual
}

bool led_is_turned_on(int led) {
    return (led_to_mask(led) & *puerto_virtual) ? true : false;
}

/* === End of documentation ==================================================================== */