/**--------------------------------------------------------------------------------------------------------------------------
* module     : Port
* file name  : Port.h
* Author     : Abdelrahman OUN
* Created on : march 27, 2021
* description: Header file for TM4C123GH6PM Microcontroller - Port Driver
--------------------------------------------------------------------------------------------------------------------------*/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
* for example OUN's ID = 2277 :) */
#define PORT_VENDOR_ID    (2277U)

/* Port Module Id */
#define PORT_MODULE_ID    (140U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
* Module Version 1.0.0
*/
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (1U)

/*
* AUTOSAR Version 4.0.3
*/
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
* Macros for Port Status
*/
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"


/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------API Service Id Macros---------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/* Service ID for PORT Init */
#define PORT_INIT_SID                     (uint8)0x00

/* Service ID for PORT Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID        (uint8)0x01

/* Service ID for PORT Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID   (uint8)0x02

/* Service ID for PORT Get Version Information */
#define PORT_GET_VERSION_INFO_SID         (uint8)0x03

/* Service ID for PORT Set Pin Mode */
#define PORT_SET_PIN_MODE_SID             (uint8)0x04


/*--------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------DET Error Codes------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                   (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE      (uint8)0x0B

/* API Port_Init service called with wrong parameter or NULL pointer */
#define PORT_E_PARAM_CONFIG                (uint8)0x0C

/* API Port_SetPinMode service called with unavailable mode */
#define PORT_E_PARAM_INVALID_MODE          (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE           (uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                      (uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER               (uint8)0x10


/*--------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------Module Data Types-----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN direction */
typedef enum
{
	PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
	OFF, PULL_UP, PULL_DOWN
}Port_InternalResistor;                                               /***************************/


/* Description: Structure to configure each individual PIN:
 *	1. the number of the pin in the MCU.
 *  2. the direction of pin --> INPUT or OUTPUT
 *  3. the initial value of the pin --> LOW or HIGH
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the mode changeabel of pin --> ON or OFF
 *  6. the mode of the pin
 */
typedef struct
{
	/* Member contains the ID of the PIN */
	Port_PinType pin_num;
	/* Member contains the direction of the PIN */
	Port_PinDirectionType direction;
	/* Member contains the direction changeable or not of the PIN*/
	uint8 direction_changeable;
	/* Member contains the initial value of the PIN */
	uint8 initial_value;
	/* Member contains the initial internal resistor of the PIN */
	Port_InternalResistor resistor;
	/* Member contains the mode changeable or not of the PIN */
	uint8 mode_changeable;
	/* Member contains the ID of the mode of the PIN */
	Port_PinModeType mode;
}Port_ConfigPin;


/* Data Structure required for initializing the Port Driver */
typedef struct
{
	Port_ConfigPin Pins[PORT_CONFIGURED_PINS];
}Port_ConfigType;


/*--------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------Function Prototypes----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/* Function for PORT Initialization API */
void Port_Init(const Port_ConfigType * ConfigPtr);

/* Function for Setting the port pin direction API */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function for PORT refresh direction API */
void Port_RefreshPortDirection(void);

/* Function for PORT Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* Function for Setting the port pin mode. */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

/*--------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------External Variables----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */

