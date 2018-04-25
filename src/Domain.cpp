#include <Domain.h>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/random.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>

#include <iostream>
#include <fstream>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

RNGType Domain::gen(time(0));

template < typename VertexAndEdgeListGraph >
void draw(string path, const VertexAndEdgeListGraph& graph) {
	ofstream myGraphFile;
		
  myGraphFile.open(path);
  write_graphviz(myGraphFile, graph);
}
	
void Domain::drawGraph(string path) {
	draw(path, graph);
}

struct found_goal {};

template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
public:
  astar_goal_visitor(Vertex goal) : m_goal(goal) {}
  template <class Graph>
  void examine_vertex(Vertex u, Graph& g) {
    if(u == m_goal)
      throw found_goal();
  }
private:
  Vertex m_goal;
};

Plan Domain::getPlan(Instance instance, WeightMap weightmap) {

	Plan plan;

	vector<Vertex> p(num_vertices(graph));
	vector<float> d(num_vertices(graph));

	try {
		astar_search(
			graph, instance.start, 
			astar_heuristic<Graph, float>(), 
			weight_map(weightmap).
			predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, graph))).
  	  distance_map(make_iterator_property_map(d.begin(), get(vertex_index, graph))).
  	  visitor(astar_goal_visitor<Vertex>(instance.goal))
  	);
  }
  catch(found_goal fg) {

  	for (Vertex v = instance.goal;; v = p[v]) {
  	  plan.states.push_front(v);
  	  plan.distances.push_front(d[v]);
  	  if (p[v] != v) {
  	  	plan.actions.push_front(edge(p[v], v, graph).first);
  	  }
  	  else break;
  	}

  }

	return plan;
}

Vertex Domain::getRandomVertex() {
	uniform_int<> distrib(0, num_vertices(graph)-1);
  variate_generator<RNGType&, uniform_int<> > rand_gen(gen, distrib);
  std::size_t n = rand_gen();
	Graph::vertex_iterator i = vertices(graph).first;
  return *(next(i, n));
}

Vertex Domain::getRandomConnectedVertex(Vertex source) {
	vector<Vertex> p(num_vertices(graph));
	vector<float> d(num_vertices(graph), -1);

  breadth_first_search(graph, source, 
              visitor(make_bfs_visitor(record_distances(d.data(), on_tree_edge())))
  );

  typedef filtered_graph<Graph, keep_all, std::function<bool(Graph::vertex_descriptor)>> FilteredGraph;

	FilteredGraph fg(graph, {}, [&](Graph::vertex_descriptor vd) { return d[vd] != -1; });

  stringstream path;
	path << "../graphs/graph_filtered" << ".dot";
  draw(path.str(), fg);

  FilteredGraph::vertex_iterator vi,ve;
  vi = vertices(fg).first;
  ve = vertices(fg).second;

  vector<FilteredGraph::vertex_descriptor> connected;
  copy(vi, ve, back_inserter(connected));

  uniform_int<> distrib(0, connected.size()-1);
  variate_generator<RNGType&, uniform_int<> > rand_gen(gen, distrib);
  size_t n = rand_gen();

	return connected[n];

}

Instance Domain::getRandomInstance() {
	Instance instance;
	instance.start = getRandomVertex();
	instance.goal = getRandomConnectedVertex(instance.start);

	return instance;
}

string Plan::toString() const {
	stringstream ss;
	for (auto i = this->states.begin(); i != this->states.end(); ++i) {
		ss << *i << " ";
	}

	return ss.str();
}

}