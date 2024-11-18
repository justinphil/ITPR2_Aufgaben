/*
 * Fahrrad.h
 *
 *  Created on: 20 Oct 2024
 *      Author: Justin
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug {

public:

	Fahrrad();
	Fahrrad(std::string sName, double dMaxgeschwindigkeit);
	virtual ~Fahrrad();

	double dGeschwindigkeit() const;

};

#endif /* FAHRRAD_H_ */
