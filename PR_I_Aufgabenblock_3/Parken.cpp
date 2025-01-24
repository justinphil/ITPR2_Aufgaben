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
  // Wenn die globale Zeit gleich dem Startzeitpunkt ist oder die globale Zeit größer als der Startzeitpunkt ist
	if (fabs(dGlobaleZeit - p_dStartZeitpunkt) < 1e-6 || dGlobaleZeit > p_dStartZeitpunkt) {
		throw Losfahren(fz, p_pWeg);
  }

    return 0.0; // Geparkte Fahrzeuge legen keine Strecke zurück
}
