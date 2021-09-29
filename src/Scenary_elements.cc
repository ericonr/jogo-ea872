
#pragma once
#include "models.h"


void Scenary_element_vector::add_element(Scenary_element &element) {
    
    element_vector.push_back(element);

}

void Scenary_element_vector::delete_element(int pos) {

    element_vector.erase(element_vector.begin()+ (pos - 1));

}