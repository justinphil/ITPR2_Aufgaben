/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 5 Nov 2024
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>

#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt() {
	vInit();
}	

Simulationsobjekt::Simulationsobjekt(const std::string name) {
	vInit();
	p_sName = name;
}

void Simulationsobjekt::vInit() {
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dZeit = 0.0;
}

void Simulationsobjekt::vAusgeben() const
{
	std::cout << std::setprecision(2) << std::fixed // 2 feste Nachkommastellen
		<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(2) << p_iID << " " 
		<< std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setw(10) << p_sName << ": ";

}

std::ostream& Simulationsobjekt::vAusgeben(std::ostream& o) const {
	o << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(2) << p_iID
				<< " " << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setw(10) << p_sName;
		return o;
}

Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& x) {
	vInit();
	p_sName = x.p_sName + "Kopie";
	return *this;
}

bool operator== (const Simulationsobjekt& x, const Simulationsobjekt& y){
		return x.getID() == y.getID();
	}

std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& x){
	return x.vAusgeben(o);
}
