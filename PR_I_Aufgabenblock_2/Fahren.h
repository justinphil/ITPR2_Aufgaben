/*
 * Fahren.h
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */
#pragma once

#include "Verhalten.h"

class Fahren : public Verhalten {
public:
	explicit Fahren(Weg& pWeg) : Verhalten(pWeg) {}
	virtual ~Fahren() = default;

	double dStrecke(Fahrzeug& fz, double dZeitIntervall) const override;

};

