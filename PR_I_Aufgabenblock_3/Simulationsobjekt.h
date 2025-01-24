/*
 * Simulationsobjekt.h
 *
 *  Created on: 5 Nov 2024
 *      Author: Justin
 */

#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class Simulationsobjekt {

public:
	Simulationsobjekt();
	Simulationsobjekt(const std::string name);
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	virtual ~Simulationsobjekt() = default;

	std::string getName() const { return p_sName; }
	int getID() const { return p_iID; }

	// Rein virtuelle Methode
	virtual void vSimulieren() = 0;

	// Ausgabe Methoden
	virtual void vAusgeben() const;
	virtual std::ostream& vAusgeben(std::ostream& out) const;

	virtual void vEinlesen(std::istream& i);

	// Operator Overloading
	Simulationsobjekt& operator=(const Simulationsobjekt& x);

protected:

	std::string p_sName;
	int p_iID;
	double p_dZeit;

private:

	static int p_iMaxID;
	void vInit();
};

std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& x);
std::istream& operator>>(std::istream& i, Simulationsobjekt& x);
bool operator== (const Simulationsobjekt& x, const Simulationsobjekt& y);

