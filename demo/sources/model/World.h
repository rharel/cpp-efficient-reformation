#pragma once

#include <vector>

#include "Vehicle.h"


namespace rharel::efficient_reformation::demo
{
    /// Evaluates the state of vehicles embedded in a plane over time.
    class World
    {
        public:
        /// Creates a new simulation with the specified number of vehicles.
        explicit World(unsigned int vehicle_count);

        /// Steps the simulation forward in time by the specified duration.
        /// Has no effect for durations <= 0.
        void step(float duration);

        /// Gets the number of vehicles in the simulation.
        unsigned int get_vehicle_count() const;

        /// Gets the vehicle with the specified index (const version).
        const Vehicle& get_vehicle(unsigned int index) const;
        /// Gets the vehicle with the specified index.
              Vehicle& get_vehicle(unsigned int index);

        private:
        /// Steps the specified vehicle forward in time by the specified 
        /// duration.
        ///
        /// The vehicle advances towards its target (but not beyond it).
        void step_vehicle(Vehicle& vehicle, float duration);

        std::vector<Vehicle> vehicles;
    };
}
