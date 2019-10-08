/*
 * Default parser implementation.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#pragma once

#include <nlohmann/json.hpp>
#include <dsmr/dsmr.h>

#include <string>
#include <iostream>

namespace dsmr
{
	class DefaultParser;

	namespace detail
	{
		struct PrinterFunc;
	}

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

		std::string parse(const std::string& datagram);
		std::string parse(std::string&& datagram);

		void setJsonValue(const std::string& key, const std::string& value)
		{
			this->_json[key] = value;
		}

		void setJsonValue(const std::string& key, uint32_t value)
		{
			this->_json[key] = value;
		}

		void reset()
		{
			this->_json.clear();
		}

		std::string serialize()
		{
			return std::move(this->_json.dump(4));
		}
	private:
		nlohmann::json _json;

	};

	namespace detail
	{
		struct PrinterFunc {
			explicit constexpr PrinterFunc(DefaultParser* parser) : parser(parser)
			{ }

			template <typename AttrType>
			void apply(AttrType& attr)
			{
				std::cout << "Name: " << AttrType::name << std::endl;
				std::cout << "Value: " << attr.val() << AttrType::unit() << std::endl;
				this->parser->setJsonValue(AttrType::name, attr.val());
			}

		private:
			DefaultParser* parser;
		};

	}
}
