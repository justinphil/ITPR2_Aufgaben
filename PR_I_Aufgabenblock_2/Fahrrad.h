/*
 * Fahrrad.h
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */

#pragma once

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug {

public:

	Fahrrad(): Fahrzeug() {}
	Fahrrad(std::string sName, double dMaxgeschwindigkeit) : Fahrzeug(sName, dMaxgeschwindigkeit) {}
	virtual ~Fahrrad() = default;

	double dGeschwindigkeit() const;

};
