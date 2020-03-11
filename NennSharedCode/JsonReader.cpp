#include "JsonReader.h"

void JsonReader::read(json& outJson, string filename)
{
	FILE* file;
	fopen_s(&file, filename.c_str(), "r");
	if (!file)
	{
		printf("Config: Failed to open config file for reading (%s).\n", filename.c_str());
		outJson = json(nullptr);
	}

	constexpr size_t BufferSize = 1024 * 16;
	char* buffer = new char[BufferSize];
	size_t strLen = fread_s(buffer, BufferSize, sizeof(char), BufferSize / sizeof(char), file);
	fclose(file);

	string jString = string(buffer, strLen);
	outJson = json::parse(jString);
}
