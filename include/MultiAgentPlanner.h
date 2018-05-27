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

	std::vector<Plan> solve_increasing_dependency(std::vector<PlanningAgent>& agents, 
																								const std::vector<Instance>& instances, 
																								const Scenario& scenario,
																								const int theta);

	std::vector<Plan> solve_best_alternative(std::vector<PlanningAgent>& agents, 
																					const std::vector<Instance>& instances, 
																					const Scenario& scenario,
																					const int theta);

	std::vector<Plan> solve_best_alternative_grouping(std::vector<PlanningAgent>& agents, 
																					const std::vector<Instance>& instances, 
																					const Scenario& scenario,
																					const int theta);

	std::tuple<int, int, int> evaluate_plans(const std::vector<Plan>& plans, 
																									const Scenario& scenario, bool print);

	int evaluate_one_plan(const std::vector<Plan>& plans, 
												const Scenario& scenario,
												const Plan plan,
												int agent_id);

private:
	std::vector<std::vector<int> > get_interacting_groups(const std::vector<Plan>& plans, 
																												const Scenario& scenario);


};

}

#endif