#include <MultiAgentPlanner.h>

using namespace std;
using namespace multi_agent_planning;

int main(int argc, char** argv) {

	int numAgents = 5;
	int numVertices = 4;
	int numConnected = 4;
	int numInteractions = 160;
	int numConflicts = 80;
	int numSynergies = 80;
	float prob = 0;

	vector<Graph> graphs;
	vector<PlanningAgent> agents;
	vector<vector<Edge> > actions;
	vector<Instance> instances;

	for (int i = 0; i < numAgents; ++i) {
		Graph g = generateGraph(numVertices, numConnected, prob, 1);
		graphs.push_back(g);

		PlanningAgent agent(i, g);
		agents.push_back(agent);

		stringstream path;
		path << "../graphs/graph_" << i << ".dot";
		agent.drawGraph(path.str());
	}

	for (int i = 0; i < numAgents; ++i) {	
		vector<Vertex> states = agents[i].getAllStates();
		Instance instance = agents[i].getRandomInstance();
		instances.push_back(instance);

		actions.push_back(agents[i].getAllActions());
	}

	//Scenario scenario(actions, graphs, numInteractions);
	Scenario scenario(actions, graphs, numConflicts, numSynergies);
	cout << scenario.toString() << endl;

	MultiAgentPlanner solver;

	cout << "---------------------Baseline---------------------" << endl;

	vector<Plan> plans = solver.solve_baseline(agents, instances);
	cout << endl;
	solver.evaluate_plans(plans, scenario, true);

	cout << "---------------------Best Ordering---------------------" << endl;

	plans = solver.solve_brute_force_ordering(agents, instances, scenario);
	cout << endl;
	solver.evaluate_plans(plans, scenario, true);

	cout << "---------------------Increasing Dependency---------------------" << endl;

	plans = solver.solve_increasing_dependency(agents, instances, scenario, 4);
	cout << endl;
	solver.evaluate_plans(plans, scenario, true);

	cout << "---------------------Best Alternative---------------------" << endl;

	plans = solver.solve_best_alternative(agents, instances, scenario, 4);
	cout << endl;
	solver.evaluate_plans(plans, scenario, true);

	return 0;

}