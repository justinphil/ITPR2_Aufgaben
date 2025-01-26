/*
 * Kreuzung.cpp
 *
 *  Created on: 27 Nov 2024
 *      Author: Justin
 */

#include <memory>
#include <random>
#include <algorithm>

#include "Kreuzung.h"


std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg) {

	if(p_pWege.empty()){
		return nullptr;
	}

	std::shared_ptr<Weg> neuer_weg = nullptr;

	if (p_pWege.size() == 1)
	{
		return p_pWege.front();
	}

	do
	{
		int iRnd = rand() % p_pWege.size();
		int i = 0;

		for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
		{
			if (i++ >= iRnd)
			{
				neuer_weg = *it;
				break;
			}
		}

	} while (neuer_weg == weg.pGetRueckweg());

	return neuer_weg;
}



void Kreuzung::vSimulieren() {
	for(auto& it : p_pWege) {

		if(it) {
			it->vSimulieren();
		}

	}
}

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung>& startKreuzung, std::shared_ptr<Kreuzung>& zielKreuzung, const std::string& nameHin, const std::string& nameRueck, double laenge,
        const Tempolimit tempolimit, const bool ueberholverbot) {


	std::shared_ptr<Weg> wegHin = std::make_shared<Weg>(nameHin, laenge,  tempolimit, ueberholverbot);
	std::shared_ptr<Weg> wegRueck = std::make_shared<Weg>(nameRueck, laenge, tempolimit, ueberholverbot);

	// Verbinde Wege mit Kreuzungen
	wegHin->vSetRueckweg(wegRueck);
	wegHin->vSetKreuzung(zielKreuzung);

	wegRueck->vSetRueckweg(wegHin);
	wegRueck->vSetKreuzung(startKreuzung);


	// Füge Wege den Kreuzungen hinzu
	startKreuzung->p_pWege.push_back(wegHin);
	zielKreuzung->p_pWege.push_back(wegRueck);

	std::cout << "Verbindung " << nameHin << " und " << nameRueck << " zwischen " << startKreuzung->getName() << " und " << zielKreuzung->getName() << " erstellt." << std::endl;
}

void Kreuzung::vTanken(Fahrzeug& fz) {
	if(p_dTankstelle > 0) {
		// Die Menge des Tankens wird abgezogen
		const double dMenge = fz.dTanken();
		p_dTankstelle -= dMenge;

		// Falls der Wert beim Tanken unter Null fällt, so wird dieser auf 0 gesetzt
		if(p_dTankstelle < 0) {
			p_dTankstelle = 0;
		}
	}
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFz, double dStartZeit) {
	//std::cout << *pFz << " ist angenommen! olaf " << std::endl;

	if (p_pWege.empty()) {
		return;
	}

	std::shared_ptr<Weg> weg = p_pWege.front();

	//std::cout << *pFz << " ist angenommen!" << std::endl;

	this->vTanken(*pFz);

	if(weg) {
		std::cout << *weg << std::endl;
		weg->vAnnahme(std::move(pFz), dStartZeit);
	}

}

void Kreuzung::vZeichnen() const {
	for(auto& it : p_pWege) {
		it->vZeichnen();
	}
}

std::ostream& Kreuzung::vAusgeben(std::ostream& out) const {
	Simulationsobjekt::vAusgeben(out)
	<< "Tankstelle Volumen: " << p_dTankstelle << " Liter" << std::endl;
	for (const auto& weg : p_pWege) {
		weg->vAusgeben(out) << std::endl;
	}
	out << std::endl;
	return out;
}

void Kreuzung::vEinlesen(std::istream& i) {
    Simulationsobjekt::vEinlesen(i);
    i >> p_dTankstelle;
}
