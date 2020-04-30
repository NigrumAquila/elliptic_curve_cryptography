#include "ECDH.h"

ECDH::ECDH(EllipticCurve& ec)
{
	this->ec = ec;
	this->generator = this->ec.getGenerator();
	this->subgroupOrder = this->ec.getSubgroupOrder(this->generator);
}

EllipticCurve::Point ECDH::generatePublicKey(__int64 privateKey)
{
	return this->ec.multiply(this->generator, privateKey);
}

EllipticCurve::Point ECDH::generateSharedSecret(EllipticCurve::Point& publicKey, __int64 privateKey)
{
		return this->ec.multiply(publicKey, privateKey);
}

EllipticCurve ECDH::getEllipticCurve() { return this->ec; }
EllipticCurve::Point ECDH::getGenerator() { return this->generator; }
__int64 ECDH::getSubgroupOrder() { return this->subgroupOrder; }