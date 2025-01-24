/*
 * Fahren.cpp
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */
#include <cmath>

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"

double Fahren::dStrecke(Fahrzeug& fz, double dZeitIntervall) const {
	// Strecke bis der Weg endet
	double dStrecke = fz.dGeschwindigkeit() * dZeitIntervall;

	// Wenn die Strecke die das Fahrzeug zuruecklegen wuerde groesser ist als die Strecke bis zum Wegende
	if (fabs(fz.dGetAbschnittstrecke() - p_pWeg.dGetLaenge()) < 1e-6) {
		// Streckenende erreicht
		throw Streckenende(fz, p_pWeg);
	}
	else if (fz.dGetAbschnittstrecke() + dStrecke > p_pWeg.dGetVirtuelleSchranke() - 1e-6) {
		// Fahrzeug darf nicht überholt werden. Oder Wegende
		dStrecke = p_pWeg.dGetVirtuelleSchranke() - fz.dGetAbschnittstrecke();
	}
	else {
		// Fahre die Strecke und setze die Schranke
		p_pWeg.vSetVirtuelleSchranke(fz.dGetAbschnittstrecke() + dStrecke);
	}

	return dStrecke;

}

