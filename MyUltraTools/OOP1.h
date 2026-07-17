#pragma once
#include "Tester.h"

#include <math.h>

//IPrintable.h
class IPrintable
{
protected:
	virtual void print() = 0;
};

//Figure.h
class Figure : public IPrintable
{
public:
	void print() override;
	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual std::string name() = 0;
private:

};
//Figure.cpp
void Figure::print() {}


//Circle.h
class Circle : public Figure
{
public:
	Circle(double radius) : Radius(radius) { if (radius <= 0) throw std::invalid_argument("Radius must be positive"); }
	double area() override;
	double perimeter() override;
	std::string name() override;

private:
	double Radius;
};

//Circle.cpp
double Circle::area() { return 3.14159 * Radius * Radius; }
double Circle::perimeter() { return 2.0 * 3.14159 * Radius; }
std::string Circle::name() { return "Circle"; }


//Rectangle.h
class Rectangle : public Figure
{
public:
	Rectangle(double width, double height) : Width(width), Height(height) { if (width <= 0 || height <= 0) throw std::invalid_argument("Size must be positive"); }
	double area() override;
	double perimeter() override;
	std::string name() override;
private:
	double Width;
	double Height;
};
//Rectangle.cpp
double Rectangle::area() { return Width * Height; }
double Rectangle::perimeter() { return 2 * (Width + Height); }
std::string Rectangle::name() { return "Rectangle"; }


//Triangle.h
class Triangle : public Figure
{
public:
	Triangle(double a, double b, double c) : A(a), B(b), C(c) { if (a <= 0 || b <= 0 || c <= 0) throw std::invalid_argument("Point must be positive"); }
	double area() override;
	double perimeter() override;
	std::string name() override;
private:
	double A;
	double B;
	double C;
};
//Triangle.cpp
double Triangle::area() {
	double p = perimeter() / 2;
	return sqrt(p * (p - A) * (p - B) * (p - C));
}
double Triangle::perimeter() { return A + B + C; }
std::string Triangle::name() { return "Triangle"; }


void Test1()
{
	Circle c(1.0);
	ASSERT_DOUBLE_EQUAL(3.14159, c.area(), 0.0001);
}
void testCircleAreaRadius2() {
	Circle c(2.0);
	ASSERT_DOUBLE_EQUAL(12.56637, c.area(), 0.0001);
}
void testCirclePerimeterRadius1() {
	Circle c(1.0);
	ASSERT_DOUBLE_EQUAL(6.28318, c.perimeter(), 0.0001); // 2*pi
}
void testCircleInvalidRadius() {
	ASSERT_THROWS(Circle(0));
	ASSERT_THROWS(Circle(-1.0));
}
void testFigureCollection() {
	std::vector<std::unique_ptr<Figure>> figures;
	figures.push_back(std::make_unique<Circle>(1));
	figures.push_back(std::make_unique<Rectangle>(2, 3));
	figures.push_back(std::make_unique<Triangle>(3, 4, 5));
	double totalArea = 0;
	for (auto& f : figures) totalArea += f->area();
	ASSERT_DOUBLE_EQUAL(3.14159 + 6 + 6, totalArea, 0.001);
}

void testTriangle345() {
	Triangle t(3, 4, 5);
	ASSERT_DOUBLE_EQUAL(6.0, t.area(), 0.0001);
	ASSERT_DOUBLE_EQUAL(12.0, t.perimeter(), 0.0001);
}
void testTriangleInvalid() {
	ASSERT_THROWS(Triangle(1, 2, 10));
}
void testRectangle() {
	Rectangle r(2, 3);
	ASSERT_DOUBLE_EQUAL(6.0, r.area(), 0.0001);
	ASSERT_DOUBLE_EQUAL(10.0, r.perimeter(), 0.0001);
}
void testRectangleInvalid() {
	ASSERT_THROWS(Rectangle(0, 3));
	ASSERT_THROWS(Rectangle(2, -1));
}
