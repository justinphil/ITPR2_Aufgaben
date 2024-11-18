/*
 * Weg.cpp
 *
 *  Created on: 11 Nov 2024
 *      Author: Justin
 */



#include <iomanip>
#include <iostream>
#include <algorithm>

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"


void Weg::vSimulieren() {
	// Iteriere über alle Fahrzeuge auf dem Weg
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {

        try {
			// Simuliere das Fahrzeug
        	(*it)->vSimulieren();
        } catch (const Fahrausnahme& ex) {
			// Behandle die Fahrausnahme
			ex.vBearbeiten();
        }
    }

    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fz) {
	// Setze die neue Strecke des Fahrzeugs auf den Weg
	fz->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fz));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fz, const double dStartzeitpunkt) {
	// Setze die neue Strecke des Fahrzeugs auf den Weg, mit einem Startzeitpunkt
	fz->vNeueStrecke(*this, dStartzeitpunkt);
	p_pFahrzeuge.push_back(std::move(fz));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fz) {
	// Iteriere über alle Fahrzeuge auf dem Weg
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
		// Ob der Zeiger nicht null ist und der dereferenzierte Zeiger mit dem gegebenen Fahrzeug übereinstimmt
        if (*it && **it == fz) {
            std::unique_ptr<Fahrzeug> ptr = std::move(*it);
            p_pFahrzeuge.erase(it);
            return ptr;
        }
    }
    return nullptr; // Wenn Fahrzeug nicht gefunden wurde
}

void Weg::vZeichnen() const {
	// Iteriere über alle Fahrzeuge auf dem Weg und zeichne sie
	for (auto& it : p_pFahrzeuge) {
			it->vZeichnen(*this);
	    }
}

void Weg::vKopf() {
	std::cout << "ID | Name         | Laenge | Fahrzeuge          " << std::endl
			  << "------------------------------------------------"
			<< std::endl;

}

std::ostream& Weg::vAusgeben(std::ostream& o) const {

	Simulationsobjekt::vAusgeben(o)
			<< std::setprecision(2) << std::fixed << std::resetiosflags(std::ios::left)
			<< std::setiosflags(std::ios::right) << std::setw(12) << Weg::p_dLaenge
			<< std::resetiosflags(std::ios::right) << " ( ";



		for (auto &it : p_pFahrzeuge)
		{
			o << it->getName() << " ";
		}
		o << ")";

	return o;

}
