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
	CONFIGURANDO_SENSOR = 0,
	AGUARDANDO_DADOS,
	LENDO_DADOS,
	INTERPRETANDO_DADOS,
	DESCONFIGURANDO_SENSOR,
	VERIFICANDO_TIPO_FALHA,
	ENCERRANDO_ROTINA
} sensor_EstadosEnum_t;

/*
 * Controle do estado atual da m�quina.
 */
static sensor_EstadosEnum_t estadoMaquina = CONFIGURANDO_SENSOR;
static SENSOR_RETORNO estadoSensor = SENSOR_PRONTO;

/*
 * Rotina para execu��o da m�quina de estados, conforme diagrama do Modelio - localizado na pasta documentos.
 */
void sensor_stateMachine(void) {
	while (1) {
		switch (estadoMaquina) {
		case CONFIGURANDO_SENSOR:

			estadoSensor = CONFIGURA_SENSOR_PORT();

			if (estadoSensor == CONFIGURACAO_OK)
				estadoMaquina = AGUARDANDO_DADOS;
			else if (estadoSensor == FALHA_CONFIGURACAO)
				estadoMaquina = DESCONFIGURANDO_SENSOR;

			break;

		case AGUARDANDO_DADOS:
			estadoSensor = AGUARDA_DADOS_PORT();

			if (estadoSensor == TEMPO_ESGOTADO)
				estadoMaquina = DESCONFIGURANDO_SENSOR;
			else if (estadoSensor == AMOSTRA_PRONTA)
				estadoMaquina = LENDO_DADOS;

			break;

		case LENDO_DADOS:
			estadoSensor = LER_DADOS_PORT();

			if (estadoSensor == FALHA_SENSOR)
				estadoMaquina = DESCONFIGURANDO_SENSOR;
			else if (estadoSensor == AMOSTRA_OK)
				estadoMaquina = INTERPRETANDO_DADOS;

			break;

		case INTERPRETANDO_DADOS:
			estadoSensor = INTERPRETA_DADOS_PORT();

			if (estadoSensor == DADOS_VALIDOS)
				estadoMaquina = AGUARDANDO_DADOS;
			else if (estadoSensor == DADOS_INVALIDOS)
				estadoMaquina = DESCONFIGURANDO_SENSOR;

			break;

		default:
		case DESCONFIGURANDO_SENSOR:
			estadoSensor = DESCONFIGURA_SENSOR_PORT();

			if (estadoSensor == DESCONFIGURACAO_OK)
				estadoMaquina = VERIFICANDO_TIPO_FALHA;
			else if (estadoSensor == FALHA_DESCONFIGURACAO)
				estadoMaquina = ENCERRANDO_ROTINA;

			break;

		case VERIFICANDO_TIPO_FALHA:
			estadoSensor = VERIFICA_TIPO_FALHA_PORT();

			if (estadoSensor == FALHA_RECUPERAVEL)
				estadoMaquina = CONFIGURANDO_SENSOR;
			else if (estadoSensor == FALHA_PERMANENTE)
				estadoMaquina = ENCERRANDO_ROTINA;

			break;

		case ENCERRANDO_ROTINA:
			return;

		}
	}
}
