//
// Created by Anastazja on 22.01.2026.
//
#include "factory.hpp"

#include <stdexcept>

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


bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) {
    if ( node_colors[sender]== ZWERYFIKOWANY) {
        return true;
    }
    node_colors[sender] = ODWIEDZONY;

    if (sender->receiver_preferences_.preferences.empty()) {
        throw std::logic_error("The sender has no recipients!");
    }

    bool has_another_reciever = false;
    for (const auto& receiver : sender->receiver_preferences_.preferences) {
        if (receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            has_another_reciever = true;
        }else if (receiver.first->get_receiver_type() == ReceiverType::WORKER) {
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if (sendrecv_ptr == sender) {
                continue;
            }

            has_another_reciever = true;

            if (node_colors[sender] == NIEODWIEDZONY) {
                has_reachable_storehouse(sender, node_colors);
            }
        }
    }
    node_colors[sender] = ZWERYFIKOWANY;

    if (has_another_reciever) {
        return true;
    }else {
        throw std::logic_error("The sender has no recipients!");
    }
}

bool Factory::is_consistent() {
    
}