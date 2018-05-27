#include <MultiAgentPlanner.h>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace multi_agent_planning;

int main(int argc, char** argv) {

	int numAgents = 30;
	int numVertices = 10;
	int numConnected = 4;
	float prob = 0.2;
	int numInteractions;
	int theta;

	int problem_id = 0;

	if (argc == 2) {
		numInteractions = numAgents * 100;
		theta = atoi(argv[1]) * numAgents;
	}
	else if (argc == 3) {
		problem_id = atoi(argv[2]);
		numInteractions = numAgents * 100;
		theta = atoi(argv[1]) * numAgents;
	}
	else {
		cerr << "usage: experiment_agents <theta> [<problem_id>]" << endl;
		return 1;
	}

	stringstream output_path_ss;
	output_path_ss << "../results/theta/result_" << problem_id << ".csv";
	ofstream out(output_path_ss.str().c_str());

	stringstream detail_output_path_ss;
	detail_output_path_ss << "../results/theta/detail_" << problem_id;

	ofstream detail_out(detail_output_path_ss.str());
	std::streambuf* backup = cout.rdbuf(detail_out.rdbuf());

	stringstream graphs_path_ss; 
	graphs_path_ss << "../results/theta/graphs_" << problem_id;
	boost::filesystem::create_directories(graphs_path_ss.str());

	//out << "problem_id" << "," << "num_agents" << "," << "num_vertices" << "," << "num_connected" << "," << "prob" << ",";
	//out << "num_interactions" << "," << "theta" << "," << "baseline" << "," << "increasing_dependency" << "," << "best_alternative" << ",";
	//out << "best_alternative_grouping" << endl;

	//out << problem_id << "," << numAgents << "," << numVertices << "," << numConnected << "," << prob << ",";
	//out << numInteractions << "," << theta << ",";

	out << "problem_id" << "," << "theta" << ","
			<< "independent_cost" << "," << "independent_conflicts" << "," << "independent_synergies" << ","
			<< "increasing_dependency_cost" << "," << "increasing_dependency_conflicts" << "," << "increasing_dependency_synergies" << ","
			<< "best_alternative_cost" << "," << "best_alternative_conflicts" << "," << "best_alternative_synergies" << ","
			<< "best_alternative_grouping_cost" << "," << "best_alternative_grouping_conflicts" << "," << "best_alternative_grouping_synergies"
			<< endl;

	out << problem_id << "," << theta << ",";

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
		path << graphs_path_ss.str() << "/graph_" << i << ".dot";
		agent.drawGraph(path.str());
	}

	for (int i = 0; i < numAgents; ++i) {	
		Instance instance = agents[i].getRandomInstance();
		instances.push_back(instance);

		actions.push_back(agents[i].getAllActions());
	}

	Scenario scenario(actions, graphs, numInteractions);

	cout << scenario.toString() << endl;

	MultiAgentPlanner solver;

	int cost;
	int num_conflicts;
	int num_synergies;

	cout << "---------------------Baseline---------------------" << endl;

	vector<Plan> plans = solver.solve_baseline(agents, instances);
	cout << endl;
	tie(cost, num_conflicts, num_synergies) = solver.evaluate_plans(plans, scenario, true);
	out << cost << "," << num_conflicts << "," << num_synergies << ",";

	cout << "---------------------Increasing Dependency---------------------" << endl;

	plans = solver.solve_increasing_dependency(agents, instances, scenario, theta);
	cout << endl;
	tie(cost, num_conflicts, num_synergies) = solver.evaluate_plans(plans, scenario, true);
	out << cost << "," << num_conflicts << "," << num_synergies << ",";

	cout << "---------------------Best Alternative---------------------" << endl;

	plans = solver.solve_best_alternative(agents, instances, scenario, theta);
	cout << endl;
	tie(cost, num_conflicts, num_synergies) = solver.evaluate_plans(plans, scenario, true);
	out << cost << "," << num_conflicts << "," << num_synergies << ",";

	cout << "---------------------Best Alternative With Grouping---------------------" << endl;

	plans = solver.solve_best_alternative_grouping(agents, instances, scenario, 4);
	cout << endl;
	tie(cost, num_conflicts, num_synergies) = solver.evaluate_plans(plans, scenario, true);
	out << cost << "," << num_conflicts << "," << num_synergies << endl;

	/*cout << "---------------------Best Ordering---------------------" << endl;

	plans = solver.solve_brute_force_ordering(agents, instances, scenario);
	cout << endl;
	solver.evaluate_plans(plans, scenario, true);
	*/
	
	out.close();
	detail_out.close();
	cout.rdbuf(backup);

	return 0;

}