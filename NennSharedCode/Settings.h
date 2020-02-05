#pragma once
#include <string_view>
#include <array>

using namespace std;

// Server settings
constexpr int TicksPerSecond = 15;

// Network Settings
constexpr bool EnableConnectionTimeout = false;
constexpr unsigned short ServerPort = 25565;
static const char* ServerIP = "localhost";

// Entity settings
constexpr unsigned int NumberOfPlayers = 32;
constexpr unsigned int NumberOfNPCS = 256;
constexpr unsigned int NumberOfEntities = NumberOfPlayers + NumberOfNPCS;

// Speed Hacks
constexpr bool EnableSpeedHackDetection = false;
constexpr float MaxSpeed = 1.0f;

// Utility templates
template <typename T>
using EntityTable = array<T, NumberOfEntities>;

template <typename T>
using PlayerTable = array<T, NumberOfPlayers>;