/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <osapi.h>

#include "debug.h"
#include "connection.h"
#include "user_config.h"
#include "mqtt/mqtt.h"
#include "servo.h"

static char mqtt_sensor_topic[40];

MQTT_Client mqtt_client;

void connection_init(void) {
    // setting up mqtt settings
	MQTT_InitConnection(&mqtt_client, MQTT_BROKER, 1883, 0);
	MQTT_InitClient(&mqtt_client, MQTT_CLIENT_ID, "", "", 120, 1);
	MQTT_InitLWT(&mqtt_client, "/lwt", "offline", 0, 0);

	// then copy mqtt data topic's name into a char array
	os_sprintf(mqtt_sensor_topic, MQTT_SENSOR_CH);

	// subscribe some callback for major events
	MQTT_OnConnected(&mqtt_client, mqtt_connected_cb);
	MQTT_OnDisconnected(&mqtt_client, mqtt_disconnected_cb);
	MQTT_OnPublished(&mqtt_client, mqtt_published_cb);
	MQTT_OnData(&mqtt_client, mqtt_ondata_cb);
	
	// connect to wifi
	wifi_connect(WIFI_SSID, WIFI_PASS, wifi_connected_cb);
}

void wifi_connected_cb(uint8_t status) {
    D("WiFi connected successfully.");

	if (status == STATION_GOT_IP) {
		MQTT_Connect(&mqtt_client);
	} else {
		MQTT_Disconnect(&mqtt_client);
	}
}

void wifi_disconnected_cb(uint8_t status) {
    D("WiFi disconnected successfully.");
}

void mqtt_connected_cb(uint32_t *args) {
    D("MQTT connected successfully");
	
	MQTT_Client* client = (MQTT_Client*) args;
	
	// subscribe for topic
	MQTT_Subscribe(client, mqtt_sensor_topic, 0);
}

void mqtt_published_cb(uint32_t *args) {
    D("Publish succeeded.");
}

void mqtt_disconnected_cb(uint32_t *args) {
    D("MQTT disconnected successfully");
}

char mqtt_topic_buf[50], mqtt_data_buf[50];

void mqtt_ondata_cb(
		uint32_t * args,
		const char* topic, uint32_t topic_len,
		const char *data, uint32_t data_len) {
	
	os_memcpy(mqtt_topic_buf, topic, topic_len);
	mqtt_topic_buf[topic_len] = 0;
	
	os_memcpy(mqtt_data_buf, data, data_len);
	mqtt_data_buf[data_len] = 0;

	D("MQTT message received!\ntopic: %s\ndata: %s", mqtt_topic_buf, data);

	// if we received message "open" on topic, then we open gates with servo motor
	if( strcmp(mqtt_data_buf, "open") == 0 ) {
		servo_set_to_position(Positive0Degress);
	} else if( strcmp(mqtt_data_buf, "close") == 0 ) {
		servo_set_to_position(Negative90Degress);
	}
	
    
}
