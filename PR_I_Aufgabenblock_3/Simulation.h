/*
 * Simulation.h
 *
 *  Created on: 9 Jan 2025
 *      Author: Justin
 */

#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <map>
#include "Kreuzung.h"

class Simulation {
public:
	Simulation() = default;
	virtual ~Simulation() = default;

	void vEinlesen(std::istream& i, bool bMitGrafik = false);
	void vSimulieren();
	void vSimulieren(double dDauer, double dZeitschritt);

private:
	std::map<std::string, std::shared_ptr<Kreuzung>> p_kreuzungen;

};

std::istream& operator>>(std::istream& i, const Simulation& x);
