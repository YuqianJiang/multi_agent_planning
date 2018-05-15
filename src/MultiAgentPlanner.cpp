#include <MultiAgentPlanner.h>
#include <InteractionCostCalculator.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

vector<Plan> MultiAgentPlanner::solve_baseline(vector<PlanningAgent>& agents, 
																	            const vector<Instance>& instances) {
	vector<Plan> plans;

	for (int i = 0; i < agents.size(); ++i) {
		Plan plan = agents[i].computeSingleAgentPlan(instances[i]);
		plans.push_back(plan);

		cout << agents[i].planToString(plan);
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

		int total_cost = evaluate_plans(plans, scenario, false).second;

		if (total_cost < best_cost) {
			bestPlans = plans;
			best_cost = total_cost;
		}

	} while (next_permutation(planningOrder.begin(), planningOrder.end()));

	return bestPlans;
}

vector<Plan> MultiAgentPlanner::solve_increasing_dependency(std::vector<PlanningAgent>& agents, 
																														const std::vector<Instance>& instances, 
																														const Scenario& scenario,
																														const int theta) {
	vector<Plan> plans(agents.size(), Plan());

	for (int j = 0; j <= theta; ++j) {
		float alpha = j / (theta * 1.0);
		vector<Plan> currentPlans;
		
		cout << "!!!!!!!! Planning dependency: " << alpha << " !!!!!!!!" << endl;

		for (int i = 0; i < agents.size(); ++i) {
			Plan plan = agents[i].computeInterDependentPlan(instances[i], scenario, plans, alpha);

			currentPlans.push_back(plan);

			cout << agents[i].planToString(plan);
		}

		copy(currentPlans.begin(), currentPlans.end(), plans.begin());

	}
		
	return plans;
}

vector<Plan> MultiAgentPlanner::solve_best_alternative(std::vector<PlanningAgent>& agents, 
																											const std::vector<Instance>& instances, 
																											const Scenario& scenario,
																											const int theta) {
	
	vector<Plan> plans = solve_baseline(agents, instances);
	vector<int> costs = evaluate_plans(plans, scenario, false).first;

	int iteration_counter = 1;
	bool convergence = false;

	while ((! convergence) && (iteration_counter < theta)) {
		// TODO: find subsets

		vector<Plan> alternativePlans;
		vector<int> alternativeCosts;

		cout << "!!!!!!!!!!!! Iteration " << iteration_counter << " !!!!!!!!!!!!" << endl;

		for (int i = 0; i < agents.size(); ++i) {
			Plan plan = agents[i].computeInterDependentPlan(instances[i], scenario, plans);

			alternativePlans.push_back(plan);

			cout << agents[i].planToString(plan);

			alternativeCosts.push_back(plan.cost);

			//int alt_plan_cost = evaluate_one_plan(plans, scenario, plan, i);
			
			//alternativeCosts.push_back(alt_plan_cost);

			//cout << "Inter-dependent plan cost: " << alt_plan_cost << endl;
		}

		int best_alt = 0;
		int best_diff = 0;
		convergence = true;
		
		for (int i = 0; i < agents.size(); ++i) {
			int cost_diff = costs[i] - alternativeCosts[i];

			if (cost_diff > 0) {
				convergence = false;
			}
			
			if (cost_diff > best_diff) {
				best_diff = cost_diff;
				best_alt = i;
			}
		}

		if (! convergence) {
			cout << "Agent " << best_alt << " wins!" << endl;
		}

		plans[best_alt] = alternativePlans[best_alt];
		costs[best_alt] = alternativeCosts[best_alt];

		iteration_counter++;

	}

	return plans;
}

pair<vector<int>, int> MultiAgentPlanner::evaluate_plans(const vector<Plan>& plans, 
																												const Scenario& scenario, bool print) {
	vector<int> costs(plans.size());
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

		costs[id] = plan_cost;
		total_cost += plan_cost;

		ss << "  Plan cost: " << plan_cost << endl;
	}

	ss << "************Total cost: " << total_cost << "************" << endl;
	
	if (print)
		cout << ss.str() << endl;

	return make_pair(costs, total_cost);
}

int MultiAgentPlanner::evaluate_one_plan(const std::vector<Plan>& plans, 
																				const Scenario& scenario,
																				const Plan plan,
																				int agent_id) {

	InteractionCostCalculator calc(scenario, plans, agent_id);
	int plan_cost = 0;

	for (const auto& act : plan.actions) {
		int cost = calc.getInterDependentCost(act.edge, act.start_time, act.action_cost);
		plan_cost += cost;
	}

	return plan_cost;
}


}