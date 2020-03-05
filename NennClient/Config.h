#pragma once
#include <string>
#include <json.hpp>

using namespace std;
using namespace nlohmann;

class Config
{
private:
	std::string _filename;

public:
	std::string username;
	std::string password;

	Config(std::string filename);

	json read();
	void write();
};

