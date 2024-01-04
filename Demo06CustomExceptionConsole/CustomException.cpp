#include <iostream>

class MagnitudeWasZeroException {};

struct Vector2
{
	double Magnitude() const noexcept {
		return sqrt(x * x + y * y);
	}

	void Normalize() {
		const double magnitude = Magnitude();

		if (magnitude == 0) {
			throw MagnitudeWasZeroException();
		}

		x /= magnitude;
		y /= magnitude;
	}

	void Print() const {
		std::cout << "{" << x << ", " << y << "}";
	}

	double x{}, y{};
};

int main()
{
	Vector2 myVector{0.0, 0.0};

	try {
		myVector.Normalize();
		myVector.Print();
	}
	catch (const MagnitudeWasZeroException& exception) {
		std::cout << "Magnitude is zero.\n" << "Size: " << sizeof(exception) <<"\n";
	}
}

