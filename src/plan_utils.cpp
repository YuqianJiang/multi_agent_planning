#include <plan_utils.h>
#include <Scenario.h>
#include <boost/graph/random.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>
#include <time.h>

using namespace boost;
using namespace std;

namespace multi_agent_planning {

static bool seed_set = false;
static RNGType gen;

int getRndInt(int max) {
	getRndInt(0, max);
}

int getRndInt(int min, int max) {
	if (!seed_set) {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		gen.seed((time_t)ts.tv_nsec);
		seed_set = true;
		//cout << (time_t)ts.tv_nsec << endl;
	}

	uniform_int<> distrib(min, max);
  variate_generator<RNGType&, uniform_int<> > rand_gen(gen, distrib);
  std::size_t n = rand_gen();
}

Graph generateGraph(int numV, int numConnected, float prob, int cost) {
	Graph graph = Graph(SWGen(gen, numV, numConnected, prob, false), SWGen(), numV);
	for (Graph::edge_iterator eIt = edges(graph).first; eIt != edges(graph).second; ++eIt) {
		graph[*eIt].cost = cost;
	}

	return graph;
}

}