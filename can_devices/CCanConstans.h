/* 
 * File:   CCanConstans.h
 * Author: jezierski
 *
 * Created on 10 czerwiec 2013, 21:02
 */

#ifndef CCANCONSTANS_H
#define	CCANCONSTANS_H

#define OFFSET_CAT_ID   0
#define OFFSET_CMD  1
#define OFFSET_DATA  2
#define OFFSET_SRC_ADDR  2

#define ID_MULTICAST    1
#define ID_MASTER       2
#define ID_A_SIMPLE_SWITCH       3
#define ID_S_SIMPLE_SWITCH       4
#define ID_OTHER       5

#define CMD_ACK   1
#define CMD_RESET_ADDRESS   2
#define CMD_SET_ADDRESS   3
#define CMD_POLL_GUID   4
#define CMD_GET_STATUS   5
#define CMD_SET_STATUS   6
#define CMD_PING    7


enum class EDeviceCategory{
    ALL = ID_MULTICAST,
    MASTER = ID_MASTER,
    A_SIMPLE_SWITCH = ID_A_SIMPLE_SWITCH,
    S_SIMPLE_SWITCH = ID_S_SIMPLE_SWITCH,
    OTHER = ID_OTHER,
};

#endif	/* CCANCONSTANS_H */

