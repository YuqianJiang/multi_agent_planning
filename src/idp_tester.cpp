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

	vector<Vertex> states = agents[0].getAllStates();

	Instance instance;
	instance.start = states[0];
	instance.goal = states[3];

	vector<vector<Edge> > actions;
	actions.push_back(agents[0].getAllActions());

	Plan plan = agents[0].computeInterDependentPlan(instance,
																							Scenario(actions, 0, 0),
																							vector<Plan>());
	cout << agents[0].planToString(plan);

	return 0;

}