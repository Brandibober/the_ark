//
// Created by Amisto on 4/2/2021.
//

#include "TechnicalService.h"
#include "TheArk.h"

TechnicalService::TechnicalService()
{
    this->totalState = 100;
    this->engineState = 100;
    this->protectionState = 100;
    this->serviceState = 100;
    this->maxStaff = 0;
    this->maxResources = 0;
    this->staff = 200;
    this->resources = 200;
}

// идет "корректировка" состояния корабля в зависимости от степени аварии
void TechnicalService::process_accident(AccidentSeverity as)
{
    this->protectionState -= as * 6.8; //подумать коэф
    this->engineState -= as * (100 - this->protectionState) * 0.3;
    this->totalState = 0.5 * (0.8 * this->protectionState + 1.2 * this->engineState);
    if (this->protectionState < 15)
        emergencyRepair();
    // kill some people
    kill(0);
}

void TechnicalService::kill(int victims)
{
    this->staff -= victims;
    list<shared_ptr<Human>>& humans = TheArk::get_instance()->getPopulation()->getAllClassification()[Technical_Service];
    auto it = humans.begin();
    for (int i = 0; i < victims; i ++)
    {
        (*it)->setIsAlive(false);
        it ++;
    }
}

// считает и возвращает состояние службы в зависимости от количества работающих людей и
double TechnicalService::getState() {
    return this->serviceState;
}

void TechnicalService::emergencyRepair()
{
    double repairing = double(this->staff) / this->maxStaff * double(this->resources) / this->maxResources * 50;
    this->protectionState += repairing;
    this->resources -= int(repairing / 100) * maxResources;
    // убить много людей, так как экстренная и масштабная починка
    kill(0);
}

void TechnicalService::process_year()
{
    // обновление состояния службы
    this->serviceState = 50 * (double(this->staff) / this->maxStaff + double(this->resources) / this->maxResources);
    if (this->serviceState > 100)
        this->serviceState = 100;

    // починка корабля
    double repairing = double(this->staff) / this->maxStaff * double(this->resources) / this->maxResources * 10;
    if (this->protectionState < 90)
    {
        this->protectionState += repairing;
        this->resources -= int(repairing / 100) * this->maxResources;
        // можно убить пару людей в зависимости от масштаба ремонта
    }
    if (this->protectionState > 60 && this->engineState < 90)
    {
        this->engineState += repairing;
        this->resources -= int(repairing / 100) * this->maxResources;
    }
    // износ корабля
    this->protectionState -= (101 - this->protectionState) * 0.05;
    this->engineState -= (100 - this->protectionState) * 0.05;
}

double TechnicalService::efficiencyConsumablesToComponents() {
    return double(this->staff) / this->maxStaff * 0.9;
}

double TechnicalService::efficiencyJunkToConsumables() {
    return double(this->staff) / this->maxStaff * 0.7;
}

double TechnicalService::efficiencyJunkToRefuse() {
    return double(this->staff) / this->maxStaff * 0.5;
}

void TechnicalService::setState(double s)
{
    this->serviceState = s;
}

unsigned int TechnicalService::getResourceDemand() {
    return 50;
}

unsigned int TechnicalService::getResourcePriority() {
    return 1;
}

unsigned int TechnicalService::getStaffDemand() {
    return 10;
}

unsigned int TechnicalService::getStaffPriority() {
    return 1;
}

bool TechnicalService::changeStaff(int delta) {
    staff += delta;
    // TheArk::get_instance()->getPopulation()->getAllClassification()[Technical_Service];
    return true;
}

bool TechnicalService::changeResources(int delta) {
    resources += delta;
    return true;
}