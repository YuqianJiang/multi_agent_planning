#include <PlanningAgent.h>
#include <Scenario.h>

using namespace std;
using namespace multi_agent_planning;

int main(int argc, char** argv) {

	int numAgents = 2;

	vector<PlanningAgent> agents;

	for (int i = 0; i < numAgents; ++i) {
		PlanningAgent agent(i, generateGraph(4, 4, 0));
		agents.push_back(agent);

		stringstream path;
		path << "../graphs/graph_" << 0 << ".dot";
		agent.drawGraph(path.str());

	}

	vector<vector<Edge> > actions;
	actions.push_back(agents[0].getAllActions());
	actions.push_back(agents[1].getAllActions());

	Plan plan_0;

	{
		vector<Vertex> states = agents[0].getAllStates();

		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];


		plan_0 = agents[0].computeInterDependentPlan(instance, Scenario(actions, 0, 0), vector<Plan>());
		cout << agents[0].planToString(plan_0);
	}


	Plan plan_1;

	{
		vector<Vertex> states = agents[1].getAllStates();

		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];

		plan_1 = agents[1].computeInterDependentPlan(instance, Scenario(actions, 0, 0), vector<Plan>({plan_0}));
		cout << agents[1].planToString(plan_1);
	}

	return 0;

}