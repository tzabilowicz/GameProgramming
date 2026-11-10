/**
Constants.h

Description
-----------
Defines the universal, planetary, and scale constants for the
solar system simulation.
*/

#pragma once
#include <cstdint>

namespace solar_constants {
	// Universal Constants
	inline constexpr double G = 6.67430e-20;

	// Conversion Constants
	inline constexpr uint32_t SUN_CONVERSION    = 100000;
	inline constexpr uint32_t PLANET_CONVERSION = 10000;
	inline constexpr uint32_t KM_PER_PIXEL      = 1000000;
	inline constexpr double   TIME_MULTIPLIER   = 1000000.0;

	// Planetary Mass (KG) Constants
	inline constexpr double SUN_MASS_KG     = 1.99e30;
	inline constexpr double MERCURY_MASS_KG = 3.30e23;
	inline constexpr double VENUS_MASS_KG   = 4.87e24;
	inline constexpr double EARTH_MASS_KG   = 5.97e24;
	inline constexpr double MARS_MASS_KG    = 6.42e23;
	inline constexpr double JUPITER_MASS_KG = 1.90e27;
	inline constexpr double SATURN_MASS_KG  = 5.68e26;
	inline constexpr double URANUS_MASS_KG  = 8.68e25;
	inline constexpr double NEPTUNE_MASS_KG = 1.02e26;

	// Planetary Radius (KM) Constants
	inline constexpr uint32_t SUN_RADIUS_KM     = 695700;
	inline constexpr uint32_t MERCURY_RADIUS_KM = 2440;
	inline constexpr uint32_t VENUS_RADIUS_KM   = 6052;
	inline constexpr uint32_t EARTH_RADIUS_KM   = 6371;
	inline constexpr uint32_t MARS_RADIUS_KM    = 3390;
	inline constexpr uint32_t JUPITER_RADIUS_KM = 69911;
	inline constexpr uint32_t SATURN_RADIUS_KM  = 58232;
	inline constexpr uint32_t URANUS_RADIUS_KM  = 25362;
	inline constexpr uint32_t NEPTUNE_RADIUS_KM = 26622;

	// Planetary Distance (KM) Constants (from sun)
	inline constexpr int64_t SUN_DISTANCE_KM = 0;
	inline constexpr int64_t MERCURY_DISTANCE_KM = 57909227;
	inline constexpr int64_t VENUS_DISTANCE_KM   = 108209475;
	inline constexpr int64_t EARTH_DISTANCE_KM   = 149598262;
	inline constexpr int64_t MARS_DISTANCE_KM    = 227943824;
	inline constexpr int64_t JUPITER_DISTANCE_KM = 778340821;
	inline constexpr int64_t SATURN_DISTANCE_KM  = 1426666422;
	inline constexpr int64_t URANUS_DISTANCE_KM  = 2870989228;
	inline constexpr int64_t NEPTUNE_DISTANCE_KM = 4504299579;

	// Planetary Colors (RGB)
	inline constexpr uint8_t SUN_R = 255;
	inline constexpr uint8_t SUN_G = 214;
	inline constexpr uint8_t SUN_B = 0;
	inline constexpr uint8_t MERCURY_R = 153;
	inline constexpr uint8_t MERCURY_G = 153;
	inline constexpr uint8_t MERCURY_B = 153;
	inline constexpr uint8_t VENUS_R = 255;
	inline constexpr uint8_t VENUS_G = 128;
	inline constexpr uint8_t VENUS_B = 0;
	inline constexpr uint8_t EARTH_R = 0;
	inline constexpr uint8_t EARTH_G = 59;
	inline constexpr uint8_t EARTH_B = 250;
	inline constexpr uint8_t MARS_R = 255;
	inline constexpr uint8_t MARS_G = 90;
	inline constexpr uint8_t MARS_B = 0;
	inline constexpr uint8_t JUPITER_R = 209;
	inline constexpr uint8_t JUPITER_G = 178;
	inline constexpr uint8_t JUPITER_B = 160;
	inline constexpr uint8_t SATURN_R = 232;
	inline constexpr uint8_t SATURN_G = 228;
	inline constexpr uint8_t SATURN_B = 171;
	inline constexpr uint8_t URANUS_R = 0;
	inline constexpr uint8_t URANUS_G = 220;
	inline constexpr uint8_t URANUS_B = 250;
	inline constexpr uint8_t NEPTUNE_R = 0;
	inline constexpr uint8_t NEPTUNE_G = 4;
	inline constexpr uint8_t NEPTUNE_B = 176;
}