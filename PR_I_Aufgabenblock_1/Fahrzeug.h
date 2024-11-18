/*
 * Fahrzeug.h
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>

extern double dGlobaleZeit;

class Fahrzeug {
public:

	Fahrzeug();
	Fahrzeug(const Fahrzeug &fz) = delete; // Kopierkonstruktor
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschwindigkeit);

	virtual ~Fahrzeug();

	virtual double dGeschwindigkeit() const;
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = -1.0);

	virtual void vAusgeben() const;
	virtual std::ostream& vAusgeben(std::ostream& o) const;

	bool operator<(Fahrzeug &fz) const;
	Fahrzeug &operator=(const Fahrzeug &fz);
	static void vKopf();

protected:
	int p_iID;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit = 0;
	double p_dZeit = 0;
	std::string p_sName;

private:
	static int p_iMaxID;
	void vInit();
};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& x);


#endif /* FAHRZEUG_H_ */
