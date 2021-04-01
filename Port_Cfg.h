/**--------------------------------------------------------------------------------------------------------------------------
* module     : Port
* file name  : port_Cfg.h
* Author     : Abdelrahman OUN
* Created on : march 26, 2021
* description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
--------------------------------------------------------------------------------------------------------------------------*/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
* Module Version 1.0.0
*/
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
* AUTOSAR Version 4.0.3
*/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for setting Pin direction API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for setting Pin mode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)


/* Number of the configured Port Channels */
#define PORT_CONFIGURED_PINS                 (uint8)43

/* PORT Configured Channel ID's */
#define PORT_PIN39_NUM                       (Port_PinType)39 /* Pin 1 in PORTF */
#define PORT_PIN42_NUM                       (Port_PinType)42 /* Pin 4 in PORTF */

/* PORT Configured Pin Direction */
#define PORT_PIN_DIRECTION_DEFAULT           (Port_PinDirectionType)PORT_PIN_IN   /* Default Configuration */
#define PORT_PIN39_DIRECTION                 (Port_PinDirectionType)PORT_PIN_OUT  /*PORTF Pin1 configured as a LED*/
#define PORT_PIN42_DIRECTION                 (Port_PinDirectionType)PORT_PIN_IN   /*PORTF Pin4 configured as a switch*/


/* PORT Configured Pin Internal resistor */
#define PORT_PIN_INTERNAL_RESISTOR_DEFAULT   (Port_InternalResistor)OFF         /* Default Configuration */
#define PORT_PIN39_INTERNAL_RESISTOR         (Port_InternalResistor)OFF         /* PORTF Pin1 configured to Disable internal resistor */
#define PORT_PIN42_INTERNAL_RESISTOR         (Port_InternalResistor)PULL_UP     /* PORTF Pin4 configured to pull up internal resistor */

/*  
 *  for DIO mode        Port_PinModeType = 10u
 *  for analog mode     Port_PinModeType = 00u
 *  for alternate mode  Port_PinModeType = (1 - 9)u or (14u,15u)
 *  the details of alternate modes in GPIO pins and alternate funcations table
 */

/* PORT Configured Pin Initial Mode */
#define PORT_PIN_INITIAL_MODE_DEFAULT        (Port_PinModeType)10u  /* Defualt Configuration for DIO*/
#define PORT_PIN39_INITIAL_MODE              (Port_PinModeType)10u  /*PORTF Pin1 Configured for DIO*/
#define PORT_PIN42_INITIAL_MODE              (Port_PinModeType)10u  /*PORTF Pin4 Configured for DIO*/

/* PORT Configured Pin Initial Value */
#define PORT_PIN_LEVEL_VALUE_DEFAULT         (STD_LOW)  /* Default Configuration */
#define PORT_PIN39_LEVEL_VALUE               (STD_LOW)  /* Turn Off the LED */
#define PORT_PIN42_LEVEL_VALUE               (STD_LOW)  /* default configuratino */


/* PORT Configured Pin Mode Changeable*/
#define PORT_PIN_MODE_CHANGEABLE_DEFAULT     (STD_ON)  /* Default Configuration */
#define PORT_PIN39_MODE_CHANGEABLE           (STD_OFF) /* Mode of pin 39 unchangeable */
#define PORT_PIN42_MODE_CHANGEABLE           (STD_ON)



#endif /* PORT_CFG_H */
