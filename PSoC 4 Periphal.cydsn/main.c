/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is the source code for the PSoC 4 BLE Finde Me Code Example.
*
* Hardware Dependency:
*  CY8CKIT-042 BLE Pioneer Kit
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include <project.h>

/***************************************
*        API Constants
***************************************/
#define NO_ALERT           (0u)
#define MILD_ALERT         (1u)
#define HIGH_ALERT         (2u)

#define NO_ALERT_COMPARE   (0u)
#define MILD_ALERT_COMPARE (250u)
#define HIGH_ALERT_COMPARE (500u)

#define TRUE  1
#define FALSE 0

#define LED_OFF							0x01
#define LED_ON							0x00

/***************************************
*        Function Prototypes
***************************************/
void StackEventHandler(uint32 event, void* eventParam);
void IasEventHandler(uint32 event, void* eventParam);
void HandleAlertLEDs(uint8 status);

//Connection Handle Value

CYBLE_CONN_HANDLE_T connectionHandle;


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
int main()
{
   
    //Intialization of Board
    CyGlobalIntEnable; 

    /* Start the BLE component and register StackEventHandler function */
    CyBle_Start(StackEventHandler);
    
    

    /* Register IAS event handler function */
    CyBle_IasRegisterAttrCallback(IasEventHandler);
    
    Pin_R_Write(LED_OFF);
    Pin_G_Write(LED_OFF);
    Pin_B_Write(LED_OFF);
    
    
    for(;;)
    {
        /* Process all the pending BLE tasks. This single API call to 
         * will service all the BLE stack events. This API MUST be called at least once
         * in a BLE connection interval */
        CyBle_ProcessEvents();
    }
}

/*******************************************************************************
* Function Name: StackEventHandler
********************************************************************************
*
* Summary:
*  This is an event callback function to receive events from the BLE Component.
*
* Parameters:  
*  uint8 event:       Event from the CYBLE component
*  void* eventParams: A structure instance for corresponding event type. The 
*                     list of event structure is described in the component 
*                     datasheet.
*
* Return: 
*  None
*
*******************************************************************************/
void StackEventHandler(uint32 event, void *eventParam)
{
    switch(event)
    {
        /* Mandatory events to be handled by Find Me Target design */
        case CYBLE_EVT_STACK_ON:
        
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            Pin_B_Write(LED_ON);
            Pin_R_Write(LED_ON);
            Pin_G_Write(LED_ON);
            
            break;
            
        case CYBLE_EVT_TIMEOUT:
		/* Timeout has occured */
            if(CYBLE_GAP_ADV_MODE_TO == *(uint8 *) eventParam)
            {
            /* Advertisement timeout has occured - stop advertisement */
                CyBle_GappStopAdvertisement();
            }
	        break;
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
		/* Restart Advertisement if the state is disconnected */
		    if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED )
		    {
			    CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
                Pin_B_Write(LED_ON);
                Pin_R_Write(LED_ON);
                Pin_G_Write(LED_ON);
		    }

            break;
            
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* ADD_CODE - Start the BLE fast advertisement. */
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            
            Pin_B_Write(LED_ON);
            Pin_R_Write(LED_ON);
            Pin_G_Write(LED_ON);
            break;
            
        case CYBLE_EVT_GATT_CONNECT_IND:
		/* Extract connection handle */
        connectionHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;	
		
		/* Start PWM for LED status control */
		
        Pin_B_Write(LED_OFF);
        Pin_R_Write(LED_OFF);
        Pin_G_Write(LED_OFF);
        
        break;
        
        default:
    	    break;
    }
}

/*******************************************************************************
* Function Name: IasEventHandler
********************************************************************************
*
* Summary:
*  This is an event callback function to receive events from the BLE Component,
*  which are specific to Immediate Alert Service.
*
* Parameters:  
*  uint8 event:       Write Command event from the CYBLE component.
*  void* eventParams: A structure instance of CYBLE_GATT_HANDLE_VALUE_PAIR_T
*                     type.
*
* Return: 
*  None
*
*******************************************************************************/
void IasEventHandler(uint32 event, void *eventParam)
{
    /* Local variables */
    uint8 alertLevel;
    CYBLE_IAS_CHAR_VALUE_T *iasWrCmdValueParam;
    
    if(event == CYBLE_EVT_IASS_WRITE_CHAR_CMD)
    {
        /* Check if the event received was for writing Alert level */
        iasWrCmdValueParam = (CYBLE_IAS_CHAR_VALUE_T *)eventParam;
            
		/* If size of received attribute is equal to size of Alert level data */
        if(CYBLE_IAS_ALERT_LEVEL_SIZE == iasWrCmdValueParam->value->len)
        {
			/* Extract the alert level value received from Client device*/
            alertLevel = *((iasWrCmdValueParam->value->val));
        
        /*Based on alert Level level recieved, Drive LED*/
        HandleAlertLEDs(alertLevel);
        }
        
    }
}

/*******************************************************************************
* Function Name: HandleAlertLEDs
********************************************************************************
*
* Summary:
*  This function drives the LED based on the alert level
*
* Parameters:  
*  uint8 status:      Alert level 
*
* Return: 
*  None
*
*******************************************************************************/
void HandleAlertLEDs(uint8 status)
{
    /* Update Alert LED status based on IAS Alert level characteristic. */
    switch(status)
    {
        case NO_ALERT:
            Pin_R_Write(LED_ON);
            Pin_G_Write(LED_OFF);
            Pin_B_Write(LED_OFF);
            break;

        case MILD_ALERT:
            Pin_G_Write(LED_ON);
            Pin_R_Write(LED_OFF);
            Pin_B_Write(LED_OFF);
            break;
            
        case HIGH_ALERT:
            Pin_B_Write(LED_ON);
            Pin_R_Write(LED_OFF);
            Pin_G_Write(LED_OFF);
            break;                
    }
}


/* [] END OF FILE */
