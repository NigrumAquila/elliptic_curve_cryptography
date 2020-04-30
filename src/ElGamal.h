#pragma once
#include "EllipticCurve.h"


class ElGamal
{
private:
	EllipticCurve ec;
	EllipticCurve::Point generator;
	__int64 subgroupOrder;
public:
	ElGamal(EllipticCurve& ec);
	EllipticCurve::Point generatePublicKey(__int64 privateKey);
	EllipticCurve::Point* encrypt(EllipticCurve::Point& data, EllipticCurve::Point& publicKey);
	EllipticCurve::Point decrypt(EllipticCurve::Point* cipher, __int64 privateKey);

	EllipticCurve getEllipticCurve();
	EllipticCurve::Point getGenerator();
	__int64 getSubgroupOrder();
};

