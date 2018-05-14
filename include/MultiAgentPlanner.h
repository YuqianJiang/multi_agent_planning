#ifndef multi_agent_planning_MultiAgentPlanner_h__guard
#define multi_agent_planning_MultiAgentPlanner_h__guard

#include "PlanningAgent.h"
#include "Scenario.h"

namespace multi_agent_planning {

class MultiAgentPlanner {
	
public:

	MultiAgentPlanner() {}

	std::vector<Plan> solve_baseline(std::vector<PlanningAgent>& agents, 
																	const std::vector<Instance>& instances);

	std::vector<Plan> solve_brute_force_ordering(std::vector<PlanningAgent>& agents, 
																							const std::vector<Instance>& instances, 
																							const Scenario& scenario);

	int evaluate_plans(const std::vector<Plan>& plans, const Scenario& scenario, bool print);


};

}

#endif