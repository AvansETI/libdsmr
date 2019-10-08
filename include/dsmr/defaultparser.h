/*
 * Default parser implementation.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#pragma once

#include <dsmr/dsmr.h>

#include <string>

namespace dsmr
{
	class DefaultParser {
	public:
		using ResultType = ParseResult<void>;
		using DateType = ParsedData<
				/* String */        dsmr::fields:: identification
				/* String */        ,dsmr::fields::p1_version
				/* String */        ,dsmr::fields::timestamp
				/* String */        ,dsmr::fields::equipment_id
				/* FixedValue */    ,dsmr::fields::energy_delivered_tariff1
				/* FixedValue */    ,dsmr::fields::energy_delivered_tariff2
				/* FixedValue */    ,dsmr::fields::energy_returned_tariff1
				/* FixedValue */    ,dsmr::fields::energy_returned_tariff2
				/* String */        ,dsmr::fields::electricity_tariff
				/* FixedValue */    ,dsmr::fields::power_delivered
				/* FixedValue */    ,dsmr::fields::power_returned
				/* FixedValue */    ,dsmr::fields::power_delivered_l1
				/* FixedValue */    ,dsmr::fields::power_delivered_l2
				/* FixedValue */    ,dsmr::fields::power_delivered_l3
				/* FixedValue */    ,dsmr::fields::power_returned_l1
				/* FixedValue */    ,dsmr::fields::power_returned_l2
				/* FixedValue */    ,dsmr::fields::power_returned_l3
				/* uint16_t */      ,dsmr::fields::gas_device_type
				/* String */        ,dsmr::fields::gas_equipment_id
		>;

		constexpr DefaultParser() = default;

		std::string parse(const std::string& datagram);
		std::string parse(std::string&& datagram);
	};
}
