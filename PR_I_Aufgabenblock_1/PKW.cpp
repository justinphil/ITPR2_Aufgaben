/*
 * PKW.cpp
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>

#include "PKW.h"


PKW::PKW() : Fahrzeug() { } // @suppress("Class members should be properly initialized")

PKW::PKW(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit) {} // @suppress("Class members should be properly initialized")

PKW::PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) : Fahrzeug(sName, dMaxGeschwindigkeit)
		, p_dVerbrauch(dVerbrauch),
		p_dTankinhalt(dTankvolumen / 2), p_dTankvolumen(dTankvolumen) { }

PKW::~PKW() {}

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

void PKW::vSimulieren() {

	double dGesamtStreckeTemp = p_dGesamtStrecke;

	if (p_dTankinhalt > 0) {

		Fahrzeug::vSimulieren();

		p_dTankinhalt -= (p_dGesamtStrecke - dGesamtStreckeTemp) * p_dVerbrauch / 100;

		if (p_dTankinhalt < 0) p_dTankinhalt = 0;

	}

}

double PKW::dGesamtVerbrauch() const {
	return (p_dGesamtStrecke * p_dVerbrauch / 100);
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
		<< std::setw(12) << p_dTankinhalt<< std::endl;

	return o;
}

PKW& PKW::operator=(const PKW& pkw) {
	Fahrzeug::operator=(pkw);
	p_dVerbrauch = pkw.p_dVerbrauch;
	p_dTankvolumen = pkw.p_dTankvolumen;
	p_dTankinhalt = pkw.p_dTankinhalt;
	return *this;
}


