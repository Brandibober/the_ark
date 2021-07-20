//
// Created by Amisto on 4/2/2021.
//

#include "Population.h"
#include "TheArk.h"
#include "MedicalService.h"
#include "SocialService.h"
#include "TechnicalService.h"
#include "BiologicalService.h"
#include "EmergencyService.h"
#include "NavigationService.h"
#include "Enums.cpp"
#include <cstdlib>

Population::Population() : children(0), adults(0), oldmen(0){}

unsigned int Population::getChildren() const {
    return this->children;
}

unsigned int Population::getAdults() const {
    return this->adults;
}

unsigned int Population::getOldmen() const {
    return this->oldmen;
}

unsigned int Population::getTotal() const {
    return this->people.size();
}

unsigned int Population::borderChildrenToAdults()
{
    return TheArk::get_instance()->getSocialService()->borderChildrenToAdults();
}

unsigned int Population::borderAdultsToOldmen()
{
    return TheArk::get_instance()->getMedicalService()->borderAdultsToOldmen();
}

unsigned int Population::number_staff(Classification_of_humans serves)
{
    switch(serves){
        case Technical_Service:
            return TheArk::get_instance()->getTechnicalService()->getRecommendedNStaff();
        case Biological_Service:
            return TheArk::get_instance()->getBiologicalService()->getRecommendedNStaff();
        case Medical_Service:
            return TheArk::get_instance()->getMedicalService()->getRecommendedNStaff();
        case Navigation_Service:
            return TheArk::get_instance()->getNavigationService()->getRecommendedNStaff();
        case Emergency_Service:
            return TheArk::get_instance()->getEmergencyService()->getNStaff();
        case Social_Service:
            return TheArk::get_instance()->getSocialService()->getRecommendedNStaff();
        default:
            return 0;
    }

}

void  Population::stuff_distribution(list<shared_ptr<Human>>& stuff, unsigned int demand_stuff)
{
    auto it = this->people.begin();
    unsigned int counter = 0;
    while(it != this->people.end() && counter < demand_stuff)
    {
        if((*it)->getAge() > this->borderChildrenToAdults() && (*it)->getAge() < this->borderAdultsToOldmen())
        {
            if((*it)->getTypeAsAWorker() == UNDEFINED || (*it)->getTypeAsAWorker() == UNEMPLOYED)
            {
                stuff.push_back(*it);
                (*it)->setTypeAsAWorker(WORKER);
                counter++;
            }
        }
        ++it;

    }
}

double Population::deathRateChildren()
{
    return TheArk::get_instance()->getMedicalService()->deathRateChildren();
}

double Population::deathRateAdults()
{
    return TheArk::get_instance()->getMedicalService()->deathRateAdult();
}

double Population::deathRateOldmen()
{
    return TheArk::get_instance()->getMedicalService()->deathRateOldmen();
}

list<shared_ptr<Human>>& Population::getPeople()
{
    return this->people;
}
array<list<shared_ptr<Human>>, 7>& Population::getAllClassification()
{
     return this->classifications_of_humans;
}

