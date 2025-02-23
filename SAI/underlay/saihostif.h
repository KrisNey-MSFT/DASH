/**
 * Copyright (c) 2014 Microsoft Open Technologies, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABILITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 *    Microsoft would like to thank the following companies for their review and
 *    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
 *    Dell Products, L.P., Facebook, Inc., Marvell International Ltd.
 *
 * @file    saihostif.h
 *
 * @brief   This module defines SAI host interface
 *
 * @par Abstract
 *
 *    This module defines SAI Host Interface which is responsible for
 *    creating/deleting Linux netdev corresponding to the host interface type.
 *    All the management operations of the netdevs such as changing IP address
 *    are outside the scope of SAI.
 */

#if !defined (__SAIHOSTIF_H_)
#define __SAIHOSTIF_H_

#include <saitypes.h>

/**
 * @defgroup SAIHOSTINTF SAI - Host Interface specific API definitions
 *
 * @{
 */

/**
 * @brief Defines maximum host interface name
 */
#define SAI_HOSTIF_NAME_SIZE 16

/**
 * @brief Defines maximum length of generic netlink multicast group name
 */
#define SAI_HOSTIF_GENETLINK_MCGRP_NAME_SIZE 16

/**
 * @brief Host interface trap group attributes
 */
typedef enum _sai_hostif_trap_group_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_HOSTIF_TRAP_GROUP_ATTR_START,

    /**
     * @brief Admin Mode
     *
     * @type bool
     * @flags CREATE_AND_SET
     * @default true
     */
    SAI_HOSTIF_TRAP_GROUP_ATTR_ADMIN_STATE = SAI_HOSTIF_TRAP_GROUP_ATTR_START,

    /**
     * @brief CPU egress queue
     *
     * @type sai_uint32_t
     * @flags CREATE_AND_SET
     * @default 0
     */
    SAI_HOSTIF_TRAP_GROUP_ATTR_QUEUE,

    /**
     * @brief SAI policer object id
     *
     * @type sai_object_id_t
     * @flags CREATE_AND_SET
     * @objects SAI_OBJECT_TYPE_POLICER
     * @allownull true
     * @default SAI_NULL_OBJECT_ID
     */
    SAI_HOSTIF_TRAP_GROUP_ATTR_POLICER,

    /**
     * @brief End of attributes
     */
    SAI_HOSTIF_TRAP_GROUP_ATTR_END,

    /** Start of custom range base */
    SAI_HOSTIF_TRAP_GROUP_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range */
    SAI_HOSTIF_TRAP_GROUP_ATTR_CUSTOM_RANGE_END

} sai_hostif_trap_group_attr_t;

/**
 * @brief Create host interface trap group
 *
 * @param[out] hostif_trap_group_id Host interface trap group id
 * @param[in] switch_id Switch object id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_hostif_trap_group_fn)(
        _Out_ sai_object_id_t *hostif_trap_group_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove host interface trap group
 *
 * @param[in] hostif_trap_group_id Host interface trap group id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_hostif_trap_group_fn)(
        _In_ sai_object_id_t hostif_trap_group_id);

/**
 * @brief Set host interface trap group attribute value.
 *
 * @param[in] hostif_trap_group_id Host interface trap group id
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_hostif_trap_group_attribute_fn)(
        _In_ sai_object_id_t hostif_trap_group_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get host interface trap group attribute value.
 *
 * @param[in] hostif_trap_group_id Host interface trap group id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_hostif_trap_group_attribute_fn)(
        _In_ sai_object_id_t hostif_trap_group_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Host interface trap type
 *
 * @flags Contains flags
 */
