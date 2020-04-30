#pragma once
#include "EllipticCurve.h"

class ECDH
{
private:
	EllipticCurve ec;
	EllipticCurve::Point generator;
	__int64 subgroupOrder; 

public:
	ECDH(EllipticCurve& ec);
	EllipticCurve::Point generatePublicKey(__int64 privateKey);
	EllipticCurve::Point generateSharedSecret(EllipticCurve::Point& publicKey, __int64 privateKey);

	EllipticCurve getEllipticCurve();
	EllipticCurve::Point getGenerator();
	__int64 getSubgroupOrder();
};
