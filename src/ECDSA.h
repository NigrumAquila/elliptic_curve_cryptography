#pragma once
#include "EllipticCurve.h"

class ECDSA
{
private:
	EllipticCurve ec;
	EllipticCurve::Point generator;
	__int64 subgroupOrder;
	__int64 p;

public:
	ECDSA(EllipticCurve& ec);
	EllipticCurve::Point generatePublicKey(__int64 privateKey);
	std::pair<__int64, __int64>& sign(__int64& hash, __int64 privateKey);
	bool validate(__int64& hash, std::pair<__int64, __int64>& signature, EllipticCurve::Point& publicKey);

	EllipticCurve getEllipticCurve();
	EllipticCurve::Point getGenerator();
	__int64 getSubgroupOrder();
};

