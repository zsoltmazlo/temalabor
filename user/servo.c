/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <os_type.h>
#include <pwm.h>

#include "user_config.h"
#include "debug.h"
#include "servo.h"

void servo_init(void) {
	uint32 io_info[][3] = {
		{PWM_0_OUT_IO_MUX, PWM_0_OUT_IO_FUNC, PWM_0_OUT_IO_NUM},
	};

	uint32 pwm_init_duty[PWM_CHANNEL] = {0};

	// 50Hz pwm
	pwm_init(20000, pwm_init_duty, PWM_CHANNEL, io_info);
	pwm_start();

	// disable pwm debug
	set_pwm_debug_en(0);

	D("pwm version: %08x", get_pwm_version());
}

void servo_set_to_position(ServoPosition position) {
	uint32 duty = 0;
	switch (position) {
		case Positive0Degress:
			duty = POS_00;
			break;
		case Positive90Degrees:
			duty = POS_90P;
			break;
		case Negative90Degress:
			duty = POS_90N;
			break;
		default:
			return;
	}

	D("servo position called, duty: %d", duty);
	pwm_set_duty(duty, 0);
	pwm_start();
}


void servo_set_next_position(ServoPosition* position) {
	*position = (*position + 1) % 3;
	
}




