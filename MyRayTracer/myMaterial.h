#pragma once

#include "myRGBColor.h"
#include "myShadeRec.h"

class myMaterial
{
public:
	myMaterial() {}

	myMaterial(const myMaterial& rhs) {}

	virtual ~myMaterial() {}

	virtual myRGBColor shade(myShadeRec &sr) { return (0, 0, 0); }

protected:

	myMaterial& operator= (const myMaterial& rhs) {
		if (this == &rhs)
			return *this;
		return *this;
	}
	
};