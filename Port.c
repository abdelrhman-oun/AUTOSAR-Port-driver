/**--------------------------------------------------------------------------------------------------------------------------
* module     : Port
* file name  : Port.c
* Author     : Abdelrahman OUN
* Created on : march 27, 2021
* description: Source file for TM4C123GH6PM Microcontroller - Port Driver
--------------------------------------------------------------------------------------------------------------------------*/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigType * Port_PinConfigPtr = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
			PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		uint8 i = 0;
		for (i = 0; i < 43; i++)
		{
			volatile uint8 port_num = 0;               /* hold port number of required pin */
			volatile uint8 port_pin_num = 0;           /* hold pin number in the port of required pin */
			volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
			volatile uint32 delay = 0;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
			/* check if the pin number is valid or not */
			if (ConfigPtr->Pins[i].pin_num >= PORT_CONFIGURED_PINS)
			{
				Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
					PORT_E_PARAM_PIN);
			}
			else
			{
				/* Do Nothing */
			}
#endif
			/*
			* if condition to get the port number and pin number in the port from pin number in MCU
			*/
			if (ConfigPtr->Pins[i].pin_num < 8)
			{
				port_num = 0;
				port_pin_num = ConfigPtr->Pins[i].pin_num;
			}
			else if (ConfigPtr->Pins[i].pin_num < 16)
			{
				port_num = 1;
				port_pin_num = ConfigPtr->Pins[i].pin_num - 8;
			}
			else if (ConfigPtr->Pins[i].pin_num < 24)
			{
				port_num = 2;
				port_pin_num = ConfigPtr->Pins[i].pin_num - 16;
			}
			else if (ConfigPtr->Pins[i].pin_num < 32)
			{
				port_num = 3;
				port_pin_num = ConfigPtr->Pins[i].pin_num - 24;
			}
			else if (ConfigPtr->Pins[i].pin_num < 38)
			{
				port_num = 4;
				port_pin_num = ConfigPtr->Pins[i].pin_num - 32;
			}
			else
			{
				port_num = 5;
				port_pin_num = ConfigPtr->Pins[i].pin_num - 38;
			}


			switch (port_num)
			{
			case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break;
			case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
			case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
			case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
			case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
			case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
			}

			/* Enable clock for PORT and allow time for clock to start*/
			SYSCTL_REGCGC2_REG |= (1 << port_num);
			delay = SYSCTL_REGCGC2_REG;

			if (((port_num == 3) && (port_pin_num == 7)) || ((port_num == 5) && (port_pin_num == 0))) /* PD7 or PF0 */
			{
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), port_pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if ((port_num == 2) && (port_pin_num <= 3)) /* PC0 to PC3 */
			{
				/* Do Nothing ...  this is the JTAG pins */
				continue;
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}

			if (ConfigPtr->Pins[i].direction == PORT_PIN_OUT)
			{
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

				if (ConfigPtr->Pins[i].initial_value == STD_HIGH)
				{
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), port_pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
				}
				else
				{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), port_pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
				}
			}
			else if (ConfigPtr->Pins[i].direction == PORT_PIN_IN)
			{
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

				if (ConfigPtr->Pins[i].resistor == PULL_UP)
				{
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), port_pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
				}
				else if (ConfigPtr->Pins[i].resistor == PULL_DOWN)
				{
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), port_pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
				}
				else
				{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), port_pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), port_pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
				}
			}
			else
			{
				/* Do Nothing */
			}

#if (PORT_DEV_ERROR_DETECT == STD_ON)
			/* check if the chosen mode is valid or not */
			if (ConfigPtr->Pins[i].mode == 11 || ConfigPtr->Pins[i].mode == 12 || ConfigPtr->Pins[i].mode == 13 || ConfigPtr->Pins[i].mode > 14)
			{
				Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
					PORT_E_PARAM_INVALID_MODE);
			}
			else
			{
				/* Do Nothing */
			}
#endif

			if (ConfigPtr->Pins[i].mode == PORT_PIN_MODE_DIO) /* DIO mode - default -*/
			{
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);               /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
			}
			else if (ConfigPtr->Pins[i].mode == PORT_PIN_MODE_ADC) /* ADC mode */
			{
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);                 /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);         /* clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);          /* set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

			}
			else /* alternate mode */
			{
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);                 /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((ConfigPtr->Pins[i].mode & 0x0000000F) << (port_pin_num * 4)); /* put mode number in Pin bits field in the cotrol register */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				
			}
		}
		Port_Status = PORT_INITIALIZED;
		Port_PinConfigPtr = ConfigPtr; /* address of the first Channels structure --> Channels[0] */
	}
}


/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): pin       - Port Pin ID number
                   Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	volatile uint8 port_num = 0;               /* hold port number of required pin */
	volatile uint8 port_pin_num = 0;           /* hold pin number in the port of required pin */
	volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the PORT Pin direction changeable*/
	if (Port_PinConfigPtr->Pins[Pin].direction_changeable == STD_OFF) {
		/* report det error and return withour doing any thing */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		return ;
	}
	else
	{
		/* No Action Required */
	}

	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}

	/* check if the pin number is valid or not */
	if (Pin >= PORT_CONFIGURED_PINS)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
			PORT_E_PARAM_PIN);
	}
	else
	{
		/* Do Nothing */
	}
