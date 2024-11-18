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

	/*
	@brief Berechnet die Strecke, die ein Fahrzeug in einem Zeitintervall zuruecklegt
	@param fz Fahrzeug, fuer das die Strecke berechnet wird
	@param dZeitIntervall Zeitintervall, in dem die Strecke berechnet wird
	*/
	double dStrecke(Fahrzeug& fz, double dZeitIntervall) const override;

};

