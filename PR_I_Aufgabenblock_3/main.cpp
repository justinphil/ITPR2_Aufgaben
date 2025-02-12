/*
 * main.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Justin
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Simulation.h"

using namespace std;
double dEpsilon = 0.001;
double dGlobaleZeit = 0.0;

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
	//PKW carcopy1(car);
	PKW carcopy2;
	carcopy2 = car;

	// Zweite Ausgabe nach dem kopieren
	Fahrzeug::vKopf();
	std::cout << carcopy2 << std::endl;

}

void vAufgabe_4() {

	Weg road("Ahornstr", 50, Tempolimit::Innerorts);

	Weg::vKopf();

	std::cout << road << std::endl;


}

void vAufgabe_5() {



    Weg weg1("Autobahn", 500.0, Tempolimit::Autobahn);

	auto f1 = std::make_unique<PKW>("BMW", 100.0, 9.5, 650);
	auto f2 = std::make_unique<PKW>("Audi", 120.0, 12.5, 700);

    weg1.vAnnahme(std::move(f1));
    weg1.vAnnahme(std::move(f2), 3.0);

    for (dGlobaleZeit = 0; dGlobaleZeit < 5; dGlobaleZeit += 0.3)
	{
		std::cout << dGlobaleZeit << std::endl << std::endl;
        weg1.vSimulieren();
    }
}


void vAufgabe_6() {

	Weg::vKopf();

	Weg weg1("Autobahn", 500, Tempolimit::Autobahn);
	Weg weg2("Landstr", 500, Tempolimit::Landstrasse);

	auto f1 = std::make_unique<PKW>("BMW", 120.0, 9.5, 650);
	auto f2 = std::make_unique<PKW>("Audi", 100.0, 12.5, 700);
	auto bike = std::make_unique<Fahrrad>("BMX", 15.0);

	weg1.vAnnahme(std::move(f1));
	weg2.vAnnahme(std::move(f2), 2.0);
	weg2.vAnnahme(std::move(bike));

	if(!bInitialisiereGrafik(800, 600))
	{
		std::cout << "Fehler beim Starten des Simulationsservers." << std::endl;
	}

	int iCoords[] = { 100, 200, 700, 400 };
	bZeichneStrasse(weg1.getName(), weg2.getName(), 500, 2, iCoords);

	Fahrzeug::vKopf();
	for (dGlobaleZeit = 0.0; dGlobaleZeit <= 10; dGlobaleZeit += 0.25)
	{
		weg1.vSimulieren();
		weg2.vSimulieren();

		vSetzeZeit(dGlobaleZeit);

		weg1.vZeichnen();
		weg2.vZeichnen();

		//std::cout << *f1 << std::endl << *f2 << std::endl << *bike << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

		vSleep(300);
	}

	vBeendeGrafik();

}

void vAufgabe_6a() {
    vertagt::VListe<int> vListe;

    // Zufallszahlen generieren
    std::mt19937 generator(0);
    std::uniform_int_distribution<int> dist(1, 10);

    // Elemente einfügen
    for (int i = 0; i < 10; ++i) {
        int zufallszahl = dist(generator);
        vListe.push_back(zufallszahl);
    }

    // Liste vor Aktualisierung ausgeben
    std::cout << "Liste vor vAktualisieren:\n";
    for (const auto& elem : vListe) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Elemente > 5 markieren zum Löschen
    for (auto it = vListe.begin(); it != vListe.end(); ++it) {
        if (*it > 5) {
            vListe.erase(it);
        }
    }

    // Liste erneut ausgeben (vor vAktualisieren)
    std::cout << "Liste vor vAktualisieren (nach Aktionen):\n";
    for (const auto& elem : vListe) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Aktionen ausführen
    vListe.vAktualisieren();

    // Liste nach Aktualisierung ausgeben
    std::cout << "Liste nach vAktualisieren:\n";
    for (const auto& elem : vListe) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Neue Elemente hinzufügen und erneut ausgeben
    vListe.push_front(42);
    vListe.push_back(99);
    vListe.vAktualisieren();

    std::cout << "Liste nach weiteren Änderungen:\n";
    for (const auto& elem : vListe) {
        std::cout << elem << " ";
    }
    std::cout << "\n";


}

void vAufgabe_7() {
	auto kr1 = make_shared<Kreuzung>("Kr1");
	auto kr2 = make_shared<Kreuzung>("Kr2", 1000);
	auto kr3 = make_shared<Kreuzung>("Kr3");
	auto kr4 = make_shared<Kreuzung>("Kr4");

	auto car1 = make_unique<PKW>("Tesla", 120, 4);
	auto bike1 = make_unique<Fahrrad>("Obama", 24);

    Kreuzung::vVerbinde(kr1, kr2,"W12", "W21", 40.0,  Tempolimit::Innerorts, true);
    Kreuzung::vVerbinde(kr2, kr3, "W23a", "W32a", 115.0, Tempolimit::Autobahn, false);
    Kreuzung::vVerbinde(kr2, kr3, "W23b", "W32b", 40.0, Tempolimit::Innerorts, true);
    Kreuzung::vVerbinde(kr2, kr4, "W24", "W42", 55.0, Tempolimit::Innerorts, true);
    Kreuzung::vVerbinde(kr3, kr4, "W34", "W43", 85.0, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde(kr4, kr1, "W44a", "W44b", 130.0, Tempolimit::Landstrasse, true);

	kr1->vAnnahme(std::move(car1), 4.0);
	kr1->vAnnahme(std::move(bike1), 1.8);

	if (!bInitialisiereGrafik(1200, 800))
	{
		cerr << "Fehler beim Starten des Simulationsservers." << endl;
	}

	int iCoords1[] = { 680,  40, 680, 300 };
	int iCoords2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int iCoords3[] = { 680, 300, 680, 570 };
	int iCoords4[] = { 680, 300, 320, 300 };
	int iCoords5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int iCoords6[] = { 320, 300, 320, 150, 200,  60,  80,  90,  70, 250, 170, 300, 320, 300 };

	bZeichneStrasse("W12",  "W21",   40, 2, iCoords1);
	bZeichneStrasse("W23a", "W32a", 115, 6, iCoords2);
	bZeichneStrasse("W23b", "W32b",  40, 2, iCoords3);
	bZeichneStrasse("W24",  "W42",   55, 2, iCoords4);
	bZeichneStrasse("W34",  "W43",   85, 5, iCoords5);
	bZeichneStrasse("W44a", "W44b", 130, 7, iCoords6);

	bZeichneKreuzung(680,  40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	Fahrzeug::vKopf();
	for (dGlobaleZeit = 0; dGlobaleZeit < 12; dGlobaleZeit += 0.3)
	{
		kr1->vSimulieren();
		kr2->vSimulieren();
		kr3->vSimulieren();
		kr4->vSimulieren();

		vSetzeZeit(dGlobaleZeit);

		kr1->vZeichnen();
		kr2->vZeichnen();
		kr3->vZeichnen();
		kr4->vZeichnen();

		//std::cout << *car1 << std::endl << *bike1 << std::endl << kr1 << std::endl << kr2<< std::endl << kr3 << std::endl << kr4 << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

		vSleep(100);
	}

	vBeendeGrafik();

}

void vAufgabe_8() {
	Simulation simulation;
    std::ifstream datei("VO.dat");

    if (!datei) {
        std::cerr << "Konnte 'VO.dat' nicht oeffnen!" << std::endl;
        return;
    }

    try {
		simulation.vEinlesen(datei);
		simulation.vSimulieren(20.0, 1.0);
    }
	catch (std::runtime_error& e)
	{
		std::cerr << "Error reading file: " << e.what() << std::endl;
	}


    datei.close();
}

void vAufgabe_9() {
	Simulation simulation;
    std::ifstream datei("Simu.dat");

    if (!datei.is_open()) {
        std::cerr << "Failed to open file 'Simu.dat'" << std::endl;
        return;
    }

    try {
		simulation.vEinlesen(datei);
		simulation.vSimulieren(20.0, 1.0);
    }
	catch (std::runtime_error& e)
	{
		std::cerr << "Error reading file: " << e.what() << std::endl;
	}


    datei.close();
}

void vAufgabe_9a() {
    Simulation simulation;
    std::ifstream datei("SimuDisplay.dat");

    if (!datei.is_open()) {
        std::cerr << "Fehler beim oeffnen 'SimuDisplay.dat'" << std::endl;
        return;
    }

	try {
		simulation.vEinlesen(datei, true);
		simulation.vSimulieren(20.0, 0.25);

    }
	catch (std::runtime_error& e) {
		std::cerr << "Fehler: " << e.what() << std::endl;
	}

    datei.close();

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
	int auswahl = 11;

	do {
	        std::cout << "\nWelche Aufgabe möchten Sie ausführen?\n"
	        << "1: Aufgabe 1\n"
	        << "2: Aufgabe 2\n"
	        << "3: Aufgabe 3\n"
	        << "4: Aufgabe 4\n"
	        << "5: Aufgabe 5\n"
	        << "6: Aufgabe 6\n"
	        << "7: Aufgabe 6a\n"
	        << "8: Aufgabe 7\n"
			<< "9: Aufgabe 8\n"
			<< "10: Aufgabe 9\n"
			<< "11: Aufgabe 9a\n"
	        << "0: Programm beenden\n"
	        << "Ihre Auswahl: ";

	        std::cin >> auswahl;
	        std::cout << std::endl;

	        switch (auswahl) {
	        case 1:
	            vAufgabe_1();
	            break;
	        case 2:
	            vAufgabe_2();
	            break;
	        case 3:
	            vAufgabe_3();
	            break;
	        case 4:
	            vAufgabe_4();
	            break;
	        case 5:
	            vAufgabe_5();
	            break;
	        case 6:
	            vAufgabe_6();
	            break;
	        case 7:
	        	vAufgabe_6a();
	        	break;
	        case 8:
	        	vAufgabe_7();
	        	break;
	        case 9:
	        	vAufgabe_8();
	        	break;
	        case 10:
	        	vAufgabe_9();
	        	break;
	        case 11:
	        	vAufgabe_9a();
	        	break;
	        case 0:
	            std::cout << "Programm beendet.\n";
	            break;
	        default:
	            std::cout << "Ungültige Eingabe. Bitte wählen Sie eine gültige Option.\n";
	        }

	    } while (auswahl != 0);


	return 0;
}
