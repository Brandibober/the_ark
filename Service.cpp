//
// Created by Amisto on 4/2/2021.
//

#include "Service.h"

Service::Service() : recommended_n_staff(0), recommended_resources(0) {}

unsigned int Service::getRecommendedNStaff() const {return recommended_n_staff;}

Service::~Service() = default;
