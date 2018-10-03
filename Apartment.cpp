#include <cstdlib>
#include <iostream>
#include "Apartment.h"
/*
 * Apartment (SquareType** squares, int length, int width, int price)
 * errors: IllegalArgException - if one of the arguments is not legal.
 */

Apartment::Apartment(SquareType** squares, int length, int width, int price) {

	if (squares==NULL || length<=0 || width<=0 || price<0)
	{
		throw IllegalArgException();
		return;
	}

	this->squares = new SquareType*[length];
	for (int i = 0; i < length; ++i) {
		this->squares[i] = new SquareType[width];
	}
	this->length = length;
	this->width = width;
	this->price = price;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			this->squares[i][j] = squares[i][j];
		}
	}
}
/*
 * ~Apartment() is a funtion that destroys an apartment.
 */

Apartment::~Apartment() {
	/*for (int i = 0; i < length; i++) {
		delete[] squares[i];
	}*/
	delete[] squares;
}
/*
 * Apartment (const Apartment& apt) is a function that copies an apartment.
 */

Apartment::Apartment(const Apartment& apt) {
	this->squares = new SquareType*[apt.length];
	for (int i = 0; i < apt.length; ++i) {
		this->squares[i] = new SquareType[apt.width];
	}
	this->length = apt.length;
	this->width = apt.width;
	this->price = apt.price;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			this->squares[i][j] = apt.squares[i][j];
		}
	}
}

/*
 * An operator = is an operator that assign the right apartment to the left.
 */

Apartment& Apartment::operator=(const Apartment& apt) {
	if (this == &apt) {
		return *this;
	}
	delete[] squares;
	squares = new Apartment::SquareType* [apt.length];
	for (int j = 0; j < apt.length; j++) {
		this->squares[j] = new SquareType[apt.width];
	}
	for (int i = 0; i < apt.length; i++) {
		for (int j = 0; j < apt.width; j++) {
			squares[i][j] = apt.squares[i][j];
		}
	}
	length = apt.length;
	width = apt.width;
	price = apt.price;
	return *this;
}

/*
 * getTotalArea() is an int function that returns the number of free squares.
 */

int Apartment::getTotalArea() const {
	int sum = 0;
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			if (squares[i][j] == Apartment::EMPTY) {
				sum++;
			}
		}
	}
	return sum;
}

/*
 * getPrice() is an int function that returns the price of the apartment
 */

int Apartment::getPrice() const{
	return price;
}

/*
 * getLength() is an int function that returns the length of the apartment
 *  (i.e. the number of columns)
 */

int Apartment::getLength() const {
	return length;
}

/*
 * getWidth() is an int function that returns the width of the apartment
 *  (i.e. the number of strings)
 */

int Apartment::getWidth() const {
	return width;
}

/*
 * An operator += adds two flats together. Only the left argument is changed.
 * We have some cases:
 * 1) If the widths of two flats are equal, the second just sticks
 * to the bottom of the first. (col j of 1st flat is continued by col j of 2nd)
 * 2) If the lengths of two flats are equal, the second flat sticks
 * to the right side of the first.(str j of 1st flat is continued by str j of 2nd)
 * 3) Otherwise, the second sticks to the bottom of the first. Absent squares become
 * "walls".
 */

Apartment& Apartment::operator+=(const Apartment& apt) {
	SquareType** newSquares;
	if (width == apt.width) {
		int oldLength = length;
		length += apt.length;
		newSquares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			newSquares[i] = new SquareType[width];
		}
		for (int i = oldLength; i < length; i++) {
			for (int j = 0; j < width; j++) {
				newSquares[i][j] = apt.squares[i - oldLength][j];
			}
		}
		for (int i = 0; i < oldLength; i++) {
			for (int j = 0; j < width; j++) {
				newSquares[i][j] = this->squares[i][j];
			}
		}
		delete[] squares;
		squares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			squares[i] = new SquareType[width];
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				squares[i][j] = newSquares[i][j];
			}
		}
	} else if (length == apt.length) {
		int oldWidth = width;
		width += apt.width;
		newSquares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			newSquares[i] = new SquareType[width];
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < oldWidth; j++) {
				newSquares[i][j] = squares[i][j];
			}
			for (int j = oldWidth; j < width; j++) {
				newSquares[i][j] = apt.squares[i][j - oldWidth];
			}
		}
		delete[] squares;
		squares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			squares[i] = new SquareType[width];
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				squares[i][j] = newSquares[i][j];
			}
		}
	} else {
		int oldWidth;
		int oldLength = length;
		length += apt.length;
		bool oldIsLess = (width < apt.width);
		if (oldIsLess) {
			oldWidth = width;
			width += (apt.width - width);
		}
		else {
			oldWidth = apt.width;
		}
		newSquares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			newSquares[i] = new SquareType[width];
		}
		for (int i = 0; i < oldLength; i++) {
			if (oldIsLess) {
				for (int j = 0; j < oldWidth; ++j) {
					newSquares[i][j] = squares[i][j];
				}
				for (int j = oldWidth; j < width; ++j) {
					newSquares[i][j] = WALL;
				}
			} else {
				for (int j = 0; j < width; ++j) {
					newSquares[i][j] = squares[i][j];
				}
			}
		}
		for (int i = oldLength; i < length; ++i) {
			if (oldIsLess) {
				for (int j = 0; j < width; ++j) {
					newSquares[i][j] = apt.squares[i-oldLength][j]; // fix
				}
			} else {
				for (int j = 0; j < oldWidth; ++j) {
					newSquares[i][j] = apt.squares[i-oldLength][j];
				}
				for (int j = oldWidth; j < width; ++j) {
					newSquares[i][j] = WALL;
				}
			}
		}
		delete[] squares;
		squares = new SquareType*[length];
		for (int i = 0; i < length; i++) {
			squares[i] = new SquareType[width];
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				squares[i][j] = newSquares[i][j];
			}
		}
	}
	price+=apt.price;
	for (int i = 0; i < length; ++i) {
		delete[] newSquares[i];
	}
	delete[] newSquares;
	return *this;
}

/*
 * An operator () takes two integer parameters: the 1st is a row, the 2nd is a col
 * and returns a reference to a suitable square.
 * Error: OutOfApartmentBoundsException - if one of the parameters is not legal
 * (out of bounds).
 */

Apartment::SquareType& Apartment::operator()(const int row, const int col) const {
	if ((row<0) || (col<0) || (row>=length) || (col>=width)) {
		throw OutOfApartmentBoundsException();
		//return;
		//return squares[0][0]; // should be Error
	}
	else {
	Apartment::SquareType& square=squares[row][col];
	return square;
	}
}

/*
 * An operator < compares two flats and returns 'true' if the 1st room
 * is smaller than the 2nd. The 1st flat is "smaller" iff the value of
 * price/area of the 1st flat is smaller than of the 2nd.
 */
bool Apartment::operator<(const Apartment& apt) const
{
	if (getPrice()*apt.getTotalArea() == apt.getPrice()*getTotalArea())
	{
		return getPrice() < apt.getPrice();
	}
	return (getPrice()*apt.getTotalArea() < apt.getPrice()*getTotalArea());


}



/*
 * An operator + adds to flats and returns the result.
 */

Apartment operator+(const Apartment& apt1, const Apartment& apt2)
{
	Apartment apt3(apt1);
	//apt3 += apt2;
	return apt3+=apt2;
}





