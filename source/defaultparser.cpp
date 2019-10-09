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

		if(result.err)
			return "";

		this->_json.clear();
		data.applyEach(detail::PrinterFunc(this));
		return std::move(this->_json.dump());
	}
}
