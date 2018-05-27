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

			vector<Interaction> interactions = scenario.getInteractionsOnAgent(i, a.edge, agent_id);

			for (auto const& interaction : interactions) {
					// cout << interaction.toString() << endl;
					interactionMap[interaction.actionB].push_back(make_tuple(i, a, interaction.cost));
			}

		}
	}
}

float InteractionCostCalculator::getInterDependentCost(Edge edge, int time, int cost) const {

	float inter_dependent_cost = cost;

	try {
		const PlannedActionList& interactions = interactionMap.at(edge);

		for (auto const& i : interactions) {
			if (get<1>(i).start_time == time) {
				inter_dependent_cost += get<2>(i) * alpha;
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

std::tuple<int, int, int> InteractionCostCalculator::getCostWithInteractions(Edge edge, int time, int cost) const {

	int inter_dependent_cost = cost;
	int num_conflicts = 0;
	int num_synergies = 0;

	try {
		const PlannedActionList& interactions = interactionMap.at(edge);

		for (auto const& i : interactions) {
			if (get<1>(i).start_time == time) {

				if (get<2>(i) > 0) {
					num_conflicts++;
				}
				else if (inter_dependent_cost > 0) {
					num_synergies++;
				}

				inter_dependent_cost += get<2>(i) * alpha;
			}
		}
	}
	catch (std::out_of_range) {}

	if (inter_dependent_cost < 0) {
		inter_dependent_cost = 0;
	}

	return make_tuple(inter_dependent_cost, num_conflicts, num_synergies);
}

vector<int> InteractionCostCalculator::getInteractingAgents(Edge edge, int time) const {
	vector<int> agents;

	try {
		const PlannedActionList& interactions = interactionMap.at(edge);

		for (auto const& i : interactions) {
			if (get<1>(i).start_time == time) {
				//cout << get<0>(i) << " " << get<1>(i).edge << endl;
				agents.push_back(get<0>(i));
			}
		}
	}
	catch (std::out_of_range) {
		return agents;
	}

}

}