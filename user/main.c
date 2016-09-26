#include <ets_sys.h>
#include <gpio.h>
#include <os_type.h>
#include <user_interface.h>

#include "driver/uart.h"
#include "debug.h"
#include "user_config.h"
#include "servo.h"
#include "connection.h"

#define TASK_SERVO_PRIO 1
#define TASK_SERVO_QUEUE_LEN 1
os_event_t user_servoTaskQueue[TASK_SERVO_QUEUE_LEN];

void user_rf_pre_init(void) {
	D("user_rf_pre_init done.");

}

ServoPosition position = Positive90Degrees;

void ICACHE_FLASH_ATTR user_servo_task(os_event_t *events) {
	os_delay_us(1000000);

	// set next position for servo motor
	D("setting next servo position...");
	servo_set_next_position(&position);
	D("done.");

	// setup servo position
	D("setting servo position...");
	servo_set_to_position(position);
	D("done.");

	// then post task to give process time for other tasks
	system_os_post(TASK_SERVO_PRIO, 0, 0);
}

/**
 * callback function if ESP powered up successfully
 */
void ICACHE_FLASH_ATTR init_done(void) {
	D("Initialization done.");

}

void ICACHE_FLASH_ATTR user_init(void) {
	// before everything, we need to reinit timer to use microsecond resolution 
	// in software timers
	system_timer_reinit();

	// initializing uart
	uart_init(BIT_RATE_115200, BIT_RATE_115200);

	uint8 maccaddr[6];
	wifi_get_macaddr(STATION_IF, maccaddr);
	char mac[20];
	os_sprintf(mac, MACSTR, MAC2STR(maccaddr));
	D("Mac: %s", mac);

	servo_init();
	servo_set_to_position(Positive0Degress);

	connection_init();

	//Start os tasks
	//	system_os_task(
	//			user_servo_task, TASK_SERVO_PRIO,
	//			user_servoTaskQueue, TASK_SERVO_QUEUE_LEN);
	//
	//	system_os_post(TASK_SERVO_PRIO, 0, 0);

	system_init_done_cb(init_done);
}
