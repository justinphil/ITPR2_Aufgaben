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

	if(dMenge != -1.0 && dMenge < dMaxTankbar) {
		// Setze den Tankinhalt auf das Maximum, wenn eine unzulässliche Eingabe erfolgt. Also neg. Zahlen
		p_dTankinhalt += dMenge;
	}
	else {
		dMenge = dMaxTankbar;
		p_dTankinhalt = p_dTankvolumen;
	}

	return dMenge;
}

double PKW::dGeschwindigkeit() const {
	if(p_pVerhalten != nullptr) {
		return std::min<double>((double)p_pVerhalten->eGeschwindigkeitslimit(), p_dMaxGeschwindigkeit);
	}

	return p_dMaxGeschwindigkeit;
}

void PKW::vZeichnen(const Weg& weg) const {
	double rPos = p_dGesamtStrecke / weg.dGetLaenge();
	bZeichnePKW(p_sName, weg.getName(), rPos, dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vSimulieren() {

	if (p_dTankinhalt > 0)
	{
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



