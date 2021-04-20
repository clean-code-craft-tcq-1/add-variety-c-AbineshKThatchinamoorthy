/******************************************************************************
*****     (C) COPYRIGHT Robert Bosch GmbH CM-CI2 - All Rights Reserved     *****
******************************************************************************/
/*!
***     \file        typewise-alert.c
***     \author
\nt                  Abinesh KanjiKovil Thatchinamoorthy
***
\par    File_description
***                  Implementation of Battery Alert management system
/*****************************************************************************/

#include "typewise-alert.h"
#include <stdio.h>

BatteryLimit_s BatteryLimit[3] = {{0,35},{0,45},{0,40}};
printChargeLevel_Mail_s printChargeLevel_Mail[3] = {charge_Normal,charge_TooLow,charge_TooHigh};
alert_Target_s alert_Target[3] = {sendToController,sendToEmail,sendToConsole};
Alert_Status_s Alert_Status = {NO_PRINT_DONE,DEFAULT_BREACH};

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{	  
  if(temperatureInC < BatteryLimit[coolingType].lowerLimit) {
    return TOO_LOW;
  }
  if(temperatureInC > BatteryLimit[coolingType].upperLimit) {
    return TOO_HIGH;
  }
  
  return NORMAL;
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: checkAndAlert
 */
/*!    \brief    Checks the received value against thresholds and alert for action
 *
 *               It is valid if either the bits are masked as "don't care" or the
 *               value matches one of the allowed value (<= maxValue).
 *
 *     \param    alertTarget - target which should receive the alert
 *     \param    batteryChar - Cooling Type
 *	   \param    temperatureInC - actual value
 *     \returns  Alert_Status
 *
 *//*------------------------------------------------------------------------*/
Alert_Status_s checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

	alert_Target[alertTarget].alertTargetType(breachType);
	
	Alert_Status.breachType = breachType;
	return Alert_Status;
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  Alert_Status.Alert_Print_Status = PRINTED_IN_CONTROLLER;
}

void sendToEmail(BreachType breachType) 
{  
  printChargeLevel_Mail[breachType].printChargeLevel();
  Alert_Status.Alert_Print_Status = PRINTED_IN_EMAIL;
}

void sendToConsole(BreachType breachType) 
{
  printf("%x\n", breachType);
  Alert_Status.Alert_Print_Status = PRINTED_IN_CONSOLE;
}

void charge_TooLow(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
}

void charge_TooHigh(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
}

void charge_Normal(void)
{
	//Do Nothing
}

/* EOF */
