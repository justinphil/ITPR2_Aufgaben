/*
 * Kreuzung.h
 *
 *  Created on: 27 Nov 2024
 *      Author: Justin
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#pragma once

#include <list>

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"

class Kreuzung: public Simulationsobjekt {
public:
	// Konstruktoren und Destruktor
	Kreuzung() : Simulationsobjekt() , p_dTankstelle(0) {}
	Kreuzung(std::string sName, const double dTankstelle = 0) : Simulationsobjekt(sName), p_dTankstelle(dTankstelle) {}
	virtual ~Kreuzung() = default;

	// Getter Methoden
	double dGetTankstelle() { return p_dTankstelle; }

	// Methoden
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& weg);
	static void vVerbinde(std::shared_ptr<Kreuzung>& startKreuzung, std::shared_ptr<Kreuzung>& zielKreuzung, const std::string& nameHin, const std::string& nameRueck, double laenge,
	         const Tempolimit tempolimit, const bool ueberholverbot);
	void vTanken(Fahrzeug& fz);
	void vAnnahme(std::unique_ptr<Fahrzeug> pFz, double dStartZeit);
	void vSimulieren();
	void vZeichnen() const;

	//void vAusgeben() const;
	std::ostream& vAusgeben(std::ostream& out) const;
	virtual void vEinlesen(std::istream& i);
private:

	std::list<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;
};

#endif /* KREUZUNG_H_ */
