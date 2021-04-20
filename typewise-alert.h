/******************************************************************************
*****     (C) COPYRIGHT Robert Bosch GmbH CM-CI2 - All Rights Reserved     *****
******************************************************************************/
/*!
***     \file        typewise-alert.c
***     \author
\nt                  Abinesh KanjiKovil Thatchinamoorthy
***
\par    File_description
***                  Header of Battery Alert management system
/*****************************************************************************/

#ifndef BMS_TYPE_ALERT_H_
#define BMS_TYPE_ALERT_H_

#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  DEFAULT_BREACH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE,
  DEFAULT_TARGET
} AlertTarget;

typedef enum {
	PRINTED_IN_CONTROLLER,
	PRINTED_IN_EMAIL,
	PRINTED_IN_CONSOLE,
	NO_PRINT_DONE
}Alert_Print_Status_t;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
	int lowerLimit;
	int upperLimit;
}BatteryLimit_s;

typedef struct 
{
   void (*printChargeLevel)();
}printChargeLevel_Mail_s;

typedef struct{
	void (*alertTargetType)(BreachType breachType);
}alert_Target_s;

typedef struct {
		Alert_Print_Status_t Alert_Print_Status;
		BreachType breachType;
}Alert_Status_s;

Alert_Status_s checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void sendToConsole(BreachType breachType);

void charge_TooLow(void);
void charge_TooHigh(void);
void charge_Normal(void);

#endif /*BMS_TYPE_ALERT_H_*/
