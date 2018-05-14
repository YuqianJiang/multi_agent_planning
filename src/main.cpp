#include <PlanningAgent.h>
#include <MultiAgentPlanner.h>

using namespace std;
using namespace multi_agent_planning;


int main(int argc, char** argv) {
	int numAgents = 1;

  vector<PlanningAgent> agents;
  vector<Instance> instances;

  for (int i = 0; i < numAgents; ++i) {
  	PlanningAgent agent(i, generateGraph(30, 5, 0.5));
  	agents.push_back(agent);

  	stringstream path;
		path << "../graphs/graph_" << i << ".dot";
  	agent.drawGraph(path.str());

  	Instance instance = agent.getRandomInstance();
  	instances.push_back(instance);
  }

  MultiAgentPlanner solver(agents);

  /*vector<Plan> plans = solver.solve_baseline(instances);

  for (int i = 0; i < plans.size(); ++i) {
		cout << plans[i].toString() << endl;

		WeightMap wm = domains[i].getWeightMap();
		for (auto it = plans[i].actions.begin(); it != plans[i].actions.end(); ++it) {
			cout << wm[*it] << " ";
		}
		cout << endl;
	}
	
	Plan plan = agents[0].computeInterDependentPlan(instances[0], Scenario(agents[0].getAllActions(), 0, 0), vector<Plan>());
  cout << agents[0].planToString(plan);
  */
  
  return 0;
}
