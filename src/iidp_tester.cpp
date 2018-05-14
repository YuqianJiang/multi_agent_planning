#include <MultiAgentPlanner.h>

using namespace std;
using namespace multi_agent_planning;

int main(int argc, char** argv) {

	int numAgents = 2;

	vector<Graph> graphs;
	vector<PlanningAgent> agents;
	vector<vector<Edge> > actions;
	vector<Instance> instances;

	for (int i = 0; i < numAgents; ++i) {
		Graph g = generateGraph(4, 4, 0, 1);
		graphs.push_back(g);

		PlanningAgent agent(i, g);
		agents.push_back(agent);

		stringstream path;
		path << "../graphs/graph_" << i << ".dot";
		agent.drawGraph(path.str());

		/*
		vector<Edge> actions = agent.getAllActions();
		for (int j = 0; j < actions.size(); ++j) {
			cout << "cost of " << actions[j] << ": " << g[actions[j]].cost << endl;
		}
		
		vector<Vertex> states = agent.getAllStates();
		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];
		instances.push_back(instance);

		actions.push_back(agent.getAllActions());
		*/
	}

	for (int i = 0; i < numAgents; ++i) {	
		vector<Vertex> states = agents[i].getAllStates();
		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];
		instances.push_back(instance);

		actions.push_back(agents[i].getAllActions());
	}

	Scenario scenario(actions, graphs, 16);
	cout << scenario.toString() << endl;

	MultiAgentPlanner solver;

	//cout << "..........." << endl;
	//cout << scenario.toString();

	solver.solve_brute_force_ordering(agents, instances, scenario);

	/*
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	Plan plan_0;

	{
		vector<Vertex> states = agents[0].getAllStates();

		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];


		plan_0 = agents[0].computeInterDependentPlan(instance, scenario, vector<Plan>());
		cout << agents[0].planToString(plan_0);
	}


	Plan plan_1;

	{
		vector<Vertex> states = agents[1].getAllStates();

		Instance instance;
		instance.start = states[0];
		instance.goal = states[3];

		plan_1 = agents[1].computeInterDependentPlan(instance, scenario, vector<Plan>({plan_0}));
		cout << agents[1].planToString(plan_1);
	}
	*/

	return 0;

}