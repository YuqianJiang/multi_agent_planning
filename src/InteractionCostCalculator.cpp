#include <InteractionCostCalculator.h>
#include <plan_utils.h>

using namespace std;

namespace multi_agent_planning {

int InteractionCostCalculator::collision_cost(100);

InteractionCostCalculator::InteractionCostCalculator(Scenario scenario, 
																										 const vector<Plan>& plans,
																										 int agent_id) {
	for (auto const& p : plans) {
		for (auto const& a: p.actions) {
			AgentAction aa(agent_id, a.edge);
			
			vector<AgentAction> collisions = scenario.getPotentialCollisions(aa);
			for (auto const& action : collisions) {
				collisionMap[action.edge].push_back(a);
			}

			vector<AgentAction> synergies = scenario.getPotentialSynergies(aa);
			for (auto const& action : synergies) {
				synergyMap[action.edge].push_back(a);
			}

		}
	}
}

int InteractionCostCalculator::getInterDependentCost(Edge edge, int time, int cost) const {

	int inter_dependent_cost = cost;

	try {
		const vector<PlannedAction>& synergies = synergyMap.at(edge);

		for (auto const& action : synergies) {
			if ((action.end_time < (time + cost)) && (action.end_time > time)) {
				inter_dependent_cost = action.end_time - time;
			}
		}
	}
	catch (std::out_of_range) {}

	try {
		const vector<PlannedAction>& collisions = collisionMap.at(edge);

		for (auto const& action : collisions) {
			if ((action.end_time < (time + cost)) && (action.end_time > time)) {
				inter_dependent_cost += collision_cost;
			}
		}
	}
	catch (std::out_of_range) {}
	
	return inter_dependent_cost;
}

}