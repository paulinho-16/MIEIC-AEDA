/*
 * Doctor.cpp
 */

#include "Doctor.h"

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    vector<Patient> aux;
    queue<Patient> auxQueue = patients;
    bool encontrado = false;
    int contador = 0;
    for (unsigned int i = 0 ; i < patients.size() ; i++) {
        aux.push_back(auxQueue.front());
        auxQueue.pop();
    }
    for (auto d : aux) {
        if (d.getCode() == codP1) {
            auxQueue.push(d);
            encontrado = true;
            break;
        }
        contador++;
    }
    if (encontrado) {
        aux.erase(aux.begin() + contador);
        for (auto d : aux) {
            auxQueue.push(d);
        }
        patients = auxQueue;
    }
}

