// this section was generated automatically by rusEFI tool ConfigDefinition.jar based on (unknown script) controllers/trigger/trigger_central.txt Thu Sep 01 03:55:33 UTC 2022
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
#define HW_EVENT_TYPES 6
// start of trigger_central_s
struct trigger_central_s {
	/**
	 * Hardware events since boot
	 * offset 0
	 */
	int hwEventCounters[HW_EVENT_TYPES];
	/**
	 * offset 24
	 */
	int vvtCamCounter = (int)0;
	/**
	 * offset 28
	 */
	scaled_channel<float, 1, 1> mapVvt_MAP_AT_SPECIAL_POINT = (float)0;
	/**
	 * offset 32
	 */
	scaled_channel<float, 1, 1> mapVvt_MAP_AT_DIFF = (float)0;
	/**
	 * offset 36
	 */
	uint8_t mapVvt_MAP_AT_CYCLE_COUNT = (uint8_t)0;
	/**
	 * offset 37
	 */
	uint8_t mapVvt_map_peak = (uint8_t)0;
	/**
	 * Engine Phase2
	deg
	 * offset 38
	 */
	scaled_channel<uint16_t, 1, 1> currentEngineDecodedPhase = (uint16_t)0;
};
static_assert(sizeof(trigger_central_s) == 40);

// end
// this section was generated automatically by rusEFI tool ConfigDefinition.jar based on (unknown script) controllers/trigger/trigger_central.txt Thu Sep 01 03:55:33 UTC 2022