void Population::processYear() {
    //рождаемость
    for(int i = 0; i < TheArk::get_instance()->getMedicalService()->BirthRate(); i++)
    {
        auto* micro_chelik = new Human();
        micro_chelik->setAge(0);
        auto ptr = shared_ptr<Human>(micro_chelik);
        this->people.push_back(ptr);
    }
    //распределение стафа, сделал бы в цикле, но нужно вызывать каждую ф-ю отдельно
    stuff_distribution(classifications_of_humans[0], TheArk::get_instance()->getTechnicalService()->getStaffDemand());
    stuff_distribution(classifications_of_humans[1], TheArk::get_instance()->getBiologicalService()->getStaffDemand());
    stuff_distribution(classifications_of_humans[2], TheArk::get_instance()->getMedicalService()->getStaffDemand());
    stuff_distribution(classifications_of_humans[3], TheArk::get_instance()->getNavigationService()->getStaffDemand());
    stuff_distribution(classifications_of_humans[4], TheArk::get_instance()->getEmergencyService()->getStaffDemand());
    stuff_distribution(classifications_of_humans[5], TheArk::get_instance()->getSocialService()->getStaffDemand());
    //


    // обработка по возрасту и смертность сразу же, чтобы два раза не ходить
    children = 0;
    adults = 0;
    oldmen = 0;
    unsigned int HisAge = 0;

    for (auto it = people.begin(); it != people.end();)
    {

        HisAge = (*it)->getAge();

        //подсчёт количества населения по группам и обработка случайной смертности
        if (HisAge < this->borderChildrenToAdults())
        {
            children++;
            if (rand() <= this->deathRateChildren() * RAND_MAX)
            {
                (*it)->setIsAlive(false);
                children--;
            }
        }
        if ((HisAge >= this->borderChildrenToAdults()) && (HisAge < borderAdultsToOldmen()))
        {
            adults++;
            if (rand() <= this->deathRateAdults() * RAND_MAX)
            {
                (*it)->setIsAlive(false);
                adults--;
            }
        }
        if (HisAge >= this->borderAdultsToOldmen() && HisAge <= 100)
        {
            oldmen++;
            if (rand() <= this->deathRateOldmen() * RAND_MAX)
            {
                (*it)->setIsAlive(false);
                oldmen--;
            }
        }
        if((*it)->getPhysicalHealth() <= 10 || (*it)->getMoralHealth() <= 5){
            (*it)->setIsAlive(false);
        }
        if(HisAge > 100){
            (*it)->setIsAlive(false);
        }

        //старение
        (*it)->setAge(HisAge + 1);

        //попанье мертвых
        if (!(*it)->isAlive())
        {
            auto tmpit = it;
            ++it;
            this->people.erase(tmpit);
        }
        else{
            ++it;
        }

    }
    // конец обработки по возрасту

    this->check_dead_people_is_classifications(); // см коммент в ф-ции

    // тут ещё безусловно нужно написать рождаемость, иначе все подохнут
    // дальше идет просмотр обучающихся и обработка тех, кто отучился. Их пихаем в службы по запросам
    // распределение остальных людей по соответвующим категориям

    //конец обработки
}

void Population::check_dead_people_is_classifications()
{
    // удаление людей с is_alive == false из всех классификаций
    for (list<shared_ptr<Human>>& classification: this->classifications_of_humans)
    {
        for (auto it = classification.begin(); it != classification.end();)
        {
            if (!(*it)->isAlive()){
                auto nit = it;
                ++it;
                classification.erase(nit);
            }
            else{
                ++it;
            }
        }
    }
}

void Population::init(unsigned int total) {
    this->children = (unsigned int)(0.1 * total);
    this->oldmen = (unsigned int)(0.2 * total);
    this->adults = total - children - oldmen;

    for(int i = 0; i < this->children; i++)
    {          // заполняем детьми
        auto* person = new Human();
        person->setAge((rand()% this->borderChildrenToAdults()));
        auto ptr = shared_ptr<Human>(person);
        this->people.push_back(ptr);
    }
    for(int i = 0; i < this->oldmen; i++)
    {            // заполняем стариками
        auto *person = new Human;
        person->setAge((this->borderAdultsToOldmen() + rand() % (100 - this->borderAdultsToOldmen() + 1)));
        auto ptr = shared_ptr<Human>(person);
        this->people.push_back(ptr);
    }
    for(int i = 0; i < this->adults; i++)
    {        // заполняем взрослыми всех остальных людей
        auto* person = new Human;
        person->setAge((this->borderChildrenToAdults()+ rand()% (this->borderAdultsToOldmen() - this->borderChildrenToAdults() + 1)));
        auto ptr = shared_ptr<Human>(person);
        this->people.push_back(ptr);
    }
    // далее идет сортировка по необходимым классификациям
    int staffs = 0, o = 0;

   for(int i = 0; i < this->classifications_of_humans.size(); i++)
   {
       staffs = number_staff(Classification_of_humans(i));
       o = 0;
       auto iter = this->people.begin();

        while(o!= staffs && iter != this->people.end() )
        {
            if((*iter)->getAge() > this->borderChildrenToAdults() + Education::FifthYear && (*iter)->getAge() < this->borderAdultsToOldmen())
            {
                if((*iter)->getTypeAsAWorker() == UNDEFINED || (*iter)->getTypeAsAWorker() == UNEMPLOYED)
                {
                    this->classifications_of_humans[i].push_back(*iter);
                    (*iter)->setTypeAsAWorker(WORKER);
                    o++;
                }
            }
            iter++;
        }
    }
}


