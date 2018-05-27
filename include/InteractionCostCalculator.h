#ifndef multi_agent_planning_InteractionCostCalculator_h__guard
#define multi_agent_planning_InteractionCostCalculator_h__guard

#include <Scenario.h>


namespace multi_agent_planning {

class InteractionCostCalculator {

public:

	InteractionCostCalculator(Scenario scenario, 
														const std::vector<Plan>& plans,
														int agent_id);

	InteractionCostCalculator(Scenario scenario, 
														const std::vector<Plan>& plans,
														int agent_id,
														float alpha);

	float getInterDependentCost(Edge edge, int time, int cost) const;

	std::tuple<int, int, int> getCostWithInteractions(Edge edge, int time, int cost) const;

	std::vector<int> getInteractingAgents(Edge, int time) const;

private:

	typedef std::vector<std::tuple<int, PlannedAction, int> > PlannedActionList;
	std::map<Edge, PlannedActionList > interactionMap;

	float alpha;

};

}

#endif