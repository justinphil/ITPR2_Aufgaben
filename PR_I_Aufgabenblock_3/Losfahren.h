/*
 * Losfahren.h
 *
 *  Created on: 14 Nov 2024
 *      Author: Justin
 */

#pragma once

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
	Losfahren(Fahrzeug& fz, Weg& weg) : Fahrausnahme(fz, weg) {}
	~Losfahren() = default; 

	/*
	@brief: Bearbeitet die Fahrausnahme
	@return: void
	*/
	void vBearbeiten() const override {
		std::cout << "Fahrausnahme: Losfahren Mit Fahrzeug und Weg:" << std::endl;
		std::cout << pFahrzeug << std::endl << pWeg << std::endl << std::endl;

		auto fz_ptr = pWeg.pAbgabe(pFahrzeug);

		std::cout << fz_ptr->getName() << " wurde abgegeben!" << std::endl;
		if(fz_ptr) {
			pWeg.vAnnahme(std::move(fz_ptr));
		} else {
			std::cerr << "Fehler: Fahrzeug konnte nicht entfernt werden!" << std::endl;
		}
	}

};


