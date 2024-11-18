/*
 * Streckenende.h
 *
 *  Created on: 15 Nov 2024
 *      Author: Justin
 */
#pragma once

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
	Streckenende(Fahrzeug& fz,Weg& weg) : Fahrausnahme(fz, weg) {}

	void vBearbeiten() const override {
		std::cout << "Ausnahme Streckenende ist aufgetreten mit Fahrzeug und Weg:" << std::endl;
		std::cout << pFahrzeug << std::endl << pWeg << std::endl << std::endl;

		pWeg.pAbgabe(pFahrzeug);
	}
};

