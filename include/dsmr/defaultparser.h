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
			dsmr::fields::identification,
			dsmr::fields::p1_version,
			dsmr::fields::timestamp,
			dsmr::fields::equipment_id,
			dsmr::fields::energy_delivered_tariff1,
			dsmr::fields::energy_delivered_tariff2,
			dsmr::fields::energy_returned_tariff1,
			dsmr::fields::energy_returned_tariff2,
			dsmr::fields::electricity_tariff,
			dsmr::fields::power_delivered,
			dsmr::fields::power_returned,
			dsmr::fields::power_delivered_l1,
			dsmr::fields::power_delivered_l2,
			dsmr::fields::power_delivered_l3,
			dsmr::fields::power_returned_l1,
			dsmr::fields::power_returned_l2,
			dsmr::fields::power_returned_l3,
			dsmr::fields::gas_device_type,
			dsmr::fields::gas_equipment_id
		>;

		std::string parse(const std::string& datagram);
		std::string parse(const std::vector<std::string>& datagrams);

		void setJsonValue(const std::string& key, const std::string& value)
		{
			this->_json[key] = value;
		}

		/*void setJsonValue(const std::string& key, uint32_t value)
		{
			this->_json[key] = value;
		}*/

		void setJsonValue(const std::string& key, float value)
		{
			this->_json[key] = value;
		}

		void reset()
		{
			this->_json.clear();
		}

	private:
		nlohmann::json _json;

		/* Methods */
	};

	namespace detail
	{
		struct PrinterFunc {
			explicit constexpr PrinterFunc(DefaultParser* parser) : parser(parser)
			{ }

			template <typename AttrType>
			void apply(AttrType& attr)
			{
				if(!attr.present())
					return;

				this->parser->setJsonValue(AttrType::name, attr.val());
			}

		private:
			DefaultParser* parser;
		};

	}
}
