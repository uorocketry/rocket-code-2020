#ifndef _HELPER_H
#define _HELPER_H

#include <string>
#include <vector>

namespace helper {
	std::vector<std::string> stringSplit(std::string text, char delimiter) {
		std::stringstream lineStream(text);
		std::string cell;
		std::vector<std::string> result;

		while (std::getline(lineStream, cell, delimiter)) {
			result.push_back(cell);
		}

		return result;
	}
}

#endif