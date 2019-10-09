/**
 * Arduino DSMR parser.
 *
 * This software is licensed under the MIT License.
 *
 * Copyright (c) 2015 Matthijs Kooijman <matthijs@stdin.nl>
 * Copyright (c) 2019 Michel Megens <michel@michelmegens.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Field parsing functions
 */

#include <dsmr/fields.h>

using namespace dsmr;
using namespace dsmr::fields;

constexpr char units::none[];
constexpr char units::kWh[];
constexpr char units::Wh[];
constexpr char units::kW[];
constexpr char units::W[];
constexpr char units::V[];
constexpr char units::mV[];
constexpr char units::A[];
constexpr char units::m3[];
constexpr char units::dm3[];
constexpr char units::GJ[];
constexpr char units::MJ[];

constexpr ObisId identification::id;
constexpr const char* identification::name_progmem;
constexpr const __FlashStringHelper *identification::name;

constexpr ObisId p1_version::id;
constexpr const char* p1_version::name_progmem;
constexpr const __FlashStringHelper *p1_version::name;

constexpr ObisId timestamp::id;
constexpr const char* timestamp::name_progmem;
constexpr const __FlashStringHelper *timestamp::name;

constexpr ObisId equipment_id::id;
constexpr const char* equipment_id::name_progmem;
constexpr const __FlashStringHelper *equipment_id::name;

constexpr ObisId energy_delivered_tariff1::id;
constexpr const char* energy_delivered_tariff1::name_progmem;
constexpr const __FlashStringHelper *energy_delivered_tariff1::name;

constexpr ObisId energy_delivered_tariff2::id;
constexpr const char* energy_delivered_tariff2::name_progmem;
constexpr const __FlashStringHelper *energy_delivered_tariff2::name;

constexpr ObisId energy_returned_tariff1::id;
constexpr const char* energy_returned_tariff1::name_progmem;
constexpr const __FlashStringHelper *energy_returned_tariff1::name;

constexpr ObisId energy_returned_tariff2::id;
constexpr const char* energy_returned_tariff2::name_progmem;
constexpr const __FlashStringHelper *energy_returned_tariff2::name;

constexpr ObisId electricity_tariff::id;
constexpr const char* electricity_tariff::name_progmem;
constexpr const __FlashStringHelper *electricity_tariff::name;

constexpr ObisId power_delivered::id;
constexpr const char* power_delivered::name_progmem;
constexpr const __FlashStringHelper *power_delivered::name;

constexpr ObisId power_returned::id;
constexpr const char* power_returned::name_progmem;
constexpr const __FlashStringHelper *power_returned::name;

constexpr ObisId electricity_threshold::id;
constexpr const char* electricity_threshold::name_progmem;
constexpr const __FlashStringHelper *electricity_threshold::name;

constexpr ObisId electricity_switch_position::id;
constexpr const char* electricity_switch_position::name_progmem;
constexpr const __FlashStringHelper *electricity_switch_position::name;

constexpr ObisId electricity_failures::id;
constexpr const char* electricity_failures::name_progmem;
constexpr const __FlashStringHelper *electricity_failures::name;

constexpr ObisId electricity_long_failures::id;
constexpr const char* electricity_long_failures::name_progmem;
constexpr const __FlashStringHelper *electricity_long_failures::name;

constexpr ObisId electricity_failure_log::id;
constexpr const char* electricity_failure_log::name_progmem;
constexpr const __FlashStringHelper *electricity_failure_log::name;

constexpr ObisId electricity_sags_l1::id;
constexpr const char* electricity_sags_l1::name_progmem;
constexpr const __FlashStringHelper *electricity_sags_l1::name;

constexpr ObisId electricity_sags_l2::id;
constexpr const char* electricity_sags_l2::name_progmem;
constexpr const __FlashStringHelper *electricity_sags_l2::name;

constexpr ObisId electricity_sags_l3::id;
constexpr const char* electricity_sags_l3::name_progmem;
constexpr const __FlashStringHelper *electricity_sags_l3::name;

constexpr ObisId electricity_swells_l1::id;
constexpr const char* electricity_swells_l1::name_progmem;
constexpr const __FlashStringHelper *electricity_swells_l1::name;

constexpr ObisId electricity_swells_l2::id;
constexpr const char* electricity_swells_l2::name_progmem;
constexpr const __FlashStringHelper *electricity_swells_l2::name;

constexpr ObisId electricity_swells_l3::id;
constexpr const char* electricity_swells_l3::name_progmem;
constexpr const __FlashStringHelper *electricity_swells_l3::name;

constexpr ObisId message_short::id;
constexpr const char* message_short::name_progmem;
constexpr const __FlashStringHelper *message_short::name;

