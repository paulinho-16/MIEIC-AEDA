#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    Property* aux = properties[0];
    vector<Property*> vetor = {properties[0]};
    int preco_maximo = aux->getPrice();
    for (unsigned int i = 1 ; i < properties.size() ; i++) {
        if (aux->getAddress() != properties[i]->getAddress() || aux->getPostalCode() != properties[i]->getPostalCode() || aux->getTypology() != properties[i]->getTypology()) {
            PropertyTypeItem pti(aux->getAddress(),aux->getPostalCode(),aux->getTypology(),preco_maximo);
            pti.setItems(vetor);
            catalogItems.insert(pti);
            vetor = {properties[i]};
            aux = properties[i];
            preco_maximo = properties[i]->getPrice();
        }
        else {
            if (properties[i]->getPrice() > preco_maximo)
                preco_maximo = properties[i]->getPrice();
            vetor.push_back(properties[i]);
        }
    }
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd()) {
	    vector<Property*> aux = it.retrieve().getItems();
	    for (unsigned int i = 0 ; i < aux.size() ; i++) {
	        if (aux[i]->getAddress() == property->getAddress() && aux[i]->getPostalCode() == property->getPostalCode() && aux[i]->getTypology() == property->getTypology()) {
	            if (get<0>(aux[i]->getReservation()) == NULL) {
	                temp.push_back(aux[i]);
	            }
	        }
	    }
	    it.advance();
	}
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    while (!it.isAtEnd()) {
        if (it.retrieve().getAddress() == property->getAddress() && it.retrieve().getPostalCode() == property->getPostalCode() && it.retrieve().getTypology() == property->getTypology()) {
            vector<Property*> aux = it.retrieve().getItems();
            for (unsigned int i = 0 ; i < aux.size() ; i++) {
                if (get<0>(aux[i]->getReservation()) == NULL) {
                    aux[i]->setReservation(make_tuple(client, aux[i]->getPrice()*((100-percentage)/100.0)));
                    client->addVisiting(aux[i]->getAddress(),aux[i]->getPostalCode(),aux[i]->getTypology(),to_string(aux[i]->getPrice()));
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
void REAgency::addClientRecord(Client* client) {
	ClientRecord r(client);
	listingRecords.insert(r);
}

void REAgency::deleteClients() {
    HashTabClientRecord::iterator it = listingRecords.begin();
    while (it != listingRecords.end()) {
        if (!get<0>((*it).getClientPointer()->getVisiting()).empty()) {
            it = listingRecords.erase(it);
        }
        else
            it++;
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    vector<Client>::const_iterator it = candidates.begin();
    while (it != candidates.end()) {
        int reservas = 0;
        for (unsigned int i = 0 ; i < properties.size() ; i++) {
            if (get<0>(properties[i]->getReservation())->getEMail() == (*it).getEMail())
                reservas++;
        }
        if (!(*it).getVisitedProperties().empty()) {
            if ((float) reservas / (*it).getVisitedProperties().size() > min) {
                clientProfiles.push((*it));
            }
        }
        it++;
    }
}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> temp = getClientProfiles();
    Property *adicionar = nullptr;
    while (!temp.empty()) {
        int aux = stoi(get<1>(temp.top().getVisiting()));
        adicionar = nullptr;
        int diff = 100000;
        for (auto &p: properties) {
            if (get<0>(p->getReservation()) == nullptr && (get<0>(temp.top().getVisiting()) != p->getAddress() || get<1>(temp.top().getVisiting()) != p->getPostalCode() || get<2>(temp.top().getVisiting()) != p->getTypology() ||
            get<3>(temp.top().getVisiting()) != to_string(p->getPrice()))) {
                if (abs(stoi(p->getPostalCode())-aux) < diff) {
                    diff = abs(stoi(p->getPostalCode())-aux);
                    adicionar = p;
                }
            }
        }
        if (adicionar != nullptr) {
            tempProperties.push_back(adicionar);
        }
        temp.pop();
    }
	return tempProperties;
}
