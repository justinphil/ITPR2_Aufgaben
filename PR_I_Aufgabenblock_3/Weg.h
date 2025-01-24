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
class Kreuzung;

class Weg : public Simulationsobjekt {

public:
	// Konstruktor
	Weg() : Simulationsobjekt(), p_dLaenge(0), p_eTempoLimit(Tempolimit::Autobahn), p_bUeberholverbot(true) {}
	Weg(const std::string& sName, const double dLaenge, const Tempolimit eTempolimit = Tempolimit::Autobahn, const bool bUeberholverbot = true)
		: Simulationsobjekt(sName)
	, p_dLaenge(dLaenge), p_eTempoLimit(eTempolimit)
	, p_bUeberholverbot(bUeberholverbot) {}

	virtual ~Weg() = default;

	// Getter Methoden
	Tempolimit getTempolimit() const { return p_eTempoLimit; }
	double dGetLaenge() const { return p_dLaenge; }
	double dGetVirtuelleSchranke() const { return p_bUeberholverbot ? p_dVirtuelleSchranke : p_dLaenge; }
	std::shared_ptr<Weg> pGetRueckweg() const { return p_pRueckweg.lock(); }
	std::shared_ptr<Kreuzung> pGetKreuzung() const { return p_pZielkreuzung.lock(); }

	// Setter Methoden
	void vSetRueckweg(std::shared_ptr<Weg>& rueckweg) { p_pRueckweg = rueckweg; }
	void vSetKreuzung(std::shared_ptr<Kreuzung>& kreuzung) { p_pZielkreuzung = kreuzung; }
	void vSetVirtuelleSchranke(double dSchranke) { p_dVirtuelleSchranke = dSchranke; }

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

	bool operator==(const Weg& x) const { return getID() == x.getID(); }

private:

	const bool p_bUeberholverbot;
	Tempolimit p_eTempoLimit;

	double p_dLaenge = 0;
	double p_dVirtuelleSchranke = p_dLaenge;

	std::weak_ptr<Weg> p_pRueckweg;
	std::weak_ptr<Kreuzung> p_pZielkreuzung;

	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

};
