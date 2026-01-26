//
// Created by Anastazja on 22.01.2026.
//
#include "factory.hpp"

/*
is_consistent() – sprawdzanie spójności sieci

do_deliveries() – dokonywanie ewentualnych dostaw na rampy

do_package_passing() – dokonywanie ewentualnego
przekazywania półproduktów

do_work() – dokonywanie ewentualnego przetwarzania
półproduktów przez robotników

(W praktyce każda z metod do_XXX() powinna jedynie wywoływać
właściwe metody z klas Ramp i Worker dla każdego elementu z
właściwej kolekcji węzłów.)
*/


bool Factory::is_consistent()
{
    return true;
}

void Factory::do_deliveries(Time t)
{

}

void Factory::do_package_passing()
{

}

void Factory::do_work(Time t)
{

}
