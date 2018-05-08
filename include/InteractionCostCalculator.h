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

	int getInterDependentCost(Edge edge, int time, int cost) const;

private:

	static int collision_cost;

	std::map<Edge, std::vector<PlannedAction> > collisionMap;
	std::map<Edge, std::vector<PlannedAction> > synergyMap;

};

}

#endif