typedef enum _sai_hostif_trap_type_t
{
    /**
     * @brief Start of trap types
     */
    SAI_HOSTIF_TRAP_TYPE_START = 0x00000000,

    /* Control plane protocol */

    /* Switch trap */

    /** Default action is drop */
    SAI_HOSTIF_TRAP_TYPE_LLDP = 0x00000003,

    /* Router traps */

    /** Default packet action is forward */
    SAI_HOSTIF_TRAP_TYPE_ARP_REQUEST = 0x00002000,

    /** Default packet action is forward */
    SAI_HOSTIF_TRAP_TYPE_ARP_RESPONSE = 0x00002001,

    /** Default packet action is forward */
    SAI_HOSTIF_TRAP_TYPE_IPV6_NEIGHBOR_DISCOVERY = 0x00002009,

    /** Default packet action is forward */
    SAI_HOSTIF_TRAP_TYPE_IPV6_NEIGHBOR_SOLICITATION = 0x00002012,

    /** Default packet action is forward */
    SAI_HOSTIF_TRAP_TYPE_IPV6_NEIGHBOR_ADVERTISEMENT = 0x00002013,

    /* Local IP traps */

    /**
     * @brief IP packets to local router IP address (routes with
     * #SAI_ROUTE_ENTRY_ATTR_NEXT_HOP_ID = #SAI_SWITCH_ATTR_CPU_PORT)
     * (default packet action is drop)
     */
    SAI_HOSTIF_TRAP_TYPE_IP2ME = 0x00004000,

    /**
     * @brief BGP traffic (TCP src port == 179 or TCP dst port == 179) to local
     * router IP address (default packet action is drop)
     */
    SAI_HOSTIF_TRAP_TYPE_BGP = 0x00004003,

    /**
     * @brief BGPv6 traffic (TCP src port == 179 or TCP dst port == 179) to
     * local router IP address (default packet action is drop)
     */
    SAI_HOSTIF_TRAP_TYPE_BGPV6 = 0x00004004,

    /**
     * @brief End of trap types
     */
    SAI_HOSTIF_TRAP_TYPE_END = 0x0000a000

} sai_hostif_trap_type_t;

/**
 * @brief Host interface trap attributes
 */
typedef enum _sai_hostif_trap_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_HOSTIF_TRAP_ATTR_START,

    /**
     * @brief Host interface trap type
     *
     * @type sai_hostif_trap_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY | KEY
     */
    SAI_HOSTIF_TRAP_ATTR_TRAP_TYPE = SAI_HOSTIF_TRAP_ATTR_START,

    /**
     * @brief Trap action
     *
     * @type sai_packet_action_t
     * @flags MANDATORY_ON_CREATE | CREATE_AND_SET
     */
    SAI_HOSTIF_TRAP_ATTR_PACKET_ACTION,

    /**
     * @brief Trap priority.
     *
     * This is equivalent to ACL entry priority #SAI_ACL_ENTRY_ATTR_PRIORITY.
     *
     * @type sai_uint32_t
     * @flags CREATE_AND_SET
     * @default attrvalue SAI_SWITCH_ATTR_ACL_ENTRY_MINIMUM_PRIORITY
     * @validonly SAI_HOSTIF_TRAP_ATTR_PACKET_ACTION == SAI_PACKET_ACTION_TRAP or SAI_HOSTIF_TRAP_ATTR_PACKET_ACTION == SAI_PACKET_ACTION_COPY
     */
    SAI_HOSTIF_TRAP_ATTR_TRAP_PRIORITY,

    /**
     * @brief End of attributes
     */
    SAI_HOSTIF_TRAP_ATTR_END,

    /** Custom range start */
    SAI_HOSTIF_TRAP_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** Custom range end */
    SAI_HOSTIF_TRAP_ATTR_CUSTOM_RANGE_END

} sai_hostif_trap_attr_t;

/**
 * @brief Create host interface trap
 *
 * @param[out] hostif_trap_id Host interface trap id
 * @param[in] switch_id Switch object id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_hostif_trap_fn)(
        _Out_ sai_object_id_t *hostif_trap_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove host interface trap
 *
 * @param[in] hostif_trap_id Host interface trap id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_hostif_trap_fn)(
        _In_ sai_object_id_t hostif_trap_id);

/**
 * @brief Set trap attribute value.
 *
 * @param[in] hostif_trap_id Host interface trap id
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_hostif_trap_attribute_fn)(
        _In_ sai_object_id_t hostif_trap_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get trap attribute value.
 *
 * @param[in] hostif_trap_id Host interface trap id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_hostif_trap_attribute_fn)(
        _In_ sai_object_id_t hostif_trap_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Attribute data for SAI_HOSTIF_ATTR_TYPE
 */
typedef enum _sai_hostif_type_t
{
    /** Netdevice */
    SAI_HOSTIF_TYPE_NETDEV,

    /** File descriptor */
    SAI_HOSTIF_TYPE_FD,

    /** Generic netlink */
    SAI_HOSTIF_TYPE_GENETLINK

} sai_hostif_type_t;

