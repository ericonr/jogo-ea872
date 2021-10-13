
#include "models.h"


void Scenary_element_vector::add_element(Scenary_element &element) {
    
    element_vector.push_back(element);

}

void Scenary_element_vector::delete_element(int pos) {

    element_vector.erase(element_vector.begin()+ (pos - 1));

}


void insert_Scenary_element(Scenary_element &e, Scenary_element_vector &sev) {
	sev.add_element(e);
    
}