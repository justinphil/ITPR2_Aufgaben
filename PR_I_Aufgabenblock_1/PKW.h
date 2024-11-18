/*
 * PKW.h
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"

class PKW: public Fahrzeug {

public:
	PKW();
	PKW(std::string sName, double dMaxGeschwindigkeit);
	PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);

	virtual ~PKW();

	virtual double dTanken(double dMenge = -1.0);
	double dGesamtVerbrauch() const ;
	virtual void vSimulieren();

	virtual void vAusgeben() const;
	virtual std::ostream& vAusgeben(std::ostream& o) const;
	PKW& operator=(const PKW &pkw);

private:
	// Gibt den Verbrauch in Liter/100KM an
	double p_dVerbrauch;
	// In Liter
	double p_dTankinhalt;
	// In Liter
	double p_dTankvolumen;

};



#endif /* PKW_H_ */
