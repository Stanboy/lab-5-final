/*******************************************************************************
* File Name: User_Button.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_User_Button_H) /* Pins User_Button_H */
#define CY_PINS_User_Button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "User_Button_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    User_Button_Write(uint8 value) ;
void    User_Button_SetDriveMode(uint8 mode) ;
uint8   User_Button_ReadDataReg(void) ;
uint8   User_Button_Read(void) ;
uint8   User_Button_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define User_Button_DRIVE_MODE_BITS        (3)
#define User_Button_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - User_Button_DRIVE_MODE_BITS))

#define User_Button_DM_ALG_HIZ         (0x00u)
#define User_Button_DM_DIG_HIZ         (0x01u)
#define User_Button_DM_RES_UP          (0x02u)
#define User_Button_DM_RES_DWN         (0x03u)
#define User_Button_DM_OD_LO           (0x04u)
#define User_Button_DM_OD_HI           (0x05u)
#define User_Button_DM_STRONG          (0x06u)
#define User_Button_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define User_Button_MASK               User_Button__MASK
#define User_Button_SHIFT              User_Button__SHIFT
#define User_Button_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define User_Button_PS                     (* (reg32 *) User_Button__PS)
/* Port Configuration */
#define User_Button_PC                     (* (reg32 *) User_Button__PC)
/* Data Register */
#define User_Button_DR                     (* (reg32 *) User_Button__DR)
/* Input Buffer Disable Override */
#define User_Button_INP_DIS                (* (reg32 *) User_Button__PC2)


#if defined(User_Button__INTSTAT)  /* Interrupt Registers */

    #define User_Button_INTSTAT                (* (reg32 *) User_Button__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define User_Button_DRIVE_MODE_SHIFT       (0x00u)
#define User_Button_DRIVE_MODE_MASK        (0x07u << User_Button_DRIVE_MODE_SHIFT)


#endif /* End Pins User_Button_H */


/* [] END OF FILE */
