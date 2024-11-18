/*
 * Parken.cpp
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */
#include <cmath>

#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

double Parken::dStrecke(Fahrzeug& fz, double dZeitIntervall) const {
	if (fabs(dGlobaleZeit - p_dStartZeitpunkt) < 1e-6 || dGlobaleZeit > p_dStartZeitpunkt) {
		throw Losfahren(fz, p_pWeg);
    }

    return 0.0; // Parked vehicles do not move
}
