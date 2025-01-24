/*
 * Verhalten.h
 *
 *  Created on: 11 Nov 2024
 *      Author: Justin
 */

#pragma once

#include "Weg.h"

//class Fahrzeug;
//class Weg;

class Verhalten {

public:
	Verhalten(Weg& pWeg) : p_pWeg(pWeg) {}
	virtual ~Verhalten() = default;

	const Weg& getWeg() const { return p_pWeg; }

	virtual double dStrecke (Fahrzeug& fz, double dZeitIntervall) const = 0;

	Tempolimit eGeschwindigkeitslimit() { return p_pWeg.getTempolimit(); }

protected:
	Weg& p_pWeg;
};
