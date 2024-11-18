/*
 * Weg.h
 *
 *  Created on: 11 Nov 2024
 *      Author: Justin
 */

#pragma once

#include <string>
#include <list>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;

class Weg : public Simulationsobjekt {

public:
	Weg() : Simulationsobjekt() {}
	Weg(const std::string sName, const double dLaenge, const Tempolimit eTempolimit = Tempolimit::Autobahn)
		: Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempoLimit(eTempolimit) {}

	virtual ~Weg() = default;

	// Getter Methoden
	Tempolimit getTempolimit() const { return p_eTempoLimit; }
	double dGetLaenge() const { return p_dLaenge; }

	/*
	@brief Simuliert die Fahrzeuge auf dem Weg
	*/
	virtual void vSimulieren();
	/*
	@brief Annahme eines Fahrzeugs auf dem Weg
	@params std::unique_ptr<Fahrzeug> pFz
	*/
	void vAnnahme(std::unique_ptr<Fahrzeug> fz);
	/*
	@brief Annahme eines Fahrzeugs auf dem Weg
	@params std::unique_ptr<Fahrzeug> pFz, const double dStartzeitpunkt
	*/
	void vAnnahme(std::unique_ptr<Fahrzeug> fz, const double dStartzeitpunkt);
	/*
	@brief Abgabe eines Fahrzeugs auf dem Weg
	@params const Fahrzeug& fz
	*/
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fz);

	/*
	 * @brief Zeichnet den Weg
	 */
	void vZeichnen() const;

	// Ausgabe Methoden
	static void vKopf();
	virtual std::ostream& vAusgeben(std::ostream& out) const;
private:

	double p_dLaenge;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempoLimit;
};
