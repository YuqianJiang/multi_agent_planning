#include <InteractionCostCalculator.h>
#include <plan_utils.h>

using namespace std;

namespace multi_agent_planning {

InteractionCostCalculator::InteractionCostCalculator(Scenario scenario, 
																										 const vector<Plan>& plans,
																										 int agent_id) {
	for (auto const& p : plans) {
		for (auto const& a: p.actions) {
			
			vector<Interaction> interactions = scenario.getAllInteractionsOfAction(agent_id, a.edge);
			for (auto const& interaction : interactions) {
				interactionMap[interaction.actionB].push_back(make_pair(a, interaction.cost));
			}

		}
	}
}

int InteractionCostCalculator::getInterDependentCost(Edge edge, int time, int cost) const {

	int inter_dependent_cost = cost;

	/*
	try {
		const vector<PlannedAction>& synergies = synergyMap.at(edge);

		for (auto const& action : synergies) {
			if ((action.end_time < (time + cost)) && (action.end_time > time)) {
				inter_dependent_cost = action.end_time - time;
			}
		}
	}
	catch (std::out_of_range) {}
	*/

	/*try {
		const vector<PlannedAction>& collisions = collisionMap.at(edge);

		for (auto const& action : collisions) {
			if ((action.end_time < (time + cost)) && (action.end_time > time)) {
				inter_dependent_cost += collision_cost;
			}
		}
	}
	catch (std::out_of_range) {}
	*/
	
	return inter_dependent_cost;
}

}