#include "core/formations/Arrow.h"
#include "core/formations/Column.h"
#include "Scene.h"


using rharel::efficient_reformation::core::Arrow;
using rharel::efficient_reformation::core::Column;
using namespace rharel::efficient_reformation::demo;


const glm::vec2 DEFAULT_FORMATION_SPACING(3.0f, 3.0f);

Scene::Scene(const Vehicle&     default_vehicle,
             const unsigned int vehicle_count)
    : world(vehicle_count)
{
    // Initialize formations:
    const unsigned int sqrt_vc = static_cast<unsigned int>(
        sqrt(vehicle_count)
    );
    for (float f = 0.5f; f < 2.0f; f += 0.5f)
    {
        const auto f_uint = static_cast<unsigned int>(sqrt_vc * f);
        formations.push_back(std::make_unique<Column>(
            f_uint, 
            DEFAULT_FORMATION_SPACING
        ));
        formations.push_back(std::make_unique<Arrow>(
            f_uint,
            DEFAULT_FORMATION_SPACING
        ));
    }
    // Initialize vehicles:
    for (unsigned int i = 0; i < world.get_vehicle_count(); ++i)
    {
        auto& vehicle = world.get_vehicle(i) = default_vehicle;
        unit.add(vehicle);
    }
    unit.reform(formations.at(0).get());
}
void Scene::destroy() 
{ 
    if (unit.is_reforming()) { unit.cancel_reform(); }
}

void Scene::step(const float duration) 
{ 
    world.step(duration);
    unit.update();
}

void Scene::next_formation()
{
    assert(formations.size() > 0);

    active_formation_index = (active_formation_index + 1) % formations.size();
    unit.reform(formations.at(active_formation_index).get());
}

const World& Scene::get_world() const { return world; }
