/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned contador = 0;
    list<Doctor>::const_iterator it;
    for (it = doctors.begin() ; it != doctors.end(); it++) {
        if ((*it).getMedicalSpecialty() == medicalSpecialty) {
            contador += (*it).getPatients().size();
        }
    }
	return contador;
}

bool CompararDoctors(Doctor &d1, Doctor &d2) {
    if (d1.getPatients().size() < d2.getPatients().size())
        return true;
    else if (d1.getPatients().size() == d2.getPatients().size())
        return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
    else
        return d1.getCode() < d2.getCode();
}

void Hospital::sortDoctors() {
    doctors.sort(CompararDoctors);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    Doctor d1(codM1,medicalSpecialty1);
    int contador = 0;
    for (auto d : doctors) {
        if (d.getMedicalSpecialty() == medicalSpecialty1)
            contador++;
    }
    if (contador < 3) {
        doctors.push_back(d1);
        return true;
    }
	return false;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;
	for (auto it = doctors.begin() ; it != doctors.end() ; it++) {
	    if ((*it).getCode() == codM1) {
            p1 = (*it).getPatients();
            doctors.erase(it);
            return p1;
	    }
	}
	throw DoctorInexistent();
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    bool encontrado = false;
    vector<Doctor> aux;
    for (auto it = doctors.begin() ; it != doctors.end() ; it++) {
        if ((*it).getMedicalSpecialty() == medicalSpecialty1) {
            aux.push_back(*it);
            encontrado = true;
        }
    }
    if (encontrado) {
        Doctor daux = aux[0];
        for (auto it = aux.begin(); it != aux.end(); it++) {
            if ((*it).getPatients().size() < daux.getPatients().size())
                daux = (*it);
        }
        Patient p1(cod1,medicalSpecialty1);
        for (auto it = doctors.begin() ; it != doctors.end() ; it++) {
            if ((*it).getCode() == daux.getCode()) {
                (*it).addPatient(p1);
                return true;
            }
        }
    }
	return false;
}



void Hospital::processPatient(unsigned codM1) {
    bool done = false;
    Patient p1(444,"default");
    for (auto it = doctors.begin() ; it != doctors.end() ; it++) {
        if ((*it).getCode() == codM1) {
            if ((*it).getPatients().empty())
                return;
            p1 = (*it).removeNextPatient();
            for (auto itb = letterTray.begin() ; itb != letterTray.end() ; itb++) {
                if ((*itb).size() < trayCapacity) {
                    (*itb).push(p1);
                    done = true;
                    return;
                }
            }
            if (!done) {
                stack<Patient> pilha;
                pilha.push(p1);
                letterTray.push_back(pilha);
                return;
            }
        }
    }
}


unsigned Hospital::removePatients(unsigned codP1) {
    unsigned contador = 0;
    for (auto it = letterTray.begin() ; it != letterTray.end() ; it++) {
        if ((*it).top().getCode() == codP1) {
            (*it).pop();
            contador++;
            if ((*it).empty()) {
                it = --letterTray.erase(it);
            }
        }
    }
    return contador;
}



