#include <MultiAgentPlanner.h>
#include <InteractionCostCalculator.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

vector<Plan> MultiAgentPlanner::solve_baseline(vector<PlanningAgent>& agents, 
																	            const vector<Instance>& instances) {
	vector<Plan> plans;

	for (int i = 0; i < agents.size(); ++i) {
		plans.push_back(agents[i].computeSingleAgentPlan(instances[i]));
	}

	return plans;
}

vector<Plan> MultiAgentPlanner::solve_brute_force_ordering(vector<PlanningAgent>& agents, 
																													const vector<Instance>& instances, 
																													const Scenario& scenario) {

	vector<Plan> bestPlans(agents.size(), Plan());

	int best_cost = numeric_limits<int>::max();

	vector<int> planningOrder(agents.size());
	iota(planningOrder.begin(), planningOrder.end(), 0);

	do {
		cout << "!!!!!!!!!! Agent ordering: ";
		copy(planningOrder.begin(), planningOrder.end(), 
			ostream_iterator<int>(cout, " "));
		cout << "!!!!!!!!!!" << endl;

		vector<Plan> plans(agents.size(), Plan());

		for (int id : planningOrder) {
			Plan plan = agents[id].computeInterDependentPlan(instances[id], scenario, plans);
			
			plans[id] = plan;

			cout << agents[id].planToString(plan);

		}

		int total_cost = evaluate_plans(plans, scenario, true);

		if (total_cost < best_cost) {
			bestPlans = plans;
			best_cost = total_cost;
		}

	} while (next_permutation(planningOrder.begin(), planningOrder.end()));

	return bestPlans;
}

int MultiAgentPlanner::evaluate_plans(const vector<Plan>& plans, const Scenario& scenario, bool print) {
	int total_cost = 0;

	stringstream ss;
	ss << "**********Evaluating plans**********" << endl;

	for (int id = 0; id < plans.size(); ++id) {
		ss << " -----Agent " << id << "-----" << endl;

		InteractionCostCalculator calc(scenario, plans, id);
		int plan_cost = 0;

		for (const auto& act : plans[id].actions) {
			int cost = calc.getInterDependentCost(act.edge, act.start_time, act.action_cost);
			plan_cost += cost;

			ss << "  " << act.edge << ": " << cost << endl;
		}

		total_cost += plan_cost;

		ss << "Plan cost: " << plan_cost << endl;
	}

	ss << "************Total cost: " << total_cost << "************" << endl;
	
	if (print)
		cout << ss.str() << endl;

	return total_cost;
}


}