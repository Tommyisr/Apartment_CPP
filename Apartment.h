#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment
{
public:
    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

    Apartment (SquareType** squares, int length, int width, int price);
    Apartment (const Apartment& apt);
    ~Apartment();
    Apartment& operator=(const Apartment& apt);
	int getTotalArea() const;
	int getPrice() const;
	int getLength() const;
	int getWidth() const;
	Apartment& operator+=(const Apartment& apt);
	SquareType& operator()(const int row, const int col) const;
	bool operator<(const Apartment& apt) const;
private:
    SquareType** squares;
    int length;
    int width;
    int price;
};

/*****************************
 * External operator function
 ****************************/
//bool operator<(const Apartment& apt1, const Apartment& apt2);
Apartment operator+(const Apartment& apt1, const Apartment& apt2);


#endif //MTM4_APARTMENT_H
