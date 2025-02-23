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
 * @file    sairouterinterface.h
 *
 * @brief   This module defines SAI Router interface
 */

#if !defined (__SAIROUTERINTERFACE_H_)
#define __SAIROUTERINTERFACE_H_

#include <saitypes.h>

/**
 * @defgroup SAIROUTERINTF SAI - Router interface specific API definitions
 *
 * @{
 */

/**
 * @brief Attribute data for #SAI_ROUTER_INTERFACE_ATTR_TYPE
 */
typedef enum _sai_router_interface_type_t
{
    /** Port or LAG or System Port Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_PORT,

    /** VLAN Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_VLAN,

    /** Loopback Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_LOOPBACK,

    /** MPLS Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_MPLS_ROUTER,

    /** Sub port Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_SUB_PORT,

    /** .1D Bridge Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_BRIDGE,

    /** Q-in-Q Router Interface Type */
    SAI_ROUTER_INTERFACE_TYPE_QINQ_PORT,

} sai_router_interface_type_t;

/**
 * @brief Routing interface attribute IDs
 */
typedef enum _sai_router_interface_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_ROUTER_INTERFACE_ATTR_START,

    /* READ-ONLY */

    /**
     * @brief Virtual router id
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_VIRTUAL_ROUTER
     */
    SAI_ROUTER_INTERFACE_ATTR_VIRTUAL_ROUTER_ID = SAI_ROUTER_INTERFACE_ATTR_START,

    /**
     * @brief Router interface type
     *
     * @type sai_router_interface_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_ROUTER_INTERFACE_ATTR_TYPE,

    /**
     * @brief Associated Port, System Port or LAG object id
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_PORT, SAI_OBJECT_TYPE_LAG, SAI_OBJECT_TYPE_SYSTEM_PORT
     * @condition SAI_ROUTER_INTERFACE_ATTR_TYPE == SAI_ROUTER_INTERFACE_TYPE_PORT or SAI_ROUTER_INTERFACE_ATTR_TYPE == SAI_ROUTER_INTERFACE_TYPE_SUB_PORT
     */
    SAI_ROUTER_INTERFACE_ATTR_PORT_ID,

    /**
     * @brief End of attributes
     */
    SAI_ROUTER_INTERFACE_ATTR_END,

    /** Custom range base value */
    SAI_ROUTER_INTERFACE_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_ROUTER_INTERFACE_ATTR_CUSTOM_RANGE_END

} sai_router_interface_attr_t;

/**
 * @brief Create router interface.
 *
 * @param[out] router_interface_id Router interface id
 * @param[in] switch_id Switch id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_router_interface_fn)(
        _Out_ sai_object_id_t *router_interface_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove router interface
 *
 * @param[in] router_interface_id Router interface id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_router_interface_fn)(
        _In_ sai_object_id_t router_interface_id);

/**
 * @brief Set router interface attribute
 *
 * @param[in] router_interface_id Router interface id
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_router_interface_attribute_fn)(
        _In_ sai_object_id_t router_interface_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get router interface attribute
 *
 * @param[in] router_interface_id Router interface id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_router_interface_attribute_fn)(
        _In_ sai_object_id_t router_interface_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Routing interface methods table retrieved with sai_api_query()
 */
typedef struct _sai_router_interface_api_t
{
    sai_create_router_interface_fn          create_router_interface;
    sai_remove_router_interface_fn          remove_router_interface;
    sai_set_router_interface_attribute_fn   set_router_interface_attribute;
    sai_get_router_interface_attribute_fn   get_router_interface_attribute;

} sai_router_interface_api_t;

/**
 * @}
 */
#endif /** __SAIROUTERINTERFACE_H_ */
