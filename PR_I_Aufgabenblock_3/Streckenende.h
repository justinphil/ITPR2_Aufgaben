/*
 * Streckenende.h
 *
 *  Created on: 15 Nov 2024
 *      Author: Justin
 */
#pragma once

#include "Fahrausnahme.h"
#include "Kreuzung.h"

class Streckenende : public Fahrausnahme {
public:
	Streckenende(Fahrzeug& fz,Weg& weg) : Fahrausnahme(fz, weg) {}

	void vBearbeiten() const override {
		std::cout << "Ausnahme Streckenende ist aufgetreten mit Fahrzeug und Weg:" << std::endl;
		std::cout << pFahrzeug << std::endl << pWeg << std::endl << std::endl;

		std::shared_ptr<Weg> naechsterWeg = nullptr;

		if(pWeg.pGetKreuzung() != nullptr) {
			naechsterWeg = pWeg.pGetKreuzung()->pZufaelligerWeg(pWeg);
			pWeg.pGetKreuzung()->vTanken(pFahrzeug);
			naechsterWeg->vAnnahme(pWeg.pAbgabe(pFahrzeug));

			std::cout << "ZEIT     : " << dGlobaleZeit << std::endl
				 << "KREUZUNG : " << pWeg.pGetKreuzung()->getName() << " " << pWeg.pGetKreuzung()->dGetTankstelle() << std::endl
				 << "WECHSEL  : " << pWeg.pGetKreuzung()->getName() << " => " << naechsterWeg->getName() << std::endl
				 << "FAHRZEUG : " << pFahrzeug << std::endl;

		}

	}
};

