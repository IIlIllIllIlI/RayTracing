#pragma once
#include <limits>
#include <cstdlib>

class util
{
public:
	// Constants
	const double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
	const double PI = 3.1415926535897932385;

	// Utility Functions

	inline double degreesToRadians(double degrees) {
		return degrees * PI / 180.0;
	}

	// Returns a random real in [0,1).
	inline double randomDouble() {
		return rand() / (RAND_MAX + 1.0);
	}

	// Returns a random real in [min,max).
	inline double randomDouble(double min, double max) {	
		return min + (max - min) * randomDouble();
	}

	inline double clamp(double x, double min, double max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

};

