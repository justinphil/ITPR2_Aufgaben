/*
 * Fahrausnahme.h
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */

#pragma once

#include <string>

#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : public std::exception {
public:
	Fahrausnahme(Fahrzeug& fz, Weg& weg) : pFahrzeug(fz), pWeg(weg) {}
	virtual ~Fahrausnahme() = default;

	// Rein virtuelle Methode
	virtual void vBearbeiten() const = 0;


protected:

	Fahrzeug& pFahrzeug;
	Weg& pWeg;

};

