#include "ElGamal.h"

ElGamal::ElGamal(EllipticCurve& ec)
{
	this->ec = ec;
	this->generator = this->ec.getGenerator();
	this->subgroupOrder = this->ec.getSubgroupOrder(this->generator);
}

EllipticCurve::Point ElGamal::generatePublicKey(__int64 privateKey)
{
	return this->ec.multiply(this->generator, privateKey);
}

EllipticCurve::Point* ElGamal::encrypt(EllipticCurve::Point& data, EllipticCurve::Point& publicKey)
{
	// random between 1 and p - 1
	__int64 random = std::rand();
	EllipticCurve::Point* cipher = new EllipticCurve::Point[2];
	cipher[0] = this->ec.multiply(this->generator, random);
	cipher[1] = this->ec.addition(data, this->ec.multiply(publicKey, random));
	return cipher;
}

EllipticCurve::Point ElGamal::decrypt(EllipticCurve::Point* cipher, __int64 privateKey)
{
	EllipticCurve::Point res = this->ec.addition(cipher[1], this->ec.reflect(this->ec.multiply(cipher[0], privateKey)));
	return res;
}

EllipticCurve ElGamal::getEllipticCurve() { return this->ec; }
EllipticCurve::Point ElGamal::getGenerator() { return this->generator; }
__int64 ElGamal::getSubgroupOrder() { return this->subgroupOrder; }