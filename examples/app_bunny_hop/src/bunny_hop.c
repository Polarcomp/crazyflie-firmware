#include <string.h>
#include "app.h"

#include "commander.h"

#include "FreeRTOS.h"
#include "task.h"

#include "debug.h"

#define DEBUG_MODULE "BUNNY_HOP"

static void	zeroSetpoint(setpoint_t *setpoint)
{
	bzero(setpoint, sizeof(setpoint_t));
	commanderSetSetpoint(setpoint, 3);
}

static void	setSetpoint(setpoint_t *setpoint)
{
	setpoint->mode.z = modeAbs;
	setpoint->velocity.z = 0.0001f;
	setpoint->mode.x = modeVelocity;
	setpoint->mode.y = modeVelocity;
	setpoint->velocity_body = true;
}

void	appMain()
{
	static setpoint_t	setpoint;

	DEBUG_PRINT("Waiting for activation ...\n");
	while (1)
	{
		vTaskDelay(M2T(2000));
		DEBUG_PRINT("Bunny hop!\n");
		setSetpoint(&setpoint);
		commanderSetSetpoint(&setpoint, 3);
		vTaskDelay(M2T(1000));
		zeroSetpoint(&setpoint);
	}
}
