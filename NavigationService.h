//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_NAVIGATIONSERVICE_H
#define THE_ARK_NAVIGATIONSERVICE_H

#include <ctime>
#include <cmath>
#include "Service.h"
#include "TheArk.h"
#include "MedicalService.h"
#include "NavigationService.h"
#include "BiologicalService.h"
#include "SocialService.h"
#include "TechnicalService.h"
#include "Human.h"
#include "Population.h"
#include "Resources.h"

class NavigationService : public Service {
private:
    double State;
    unsigned int staff;                                 // количество рабочих всего
    unsigned int resources;
    unsigned int need_staff;
    unsigned int need_resources;
    unsigned int stage;                               //стадия полета(маневрирование, разгон, выход на макс. скорость, торможение) в процентах
    double lost_years;                                 //сколько потеряно времени из-за происшествий
public:
    NavigationService();
 void process_accident(AccidentSeverity as)  override; // каждая служба должна уметь в своих терминах обработать переданную ей аварию
     void process_year()  override;                        // если у службы есть какая-то личная жизнь, она может заниматься ей тут
   double getState()  override;                          // каждая служба должна уметь вернуть свое состояние в процентах, посчитав его в своих терминах
     void setState(double s)  override;                    // функция для инициализации, каждая служба должна уметь получить состояние в процентах и пересчитать  его в своих терминах

    //unsigned int getResourceDemand();
    unsigned int getStaffDemand();
    bool changeResources(int delta);
    bool changeStaff(int delta);
    unsigned int getResourceDemand();
   

};


#endif //THE_ARK_NAVIGATIONSERVICE_H
