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
	double dStreckeWegende = p_pWeg.dGetLaenge()- fz.dGetAbschnittstrecke();
	// Strecke die das Fahrzeug mit normaler Geschwindigkeit zuruecklegen wuerde
	double dStreckeGeschwindigkeit = fz.dGeschwindigkeit() * dZeitIntervall;
	// Wenn die Strecke die das Fahrzeug zuruecklegen wuerde groesser ist als die Strecke bis zum Wegende
	if (fabs(dStreckeWegende - 0.0) < 1e-6)
	{
		throw Streckenende(fz, p_pWeg); // Streckenende erreicht
	}

	// Minimum der beiden Strecken
	return std::min<double>(dStreckeWegende, dStreckeGeschwindigkeit);

}

