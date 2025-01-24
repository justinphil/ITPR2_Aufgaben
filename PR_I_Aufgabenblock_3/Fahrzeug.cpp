/*
 * Fahrzeug.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"
#include "Losfahren.h"
#include "Streckenende.h"

Fahrzeug::Fahrzeug() : Simulationsobjekt() {
	vInit();

	std::cout << "Das Fahrzeug: " << p_iID << " ohne Namen wurde erstellt!" << std::endl;
}

Fahrzeug::Fahrzeug(std::string sName)
	: Simulationsobjekt(sName){
	vInit();

	std::cout << "Das Fahrzeug: " << p_iID << " mit dem Namen " << p_sName << " wurde erstellt!" << std::endl;
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit)
	: Simulationsobjekt(sName){
	vInit();

	p_dMaxGeschwindigkeit = (dMaxGeschwindigkeit >= 0) ? dMaxGeschwindigkeit : 0;

}

Fahrzeug::~Fahrzeug() {

	delete p_pVerhalten.get();

	//std::cout << "Das Fahrzeug: " << p_iID << " mit dem Namen " << p_sName << " wurde geloescht!" << std::endl;
}

void Fahrzeug::vInit() {

	p_dAbschnittStrecke = 0;
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dGesamtZeit = 0;
	p_pVerhalten = nullptr;
}

double Fahrzeug::dGeschwindigkeit () const {

	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dGetAbschnittstrecke() const {
	return p_dAbschnittStrecke;
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
	delete p_pVerhalten.get(); //  Memory Leak vermeiden

	p_pVerhalten = std::make_shared<Fahren>(weg);
	p_dAbschnittStrecke = 0.0;

}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeitpunkt) {
	delete p_pVerhalten.get(); //  Memory Leak vermeiden

	p_pVerhalten = std::make_shared<Parken>(weg, dStartzeitpunkt);
	p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vSimulieren() {
	// Prüfen ob ein Verhalten vorhanden ist
    if (!p_pVerhalten) return;

	// Prüfen ob die GlobaleZeit gleich der Zeit des Fahrzeugs ist
    if(fabs(dGlobaleZeit - p_dZeit) < 1e-6) return;

	double dZeitIntervall = dGlobaleZeit - p_dZeit;
	p_dGesamtZeit += dZeitIntervall;
	p_dZeit = dGlobaleZeit;

	// Berechnen der Strecke die das Fahrzeug zurücklegt
    double dStrecke = p_pVerhalten->dStrecke(*this, dZeitIntervall);
    p_dAbschnittStrecke += dStrecke;
    p_dGesamtStrecke += dStrecke;
    
}

void Fahrzeug::vZeichnen(const Weg& weg) const
{
	double dRelPos = p_dAbschnittStrecke / weg.dGetLaenge();

	if (dRelPos < 0) dRelPos = 0;
	if (dRelPos > 1) dRelPos = 1;

	bZeichneFahrrad(p_sName, weg.getName(), dRelPos, dGeschwindigkeit());
}


void Fahrzeug::vAusgeben() const {

	Simulationsobjekt::vAusgeben();

	std::cout
	<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(8) << p_dMaxGeschwindigkeit
		<< std::setw(16) << dGeschwindigkeit()
		<< std::setw(16) << p_dGesamtStrecke
		<< std::setw(12) << p_dAbschnittStrecke
		<< std::endl;

}

std::ostream& Fahrzeug::vAusgeben(std::ostream& o) const {
	Simulationsobjekt::vAusgeben(o)
		<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::setw(8) << p_dMaxGeschwindigkeit
		<< std::setw(16) << dGeschwindigkeit()
		<< std::setw(16) << p_dGesamtStrecke
		<< std::setw(12) << p_dAbschnittStrecke
		<< std::endl;
	return o;
}

void Fahrzeug::vKopf() {
	std::cout << std::fixed << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)  << "ID "
			<< std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << " Name "
			<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << " Max Geschw. "
			" Geschwindigkeit " " Gesamtstrecke " " GesamtVerbrauch " " Tankinhalt " << std::endl;

	std::cout << std::string(60, '-') << std::endl;
}

void Fahrzeug::vEinlesen(std::istream& i) {
	Simulationsobjekt::vEinlesen(i);
	i >> p_dMaxGeschwindigkeit;
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



