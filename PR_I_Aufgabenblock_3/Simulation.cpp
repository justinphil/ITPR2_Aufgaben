/*
 * Simulation.cpp
 *
 *  Created on: 9 Jan 2025
 *      Author: Justin
 */

#include <stdexcept>
#include <sstream>
#include "Simulation.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

void Simulation::vEinlesen(std::istream& i, bool bMitGrafik) {
	std::string line;
	int lineNumber = 0;

	if(bMitGrafik) {
		if(!bInitialisiereGrafik(1200, 1000)) {
			std::cerr << "Fehler beim verbinden!" << std::endl;
			return;
		}
	}



	while (std::getline(i, line)) {
	        lineNumber++;
	        std::istringstream iss(line);
	        std::string type;
	        iss >> type;
	        try {
	            if (type == "KREUZUNG") {
	                std::string name;
					double tankstelle;

	                iss >> name >> tankstelle;
					if (p_kreuzungen.find(name) != p_kreuzungen.end()) {
	                    throw std::runtime_error("Kreuzung mit dem Namen:  " + name + " existiert bereits!");
	                }

	                 auto kr = std::make_shared<Kreuzung>(name,tankstelle);
	                p_kreuzungen[name] = kr;
					if(bMitGrafik){
						int posX, posY;
						iss >> posX >> posY;
	                    bZeichneKreuzung(posX, posY);
					}


	            } else if (type == "STRASSE") {
	                std::string nameQ, nameZ, nameW1, nameW2;
	                double laenge;
	                int tempolimit;
	                bool ueberholverbot;
	                iss >> nameQ >> nameZ >> nameW1 >> nameW2 >> laenge >> tempolimit >> ueberholverbot;

					auto itQ = p_kreuzungen.find(nameQ);
					if (itQ == p_kreuzungen.end()){
						 throw std::runtime_error("Kreuzung kann nicht gefunden werden: " + nameQ);
					}
	                auto itZ = p_kreuzungen.find(nameZ);
					if (itZ == p_kreuzungen.end()){
						 throw std::runtime_error("Kreuzung kann nicht gefunden werden: " + nameZ);
					}

					std::shared_ptr<Kreuzung>  start = itQ->second;
	                std::shared_ptr<Kreuzung> ziel = itZ->second;

					Tempolimit eTempolimit;
					if(tempolimit == 1) eTempolimit = Tempolimit::Innerorts;
					else if (tempolimit == 2) eTempolimit = Tempolimit::Landstrasse;
					else if (tempolimit == 3) eTempolimit = Tempolimit::Autobahn;
					else {
	                    throw std::runtime_error("Invalides Tempolimit!");
					}

	                Kreuzung::vVerbinde(nameW1, nameW2, laenge, start, ziel, eTempolimit, ueberholverbot);
	                if(bMitGrafik){
	                    int anzKoords;
	                    iss >> anzKoords;
	                    int* coords = new int[anzKoords * 2];
	                    for (int i = 0; i < anzKoords * 2; ++i) {
	                        iss >> coords[i];
	                    }
	                    bZeichneStrasse(nameW1, nameW2, laenge, anzKoords, coords);
	                    delete[] coords;
	                }


	            } else if (type == "PKW") {
	            	std::string name;
	            	double dMaxGeschwindigkeit;
	            	double dVerbrauch;
	            	double dTankinhalt;
	                std::string nameS;
	                double startZeit;

	                iss >> name >> dMaxGeschwindigkeit >> dVerbrauch >> dTankinhalt >> nameS >> startZeit;

	                auto pkw = std::make_unique<PKW>(name, dMaxGeschwindigkeit, dVerbrauch, dTankinhalt);

					auto itS = p_kreuzungen.find(nameS);
					if(itS == p_kreuzungen.end()) {
	                    throw std::runtime_error("Start-Kreuzung kann nicht gefunden werden: " + nameS);
					}


	                itS->second->vAnnahme(std::move(pkw), startZeit);

	            }else if (type == "FAHRRAD") {
	                std::string name;
	                double dMaxGeschwindigkeit;
	                std::string nameS;
	                double startZeit;
	                iss >> name >> dMaxGeschwindigkeit >> nameS >> startZeit;

	                auto fahrrad = std::make_unique<Fahrrad>(name, dMaxGeschwindigkeit);

					auto itS = p_kreuzungen.find(nameS);
					if(itS == p_kreuzungen.end()) {
	                    throw std::runtime_error("Start-Kreuzung kann nicht gefunden werden: " + nameS);
					}

	                itS->second->vAnnahme(std::move(fahrrad), startZeit);


	            } else if(type != "") {
	                throw std::runtime_error("Unbekannter Objekt-Typ: " + type + " in Zeile: " + std::to_string(lineNumber));
	            }


	        } catch (const std::runtime_error& e) {
	            std::cerr << "Fehler in Zeile: " << lineNumber << ": " << e.what() << std::endl;
	             if(bMitGrafik) {
	            	 vBeendeGrafik();
	             }
	            return;
	        }


	    }
	    if(bMitGrafik){
	        vBeendeGrafik();
	    }

	}

void Simulation::vSimulieren() {
	for (double time = 0; time < 10; time += 0.25) {
		for (auto& it : p_kreuzungen) {
			it.second->vSimulieren();
		}
		std::cout << "------------------------------------------------" << std::endl;
	}

}

void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
    for (double time = 0; time < dDauer; time += dZeitschritt) {
        for (auto& it : p_kreuzungen) {
            it.second->vSimulieren();
        }
		std::cout << "------------------------------------------------" << std::endl;
    }
}

std::istream& operator>>(std::istream& i, const Simulation& x) {
	return i;
}