/**
 * @brief Host interface attribute IDs
 */
typedef enum _sai_hostif_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_HOSTIF_ATTR_START,

    /**
     * @brief Host interface type
     *
     * @type sai_hostif_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_HOSTIF_ATTR_TYPE = SAI_HOSTIF_ATTR_START,

    /**
     * @brief Host interface object ID
     *
     * Port netdev will be created when object type is SAI_OBJECT_TYPE_PORT
     * LAG netdev will be created when object type is SAI_OBJECT_TYPE_LAG
     * VLAN netdev will be created when object type is SAI_OBJECT_TYPE_VLAN
     * System Port netdev will be created when object type is SAI_OBJECT_TYPE_SYSTEM_PORT
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_PORT, SAI_OBJECT_TYPE_LAG, SAI_OBJECT_TYPE_VLAN, SAI_OBJECT_TYPE_SYSTEM_PORT
     * @condition SAI_HOSTIF_ATTR_TYPE == SAI_HOSTIF_TYPE_NETDEV
     */
    SAI_HOSTIF_ATTR_OBJ_ID,

    /**
     * @brief Name [char[SAI_HOSTIF_NAME_SIZE]]
     *
     * The maximum number of characters for the name is SAI_HOSTIF_NAME_SIZE - 1 since
     * it needs the terminating null byte ('\0') at the end.
     *
     * If Hostif is a generic netlink, this indicates the generic netlink family name.
     *
     * @type char
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @condition SAI_HOSTIF_ATTR_TYPE == SAI_HOSTIF_TYPE_NETDEV or SAI_HOSTIF_ATTR_TYPE == SAI_HOSTIF_TYPE_GENETLINK
     */
    SAI_HOSTIF_ATTR_NAME,

    /**
     * @brief End of attributes
     */
    SAI_HOSTIF_ATTR_END,

    /** Custom range base value */
    SAI_HOSTIF_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_HOSTIF_ATTR_CUSTOM_RANGE_END

} sai_hostif_attr_t;

/**
 * @brief Create host interface
 *
 * @param[out] hostif_id Host interface id
 * @param[in] switch_id Switch object id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_hostif_fn)(
        _Out_ sai_object_id_t *hostif_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove host interface
 *
 * @param[in] hostif_id Host interface id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_hostif_fn)(
        _In_ sai_object_id_t hostif_id);

/**
 * @brief Set host interface attribute
 *
 * @param[in] hostif_id Host interface id
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_hostif_attribute_fn)(
        _In_ sai_object_id_t hostif_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get host interface attribute
 *
 * @param[in] hostif_id Host interface id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_hostif_attribute_fn)(
        _In_ sai_object_id_t hostif_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Attribute data for SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE
 */
typedef enum _sai_hostif_table_entry_type_t
{
    /** Port-based Host Interface entry Type */
    SAI_HOSTIF_TABLE_ENTRY_TYPE_PORT,

    /** LAG based Host Interface entry Type */
    SAI_HOSTIF_TABLE_ENTRY_TYPE_LAG,

    /** Vlan based Host Interface entry Type */
    SAI_HOSTIF_TABLE_ENTRY_TYPE_VLAN,

    /** Wildcard Interface entry Type */
    SAI_HOSTIF_TABLE_ENTRY_TYPE_TRAP_ID,

    /** Wildcard Interface, wildcard trap id */
    SAI_HOSTIF_TABLE_ENTRY_TYPE_WILDCARD

} sai_hostif_table_entry_type_t;

/**
 * @brief Attribute data for SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE
 */
typedef enum _sai_hostif_table_entry_channel_type_t
{
    /** Receive packets via callback */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_CB,

    /** Receive packets via file descriptor */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_FD,

    /** Receive packets via Linux netdev type port */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_NETDEV_PHYSICAL_PORT,

    /** Receive packets via Linux netdev logical port (LAG or port) */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_NETDEV_LOGICAL_PORT,

    /** Receive packets via Linux netdev L3 interface */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_NETDEV_L3,

    /** Receive packets via Linux generic netlink interface */
    SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_GENETLINK

} sai_hostif_table_entry_channel_type_t;

