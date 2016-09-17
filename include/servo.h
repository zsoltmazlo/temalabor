/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   servo.h
 * Author: zsoltmazlo
 *
 * Created on September 10, 2016, 12:49 PM
 */

#ifndef SERVO_H
#define SERVO_H

// 2ms
#define POS_90N 61000

// 1ms
#define POS_90P 17000

// 1.5ms 
#define POS_00 37500

typedef enum {
	Positive90Degrees,
	Positive0Degress,
	Negative90Degress
} ServoPosition;

void servo_init(void);

void servo_set_to_position(ServoPosition position);

void servo_set_next_position(ServoPosition* position);

#endif /* SERVO_H */

