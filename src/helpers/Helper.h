#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace helper {

	std::vector<std::string> stringSplit(std::string text, char delimiter);

	const char* getEnvOrDefault(const char* envName, const char* defaultValue);

	uint64_t getEnvOrDefault(const char* envName, uint64_t defaultValue);

	int processInt(std::string data);

	uint64_t processUInt64(std::string data);

	uint32_t processUInt32(std::string data);

	float processFloat(std::string data);

	double processDouble(std::string data);
}