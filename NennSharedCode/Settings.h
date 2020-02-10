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

// Camera Settings
const float CameraAngle = 0.5f; // Radians
const float CameraBoomLength = 2.5f;

// Speed Hacks
constexpr bool EnableSpeedHackDetection = false;
constexpr float MaxSpeed = 1.0f;

// Utility templates
template <typename T>
using EntityTable = std::array<T, NumberOfEntities>;

template <typename T>
using PlayerTable = std::array<T, NumberOfPlayers>;
