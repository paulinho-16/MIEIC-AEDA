/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle)
{
    if (vehicles.size() >= capacity)
        return false;
    typename std::vector<Vehicle *>::const_iterator it;
    for (it = vehicles.begin() ; it != vehicles.end() ; it++)
    {
        if (*(*it) == *vehicle)
            return false;
    }
    vehicles.push_back(vehicle);
    return true;
}

template<class Vehicle>
bool OrdenarVeiculos(Vehicle* t1,Vehicle* t2)
{
    if ((*t1).getBrand() < (*t2).getBrand())
        return true;
    else if ((*t1).getBrand() == (*t2).getBrand())
        return ((*t1).getPrice() > (*t2).getPrice());
    else
        return false;
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles()
{
    sort(vehicles.begin(),vehicles.end(),OrdenarVeiculos<Vehicle>);
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model)
{
    Vehicle* removido;
    bool Encontrou = false;
    typename std::vector<Vehicle *>::iterator it;
    for (it = vehicles.begin() ; it != vehicles.end() ; it++)
    {
        if ((*it)->getBrand() == brand && (*it)->getModel() == model)
        {
            removido = *it;
            vehicles.erase(it);
            return removido;
        }
    }
    throw NoSuchVehicleException();
}

class NoSuchBrandException
{
        std::string marca;
public:
    NoSuchBrandException(std::string marc) {marca = marc;}
    std::string getBrand() const {return marca;}
};

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const
{
    bool Encontrou = false;
    float result = 0;
    unsigned int  contador = 0;
    typename std::vector<Vehicle *>::const_iterator it;
    for (it = vehicles.begin() ; it != vehicles.end() ; it++)
    {
        if ((*it)->getBrand() == brand)
        {
            Encontrou = true;
            contador++;
            result += (*it)->getPrice();
        }
    }
    if (!Encontrou) throw NoSuchBrandException(brand);
    return result / (float) contador;
}

#endif /* SRC_GARAGE_H_ */
