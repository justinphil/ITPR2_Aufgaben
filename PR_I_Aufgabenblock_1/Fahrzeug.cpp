/*
 * Fahrzeug.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */

#include "Fahrzeug.h"

#include <iostream>
#include <iomanip>

int Fahrzeug::p_iMaxID = 0;
double dGlobaleZeit = 0.0;

Fahrzeug::Fahrzeug() {
	vInit();

	std::cout << "Das Fahrzeug: " << p_iID << " ohne Namen wurde erstellt!" << std::endl;
}

Fahrzeug::Fahrzeug(std::string sName) {
	vInit();
	p_sName = sName;

	std::cout << "Das Fahrzeug: " << p_iID << " mit dem Namen " << p_sName << " wurde erstellt!" << std::endl;
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit) {
	vInit();
	p_sName = sName;
	p_dMaxGeschwindigkeit = (dMaxGeschwindigkeit >= 0) ? dMaxGeschwindigkeit : 0;

}

Fahrzeug::~Fahrzeug() {

	std::cout << "Das Fahrzeug: " << p_iID << " mit dem Namen " << p_sName << " wurde geloescht!" << std::endl;
}

void Fahrzeug::vInit() {
	p_iID = p_iMaxID++;
	p_sName == "";


	p_dMaxGeschwindigkeit = 0;
}

double Fahrzeug::dGeschwindigkeit () const {

	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
}

void Fahrzeug::vSimulieren() {


	//if (p_dZeit - dGlobaleZeit < 1e-10) return;

	p_dGesamtZeit += dGlobaleZeit - p_dZeit;

	p_dGesamtStrecke += (dGlobaleZeit - p_dZeit) * dGeschwindigkeit();

	p_dZeit = dGlobaleZeit;

}

void Fahrzeug::vAusgeben() const {
	std::cout << std::fixed << std::setprecision(2)
			<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(2) << p_iID
			<< std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setw(10) << p_sName
			<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(6) << p_dMaxGeschwindigkeit
			<< std::setw(16) << dGeschwindigkeit()
			<< std::setw(16) << p_dGesamtStrecke;
			// << std::endl;
}

std::ostream& Fahrzeug::vAusgeben(std::ostream& o) const {
	o << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(2) << p_iID
		<< std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setw(10) << p_sName
		<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(6) << p_dMaxGeschwindigkeit
		<< std::setw(16) << dGeschwindigkeit()
		<< std::setw(16) << p_dGesamtStrecke;
	return o;
}

void Fahrzeug::vKopf() {
	std::cout << std::fixed << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)  << "ID "
			<< std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << " Name "
			<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << " Max Geschw. "
			" Geschwindigkeit " " Gesamtstrecke " " GesamtVerbrauch " " Tankinhalt " << std::endl;

	std::cout << "------------------------------------------------------------------------------" << std::endl;
}



Fahrzeug& Fahrzeug::operator =(const Fahrzeug &fz) {
	vInit();
	p_sName = fz.p_sName + " (Kopie)";
	p_dMaxGeschwindigkeit = fz.p_dMaxGeschwindigkeit;
	return *this;
}

bool Fahrzeug::operator <(Fahrzeug &fz) const {
	return (this->p_dGesamtStrecke < fz.p_dGesamtStrecke);
}

std::ostream& operator<<(std::ostream& o, const Fahrzeug& fz) {

	return fz.vAusgeben(o);
}







