#pragma once

#include <memory>
#include <vector>

#include "VehicleUnit.h"
#include "World.h"


namespace rharel::efficient_reformation::demo
{
    /// Controls the demo scene.
    ///
    /// In the scene, all vehicles of the simulation form a single unit, and 
    /// this unit may cycle through a predetermined set of formations.
    class Scene
    {
        public:
        /// Creates a new scene.
        explicit Scene(const Vehicle& default_vehicle,
                       unsigned int   vehicle_count = 100);
        
        /// Destructs the scene.
        void destroy();

        /// Steps the simulation forward in time by the specified duration.
        /// Has no effect for durations <= 0.
        void step(float duration);

        /// Cycles the active formation.
        void next_formation();

        /// Gets the simulation world.
        const World& get_world() const;

        private:
        World       world;
        VehicleUnit unit;

        std::vector<std::unique_ptr<core::Formation>> formations;
        unsigned int active_formation_index = 0;;
    };
}
