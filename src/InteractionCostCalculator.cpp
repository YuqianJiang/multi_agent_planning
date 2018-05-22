#include <InteractionCostCalculator.h>
#include <plan_utils.h>

using namespace std;

namespace multi_agent_planning {

InteractionCostCalculator::InteractionCostCalculator(Scenario scenario, 
																										 const vector<Plan>& plans,
																										 int agent_id) : 
	InteractionCostCalculator(scenario, plans, agent_id, 1) {
}

InteractionCostCalculator::InteractionCostCalculator(Scenario scenario, 
																										const std::vector<Plan>& plans,
																										int agent_id,
																										float alpha) : alpha(alpha) {
	for (int i = 0; i < plans.size(); ++i) {

		if (i == agent_id) continue;

		for (auto const& a: plans[i].actions) {
			
			vector<Interaction> interactions = scenario.getAllInteractionsOfAction(i, a.edge);

			for (auto const& interaction : interactions) {
				interactionMap[interaction.actionB].push_back(make_pair(a, interaction.cost));
			}

		}
	}
}

float InteractionCostCalculator::getInterDependentCost(Edge edge, int time, int cost) const {

	float inter_dependent_cost = cost;

	try {
		const PlannedActionList& interactions = interactionMap.at(edge);

		for (auto const& i : interactions) {
			if (i.first.start_time == time) {
				inter_dependent_cost += i.second * alpha;
			}
		}
	}
	catch (std::out_of_range) {}

	//cout << edge << ": " << inter_dependent_cost << endl;

	if (inter_dependent_cost < 0) {
		return 0;
	}

	return inter_dependent_cost;
}

}