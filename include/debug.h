/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   debug.h
 * Author: zsoltmazlo
 *
 * Created on September 5, 2016, 11:52 PM
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <osapi.h>

#define D(fmt, ...) \
            do { os_printf(">>>"); os_printf(fmt, ##__VA_ARGS__); os_printf("\r\n"); } while (0)

#endif /* DEBUG_H */

