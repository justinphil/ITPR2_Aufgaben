/*
 * Fahrrrad.cpp
 *
 *  Created on: 23 Oct 2024
 *      Author: Justin
 */

#include <math.h>

#include "Fahrrad.h"

double Fahrrad::dGeschwindigkeit() const
{
	double dGeschwindigkeit = pow(0.9 , (int)(p_dGesamtStrecke/ 20)) * p_dMaxGeschwindigkeit;

	return ((dGeschwindigkeit < 12) ? 12 : dGeschwindigkeit);
}



