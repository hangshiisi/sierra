/***************************************************************************
                          nasmt_iocontrol.h  -  description
 ***************************************************************************
  Eurecom OpenAirInterface 2
  Copyright(c) 1999 - 2013 Eurecom

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information
  Openair Admin: openair_admin@eurecom.fr
  Openair Tech : openair_tech@eurecom.fr
  Forums       : http://forums.eurecom.fsr/openairinterface
  Address      : Eurecom, 450 route des Chappes, 06410 Biot Sophia Antipolis, France
*******************************************************************************/
/*! \file nasmt_iocontrol.h
* \brief I/O control constnats and structures for upper layers of driver for OpenAirInterface CELLULAR version - MT
* \author  michelle.wetterwald, navid.nikaein, raymond.knopp, Lionel Gauthier
* \company Eurecom
* \email: michelle.wetterwald@eurecom.fr, raymond.knopp@eurecom.fr, navid.nikaein@eurecom.fr,  lionel.gauthier@eurecom.fr
*/
/*******************************************************************************/
#ifndef NASMTD_CTL_H
#define NASMTD_CTL_H

#include <asm/byteorder.h>
#include <asm/types.h>
#include <linux/udp.h>
#include <linux/tcp.h>

#define NAS_MSG_MAXLEN 1100

// type of CTL message
#define NAS_MSG_STATISTIC_REQUEST   1
#define NAS_MSG_STATISTIC_REPLY     2
#define NAS_MSG_ECHO_REQUEST        3
#define NAS_MSG_ECHO_REPLY          4
#define NAS_MSG_CX_ESTABLISHMENT_REQUEST  5
#define NAS_MSG_CX_ESTABLISHMENT_REPLY    6
#define NAS_MSG_CX_RELEASE_REQUEST  7
#define NAS_MSG_CX_RELEASE_REPLY    8
#define NAS_MSG_CX_LIST_REQUEST     9
#define NAS_MSG_CX_LIST_REPLY      10
#define NAS_MSG_RB_ESTABLISHMENT_REQUEST  11
#define NAS_MSG_RB_ESTABLISHMENT_REPLY    12
#define NAS_MSG_RB_RELEASE_REQUEST  13
#define NAS_MSG_RB_RELEASE_REPLY    14
#define NAS_MSG_RB_LIST_REQUEST    15
#define NAS_MSG_RB_LIST_REPLY      16
#define NAS_MSG_CLASS_ADD_REQUEST  17
#define NAS_MSG_CLASS_ADD_REPLY    18
#define NAS_MSG_CLASS_DEL_REQUEST  19
#define NAS_MSG_CLASS_DEL_REPLY    20
#define NAS_MSG_CLASS_LIST_REQUEST  21
#define NAS_MSG_CLASS_LIST_REPLY    22
#define NAS_MSG_MEAS_REQUEST  23
#define NAS_MSG_MEAS_REPLY    24
#define NAS_MSG_IMEI_REQUEST  25
#define NAS_MSG_IMEI_REPLY    26

// Max number of entry of a message list
#define NAS_LIST_CX_MAX  32
#define NAS_LIST_RB_MAX  32
#define NAS_LIST_CLASS_MAX  32

typedef uint16_t nasMsgType_t;

struct nas_ioctl {
  char name[IFNAMSIZ];
  nasMsgType_t type;
  char *msg;
};

struct nas_msg_statistic_reply {
  uint32_t rx_packets;
  uint32_t tx_packets;
  uint32_t rx_bytes;
  uint32_t tx_bytes;
  uint32_t rx_errors;
  uint32_t tx_errors;
  uint32_t rx_dropped;
  uint32_t tx_dropped;
};

struct nas_msg_cx_list_reply {
  nasLocalConnectionRef_t lcr;   // Local Connection reference
  uint8_t state;
  nasCellID_t cellid;    // cell identification
  uint32_t iid6[2];       // IPv6  interface identification
  uint8_t iid4;       // IPv4 interface identification
  uint16_t num_rb;
  uint16_t nsclassifier;
};
struct nas_msg_cx_establishment_reply {
  int status;
};
struct nas_msg_cx_establishment_request {
  nasLocalConnectionRef_t lcr;  // Local Connection reference
  nasCellID_t cellid; // Cell identification
};
struct nas_msg_cx_release_reply {
  int status;
};
struct nas_msg_cx_release_request {
  nasLocalConnectionRef_t lcr; // Local Connection reference
};

struct nas_msg_rb_list_reply {
  nasRadioBearerId_t rab_id;
  nasSapId_t sapi;
  nasQoSTrafficClass_t qos;
  uint8_t state;
};
struct nas_msg_rb_list_request {
  nasLocalConnectionRef_t lcr;   // Local Connection reference
};
struct nas_msg_rb_establishment_reply {
  int status;
};
struct nas_msg_rb_establishment_request {
  nasLocalConnectionRef_t lcr;  // Local Connection reference
  nasRadioBearerId_t rab_id;
  nasQoSTrafficClass_t qos;
};

struct nas_msg_rb_release_reply {
  int status;
};
struct nas_msg_rb_release_request {
  nasLocalConnectionRef_t lcr; // Local Connection reference
  nasRadioBearerId_t rab_id;
};

struct nas_msg_class_add_request {
  nasLocalConnectionRef_t lcr; // Local Connection reference
  nasRadioBearerId_t rab_id;
  uint8_t dir; // direction (send or receive)
  uint8_t dscp; // codepoint
  uint8_t fct;
  uint16_t classref;
  uint8_t version;
  union {
    struct in6_addr ipv6;
    uint32_t ipv4;
  } saddr; // IP source address
  uint8_t splen; // prefix length
  union {
    struct in6_addr ipv6;
    uint32_t ipv4;
  } daddr; // IP destination address
  uint8_t dplen; // prefix length
  uint8_t protocol;   // high layer protocol type
  uint16_t sport;   // source port
  uint16_t dport;   // destination port
};
struct nas_msg_class_add_reply {
  int status;
};
struct nas_msg_class_del_request {
  nasLocalConnectionRef_t lcr; // Local Connection reference
  uint8_t dir; // direction (send or receive)
  uint8_t dscp; // codepoint
  uint16_t classref;
};
struct nas_msg_class_del_reply {
  int status;
};
#define nas_msg_class_list_reply nas_msg_class_add_request
struct nas_msg_class_list_request {
  nasLocalConnectionRef_t lcr;   // Local Connection reference
  uint8_t dir;
  uint8_t dscp;
};


// Messages for Measurement transfer - MW 01/04/2005
typedef uint32_t nioctlProviderId_t;
typedef uint16_t nioctlSignalLoss_t;
typedef struct nioctlMeasures {
  nasCellID_t cell_id;
  nasSigLevel_t level;
  nioctlProviderId_t provider_id;
} nioctlMeasures_t;

struct nas_msg_measure_request {
  nasNumRGsMeas_t num_cells;
  nasCellID_t cellid[MAX_MEASURE_NB]; // Cell identification
  uint16_t num_providers;
  nioctlProviderId_t provider_id[MAX_MEASURE_NB]; // Provider identification
};
struct nas_msg_measure_reply {
  nasNumRGsMeas_t num_cells;
  nioctlMeasures_t measures[MAX_MEASURE_NB];
  nioctlSignalLoss_t signal_lost_flag;
};

// Messages for L2Id transfer - MW
typedef uint32_t nioctlL2Id_t[2];

struct nas_msg_l2id_reply {
  nioctlL2Id_t l2id;
};


#endif
