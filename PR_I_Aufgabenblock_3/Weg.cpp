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
	p_pFahrzeuge.vAktualisieren();
	p_dVirtuelleSchranke = p_dLaenge;

	// Iteriere über alle Fahrzeuge auf dem Weg
    for (auto& it : p_pFahrzeuge) {

        try {
			// Simuliere das Fahrzeug
        	it->vSimulieren();
        } catch (const Fahrausnahme& ex) {
			// Behandle die Fahrausnahme
			ex.vBearbeiten();
        }
    }

    p_pFahrzeuge.vAktualisieren();
    p_dZeit = dGlobaleZeit;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fz) {
	// Setze die neue Strecke des Fahrzeugs auf den Weg
	fz->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fz));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fz, const double dStartzeitpunkt) {
	// Setze die neue Strecke des Fahrzeugs auf den Weg, mit einem Startzeitpunkt
	fz->vNeueStrecke(*this, dStartzeitpunkt);
	p_pFahrzeuge.push_front(std::move(fz));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fz) {

   auto it = std::find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), [&](const std::unique_ptr<Fahrzeug>& fzg_ptr) {
       return *fzg_ptr == fz;
   });

    if (it == p_pFahrzeuge.end())
   {
       return nullptr;
   }

   auto fahrzeug_ptr = std::move(*it);
   p_pFahrzeuge.erase(it);

   return fahrzeug_ptr;
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
			<< (p_bUeberholverbot ? " Ja " : " Nein ")
			<< std::resetiosflags(std::ios::right) << " ( ";

		for (auto &it : p_pFahrzeuge)
		{
			o << it->getName() << " ";
		}
		o << ")";

	return o;

}
