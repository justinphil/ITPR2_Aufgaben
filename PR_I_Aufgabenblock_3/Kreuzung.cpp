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

	// Zufällige Auswahl eines Weges
	std::vector<std::shared_ptr<Weg>> auswahl;
	for (auto& w : p_pWege) {
		auswahl.push_back(w);
	}

	if (auswahl.empty()) {
		// Sackgasse: zurück auf den alten Weg
		for (auto& w : p_pWege) {
			if (*w == weg) {
				return w;
			}
		}
		return nullptr;
	}

	// Zufallsgenerator
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(0, auswahl.size() - 1);
	int zufallsIndex = dist(device);
	return auswahl[zufallsIndex];
}


void Kreuzung::vSimulieren() {
	for(auto& it : p_pWege) {

		if(it) {
			it->vSimulieren();
		}

	}
}

void Kreuzung::vVerbinde(const std::string& nameHin, const std::string& nameRueck, double laenge,
        std::shared_ptr<Kreuzung>& startKreuzung, std::shared_ptr<Kreuzung>& zielKreuzung, const Tempolimit tempolimit, const bool ueberholverbot) {


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

	std::cout << "Verbindung " << nameHin << " und " << nameRueck << " zwischen " << startKreuzung->getID() << " und " << zielKreuzung->getName() << " erstellt." << std::endl;
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
	if (p_dTankstelle > 0.0) {
        pFz->dTanken();
	}
	if (!p_pWege.empty()) {
		return;
	}

	std::shared_ptr<Weg> weg = p_pWege.front();

	if (dStartZeit < 0.0) {

		if (weg) {
			weg->vAnnahme(std::move(pFz));
		}

	} else {

		if(weg) {
			weg->vAnnahme(std::move(pFz), dStartZeit);
		}

	}

}

void Kreuzung::vZeichnen() const {
	for(auto& it : p_pWege) {
		it->vZeichnen();
	}
}

std::ostream& Kreuzung::vAusgeben(std::ostream& out) const {
	Simulationsobjekt::vAusgeben(out);
	std::cout << "Tankstelle Volumen: " << p_dTankstelle << " Liter" << std::endl;
	for (const auto& weg : p_pWege) {
		weg->vAusgeben(out);
	}

	return out;
}

void Kreuzung::vEinlesen(std::istream& i) {
    Simulationsobjekt::vEinlesen(i);
    i >> p_dTankstelle;
}
