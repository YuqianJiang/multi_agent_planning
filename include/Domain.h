#ifndef multi_agent_planning_Domain_h__guard
#define multi_agent_planning_Domain_h__guard

#include <boost/graph/adjacency_list.hpp>
#include <boost/random.hpp>

namespace multi_agent_planning {

struct Action {
	Action(int cost) : cost(cost) {}
	int cost;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;
typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;

typedef boost::mt19937 RNGType;

struct Instance {
	Vertex start;
	Vertex goal;
};

struct Plan {
	std::list<Vertex> states;
	std::list<Edge> actions;
	std::list<float> distances;

	std::string toString() const;
};

class Domain {
public:

	template <class EdgeIterator>
	Domain(EdgeIterator first, EdgeIterator last, int numV) : 
		graph(first, last, numV) 
	{
		WeightMap wm = get(boost::edge_weight, graph);
		for (Graph::edge_iterator eIt = edges(graph).first; eIt != edges(graph).second; ++eIt) {
			wm[*eIt] = 1;
		}
	}

	Graph getGraph() const { return graph; }

	void drawGraph(std::string path);

	Plan getPlan(Instance instance, WeightMap weightmap);

	Instance getRandomInstance();

	WeightMap getWeightMap() {
		return get(boost::edge_weight, graph);
	}

private:

	Graph graph;

	static RNGType gen;

	Vertex getRandomVertex();

	Vertex getRandomConnectedVertex(Vertex source);
};

}



#endif