/*
 * PKW.h
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */
#pragma once

#include "Fahrzeug.h"

class PKW: public Fahrzeug {

public:
	PKW() : Fahrzeug() { }
	PKW(const std::string sName, const double dMaxGeschwindigkeit)
		: Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(5), p_dTankinhalt(55), p_dTankvolumen(55) {}
	PKW(const std::string sName, const double dMaxGeschwindigkeit, const double dVerbrauch, const double dTankvolumen = 55) 
		: Fahrzeug(sName, dMaxGeschwindigkeit)
		, p_dVerbrauch(dVerbrauch),
		p_dTankinhalt(dTankvolumen / 2), p_dTankvolumen(dTankvolumen) { }

	virtual ~PKW() = default;

	double dGeschwindigkeit() const;
	double dGesamtVerbrauch() const;
	virtual double dTanken(double dMenge = -1.0);

	virtual void vSimulieren();
	void vZeichnen(const Weg& weg) const;

	void vAusgeben() const;
	std::ostream& vAusgeben(std::ostream& o) const;
	
	PKW& operator=(const PKW &pkw);

private:
	// Gibt den Verbrauch in Liter/100KM an
	double p_dVerbrauch;
	// In Liter
	double p_dTankinhalt;
	// In Liter
	double p_dTankvolumen;

};
