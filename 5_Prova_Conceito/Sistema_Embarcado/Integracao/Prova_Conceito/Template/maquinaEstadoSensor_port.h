/*
 ******************************************************************************
 * @file    maquinaEstadoSensor_port.h
 * @author  V�tor Eduardo Sabadine da Cruz
 * @version 0
 * @date    10-Outubro-2019
 * @brief   M�quina de estados para tratamento de sensor gen�rico.
 ******************************************************************************
 */

#include "stdint.h"

#define		SENSOR_RETORNO									uint8_t

#define 	CONFIGURACAO_OK									1
#define 	FALHA_CONFIGURACAO							2

#define		CONFIGURA_SENSOR_PORT()					FALHA_CONFIGURACAO