constexpr ObisId message_long::id;
constexpr const char* message_long::name_progmem;
constexpr const __FlashStringHelper *message_long::name;

constexpr ObisId voltage_l1::id;
constexpr const char* voltage_l1::name_progmem;
constexpr const __FlashStringHelper *voltage_l1::name;

constexpr ObisId voltage_l2::id;
constexpr const char* voltage_l2::name_progmem;
constexpr const __FlashStringHelper *voltage_l2::name;

constexpr ObisId voltage_l3::id;
constexpr const char* voltage_l3::name_progmem;
constexpr const __FlashStringHelper *voltage_l3::name;

constexpr ObisId current_l1::id;
constexpr const char* current_l1::name_progmem;
constexpr const __FlashStringHelper *current_l1::name;

constexpr ObisId current_l2::id;
constexpr const char* current_l2::name_progmem;
constexpr const __FlashStringHelper *current_l2::name;

constexpr ObisId current_l3::id;
constexpr const char* current_l3::name_progmem;
constexpr const __FlashStringHelper *current_l3::name;

constexpr ObisId power_delivered_l1::id;
constexpr const char* power_delivered_l1::name_progmem;
constexpr const __FlashStringHelper *power_delivered_l1::name;

constexpr ObisId power_delivered_l2::id;
constexpr const char* power_delivered_l2::name_progmem;
constexpr const __FlashStringHelper *power_delivered_l2::name;

constexpr ObisId power_delivered_l3::id;
constexpr const char* power_delivered_l3::name_progmem;
constexpr const __FlashStringHelper *power_delivered_l3::name;

constexpr ObisId power_returned_l1::id;
constexpr const char* power_returned_l1::name_progmem;
constexpr const __FlashStringHelper *power_returned_l1::name;

constexpr ObisId power_returned_l2::id;
constexpr const char* power_returned_l2::name_progmem;
constexpr const __FlashStringHelper *power_returned_l2::name;

constexpr ObisId power_returned_l3::id;
constexpr const char* power_returned_l3::name_progmem;
constexpr const __FlashStringHelper *power_returned_l3::name;

constexpr ObisId gas_device_type::id;
constexpr const char* gas_device_type::name_progmem;
constexpr const __FlashStringHelper *gas_device_type::name;

constexpr ObisId gas_equipment_id::id;
constexpr const char* gas_equipment_id::name_progmem;
constexpr const __FlashStringHelper *gas_equipment_id::name;

constexpr ObisId gas_valve_position::id;
constexpr const char* gas_valve_position::name_progmem;
constexpr const __FlashStringHelper *gas_valve_position::name;

constexpr ObisId gas_delivered::id;
constexpr const char* gas_delivered::name_progmem;
constexpr const __FlashStringHelper *gas_delivered::name;

constexpr ObisId thermal_device_type::id;
constexpr const char* thermal_device_type::name_progmem;
constexpr const __FlashStringHelper *thermal_device_type::name;

constexpr ObisId thermal_equipment_id::id;
constexpr const char* thermal_equipment_id::name_progmem;
constexpr const __FlashStringHelper *thermal_equipment_id::name;

constexpr ObisId thermal_valve_position::id;
constexpr const char* thermal_valve_position::name_progmem;
constexpr const __FlashStringHelper *thermal_valve_position::name;

constexpr ObisId thermal_delivered::id;
constexpr const char* thermal_delivered::name_progmem;
constexpr const __FlashStringHelper *thermal_delivered::name;

constexpr ObisId water_device_type::id;
constexpr const char* water_device_type::name_progmem;
constexpr const __FlashStringHelper *water_device_type::name;

constexpr ObisId water_equipment_id::id;
constexpr const char* water_equipment_id::name_progmem;
constexpr const __FlashStringHelper *water_equipment_id::name;

constexpr ObisId water_valve_position::id;
constexpr const char* water_valve_position::name_progmem;
constexpr const __FlashStringHelper *water_valve_position::name;

constexpr ObisId water_delivered::id;
constexpr const char* water_delivered::name_progmem;
constexpr const __FlashStringHelper *water_delivered::name;

constexpr ObisId slave_device_type::id;
constexpr const char* slave_device_type::name_progmem;
constexpr const __FlashStringHelper *slave_device_type::name;

constexpr ObisId slave_equipment_id::id;
constexpr const char* slave_equipment_id::name_progmem;
constexpr const __FlashStringHelper *slave_equipment_id::name;

constexpr ObisId slave_valve_position::id;
constexpr const char* slave_valve_position::name_progmem;
constexpr const __FlashStringHelper *slave_valve_position::name;

constexpr ObisId slave_delivered::id;
constexpr const char* slave_delivered::name_progmem;
constexpr const __FlashStringHelper *slave_delivered::name;
