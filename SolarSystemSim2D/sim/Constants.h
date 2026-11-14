/**
Constants.h

Description
-----------
Defines the universal, planetary, and scale constants for the
solar system simulation.
*/

#pragma once
#include <cstdint>
#include <string>

namespace solar_constants {
	// Universal Constants
	const double G = 6.67430e-20;

	// Planet Names
	const std::string SUN = "Sun";
	const std::string MERCURY = "Mercury";
	const std::string VENUS = "Venus";
	const std::string EARTH = "Earth";
	const std::string MARS = "Mars";
	const std::string JUPITER = "Jupiter";
	const std::string SATURN = "Saturn";
	const std::string URANUS = "Uranus";
	const std::string NEPTUNE = "Neptune";

	// Conversion Constants
	const uint32_t SUN_CONVERSION    = 100000;
	const uint32_t PLANET_CONVERSION = 10000;
	const uint32_t KM_PER_PIXEL      = 1000000;
	const double   TIME_MULTIPLIER   = 1000000.0;

	// Planetary Mass (KG) Constants
	const double SUN_MASS_KG     = 1.99e30;
	const double MERCURY_MASS_KG = 3.30e23;
	const double VENUS_MASS_KG   = 4.87e24;
	const double EARTH_MASS_KG   = 5.97e24;
	const double MARS_MASS_KG    = 6.42e23;
	const double JUPITER_MASS_KG = 1.90e27;
	const double SATURN_MASS_KG  = 5.68e26;
	const double URANUS_MASS_KG  = 8.68e25;
	const double NEPTUNE_MASS_KG = 1.02e26;

	// Planetary Radius (KM) Constants
	const uint32_t SUN_RADIUS_KM     = 695700;
	const uint32_t MERCURY_RADIUS_KM = 2440;
	const uint32_t VENUS_RADIUS_KM   = 6052;
	const uint32_t EARTH_RADIUS_KM   = 6371;
	const uint32_t MARS_RADIUS_KM    = 3390;
	const uint32_t JUPITER_RADIUS_KM = 69911;
	const uint32_t SATURN_RADIUS_KM  = 58232;
	const uint32_t URANUS_RADIUS_KM  = 25362;
	const uint32_t NEPTUNE_RADIUS_KM = 26622;

	// Planetary Distance (KM) Constants (from sun)
	const int64_t SUN_DISTANCE_KM = 0;
	const int64_t MERCURY_DISTANCE_KM = 57909227;
	const int64_t VENUS_DISTANCE_KM   = 108209475;
	const int64_t EARTH_DISTANCE_KM   = 149598262;
	const int64_t MARS_DISTANCE_KM    = 227943824;
	const int64_t JUPITER_DISTANCE_KM = 778340821;
	const int64_t SATURN_DISTANCE_KM  = 1426666422;
	const int64_t URANUS_DISTANCE_KM  = 2870989228;
	const int64_t NEPTUNE_DISTANCE_KM = 4504299579;

	// Orbital Trace Points
	const uint32_t SUN_TRACE_POINTS = 0;
	const uint32_t MERCURY_TRACE_POINTS = 1000;
	const uint32_t VENUS_TRACE_POINTS = 1000;
	const uint32_t EARTH_TRACE_POINTS = 1000;
	const uint32_t MARS_TRACE_POINTS = 1000;
	const uint32_t JUPITER_TRACE_POINTS = 1000;
	const uint32_t SATURN_TRACE_POINTS = 1000;
	const uint32_t URANUS_TRACE_POINTS = 1000;
	const uint32_t NEPTUNE_TRACE_POINTS = 1000;

	// Planetary Colors (RGB)
	const uint8_t SUN_R = 255;
	const uint8_t SUN_G = 214;
	const uint8_t SUN_B = 0;
	const uint8_t MERCURY_R = 153;
	const uint8_t MERCURY_G = 153;
	const uint8_t MERCURY_B = 153;
	const uint8_t VENUS_R = 255;
	const uint8_t VENUS_G = 128;
	const uint8_t VENUS_B = 0;
	const uint8_t EARTH_R = 0;
	const uint8_t EARTH_G = 59;
	const uint8_t EARTH_B = 250;
	const uint8_t MARS_R = 255;
	const uint8_t MARS_G = 90;
	const uint8_t MARS_B = 0;
	const uint8_t JUPITER_R = 209;
	const uint8_t JUPITER_G = 178;
	const uint8_t JUPITER_B = 160;
	const uint8_t SATURN_R = 232;
	const uint8_t SATURN_G = 228;
	const uint8_t SATURN_B = 171;
	const uint8_t URANUS_R = 0;
	const uint8_t URANUS_G = 220;
	const uint8_t URANUS_B = 250;
	const uint8_t NEPTUNE_R = 0;
	const uint8_t NEPTUNE_G = 4;
	const uint8_t NEPTUNE_B = 176;
}