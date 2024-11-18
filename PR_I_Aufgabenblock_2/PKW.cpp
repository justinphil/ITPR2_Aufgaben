/*
 * PKW.cpp
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>

#include "PKW.h"

double PKW::dGesamtVerbrauch() const {
	return (p_dGesamtStrecke * p_dVerbrauch / 100);
}

double PKW::dTanken(double dMenge) {

	double dMaxTankbar = p_dTankvolumen - p_dTankinhalt;

	// Wenn die Menge nicht -1 ist und kleiner als das Maximum ist, dann füge die Menge hinzu
	if(dMenge != -1.0 && dMenge < dMaxTankbar) {
		// Setze den Tankinhalt auf das Maximum, wenn eine unzulässliche Eingabe erfolgt. Also neg. Zahlen
		p_dTankinhalt += dMenge;
	}
	else {
		// Setze den Tankinhalt auf das Maximum, wenn eine unzulässliche Eingabe erfolgt.
		dMenge = dMaxTankbar;
		p_dTankinhalt = p_dTankvolumen;
	}

	return dMenge;
}

double PKW::dGeschwindigkeit() const {
	// Wenn das Verhalten nicht nullptr ist, dann gib das Geschwindigkeitslimit zurück
	if(p_pVerhalten != nullptr) {
		return std::min<double>((double)p_pVerhalten->eGeschwindigkeitslimit(), p_dMaxGeschwindigkeit);
	}

	return p_dMaxGeschwindigkeit;
}

void PKW::vZeichnen(const Weg& weg) const {
	// Berechne die rel. Position des PKWs auf der Strasse
	double rPos = p_dGesamtStrecke / weg.dGetLaenge();
	bZeichnePKW(p_sName, weg.getName(), rPos, dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vSimulieren() {
	// Wenn der Tankinhalt größer als 0 ist, dann simuliere
	if (p_dTankinhalt > 0)
	{
		// Speichere die Gesamtstrecke in einer temporären Variable
		double dGesamtStreckeTemp = p_dGesamtStrecke;
		
		Fahrzeug::vSimulieren();

		p_dTankinhalt -= (p_dGesamtStrecke - dGesamtStreckeTemp) * p_dVerbrauch / 100;

		// Keine neg. Werte
		if (p_dTankinhalt < 0) p_dTankinhalt = 0;
	}

}



void PKW::vAusgeben() const {
	Fahrzeug::vAusgeben();
	std::cout << std::setprecision(2) << std::fixed
			<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
			<< std::setw(12) << dGesamtVerbrauch()
			<< std::setw(12) << p_dTankinhalt;
}

std::ostream& PKW::vAusgeben(std::ostream& o) const {
	Fahrzeug::vAusgeben(o) << std::setprecision(2) << std::fixed
		<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
		<< std::setw(12) << dGesamtVerbrauch()
		<< std::setw(12) << p_dTankinhalt;

	return o;
}

PKW& PKW::operator=(const PKW& pkw) {
	Fahrzeug::operator=(pkw);
	p_dVerbrauch = pkw.p_dVerbrauch;
	p_dTankvolumen = pkw.p_dTankvolumen;
	p_dTankinhalt = pkw.p_dTankinhalt;
	return *this;
}



