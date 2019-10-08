/*
 * DSMR 2.2 example project.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <stdlib.h>

#include <dsmr/dsmr.h>

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

static const char *raw_packet = "/XMX5LGBBFG1012471273\r\n\r\n1-3:0.2.8(42)\r\n"
								"0-0:1.0.0(190927214707S)\r\n"
		"0-0:96.1.1(4530303331303033323530393235343136)\r\n1-0:1.8.1(008771.849*kWh)\r\n"
  "1-0:1.8.2(006475.011*kWh)\r\n1-0:2.8.1(003412.635*kWh)\r\n1-0:2.8.2(008741.572*kWh)\r\n"
  "0-0:96.14.0(0001)\r\n1-0:1.7.0(00.792*kW)\r\n1-0:2.7.0(00.000*kW)\r\n0-0:96.7.21(00004)\r\n"
  "0-0:96.7.9(00003)\r\n"
  "1-0:99.97.0(3)(0-0:96.7.19)(181124150040W)(0000001888*s)(180206113955W)(0000004457*s)(170905104526S)(0000003233*s)\r\n"
  "1-0:32.32.0(00000)\r\n1-0:32.36.0(00000)\r\n0-0:96.13.1()\r\n0-0:96.13.0()\r\n"
  "1-0:31.7.0(004*A)\r\n1-0:21.7.0(00.792*kW)\r\n"
  "1-0:22.7.0(00.000*kW)\r\n0-1:24.1.0(003)\r\n"
  "0-1:96.1.0(4730303235303033333133333737333135)\r\n"
  "0-1:24.2.1(190927210000S)(03749.001*m3)\r\n!1A6A\r\n";

int main(int argc, char **argv)
{
	std::cout << "Parsing DSMR v4 packet..!" << std::endl;

	DsmrData data;
	ResultData result = P1Parser::parse(&data, raw_packet, strlen(raw_packet));

	if(result.err) {
		std::cout << "Unable to parse data: " <<
		          result.fullError(raw_packet, raw_packet + strlen(raw_packet));
	} else {
		float energy = data.energy_delivered_tariff1.int_val() +
				data.energy_delivered_tariff2.int_val();
		energy *= 0.001;
		std::cout << "Energy delivered: " << energy;
	}

	return -EXIT_SUCCESS;
}