/**
 * @brief Host interface table entry attribute IDs
 */
typedef enum _sai_hostif_table_entry_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_START,

    /**
     * @brief Host interface table entry type
     *
     * @type sai_hostif_table_entry_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE = SAI_HOSTIF_TABLE_ENTRY_ATTR_START,

    /**
     * @brief Host interface table entry match field object-id
     *
     * Should be port object when type is SAI_HOSTIF_TABLE_ENTRY_TYPE_PORT.
     * Should be LAG object when type is SAI_HOSTIF_TABLE_ENTRY_TYPE_LAG.
     * Should be VLAN ID object when type is SAI_HOSTIF_TABLE_ENTRY_TYPE_VLAN.
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_PORT, SAI_OBJECT_TYPE_LAG, SAI_OBJECT_TYPE_ROUTER_INTERFACE
     * @condition SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_PORT or SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_VLAN or SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_LAG
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_OBJ_ID,

    /**
     * @brief Host interface table entry match field trap-id
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_HOSTIF_TRAP, SAI_OBJECT_TYPE_HOSTIF_USER_DEFINED_TRAP
     * @condition SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_PORT or SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_VLAN or SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_LAG or SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE == SAI_HOSTIF_TABLE_ENTRY_TYPE_TRAP_ID
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_TRAP_ID,

    /**
     * @brief Host interface table entry action channel
     *
     * @type sai_hostif_table_entry_channel_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE,

    /**
     * @brief Host interface table entry action target host interface object
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_HOSTIF
     * @condition SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE == SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_FD or SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE == SAI_HOSTIF_TABLE_ENTRY_CHANNEL_TYPE_GENETLINK
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_HOST_IF,

    /**
     * @brief End of attributes
     */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_END,

    /** Custom range base value */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_HOSTIF_TABLE_ENTRY_ATTR_CUSTOM_RANGE_END

} sai_hostif_table_entry_attr_t;

/**
 * @brief Create host interface table entry
 *
 * @param[out] hostif_table_entry_id Host interface table entry
 * @param[in] switch_id Switch object id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_hostif_table_entry_fn)(
        _Out_ sai_object_id_t *hostif_table_entry_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove host interface table entry
 *
 * @param[in] hostif_table_entry_id Host interface table entry
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_hostif_table_entry_fn)(
        _In_ sai_object_id_t hostif_table_entry_id);

/**
 * @brief Set host interface table entry attribute
 *
 * @param[in] hostif_table_entry_id Host interface table entry
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_hostif_table_entry_attribute_fn)(
        _In_ sai_object_id_t hostif_table_entry_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get host interface table entry attribute
 *
 * @param[in] hostif_table_entry_id Host interface table entry
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_hostif_table_entry_attribute_fn)(
        _In_ sai_object_id_t hostif_table_entry_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Hostif methods table retrieved with sai_api_query()
 */
typedef struct _sai_hostif_api_t
{
    sai_create_hostif_fn                           create_hostif;
    sai_remove_hostif_fn                           remove_hostif;
    sai_set_hostif_attribute_fn                    set_hostif_attribute;
    sai_get_hostif_attribute_fn                    get_hostif_attribute;
    sai_create_hostif_table_entry_fn               create_hostif_table_entry;
    sai_remove_hostif_table_entry_fn               remove_hostif_table_entry;
    sai_set_hostif_table_entry_attribute_fn        set_hostif_table_entry_attribute;
    sai_get_hostif_table_entry_attribute_fn        get_hostif_table_entry_attribute;
    sai_create_hostif_trap_group_fn                create_hostif_trap_group;
    sai_remove_hostif_trap_group_fn                remove_hostif_trap_group;
    sai_set_hostif_trap_group_attribute_fn         set_hostif_trap_group_attribute;
    sai_get_hostif_trap_group_attribute_fn         get_hostif_trap_group_attribute;
    sai_create_hostif_trap_fn                      create_hostif_trap;
    sai_remove_hostif_trap_fn                      remove_hostif_trap;
    sai_set_hostif_trap_attribute_fn               set_hostif_trap_attribute;
    sai_get_hostif_trap_attribute_fn               get_hostif_trap_attribute;
} sai_hostif_api_t;

/**
 * @}
 */
#endif /** __SAIHOSTIF_H_ */
