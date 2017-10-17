#pragma once

#include <atomic>
#include <thread>
#include <unordered_set>

#include <glm/vec2.hpp>
#include <hungarian_algorithm/hungarian_algorithm.h>

#include "core/formations/Formation.h"
#include "Vehicle.h"


namespace rharel::efficient_reformation::demo
{
    /// Controls a group of vehicles.
    class VehicleUnit
    {
        public:
        /// Adds the specified vehicle to the unit.
        ////
        /// Returns true iff the specified vehicle was indeed not already a 
        /// member and now added.
        ///
        /// If a reformation is in progress, it is cancelled.
        bool add(Vehicle& recruit);
        /// Removes the specified vehicle from the unit.
        ///
        /// Returns true iff the specified vehicle was indeed a member and is 
        /// now removed.
        ///
        /// If a reformation is in progress, it is cancelled.
        bool remove(Vehicle& member);
        /// Returns true iff the specified vehicle is a member of the unit.
        bool has(Vehicle& query) const;

        /// Gets the number of members.
        unsigned int get_member_count() const;

        /// Reforms members using the specified formation and at the specified 
        /// position.
        ///
        /// This method is asynchronous. Use update() and is_reforming() to 
        /// query its progress.
        /// 
        /// If any reformation is already in progress, it is cancelled.
        void reform(const core::Formation* target_formation);

        /// Cancels a reformation in progress.
        ///
        /// Returns true iff a reformation was cancelled this way.
        bool cancel_reform();

        /// Collects a progress update from this unit's asynchronous 
        /// reformation (if any is ongoing).
        ///
        /// This ensures is_reforming() returns an up-to-date value.
        void update();

        /// Returns true iff reformation is in progress.
        bool is_reforming() const;

        private:
        std::unordered_set<Vehicle*> members;

        /// Enumerates asynchronous task states.
        enum class TaskStatus : int
        { 
            Cancelled,
            Complete,
            InProgress,
            Ready
        };
        std::thread               reformation_thread;
        std::atomic<TaskStatus>   reformation_status = TaskStatus::Ready;
        std::vector<glm::vec2>    reformation_sources;
        std::vector<glm::vec2>    reformation_targets;
        std::vector<unsigned int> reformation_assignment;

    };
}