#endif
	/*
	* if condition to get the port number and pin number in the port from pin number in MCU
	*/
	if (Pin < 8)
	{
		port_num = 0;
		port_pin_num = Pin;
	}
	else if (Pin < 16)
	{
		port_num = 1;
		port_pin_num = Pin - 8;
	}
	else if (Pin < 20)
	{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* ERROR : trying to access JTAG pins */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
			PORT_E_PARAM_PIN);
#endif

		/* Do Nothing ...  this is the JTAG pins */
		return ;
	}
	else if (Pin < 24)
	{
		port_num = 2;
		port_pin_num = Pin - 16;
	}
	else if (Pin < 32)
	{
		port_num = 3;
		port_pin_num = Pin - 24;
	}
	else if (Pin < 38)
	{
		port_num = 4;
		port_pin_num = Pin - 32;
	}
	else
	{
		port_num = 5;
		port_pin_num = Pin - 38;
	}

	switch (port_num)
	{
	case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		break;
	case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		break;
	case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		break;
	}

	if (Direction == PORT_PIN_OUT)
	{
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
	}
	else if (Direction == PORT_PIN_IN)
	{
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);              /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
	}
	else
	{
		/* Do Nothing */
	}

}
#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port driver module.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
	uint8 i = 0;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
#endif

	for (i = 0; i < 43; i++)
	{
		volatile uint8 port_num = 0;               /* hold port number of required pin */
		volatile uint8 port_pin_num = 0;           /* hold pin number in the port of required pin */
		volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

		/*
		* if condition to get the port number and pin number in the port from pin number in MCU
		*/
		if (i < 8)
		{
			port_num = 0;
			port_pin_num = i;
		}
		else if (i < 16)
		{
			port_num = 1;
			port_pin_num = i - 8;
		}
		else if (i < 20)
		{
			/* Do Nothing ...  this is the JTAG pins */
			continue;
		}
		else if (i < 24)
		{
			port_num = 2;
			port_pin_num = i - 16;
		}
		else if (i < 32)
		{
			port_num = 3;
			port_pin_num = i - 24;
		}
		else if (i < 38)
		{
			port_num = 4;
			port_pin_num = i - 32;
		}
		else
		{
			port_num = 5;
			port_pin_num = i - 38;
		}


		switch (port_num)
		{
		case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			break;
		case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
			break;
		case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
			break;
		case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
			break;
		case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
			break;
		case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
			break;
		}

		if (BIT_IS_CLEAR(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num))
		{
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
		}
		else if (BIT_IS_SET(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num))
		{
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), port_pin_num);             /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
		}
	}
}


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version 
*                                 information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}

}
#endif


/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin   - Port Pin ID number
*                  Mode  - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	volatile uint8 port_num = 0;               /* hold port number of required pin */
	volatile uint8 port_pin_num = 0;           /* hold pin number in the port of required pin */
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
	/* check if the pin number is valid or not */
	if (Pin >= PORT_CONFIGURED_PINS)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
			PORT_E_PARAM_PIN);
	}
	else
	{
		/* Do Nothing */
	}
#endif

	/*
	* if condition to get the port number and pin number in the port from pin number in MCU
	*/
	if (Pin < 8)
	{
		port_num = 0;
		port_pin_num = Pin;
	}
	else if (Pin < 16)
	{
		port_num = 1;
		port_pin_num = Pin - 8;
	}
	else if (Pin < 20)
	{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* ERROR : trying to access JTAG pins */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
			PORT_E_PARAM_PIN);
#endif

		/* Do Nothing ...  this is the JTAG pins */
		return;
	}
	else if (Pin < 24)
	{
		port_num = 2;
		port_pin_num = Pin - 16;
	}
	else if (Pin < 32)
	{
		port_num = 3;
		port_pin_num = Pin - 24;
	}
	else if (Pin < 38)
	{
		port_num = 4;
		port_pin_num = Pin - 32;
	}
	else
	{
		port_num = 5;
		port_pin_num = Pin - 38;
	}

	switch (port_num)
	{
	case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		break;
	case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		break;
	case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		break;
	}

	/* check if the pin is not changeable */
	if (Port_PinConfigPtr->Pins[Pin].mode_changeable == STD_OFF)
	{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* report Det error */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
			PORT_E_MODE_UNCHANGEABLE);
#endif
		return;   /* return without any action */
	}
	else
	{
		/* Do Nothing */
	}

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the mode is not valid */
	if (Mode == 11 || Mode == 12 || Mode == 13 || Mode > 14)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
			PORT_E_PARAM_INVALID_MODE);
	}
	else
	{
		/* Do Nothing */
	}
#endif

	if (Mode == PORT_PIN_MODE_DIO) /* DIO mode*/
	{
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);               /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
	}
	else if (Mode == PORT_PIN_MODE_ADC) /* Analog mode */
	{
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);                 /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);         /* clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);          /* set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

	}
	else /* alternate mode */
	{
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), port_pin_num);                 /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_pin_num * 4));      /* Clear the PMCx bits for this pin */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Mode & 0x0000000F) << (port_pin_num * 4)); /* put mode number in Pin bits field in the cotrol register */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), port_pin_num);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), port_pin_num);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

	}

}
#endif


