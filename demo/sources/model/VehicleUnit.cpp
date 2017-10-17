#include <glm/geometric.hpp>
#include <hungarian_algorithm/hungarian_algorithm.h>

#include "VehicleUnit.h"


using rharel::efficient_reformation::core::Formation;
using namespace rharel::efficient_reformation::demo;


bool VehicleUnit::add(Vehicle& recruit)
{
    if (is_reforming()) { cancel_reform(); }
    return members.insert(&recruit).second;
}
bool VehicleUnit::remove(Vehicle& member)
{
    if (is_reforming()) { cancel_reform(); }
    return members.erase(&member) > 0;
}
bool VehicleUnit::has(Vehicle& query) const
{
    return members.find(&query) != members.end();
}

unsigned int VehicleUnit::get_member_count() const
{
    return members.size();
}

void VehicleUnit::reform(const Formation* target_formation)
{
    if (is_reforming()) { cancel_reform(); }

    const unsigned int n = members.size();

    // Initialize source positions:
    reformation_sources.resize(n);
    {
        int i = 0;
        for (Vehicle* vehicle : members)
        {
            reformation_sources.at(i) = vehicle->position;
            ++i;
        }
    }
    // Initialize target positions:
    reformation_targets.resize(n);
    target_formation->get_member_positions(n, reformation_targets.data());
    // Initialize solution buffer:
    reformation_assignment.resize(n);

    // Solve the minimum cost assignment problem asynchronously:
    reformation_status = TaskStatus::InProgress;
    reformation_thread = std::thread([this, n]
    {
        using rharel::hungarian_algorithm::Problem;
        using std::vector;

        // Compute cost matrix:
        vector<vector<unsigned int>> C(n);
        vector<unsigned int*>        C_row_pointers(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            C[i].resize(n);
            C_row_pointers[i] = C[i].data();
        }
        for (unsigned int i = 0; i < n; ++i)
        {
            for (unsigned int j = 0; j < n; ++j)
            {
                C[i][j] = static_cast<unsigned int>(glm::dot(
                    reformation_sources[i], 
                    reformation_targets[j]
                ));
            }
        }
        unsigned int** C_raw = C_row_pointers.data();

        // Create problem and solve it step by step:
        rharel::hungarian_algorithm::Problem problem(n, C_raw);
        while (reformation_status != TaskStatus::Cancelled && 
               !problem.step());

        // Retrieve solution:
        problem.solve(reformation_assignment.data());

        reformation_status = TaskStatus::Complete;
    });
}
bool VehicleUnit::cancel_reform()
{
    if (is_reforming())
    {
        reformation_status = TaskStatus::Cancelled;
        reformation_thread.join();

        for (Vehicle* vehicle : members) 
        { 
            vehicle->target = vehicle->position; 
        }

        return true;
    }
    else { return false; }
}

void VehicleUnit::update()
{
    if (reformation_status == TaskStatus::Complete)
    {
        reformation_thread.join();
        int i = 0;
        for (Vehicle* vehicle : members)
        {
            const auto j = reformation_assignment.at(i);
            vehicle->target = reformation_targets.at(j);
            ++i;
        }
        reformation_status = TaskStatus::Ready;
    }
}

bool VehicleUnit::is_reforming() const
{
    return reformation_status == TaskStatus::InProgress;
}
