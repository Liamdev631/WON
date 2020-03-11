#pragma once
#include <json.hpp>
#include <string>

using namespace nlohmann;
using namespace std;

// A utility class for reading JSON files fiven a filename.
class JsonReader
{
public:
	static void read(json& outJson, string filename);
};

