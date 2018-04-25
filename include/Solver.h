#ifndef multi_agent_planning_Solver_h__guard
#define multi_agent_planning_Solver_h__guard

#include "Domain.h"
#include "Scenario.h"

namespace multi_agent_planning {

class Solver {
	
public:

	Solver(const std::vector<Domain>& domains) : domains(domains) {}

	std::vector<Plan> solve_baseline(std::vector<Instance> instances);

	std::vector<Plan> solve_brute_force_ordering(std::vector<Instance> instances, Scenario scenario);

private:
	std::vector<Domain> domains;

	Plan inter_dependent_planning(int agent_id, Instance instance, Scenario scenario, std::vector<Plan> plans);

};

}

#endif