/*
 * wifi.c
 *
 *  Created on: Dec 30, 2014
 *      Author: Minh
 */
#include "driver/wifi.h"
#include <user_interface.h>
#include <osapi.h>
#include <espconn.h>
#include <os_type.h>
#include <mem.h>

#include "user_config.h"
#include "debug.h"

static ETSTimer WiFiLinker;
WifiCallback wifiCb = NULL;
static uint8_t wifiStatus = STATION_IDLE, lastWifiStatus = STATION_IDLE;

static void ICACHE_FLASH_ATTR wifi_check_ip(void *arg) {
    struct ip_info ipConfig;

    os_timer_disarm(&WiFiLinker);
    wifi_get_ip_info(STATION_IF, &ipConfig);
    wifiStatus = wifi_station_get_connect_status();
    if (wifiStatus == STATION_GOT_IP && ipConfig.ip.addr != 0) {

        os_timer_setfn(&WiFiLinker, (os_timer_func_t *) wifi_check_ip, NULL);
        os_timer_arm(&WiFiLinker, 2000, 0);


    } else {
        if (wifi_station_get_connect_status() == STATION_WRONG_PASSWORD) {
            D("ERROR: STATION_WRONG_PASSWORD");
            wifi_station_connect();


        } else if (wifi_station_get_connect_status() == STATION_NO_AP_FOUND) {
            D("ERROR: STATION_NO_AP_FOUND");
            wifi_station_connect();


        } else if (wifi_station_get_connect_status() == STATION_CONNECT_FAIL) {

            D("ERROR: STATION_CONNECT_FAIL");
            wifi_station_connect();

        }

        os_timer_setfn(&WiFiLinker, (os_timer_func_t *) wifi_check_ip, NULL);
        os_timer_arm(&WiFiLinker, 500, 0);
    }
    if (wifiStatus != lastWifiStatus) {
        lastWifiStatus = wifiStatus;
        if (wifiCb)
            wifiCb(wifiStatus);
    }
}

void wifi_connect_checker() {
    os_timer_disarm(&WiFiLinker);
    os_timer_setfn(&WiFiLinker, (os_timer_func_t *) wifi_check_ip, NULL);
    os_timer_arm(&WiFiLinker, 1000, 0);
}

void ICACHE_FLASH_ATTR wifi_connect(uint8_t* ssid, uint8_t* pass, WifiCallback cb) {
    struct station_config stationConf;
    wifi_set_opmode(STATION_MODE);
    wifi_station_set_auto_connect(FALSE);
    wifiCb = cb;

    os_memset(&stationConf, 0, sizeof (struct station_config));

    os_sprintf(stationConf.ssid, "%s", ssid);
    os_sprintf(stationConf.password, "%s", pass);

    wifi_station_set_config(&stationConf);

    wifi_connect_checker(&WiFiLinker);
    wifi_station_set_auto_connect(TRUE);
    wifi_station_connect();
}

