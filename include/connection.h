/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   connection.h
 * Author: zsoltmazlo
 *
 * Created on September 17, 2016, 9:34 PM
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <c_types.h>

void connection_init(void);

void wifi_connected_cb(uint8_t status);

void wifi_disconnected_cb(uint8_t status);

void mqtt_connected_cb(uint32_t *args);

void mqtt_published_cb(uint32_t *args);

void mqtt_disconnected_cb(uint32_t *args);

void mqtt_ondata_cb(
		uint32_t * args,
		const char* topic, uint32_t topic_len,
		const char *data, uint32_t data_len);


#endif /* CONNECTION_H */

