/*
 * Xilinx Zynq MPSoC Power Management
 *
 *  Copyright (C) 2014-2015 Xilinx
 *
 *  Davorin Mista <davorin.mista@aggios.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SOC_ZYNQMP_PM_H__
#define __SOC_ZYNQMP_PM_H__

#define ZYNQMP_PM_VERSION_MAJOR	0
#define ZYNQMP_PM_VERSION_MINOR	1

#define ZYNQMP_PM_VERSION	((ZYNQMP_PM_VERSION_MAJOR << 16) | \
					ZYNQMP_PM_VERSION_MINOR)

#define ZYNQMP_PM_MAX_LATENCY	(~0U)
#define ZYNQMP_PM_MAX_QOS	100U

/* Capabilities for RAM */
#define	ZYNQMP_PM_CAPABILITY_ACCESS	0x1U
#define	ZYNQMP_PM_CAPABILITY_CONTEXT	0x2U
#define	ZYNQMP_PM_CAPABILITY_WAKEUP	0x4U
#define	ZYNQMP_PM_CAPABILITY_POWER	0x8U

enum zynqmp_pm_request_ack {
	ZYNQMP_PM_REQUEST_ACK_NO = 1,
	ZYNQMP_PM_REQUEST_ACK_BLOCKING,
	ZYNQMP_PM_REQUEST_ACK_CALLBACK_STANDARD,
};

enum zynqmp_pm_abort_reason {
	ZYNQMP_PM_ABORT_REASON_WAKEUP_EVENT = 100,
	ZYNQMP_PM_ABORT_REASON_POWER_UNIT_BUSY,
	ZYNQMP_PM_ABORT_REASON_NO_POWERDOWN,
	ZYNQMP_PM_ABORT_REASON_UNKNOWN,
};

enum zynqmp_pm_suspend_reason {
	ZYNQMP_PM_SUSPEND_REASON_POWER_UNIT_REQUEST = 201,
	ZYNQMP_PM_SUSPEND_REASON_ALERT,
	ZYNQMP_PM_SUSPEND_REASON_SYSTEM_SHUTDOWN,
};

enum zynqmp_pm_ram_state {
	ZYNQMP_PM_RAM_STATE_OFF = 1,
	ZYNQMP_PM_RAM_STATE_RETENTION,
	ZYNQMP_PM_RAM_STATE_ON,
};

enum zynqmp_pm_opchar_type {
	ZYNQMP_PM_OPERATING_CHARACTERISTIC_POWER = 1,
	ZYNQMP_PM_OPERATING_CHARACTERISTIC_ENERGY,
	ZYNQMP_PM_OPERATING_CHARACTERISTIC_TEMPERATURE,
};

/*
 * OS-level PM API
 */

/* API for suspending of APU */
int zynqmp_pm_request_suspend(const u32 node,
				      const enum zynqmp_pm_request_ack ack,
				      const u32 latency,
				      const u32 state);
int zynqmp_pm_self_suspend(const u32 node,
				const u32 latency,
				const u32 state);
int zynqmp_pm_abort_suspend(const enum zynqmp_pm_abort_reason reason);
int zynqmp_pm_request_wakeup(const u32 node,
				     const enum zynqmp_pm_request_ack ack);
int zynqmp_pm_set_wakeup_source(const u32 target,
					const u32 wakeup_node,
					const u32 enable);
int zynqmp_pm_system_shutdown(const u32 restart);

/* API for suspending of RPU */
int zynqmp_pm_force_powerdown(const u32 target,
					const enum zynqmp_pm_request_ack ack);

/* API functions for managing PM Slaves */
int zynqmp_pm_request_node(const u32 node,
				   const u32 capabilities,
				   const u32 qos,
				   const enum zynqmp_pm_request_ack ack);
int zynqmp_pm_release_node(const u32,
				const u32 latency);
int zynqmp_pm_set_requirement(const u32 node,
				   const u32 capabilities,
				   const u32 qos,
				   const enum zynqmp_pm_request_ack ack);
int zynqmp_pm_set_max_latency(const u32 node,
					  const u32 latency);

/* Miscellaneous API functions */
int zynqmp_pm_get_api_version(u32 *version);
int zynqmp_pm_set_configuration(const u32 physical_addr);
int zynqmp_pm_get_node_status(const u32 node);
int zynqmp_pm_register_notifier(const u32 node,
					const u32 event,
					const u32 wake,
					const u32 enable);
int zynqmp_pm_get_operating_characteristic(const u32 node,
					const enum zynqmp_pm_opchar_type type);

/* Direct-Control API functions */
int zynqmp_pm_reset_assert(const u32 reset,
				const u32 assert_flag);
int zynqmp_pm_reset_get_status(const u32 reset,
					u32 *status);
int zynqmp_pm_mmio_write(const u32 address,
				     const u32 mask,
				     const u32 value);
int zynqmp_pm_mmio_read(const u32 address,
				    const u32 mask,
				    u32 *value);

#endif /* __SOC_ZYNQMP_PM_H__ */
