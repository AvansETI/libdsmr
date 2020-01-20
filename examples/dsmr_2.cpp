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

/*static const char* raw_packet = "/KMP5ZABF001587315111\r\n\r\n"
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
   "!\r\n";*/
static const char *raw_data = "/KMP5 KA6U001748847113\r\n\r\n0-0:96.1.1(204B413655303031373438383437313133)\r\n1-0:1.8.1(07420.891*kWh)\r\n1-0:1.8.2(05577.665*kWh)\r\n1-0:2.8.1(00000.000*kWh)\r\n1-0:2.8.2(00000.000*kWh)\r\n0-0:96.14.0(0002)\r\n1-0:1.7.0(0000.05*kW)\r\n1-0:2.7.0(0000.00*kW)\r\n0-0:96.13.1()\r\n0-0:96.13.0()\r\n0-1:24.1.0(3)\r\n0-1:96.1.0(3238303131303031333132323630373133)\r\n0-1:24.3.0(200120100000)(00)(60)(1)(0-1:24.2.1)(m3)\r\n(02099.465)\r\n!\r\n";

static void test_mass_parse()
{
	std::vector<std::string> datagrams;
	std::string d1 = raw_data;
	DefaultParser parser;

	datagrams.push_back(d1);
	datagrams.push_back(d1);
	std::cout << "Mass parse result: " << std::endl;
	std::cout << parser.parse(datagrams) << std::endl;
}

int main(int argc, char **argv)
{
	DefaultParser parser;
	
	std::cout << "Single parse result: " << std::endl;
	std::cout << parser.parse(raw_data) << std::endl;
	std::cout << std::endl;

	test_mass_parse();

	return -EXIT_SUCCESS;
}
