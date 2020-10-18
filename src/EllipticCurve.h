#pragma once
#include <map>

class EllipticCurve
{
public:
	struct Point
	{
		__int64 m_x;
		__int64 m_y;
	};

	static const Point zero;
	
	EllipticCurve();
	EllipticCurve(__int64 a, __int64 b, __int64 p, __int64 x, __int64 y);

	void setParams(__int64 a, __int64 b, __int64 p);
	void setGenerator(__int64 x, __int64 y);

	std::map<char, __int64>* getParams();
	Point getGenerator();

	bool validatePoint(const Point& point);
	Point reflect(Point point);
	Point* findPointsOnX(__int64 x);
	__int64 getSubgroupOrder(Point& point);

	__int64 sqrtModP(__int64 &x);
	__int64 modInverse(__int64 n);

	Point addition(const Point& lhs, const Point& rhs);
	Point multiply(const Point& point, __int64 n);
	friend bool operator==(const Point& lhs, const Point& rhs);

private:
	__int64 m_a, m_b, m_p;
	Point generator;
};