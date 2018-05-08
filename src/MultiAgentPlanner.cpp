#include <MultiAgentPlanner.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

vector<Plan> MultiAgentPlanner::solve_baseline(vector<Instance> instances) {
	vector<Plan> plans;

	for (int i = 0; i < agents.size(); ++i) {
		plans.push_back(agents[i].computeSingleAgentPlan(instances[i]));
	}

	return plans;
}

vector<Plan> MultiAgentPlanner::solve_brute_force_ordering(vector<Instance> instances, Scenario scenario) {
	vector<Plan> plans;

	for (int i = 0; i < agents.size(); ++i) {
		plans.push_back(agents[i].computeSingleAgentPlan(instances[i]));
	}

	return plans;
}


}