#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace helper {

	inline std::vector<std::string> stringSplit(std::string text, char delimiter) 
	{
		std::stringstream lineStream(text);
		std::string cell;
		std::vector<std::string> result;

		while (std::getline(lineStream, cell, delimiter)) {
			result.push_back(cell);
		}

		return result;
	}

	inline const char* getEnvOrDefault(const char* envName, const char* defaultValue)
	{
		const char* value = std::getenv(envName);
		return value ? value : defaultValue;
	}
}