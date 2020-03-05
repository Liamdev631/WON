#include "Config.h"

Config::Config(string filename)
	: _filename(filename)
{

}

json Config::read()
{
	FILE* file;
	fopen_s(&file, _filename.c_str(), "r");
	if (!file)
	{
		printf("Config: Failed to open config file for reading (%s).\n", _filename.c_str());
		return json(nullptr);
	}

	constexpr unsigned int BufferSize = 512;
	char* buffer = new char[BufferSize];
	size_t strLen = fread_s(buffer, BufferSize, sizeof(char), BufferSize / sizeof(char), file);
	fclose(file);

	string jString = string(buffer, strLen);
	json j = json::parse(jString);
}

void Config::write()
{
	json j;
	j["username"] = username;
	j["password"] = password;
	string jString = j.dump(1, ' ', true);
	
	FILE* file;
	fopen_s(&file, _filename.c_str(), "w");
	if (!file)
	{
		printf("Config: Failed to open config file for writing (%s).\n", _filename.c_str());
		return;
	}
	fwrite(jString.c_str(), sizeof(char), jString.length(), file);
	fclose(file);
}
