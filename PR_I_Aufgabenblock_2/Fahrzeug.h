/*
 * Fahrzeug.h
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */
#pragma once

#include <string>
#include <memory>

#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include "Simuclient.h"

class Weg;
// class Verhalten;

extern double dGlobaleZeit;

class Fahrzeug : public Simulationsobjekt {
public:

	// Konstruktoren
	Fahrzeug();
	Fahrzeug(const Fahrzeug &fz) = delete; // Kopierkonstruktor
	Fahrzeug(const std::string sName);
	Fahrzeug(const std::string sName, const double dMaxGeschwindigkeit);

	// Destruktor
	virtual ~Fahrzeug();

	// Getter Methoden
	double dGetAbschnittstrecke() const;
	virtual double dGeschwindigkeit() const;


	// Restliches
	/*
	@brief: Simuliert das Fahrzeug
	*/
	virtual void vSimulieren();
	/*
	@brief: Gibt die Tankfüllung des Fahrzeugs zurück 
	*/
	virtual double dTanken(double dMenge = -1.0) const;
	/*
	@description: Setzt das Verhalten des Fahrzeugs auf Fahren
	@params: Weg& pWeg
	@return: void
	*/
	void vNeueStrecke(Weg& pWeg);
	/*
	@brief: Setzt das Verhalten des Fahrzeugs auf Parken
	@params: Weg& pWeg, double dStartzeitpunkt
	@return: void
	*/
	void vNeueStrecke(Weg& pWeg, double dStartzeitpunkt);
	
	/*
	 @brief Zeichnet das Fahrzeug.
	 *
	 */
	virtual void vZeichnen(const Weg& weg) const;

	// Ausgabe Methoden
	static void vKopf();
	virtual void vAusgeben() const;
	virtual std::ostream& vAusgeben(std::ostream& o) const;
	
	// Operator overloading
	bool operator<(Fahrzeug &fz) const;
	Fahrzeug& operator=(const Fahrzeug &fz);


protected:
	// Attribute
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dAbschnittStrecke;

	std::shared_ptr<Verhalten> p_pVerhalten;

private:
	void vInit();
};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& fz);
