/*
 * Fahrrrad.cpp
 *
 *  Created on: 23 Oct 2024
 *      Author: Justin
 */

#include <math.h>

#include "Fahrrad.h"


Fahrrad::Fahrrad()
	: Fahrzeug()
{
}

Fahrrad::Fahrrad(const std::string sName, const double dMaxGeschwindigkeit)
	: Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

Fahrrad::~Fahrrad()
{
}

double Fahrrad::dGeschwindigkeit() const
{

	double dGeschwindigkeit = pow(0.9 , (p_dGesamtStrecke/ 20)) * p_dMaxGeschwindigkeit;

	return ((dGeschwindigkeit >= 12) ? dGeschwindigkeit : 12);

}


