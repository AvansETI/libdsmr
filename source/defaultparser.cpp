/*
 * Default parser implementation.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

#include <dsmr/dsmr.h>
#include <dsmr/defaultparser.h>

namespace dsmr
{
	std::string DefaultParser::parse(const std::string &datagram)
	{
		DateType data;
		ResultType result = P1Parser::parse(&data, datagram.c_str(), datagram.length());

		if(result.err) {
			auto raw_packet = datagram.c_str();
			std::cout << "Unable to parse datagram: " << result.fullError(raw_packet, raw_packet + strlen(raw_packet)) << std::endl;
			return "";
		}

		this->_json.clear();
		data.applyEach(detail::PrinterFunc(this));
		return this->_json.dump();
	}

	std::string DefaultParser::parse(const std::vector<std::string> &datagrams)
	{
		uint idx = 0;
		nlohmann::json ary = nlohmann::json::array();


		for(auto& datagram : datagrams) {
			DateType data;
			ResultType result = P1Parser::parse(&data, datagram.c_str(), datagram.length());

			if(result.err) {
				auto raw_packet = datagram.c_str();
				std::cout << "Unable to parse datagram: " << result.fullError(raw_packet, raw_packet + strlen(raw_packet)) << std::endl;
				return "";
			}

			this->_json.clear();
			data.applyEach(detail::PrinterFunc(this));
			ary[idx++] = this->_json;
		}

		return ary.dump();
	}
}
