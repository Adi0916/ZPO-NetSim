//
// Created by adi on 15.01.2026.
//

#ifndef NETSIM_NODES_HXX
#define NETSIM_NODES_HXX
#include <memory>
#include <map>
#include <list>
#include "package.hxx"
#include "storage_types.hxx"
#include "types.hxx"
#include "helpers.hxx"
enum ReceiverType {WORKER, STOREHOUSE};
using const_iterator = std::list<Package>::const_iterator;

class IPackageReceiver {
public:
    virtual void receive_package(Package&&) = 0;
    virtual ElementID get_id() const;
    virtual ReceiverType get_receiver_type() const;
    virtual IPackageStockpile::const_iterator cbegin() const;
    virtual IPackageStockpile::const_iterator begin() const;
    virtual IPackageStockpile::const_iterator cend() const;
    virtual IPackageStockpile::const_iterator end() const;

    virtual ~IPackageReceiver() = default;
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = default_probability_generator): pg_(std::move(pg)) {};

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver() const;
    preferences_t& get_preferences() {return preferences_;};

private:
    ProbabilityGenerator pg_;
    preferences_t preferences_;
};
class Storehouse: public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageReceiver> d = std::make_unique<PackageQueue>(PackageQueueType::LIFO)){id_ = id; d_ = std::move(d);};
    void receive_package(Package&& p) override;
    ElementID get_id() const override {return id_;};
    ReceiverType get_receiver_type() const override {return STOREHOUSE;};

    IPackageStockpile::const_iterator cbegin() const override {return d_->cbegin();}
    IPackageStockpile::const_iterator begin() const override {return d_->begin();}
    IPackageStockpile::const_iterator cend() const override { return d_->cend();}
    IPackageStockpile::const_iterator end() const override { return d_->end();}
    IPackageStockpile* get_queue() const {return d_.get();}
    IPackageReceiver* choose_receiver();
    IPackageReceiver* get_id();
private:
    ElementID id_;
    std::unique_ptr<PackageQueue> d_;
};

#endif //NETSIM_NODES_HXX