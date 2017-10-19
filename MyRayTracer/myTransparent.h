#pragma once
#include "myPhong.h"
#include "myPerfectSpecular.h"
#include "myPerfectTransmitter.h"

class myTransparent : public myPhong
{
public:
	myTransparent() {}

	myTransparent(myPerfectSpecular* _r, myPerfectTransmitter* s) :
		reflectiveBRDF(_r), speculatBTDF(s) {}

	myTransparent(myPhong *p, myPerfectSpecular* _r, myPerfectTransmitter* s):
		myPhong(*p), reflectiveBRDF(_r), speculatBTDF(s) {}

	virtual ~myTransparent() {}

	virtual myRGBColor
		shade(myShadeRec& sr) override;

private:
	myPerfectSpecular* reflectiveBRDF;
	myPerfectTransmitter* speculatBTDF;
};