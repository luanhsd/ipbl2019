/*
 ******************************************************************************
 * @file    maquinaEstadoSensor.c
 * @author  V�tor Eduardo Sabadine da Cruz
 * @version 0
 * @date    10-Outubro-2019
 * @brief   M�quina de estados para tratamento de sensor gen�rico.
 ******************************************************************************
 */

#include "maquinaEstadoSensor_port.h"
#include "maquinaEstadoSensor.h"

/*
 * Defini��o dos estados da m�quina.
 */
typedef enum {
	CONFIGURA_SENSOR = 0,
	AGUARDA_DADOS,
	LER_DADOS,
	INTERPRETA_DADOS,
	VERIFICA_TIPO_FALHA,
	DESCONFIGURA_SENSOR
} sensor_EstadosEnum_t;

/*
 * Controle do estado atual da m�quina.
 */
static sensor_EstadosEnum_t estadoMaquina = 0;

/*
 * Rotina para execu��o da m�quina de estados, conforme diagrama do Modelio - localizado na pasta documentos.
 */
void sensor_stateMachine(void) {
	switch (estadoMaquina) {
	case CONFIGURA_SENSOR: {
		SENSOR_RETORNO estadoSensor;

		estadoSensor = CONFIGURA_SENSOR_PORT();

		if (estadoSensor == CONFIGURACAO_OK)
			estadoMaquina = LER_DADOS;
		else if (estadoSensor == FALHA_CONFIGURACAO)
			estadoMaquina = VERIFICA_TIPO_FALHA;

	}
		break;

	case AGUARDA_DADOS:

		break;

	case LER_DADOS:
		break;

	case INTERPRETA_DADOS:
		break;

	case VERIFICA_TIPO_FALHA:
		break;

	default:
	case DESCONFIGURA_SENSOR:
		break;

	}
}
