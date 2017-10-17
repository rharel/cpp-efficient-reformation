#include <assert.h>

#include <glm/geometric.hpp>

#include "World.h"


using namespace rharel::efficient_reformation::demo;


World::World(const unsigned int vehicle_count)
    : vehicles(vehicle_count)
{}

void World::step(const float duration)
{
    if (duration <= 0) { return; }

    for (auto& vehicle : vehicles)
    {
        step_vehicle(vehicle, duration);
    }
}
void World::step_vehicle(Vehicle& vehicle, const float duration)
{
    assert(vehicle.speed >= 0);
    assert(duration      >  0);

    if (vehicle.position == vehicle.target) { return; }

    const glm::vec2 path             = vehicle.target - vehicle.position;
    const float     path_length      = glm::length(path),
                    distance_covered = vehicle.speed * duration;
    
    if (path_length <= distance_covered)
    {
        vehicle.position = vehicle.target;
    }
    else
    {
        vehicle.position += path * (distance_covered / path_length);
    }
}

unsigned int World::get_vehicle_count() const
{
    return vehicles.size();
}

const Vehicle& World::get_vehicle(const unsigned int index) const
{
    return vehicles.at(index);
}
      Vehicle& World::get_vehicle(const unsigned int index)
{
    return vehicles.at(index);
}
