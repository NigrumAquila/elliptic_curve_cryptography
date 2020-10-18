#include "EllipticCurve.h"

const EllipticCurve::Point EllipticCurve::zero = {0, 0};

EllipticCurve::EllipticCurve() 
{
	setParams(1, 18, 19);
	setGenerator(7, 8);
}
EllipticCurve::EllipticCurve(__int64 a, __int64 b, __int64 p, __int64 x, __int64 y)
{
	setParams(a, b, p);
	setGenerator(x, y);
}

void EllipticCurve::setParams(__int64 a, __int64 b, __int64 p)
{
	this->m_a = a; 
	this->m_b = b;
	this->m_p = p;
}

void EllipticCurve::setGenerator(__int64 x, __int64 y)
{
	this->generator.m_x = x;
	this->generator.m_y = y;
}

std::map<char, __int64>* EllipticCurve::getParams()
{
	std::map<char, __int64>* params = new std::map<char, __int64>;
	params->insert(std::pair<char, __int64>('a', this->m_a));
	params->insert(std::pair<char, __int64>('b', this->m_b));
	params->insert(std::pair<char, __int64>('p', this->m_p));
	return params;
}

EllipticCurve::Point EllipticCurve::getGenerator()
{
	return this->generator;
}

bool EllipticCurve::validatePoint(const Point& point)
{
	if (point == EllipticCurve::zero) { return true; }
	return static_cast<int>(pow(point.m_y, 2)) % this->m_p == static_cast<int>((pow(point.m_x, 3)) + (unsigned __int64)this->m_a * point.m_x + this->m_b) % this->m_p;
}

EllipticCurve::Point EllipticCurve::reflect(Point point)
{
	point.m_y = this->m_p - point.m_y;
	return point;
}

__int64 EllipticCurve::sqrtModP(__int64& x)
{
	x = x % this->m_p;
	for (int i = 2; i < this->m_p; i++) 
		if (((unsigned __int64)i * i) % this->m_p == x) 
			return i;
}

EllipticCurve::Point* EllipticCurve::findPointsOnX(__int64 x)
{
	EllipticCurve::Point* points = new EllipticCurve::Point[2];
	__int64 left = static_cast<int>((pow(x, 3)) + (unsigned __int64)this->m_a * x + this->m_b) % this->m_p;
	points[0].m_x = x, points[1].m_x = x;
	points[0].m_y = this->sqrtModP(left);
	points[1].m_y = this->reflect(points[0]).m_y;
	return points;
}

__int64 EllipticCurve::getSubgroupOrder(Point& point)
{
	for (int i = 1; i < this->m_p + 1; i++)
		if(this->multiply(point, i) == EllipticCurve::zero) 
			return i;
}

__int64 EllipticCurve::modInverse(__int64 n)
{
	n = n % this->m_p;
	__int64 p = (n > 0) ? 1 : -(this->m_p) + 1;
	
	for (int x = 1; x < this->m_p; x++)
		if ((n * x) % this->m_p == p)
			return x;
}

EllipticCurve::Point EllipticCurve::multiply(const EllipticCurve::Point& point, __int64 n)
{
	EllipticCurve::Point r = this->zero;
	EllipticCurve::Point m2 = point;
	while(0 < n) {
		if ((n & 1) == 1)
			r = this->addition(r, m2);

		n = n >> 1;
		m2 = this->addition(m2, m2);
	}
	return r;
}

EllipticCurve::Point EllipticCurve::addition(const EllipticCurve::Point& lhs, const EllipticCurve::Point& rhs)
{
	if (lhs == EllipticCurve::zero) { return rhs; }
	if (rhs == EllipticCurve::zero) { return lhs; }
	if (lhs.m_x == rhs.m_x && (lhs.m_y != rhs.m_y || lhs.m_y == 0)) { return EllipticCurve::zero; }
	
	__int64 left;
	if (lhs.m_x == rhs.m_x)
		left = (3 * lhs.m_x * lhs.m_x + this->m_a) * EllipticCurve::modInverse(2 * lhs.m_y) % this->m_p;
	else
		left = (rhs.m_y - lhs.m_y) * EllipticCurve::modInverse(rhs.m_x - lhs.m_x) % this->m_p;

	__int64 computeX = (left * left - lhs.m_x - rhs.m_x) % this->m_p;
	__int64 x = (computeX > 0) ? computeX : this->m_p + computeX;
	__int64 computeY = (left * (lhs.m_x - x) - lhs.m_y) % this->m_p;
	__int64 y = (computeY > 0) ? computeY : this->m_p + computeY;

	return EllipticCurve::Point{ x, y };
}

bool operator==(const EllipticCurve::Point& lhs, const EllipticCurve::Point& rhs)
{
	return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
}