/*
 * DSMR 2.2 example project.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <stdlib.h>

#include <dsmr/dsmr.h>
#include <dsmr/defaultparser.h>

#include <iostream>

using ResultData = ParseResult<void>;
using DsmrData = ParsedData<
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

static const char* raw_packet = "/KMP5ZABF001587315111\r\n\r\n"
							  "0-0:96.1.1(205C4D246333034353537383234323121)\r\n"
		 "1-0:1.8.1(00185.000*kWh)\r\n"
   "1-0:1.8.2(00084.000*kWh)\r\n"
   "1-0:2.8.1(00013.000*kWh)\r\n"
   "1-0:2.8.2(00019.000*kWh)\r\n"
   "0-0:96.14.0(0001)\r\n"
   "1-0:1.7.0(0000.98*kW)\r\n"
   "1-0:2.7.0(0000.00*kW)\r\n"
   "0-0:17.0.0(999*A)\r\n"
   "0-0:96.3.10(1)\r\n"
   "0-0:96.13.1()\r\n"
   "0-0:96.13.0()\r\n"
   "0-1:24.1.0(3)\r\n"
   "0-1:96.1.0(3238313031453631373038389930337131)\r\n"
   "0-1:24.3.0(120517020000)(08)(60)(1)(0-1:24.2.1)(m3)\r\n"
   "0-1:24.4.0(1)\r\n"
   "!\r\n";

int main(int argc, char **argv)
{
	DefaultParser parser;
	std::cout << parser.parse(raw_packet) << std::endl;

	return -EXIT_SUCCESS;
}
