/**--------------------------------------------------------------------------------------------------------------------------
* module     : Port
* file name  : Port_PBcfg.c
* Author     : Abdelrahman OUN
* Created on : march 27, 2021
* description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
--------------------------------------------------------------------------------------------------------------------------*/

#include "Port.h"

/*
* Module Version 1.0.0
*/
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (1U)

/*
* AUTOSAR Version 4.0.3
*/
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {

	 0,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 1,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 2,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 3,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 4,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 5,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 6,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 7,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 8,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	 9,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	10,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	11,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	12,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	13,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	14,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	15,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	16,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	17,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	18,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	19,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	20,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	21,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	22,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	23,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	24,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	25,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	26,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	27,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	28,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	29,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	30,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	31,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	32,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	33,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	34,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	35,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	36,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	37,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	38,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	PORT_PIN_39_NUM,PORT_PIN_39_DIRECTION,PORT_PIN_39_DIRECTION_CHANGEABLE,PORT_PIN_39_LEVEL_VALUE,PORT_PIN_39_INTERNAL_RESISTOR,PORT_PIN_39_MODE_CHANGEABLE,PORT_PIN_39_INITIAL_MODE,
	40,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	41,PORT_PIN_DIRECTION_DEFAULT,PORT_PIN_DIRECTION_CHANGEABLE_DEFAULT,PORT_PIN_LEVEL_VALUE_DEFAULT,PORT_PIN_INTERNAL_RESISTOR_DEFAULT,PORT_PIN_MODE_CHANGEABLE_DEFAULT,PORT_PIN_INITIAL_MODE_DEFAULT,
	PORT_PIN_42_NUM,PORT_PIN_42_DIRECTION,PORT_PIN_42_DIRECTION_CHANGEABLE,PORT_PIN_42_LEVEL_VALUE,PORT_PIN_42_INTERNAL_RESISTOR,PORT_PIN_42_MODE_CHANGEABLE,PORT_PIN_39_INITIAL_MODE,

};