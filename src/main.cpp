#include <Domain.h>
#include <Solver.h>

#include <boost/graph/small_world_generator.hpp>

using namespace std;
using namespace multi_agent_planning;

typedef boost::small_world_iterator<RNGType, Graph> SWGen;

int main(int argc, char** argv) {

	int numAgents = 10;
	/*if (argc == 2) {
		numAgents = atoi(argv[0]);
	}*/

  RNGType gen(time(0));

  vector<Domain> domains;
  vector<Instance> instances;

  for (int i = 0; i < numAgents; ++i) {
  	Domain domain(SWGen(gen, 20, 5, 0.5, false), SWGen(), 20);
  	domains.push_back(domain);

  	stringstream path;
		path << "../graphs/graph_" << i << ".dot";
  	domain.drawGraph(path.str());

  	Instance instance = domain.getRandomInstance();
  	instances.push_back(instance);
  }

  Solver solver(domains);
  vector<Plan> plans = solver.solve_baseline(instances);

  for (int i = 0; i < plans.size(); ++i) {
		cout << plans[i].toString() << endl;

		WeightMap wm = domains[i].getWeightMap();
		for (auto it = plans[i].actions.begin(); it != plans[i].actions.end(); ++it) {
			cout << wm[*it] << " ";
		}
		cout << endl;
	}
  

  return 0;
}
