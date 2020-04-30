#include "ECDSA.h"

ECDSA::ECDSA(EllipticCurve& ec)
{
	this->ec = ec;
	this->generator = this->ec.getGenerator();
	this->subgroupOrder = this->ec.getSubgroupOrder(this->generator);
	this->p = this->ec.getParams()->find('p')->second;
}

EllipticCurve::Point ECDSA::generatePublicKey(__int64 privateKey)
{
	return this->ec.multiply(this->generator, privateKey);
}

std::pair<__int64, __int64>& ECDSA::sign(__int64& hash, __int64 privateKey)
{
	// random between 1 and p - 1
	__int64 random = std::rand();
	__int64 r = this->ec.multiply(this->generator, random).m_x % this->p;
	__int64 s = this->ec.modInverse(random) * (hash + r * privateKey) % this->p;
	return std::pair<__int64, __int64>(r, s);
}

bool ECDSA::validate(__int64& hash, std::pair<__int64, __int64>& signature, EllipticCurve::Point& publicKey)
{
	__int64 u1 = this->ec.modInverse(signature.second) * hash % this->p;
	__int64 u2 = this->ec.modInverse(signature.second) * signature.first % this->p;
	__int64 coordX = this->ec.addiction(this->ec.multiply(this->generator, u1), this->ec.multiply(publicKey, u2)).m_x;
	return coordX % this->p == signature.first;
}

EllipticCurve ECDSA::getEllipticCurve() { return this->ec; }
EllipticCurve::Point ECDSA::getGenerator() { return this->generator; }
__int64 ECDSA::getSubgroupOrder() { return this->subgroupOrder; }