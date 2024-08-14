#ifndef Unit_BatChargersSimH
#define Unit_BatChargersSimH
//---------------------------------------------------------------------------
#include "Unit_ThreadComPort.h"
#include "Unit_ComPort.h"



#define BC_NUMBERS  8
//#define EOF  VK_RETURN


//==============================================================================================================
// Protocol Constant Definition
//==============================================================================================================


#define DIM_NOMBRE_GES   12
#define PWM_MAX          600
#define PWM_MED          300
#define PWM_DTM			 200



#define HabOut48On      setRegBit(GPIO_A_DR,D6)
#define HabOut48Off     clrRegBit(GPIO_A_DR,D6)



//Comandos Sci
//*********************************
//Ordenes de habilitacion
#define CMD_BCM_SAVE             0x00
#define CMD_BCM_STATUS           0x01



//Charger Module 1 Orders
#define CMD_BCM_CMOD_1            0x20
#define CMD_BCM_CMOD_1_PWM        0x21
#define CMD_BCM_CMOD_1_TEN_DES    0x22
#define CMD_BCM_CMOD_1_COR_DES    0x23


//Charger Module 2 Orders
#define CMD_BCM_CMOD_2            0x30
#define CMD_BCM_CMOD_2_PWM        0x31
#define CMD_BCM_CMOD_2_TEN_DES    0x32
#define CMD_BCM_CMOD_2_COR_DES    0x33




#define CMD_BCM_GRAL              0x70


//Data Request
#define DRQ_BCM_MOD1           0x80
#define DRQ_BCM_MOD2           0x81
#define DRQ_BCM_MOD3           0x82
#define DRQ_BCM_MOD4           0x83
#define DRQ_BCM_MOD5           0x84
#define DRQ_BCM_MOD6           0x85
#define DRQ_BCM_MOD7           0x86
#define DRQ_BCM_MOD8           0x87


//Data Send
//Pedido de Datos
#define DAT_BCM_MOD1           0xA0
#define DAT_BCM_MOD2           0xA1
#define DAT_BCM_MOD3           0xA2
#define DAT_BCM_MOD4           0xA3
#define DAT_BCM_MOD5           0xA4
#define DAT_BCM_MOD6           0xA5
#define DAT_BCM_MOD7           0xA6
#define DAT_BCM_MOD8           0xA7


//==============================================================================================================
// Variable Types Definitions
//==============================================================================================================

typedef struct 
{
    float   Porc; /* data */
    float   PWM; /* data */
    float   Curr; /* data */
    float   Volt; /* data */
}TChargerMod;



typedef struct 
{
    TChargerMod  ChargerMod1; /* data */
    TChargerMod  ChargerMod2; /* data */
    TChargerMod  ChargerMod3; /* data */
    TChargerMod  ChargerMod4; /* data */
    TChargerMod  ChargerMod5; /* data */
    TChargerMod  ChargerMod6; /* data */
    TChargerMod  ChargerMod7; /* data */
    TChargerMod  ChargerMod8; /* data */
}TBatChargeMon;



//---------------------------------------------------------------------------
#endif
