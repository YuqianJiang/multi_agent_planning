#ifndef multi_agent_planning_plan_utils_h__guard
#define multi_agent_planning_plan_utils_h__guard

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/small_world_generator.hpp>
#include <boost/random.hpp>

namespace multi_agent_planning {

class Scenario;

struct Action {

	Action() : cost(), inter_dependent_cost() {}
	
	int cost;
	float inter_dependent_cost;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	Action > Graph;

typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;

typedef boost::mt19937 RNGType;

typedef boost::small_world_iterator<RNGType, Graph> SWGen;

struct Instance {
	Vertex start;
	Vertex goal;
};

struct PlannedAction {
	Edge edge;
	Vertex source;
	Vertex target;
	int start_time;
	int action_cost;
};

struct Plan {
	std::vector<PlannedAction> actions;
	float cost;
};

int getRndInt(int max);

int getRndInt(int min, int max);

Graph generateGraph(int numV, int numConnected, float prob);

Graph generateGraph(int numV, int numConnected, float prob, int cost);

}



#endif