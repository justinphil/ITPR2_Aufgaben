/*
 * main.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

using namespace std;
double dEpsilon = 0.001;


void vAufgabe_1() {

	vector<unique_ptr<Fahrzeug>> vUniqueFahrzeugVector = {};
	vector<shared_ptr<Fahrzeug>> vSharedFahrzeugVector = {};

	Fahrzeug fz1("LAMBORGHINI R8");

	Fahrzeug *fz2 = new Fahrzeug("LADA SAMRA");
	Fahrzeug *fz3 = new Fahrzeug("MCLARRY SENNA");

	unique_ptr<Fahrzeug> fz4 = make_unique<Fahrzeug>("FERRARI F40");
	unique_ptr<Fahrzeug> fz5 = make_unique<Fahrzeug>("PEEL P50");

	shared_ptr<Fahrzeug> fz6 = make_shared<Fahrzeug>("MISHIBISHI ECLIPSE");
	shared_ptr<Fahrzeug> fz7 = make_shared<Fahrzeug>("FIAT MULTIPLA");

	std::cout << "Vor der Zuweisung" << fz6.use_count() << std::endl;

	shared_ptr<Fahrzeug> funny = fz6;
	// unique_ptr<Fahrzeug> funny2 = fz5;

	std::cout << "Vor der Zuweisung" << fz6.use_count() << std::endl;
	// std::cout << "Vor der Zuweisung" << fz5.use_count() << std::endl;

	// Hinzufuegen der Fahrzeuge in den Vector und danach das loeschen

	// vUniqueFahrzeugVector.push_back(fz4);
	// vUniqueFahrzeugVector.push_back(fz5);

	vUniqueFahrzeugVector.clear();

	/*	Hinzufuegen der Fahrzeuge in den Vector einmal mit push_back und dann einmal mit
	* 	std::move
	*/
	vSharedFahrzeugVector.push_back(fz6);
	vSharedFahrzeugVector.push_back(std::move(fz7));


	// Iteriert durch den Vector und gibt die Referenzen aus
	for (auto& it : vSharedFahrzeugVector) {
		std::cout << it.use_count() <<std::endl;
	}


	//Destruktoren
	fz2->~Fahrzeug();
	fz3->~Fahrzeug();



}

void vAufgabe_1a() {
	vector<unique_ptr<Fahrzeug>> vFahrzeugListe;
	std::string sEingabeName;
	double dEingabeMaxGeschwindigkeit;


	for(int i = 0; i < 3;  i++) {

		std::cout << "Geben Sie den Namen des Fahrzeugs ein: " << std::endl;
		std::cin >> sEingabeName;

		std::cout << "Geben Sie die maximale Geschwindigkeit des Fahrzeugs ein: " << std::endl;
		std::cin >> dEingabeMaxGeschwindigkeit;

		unique_ptr<Fahrzeug> car = make_unique<Fahrzeug>(sEingabeName, dEingabeMaxGeschwindigkeit);
		vFahrzeugListe.push_back(std::move(car));
	}


	Fahrzeug::vKopf();

	for(; dGlobaleZeit < 5; dGlobaleZeit += 0.25) {

		for (auto &it : vFahrzeugListe){
			it->vSimulieren();
			it->vAusgeben();
		}

	}


}

void vAufgabe_2() {

	vector<unique_ptr<Fahrzeug>> vFahrzeuge;

	int iEingabePKW = 0;
	int iEingabeFahrrads = 0;

	std::cout << "Wie viele PKW's sollen erzeugt werden?" << std::endl;
	std::cin >> iEingabePKW;
	std::cout << "Wie viele Fahrräder sollen erzeugt werden?" << std::endl;
	std::cin >> iEingabeFahrrads;

	for(int i = 0; i < iEingabePKW; i++) {

		unique_ptr<PKW> nPKW = make_unique<PKW>("PKW " + std::to_string(i), 60, 5);
		vFahrzeuge.push_back(std::move(nPKW));
	}

	for (int i = 0; i < iEingabeFahrrads; i++) {

		unique_ptr<Fahrrad> nFahrrad = make_unique<Fahrrad>("Fahrrad " + std::to_string(i), 30);
		vFahrzeuge.push_back(std::move(nFahrrad));

	}

	bool bGetankt = false;
	Fahrzeug::vKopf();

	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 1)
		{
			//for (auto &it : vFahrzeuge)

			for(auto it = vFahrzeuge.begin(); it != vFahrzeuge.end(); it++)
			{
				//PKW* pPKW = dynamic_cast<PKW*>(it.get());

				if (fabs(dGlobaleZeit) > 3.0 && !bGetankt )
				{
					bGetankt = (*it)->dTanken(); // Autos nachtanken
				}

				(*it)->vSimulieren();
				(*it)->vAusgeben();
				std::cout << std::endl;
			}


			std::cout << "--------------------------------------------------------------------------" << std::endl;
		}

}

void vAufgabe_3() {
	PKW car("Subaru WRX STI", 255, 5);
	Fahrrad fahrrad("Canyon", 24);
	Fahrzeug panzer("Panther", 15);

	// Simulation

	dGlobaleZeit += 2.5;
	car.vSimulieren();
	fahrrad.vSimulieren();
	panzer.vSimulieren();

	// Ausgabe mittels << operator
	Fahrzeug::vKopf();
	std::cout << car << std::endl << fahrrad << std::endl << panzer << std::endl << std::endl;

	// < operator
	if (fahrrad < panzer) {
		cout << "Der Panzer ist bereits weiter gefahren." << endl << endl;
	} else {
		cout << "Das Fahrrad ist bereits weiter gefahren." << endl << endl;
	}

	// = operator und Copy Konstruktor
	PKW carcopy1;
	// PKW carcopy2 = car;
	carcopy1 = car;

	// Zweite Ausgabe nach dem kopieren
	Fahrzeug::vKopf();
	std::cout << carcopy1 << std::endl;

}

void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 3.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}

void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{15};
    double dTakt = 0.3;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}


int main () {

	vAufgabe_AB1();


	return 0;
}
