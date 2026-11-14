/**
Planet.h

Description
-----------
Defines the attributes for a planet simulation object.
*/

#pragma once
#include <string>
#include <tuple>
#include <vector>

struct Vector2 {
	double x;
	double y;
};

class Planet {
public:
	/**
	* @brief Constructor for planet.
	* 
	* @param[in] name planet name
	* @param[in] mass planet mass (kg)
	* @param[in] radius planet radius (km)
	* @param[in] distance planet distance from sun center (km)
	* @param[in] r R color value
	* @param[in] g G color value
	* @param[in] b B color value
	*/
	Planet(
		std::string name,
		double mass,
		uint32_t radius,
		int64_t distance,
		uint32_t max_trace_points,
		uint8_t r,
		uint8_t g,
		uint8_t b
	);

	/**
	* @brief Setter functions for planet position, velocity
	* and acceleration.
	*/
	void setPosition(double x, double y);
	void setVelocity(double vx, double vy);
	void setAcceleration(double ax, double ay);

	/**
	* @brief Getter functions for planet position, velocity
	* and acceleration.
	*/
	std::tuple<double, double> getPosition();
	std::tuple<double, double> getVelocity();
	std::tuple<double, double> getAcceleration();

	/**
	* @brief Setter for planet RGB colors.
	*/
	void setRGB(uint8_t r, uint8_t g, uint8_t b);

	/**
	* @brief Getter for planet RGB colors.
	*/
	std::tuple<uint8_t, uint8_t, uint8_t> getRGB();

	/**
	* @brief Getter functions for planet attributes.
	*/
	std::string getName();
	double getMass();
	uint32_t getRadius();
	int64_t getDistance();

	/**
	* @brief Add trace points to the orbital trace.
	* @brief Clear trace points.
	* @brief Get a trace point at a certian index.
	*/
	void addTracePoint(Vector2 point);
	void clearTracePoints();
	std::vector<Vector2> getTracePoints();

private:
	std::string m_name;          // planet name
	double m_mass;               // planet mass (kg)
	uint32_t m_radius;           // planet radius (km)
	int64_t m_distance;          // distance from sun center (km)
	uint32_t m_max_trace_points; // max number of orbital trace points

	double m_x;  // x position
	double m_y;  // y position
	double m_vx; // x velocity
	double m_vy; // y velocity
	double m_ax; // x acceleration
	double m_ay; // y acceleration

	uint8_t m_color_r; // R color value 
	uint8_t m_color_g; // G color value
	uint8_t m_color_b; // B color value

	// Orbital Points
	std::vector<Vector2> m_trace;
};