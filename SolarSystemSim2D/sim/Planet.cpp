/**
Planet.cpp

Description
-----------
Function definitions for the planet simulation object.
*/

#include "Planet.h"

Planet::Planet(
	std::string name,
	double mass,
	uint32_t radius,
	int64_t distance,
	uint32_t max_trace_points,
	uint8_t r,
	uint8_t g,
	uint8_t b
) :
	m_name(name),
	m_mass(mass),
	m_radius(radius),
	m_distance(distance),
	m_max_trace_points(max_trace_points),
	m_x(0),
	m_y(0),
	m_vx(0),
	m_vy(0),
	m_ax(0),
	m_ay(0),
	m_color_r(r),
	m_color_g(g),
	m_color_b(b)
{
	// Explicity set the trace points to an empty
	// vector.
	m_trace = {};
}

void Planet::setPosition(double x, double y) {
	m_x = x;
	m_y = y;
}

std::tuple<double, double> Planet::getPosition() {
	return { m_x, m_y };
}

void Planet::setVelocity(double vx, double vy) {
	m_vx = vx;
	m_vy = vy;
}

std::tuple<double, double> Planet::getVelocity() {
	return { m_vx, m_vy };
}

void Planet::setAcceleration(double ax, double ay) {
	m_ax = ax;
	m_ay = ay;
}

std::tuple<double, double> Planet::getAcceleration() {
	return { m_ax, m_ay };
}

void Planet::setRGB(uint8_t r, uint8_t g, uint8_t b) {
	m_color_r = r;
	m_color_g = g;
	m_color_b = b;
}

std::tuple<uint8_t, uint8_t, uint8_t> Planet::getRGB() {
	return { m_color_r, m_color_g, m_color_b };
}

std::string Planet::getName() {
	return m_name;
}

double Planet::getMass() {
	return m_mass;
}

uint32_t Planet::getRadius() {
	return m_radius;
}

int64_t Planet::getDistance() {
	return m_distance;
}

void Planet::addTracePoint(Vector2 point) {
	if (m_trace.size() > m_max_trace_points) {
		m_trace.erase(m_trace.begin());
	}

	m_trace.push_back(point);
}

void Planet::clearTracePoints() {
	m_trace.clear();
}

std::vector<Vector2> Planet::getTracePoints() {
	return m_trace;
}