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

	/*
	@brief Berechnet die Strecke, die ein Fahrzeug in einem bestimmten Zeitintervall zurücklegt
	@param fz Referenz auf ein Fahrzeug
	@param dZeitIntervall Zeitintervall, in dem die Strecke berechnet wird
	*/
	double dStrecke(Fahrzeug& fz, double dZeitIntervall) const override;

private:

	double p_dStartZeitpunkt;
};

