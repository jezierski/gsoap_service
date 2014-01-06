/* 
 * File:   CCanConstans.h
 * Author: jezierski
 *
 * Created on 10 czerwiec 2013, 21:02
 */

#ifndef CCANCONSTANS_H
#define	CCANCONSTANS_H

#define BOOT_PUT_CMD                    0
#define BOOT_PUT_DATA                   1
#define BOOT_GET_CMD                    2
#define BOOT_GET_DATA                   3

#define BOOT_WRITE_UNLOCK               1
#define BOOT_ERASE_ONLY                 2
#define BOOT_AUTO_ERASE                 4
#define BOOT_AUTO_INC                   8
#define BOOT_SEND_ACK                   16

#define BOOT_CMD_RESET                  1
#define BOOT_CMD_INIT_CHK               2
#define BOOT_CMD_CHK_RUN                3
#define BOOT_CMD_EXIT_BOOT              4
#define BOOT_CMD_CLR_PROG               5
#define BOOT_CMD_GET_UID               6
#define BOOT_CMD_SET_UID               7

#define EEPROM_DATA_OFFSET              0xf00000              
#define EEPROM_DATA_SIZE                1024                    

#define BOOT_COMMAND_ACK                0x88            
#define OFFSET_CAT_ID   0
#define OFFSET_CMD  1
#define OFFSET_DATA  2
#define OFFSET_SRC_ADDR  2

#define OFFSET_SENSOR_RESPONSE_COMMAND  3
#define OFFSET_SENSOR_RESPONSE_DATA  4

#define ID_MULTICAST    0xff
#define ID_MASTER       200
#define ID_A_SIMPLE_SWITCH       1
#define ID_A_RGB_DRIVER          2
#define ID_A_PWM_DRIVER         3
#define ID_S_SIMPLE_SWITCH       100
#define ID_OTHER       5

#define CMD_ACK   1
#define CMD_RESET_ADDRESS   2
#define CMD_SET_ADDRESS   3
#define CMD_POLL_GUID   4
#define CMD_PING    5
#define CMD_RESET_ALL_STAT        6
#define CMD_REQ_NEW_STAT        7
#define CMD_ENTER_BOOT        8

enum class EDeviceCategory {
    ALL = ID_MULTICAST,
            MASTER = ID_MASTER,
            A_SIMPLE_SWITCH = ID_A_SIMPLE_SWITCH,
            S_SIMPLE_SWITCH = ID_S_SIMPLE_SWITCH,
            A_RGB_DRIVER = ID_A_RGB_DRIVER,
            A_PWM_DRIVER = ID_A_PWM_DRIVER,
            OTHER = ID_OTHER,
};

#endif	/* CCANCONSTANS_H */

