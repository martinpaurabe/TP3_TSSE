#include "inc/leds.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












uint16_t puerto_virtual;

void suitsetUp(void) {

}











void setUp(void) {

    leds_init(&puerto_virtual);

}











void tearDown(void) {

}











void suittearDown(void) {

}













void test_todos_los_leds_deben_arrancar_apagados(void) {

    uint16_t puerto_virtual =

        0xFFFF;



    leds_init(&puerto_virtual);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_HEX16);

}













void test_prender_un_solo_led(void) {







    led_turn_on(3);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 2)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_HEX16);



}











void test_prender_y_apagar_led(void) {







    led_turn_on(

        3);



    led_turn_off(3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_HEX16);

}













void test_prender_dos_leds_y_apagar_un_solo_led(void) {







    led_turn_on(3);

    led_turn_on(7);

    led_turn_off(3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 6)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_HEX16);

}











void test_prender_todos_los_leds_juntos(void) {

    leds_turn_on_all();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_HEX16);

}













void test_prender_y_apagar_todos_los_leds_juntos(void) {



    leds_turn_on_all();

    leds_turn_off_all();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_HEX16);

}











void test_prender_un_led_y_verificar_estado(void) {

    led_turn_on(3);

    do {if ((led_is_turned_on(3))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(164)));}} while(0);

}











void test_apagar_un_led_y_verificar_estado(void) {

    do {if (!(led_is_turned_on(3))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(172)));}} while(0);

}











void test_revisar_leds_correctamente_mapeado_en_memoria(void) {

    int i = 1;

    for (; i <= 16; i++) {

        led_turn_on(i);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0001 << (i - 1))), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

       ((void *)0)

       ), (UNITY_UINT)(183), UNITY_DISPLAY_STYLE_HEX16)

                                               ;

        led_turn_off(i);

    }

}
