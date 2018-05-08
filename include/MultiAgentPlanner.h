#ifndef multi_agent_planning_MultiAgentPlanner_h__guard
#define multi_agent_planning_MultiAgentPlanner_h__guard

#include "PlanningAgent.h"
#include "Scenario.h"

namespace multi_agent_planning {

class MultiAgentPlanner {
	
public:

	MultiAgentPlanner(const std::vector<PlanningAgent>& agents) : agents(agents) {}

	std::vector<Plan> solve_baseline(std::vector<Instance> instances);

	std::vector<Plan> solve_brute_force_ordering(std::vector<Instance> instances, Scenario scenario);
	
private:
	std::vector<PlanningAgent> agents;


};

}

#endif