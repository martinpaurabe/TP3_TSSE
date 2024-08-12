/************************************************************************************************
Copyright 2024, Ingenieria de Software
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

#ifndef LEDS_H
#define LEDS_H

/** @file leds.h
 ** @brief Declaración de las funciones para el manejo del puerto con los leds
 **/

/* === Headers files inclusions ================================================================ */
#include <stdint.h> //La incluyo en el ".h" porque la declaracion de las funciones lo necesita
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
#define CANT_LEDS    16
#define LED_OFFSET   1
#define FIRST_BIT    0x0001
#define ALL_LEDS_OFF 0x0000
#define ALL_LEDS_ON  0xFFFF

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Funcion de inicializacion de los leds. Los inicializa todos apagados
 *
 * @param puerto Puntero a la direccion donde se manejan los pines de los leds
 */
void leds_init(uint16_t * puerto);

/**
 * @brief Funcion que recibe el numero de led que tiene que encender del puerto
 *
 * @param led Número de Led a apagar, contando de 1 (LSB) a 16 (MSB)
 */
void led_turn_on(int led);

/**
 * @brief Funcion que apaga un led determinado del puerto
 *
 * @param led Número de Led a apagar, contando de 1 (LSB) a 16 (MSB)
 */
void led_turn_off(int led);

/**
 * @brief Funcion que enciende todos los leds del puerto
 *
 */
void leds_turn_on_all(void);

/**
 * @brief Funcion que apaga todos los leds del puerto
 *
 */
void leds_turn_off_all(void);

/**
 * @brief Funcion que verfica si un led determinado del arreglo está encendido
 *
 * @param led Número de led que queremos verificar el estado
 * @return true Si el led consultado se encuentra encendido
 * @return false Si el ledo consultado se encuentra apagdo
 */
bool led_is_turned_on(int led);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */