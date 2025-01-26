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
	virtual ~Streckenende() = default;

	void vBearbeiten() const override {
		std::cout << "Ausnahme Streckenende ist aufgetreten mit Fahrzeug und Weg:" << std::endl;
		std::cout << pFahrzeug << std::endl << pWeg << std::endl << std::endl;

		std::shared_ptr<Weg> naechsterWeg = nullptr;
		auto kreuzung = pWeg.pGetKreuzung();

		if(kreuzung != nullptr) {

			naechsterWeg = kreuzung->pZufaelligerWeg(pWeg);
			kreuzung->vTanken(pFahrzeug);
			naechsterWeg->vAnnahme(pWeg.pAbgabe(pFahrzeug));


			std::cout << "ZEIT     : " << dGlobaleZeit << std::endl
				 << "KREUZUNG : " << pWeg.pGetKreuzung()->getName() << " " << pWeg.pGetKreuzung()->dGetTankstelle() << std::endl
				 << "WECHSEL  : " << pWeg.pGetKreuzung()->getName() << " => " << naechsterWeg->getName() << std::endl
				 << "FAHRZEUG : " << pFahrzeug << std::endl;

		} 	else
		{
			std::cout << "Streckenende ohne Zielkreuzung erreicht! Fahrzeug wird nicht umgesetzt." << std::endl;
		}

	}
};

