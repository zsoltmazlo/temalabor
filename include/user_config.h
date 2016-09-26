/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   user_config.h
 * Author: zsoltmazlo
 *
 * Created on September 5, 2016, 11:49 PM
 */

#ifndef USER_CONFIG_H
#define USER_CONFIG_H


/*Definition of GPIO PIN params, for GPIO initialization*/
//// D6
//#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
//#define PWM_0_OUT_IO_NUM 12
//#define PWM_0_OUT_IO_FUNC  FUNC_GPIO12
//
//// D8
//#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTDO_U
//#define PWM_1_OUT_IO_NUM 15
//#define PWM_1_OUT_IO_FUNC  FUNC_GPIO15
//
//// D7
//#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
//#define PWM_2_OUT_IO_NUM 13
//#define PWM_2_OUT_IO_FUNC  FUNC_GPIO13

// D5
#define PWM_3_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
#define PWM_3_OUT_IO_NUM 14
#define PWM_3_OUT_IO_FUNC  FUNC_GPIO14

// D1
#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_GPIO5_U
#define PWM_0_OUT_IO_NUM 5
#define PWM_0_OUT_IO_FUNC  FUNC_GPIO5

#define PWM_CHANNEL 2  //  5:5channel ; 3:3channel

#define MQTT_BROKER				"192.168.1.209"
#define MQTT_CLIENT_ID			"esp-servo"
#define MQTT_SENSOR_CH			"esp01"
#define MQTT_BUF_SIZE			2048
#define MQTT_RECONNECT_TIMEOUT	0
#define PROTOCOL_NAMEv31		/*MQTT version 3.1 compatible with Mosquitto v0.15*/

#define WIFI_SSID				"temalabor"
#define WIFI_PASS				""

#endif /* USER_CONFIG_H */

