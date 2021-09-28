/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
    Article *a1 = new Article(client,barCode);
    (*a1).setPresent(present);
    (*a1).setDeliverHome(deliverHome);
    return a1;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
    if (bags.back().size() < BAG_SIZE) {
        bags.back().push(article);
    }
    else {
        std::stack<Article*> saco;
        saco.push(article);
        bags.push_back(saco);
    }
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
    vector<Article*> aux;
    vector<Article *>::reverse_iterator itr;
	for (auto it = bags.begin() ; it != bags.end(); it++) {
	    while (!(*it).empty())
	    {
	        if ((*it).top()->getPresent())
	            presents.push_back((*it).top());
	        else
	            aux.push_back((*it).top());
            (*it).pop();
	    }
	    for (itr = aux.rbegin() ; itr != aux.rend() ; itr++) {
            (*it).push(*itr);
	    }
	    aux.clear();
	}
	return presents;
}

