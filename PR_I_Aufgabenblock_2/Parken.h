/*
 * Parken.h
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */
#pragma once

#include "Verhalten.h"

class Parken : public Verhalten {
public:
	Parken(Weg& pWeg, double dStartZeitpunkt)
		: Verhalten(pWeg), p_dStartZeitpunkt(dStartZeitpunkt) {}
	virtual ~Parken() = default;

	double dStrecke(Fahrzeug& fz, double dZeitIntervall) const override;

private:

	double p_dStartZeitpunkt;
};

