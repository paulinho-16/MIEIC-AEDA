/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    BSTItrIn<Expertize> it(expertizes);
    Expertize expertiz(expertizeAvailable,cost);
    while (!it.isAtEnd()) {
        expertiz = it.retrieve();
        if (expertiz.getName() == expertizeAvailable && expertiz.getCost() == cost) {
            it.retrieve().addConsultant(student);
            return;
        }
        it.advance();
    }
    Expertize nova_expertiz(expertizeAvailable,cost);
    nova_expertiz.addConsultant(student);
    expertizes.insert(nova_expertiz);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize> it(expertizes);
	while (!it.isAtEnd()) {
	    if (it.retrieve().getName() == project->getExpertize() && it.retrieve().getCost() == project->getCost()) {
	        for (unsigned int i = 0 ; i < it.retrieve().getConsultants().size() ; i++) {
	            if (it.retrieve().getConsultants()[i]->getCurrentProject() == "") {
	                temp.push_back(it.retrieve().getConsultants()[i]);
	            }
	        }
	    }
	    it.advance();
	}
	return temp;
}

bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    if (project->getConsultant() != nullptr)
        return false;
    BSTItrIn<Expertize> it(expertizes);
    while (!it.isAtEnd()) {
        if (it.retrieve().getName() == project->getExpertize() && it.retrieve().getCost() == project->getCost()) {
            for (unsigned int i = 0 ; i < it.retrieve().getConsultants().size() ; i++) {
                if (it.retrieve().getConsultants()[i]->getCurrentProject() == "" && it.retrieve().getConsultants()[i]->getEMail() == student->getEMail()) {
                    it.retrieve().getConsultants()[i]->addProject(project->getTitle());
                    project->setConsultant(student);
                    return true;
                }
            }
        }
        it.advance();
    }
    return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    StudentPtr s(student);
    students.insert(s);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
    HashTabStudentPtr::iterator it = students.begin();
    while (it != students.end()) {
        if ((*it).getEMail() == student->getEMail()) {
            student->setEMail(newEMail);
        }
        it++;
    }
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
    vector<Student>::const_iterator it = candidates.begin();
    while (it != candidates.end()) {
        if ((*it).getPastProjects().size() >= min) {
            activeStudents.push(*it);
        }
        it++;
    }
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    priority_queue<Student> temp = activeStudents;
    vector<Student> aux;
    Student estudante("","");
    int contador = -1;
    while (!temp.empty()) {
        if (contador == -1) {
            aux.push_back(temp.top());
            contador = temp.top().getPastProjects().size();
            estudante = temp.top();
            temp.pop();
        }
        else {
            if (contador == temp.top().getPastProjects().size()) {
                aux.push_back(temp.top());
            }
            temp.pop();
        }
    }
    if (aux.size() == 1) {
        studentMaximus = estudante;
        return activeStudents.size();
    }
    else {
        return 0;
    }
}





















