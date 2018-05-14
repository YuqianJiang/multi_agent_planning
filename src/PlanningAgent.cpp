#include <PlanningAgent.h>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <Scenario.h>
#include <InteractionCostCalculator.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

PlanningAgent::PlanningAgent(int agent_id, Graph g) : 
		agent_id(agent_id), graph(g) {
}

template < typename VertexAndEdgeListGraph >
void draw(string path, const VertexAndEdgeListGraph& graph) {
	ofstream myGraphFile;
		
  myGraphFile.open(path);
  write_graphviz(myGraphFile, graph);
}
	
void PlanningAgent::drawGraph(string path) {
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

Plan PlanningAgent::computeSingleAgentPlan(const Instance instance) {

	Plan plan;

	vector<Vertex> p(num_vertices(graph));
	vector<int> d(num_vertices(graph));

	try {
		astar_search(
			graph, instance.start, 
			astar_heuristic<Graph, float>(), 
			weight_map(get(&Action::cost, graph)).
			predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, graph))).
  	  distance_map(make_iterator_property_map(d.begin(), get(vertex_index, graph))).
  	  visitor(astar_goal_visitor<Vertex>(instance.goal))
  	);
  }
  catch(found_goal fg) {

  	planHelper(instance.goal, p, d, plan);

  }

	return plan;
}

template <class Vertex>
class idp_visitor : public boost::default_astar_visitor
{
public:

  idp_visitor(Vertex goal, int& time, const vector<Vertex>& p, const InteractionCostCalculator& calc, Graph* graph) : m_goal(goal), time(time), p(p), calc(calc), graph(graph) {}
  
  template <class Graph>
  void examine_vertex(Vertex u, Graph& g) {
    if(u == m_goal)
      throw found_goal();
    
    time = 0;
    for (Vertex v = u; v != p[v]; v = p[v]) {
    	Vertex s = p[v];
    	Edge e = edge(s, v, g).first;
    	time++;
    }
  }

  template <class Edge, class Graph>
  void examine_edge(Edge e, Graph& g) {
    (*graph)[e].inter_dependent_cost = calc.getInterDependentCost(e, time, g[e].cost);
  }

private:

  Vertex m_goal;
  int& time;
  const vector<Vertex>& p;
  const InteractionCostCalculator& calc;
  Graph* graph;
};


Plan PlanningAgent::computeInterDependentPlan(const Instance& instance, const Scenario& scenario, 
																							const vector<Plan>& plans) {

	/*auto wmap = 
		make_transform_value_property_map(
			[](Action& a) { return a.cost; }, 
			get(boost::edge_bundle, graph));

	for (Graph::edge_iterator eIt = edges(graph).first; eIt != edges(graph).second; ++eIt) {
			cout << wmap[*eIt] << " ";
	}

	cout << endl;*/

	cout << "Planning agent " << agent_id << "..." << endl;

	Plan plan;

	vector<Vertex> p(num_vertices(graph));
	vector<int> d(num_vertices(graph));
	int time = 0;
	InteractionCostCalculator calc(scenario, plans, agent_id);

	try {
		astar_search(
			graph, instance.start, 
			astar_heuristic<Graph, int>(), 
			weight_map(get(&Action::inter_dependent_cost, graph)).
			predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, graph))).
  	  distance_map(make_iterator_property_map(d.begin(), get(vertex_index, graph))).
  	  visitor(idp_visitor<Vertex>(instance.goal, time, p, calc, &graph))
  	);
	}
  catch(found_goal fg) {

  	planHelper(instance.goal, p, d, plan);

  }

	return plan;
}

Vertex PlanningAgent::getRandomVertex() {
  std::size_t n = getRndInt(num_vertices(graph)-1);
	Graph::vertex_iterator i = vertices(graph).first;
  return *(next(i, n));
}

Vertex PlanningAgent::getRandomConnectedVertex(Vertex source) {
	vector<Vertex> p(num_vertices(graph));
	vector<int> d(num_vertices(graph), -1);

  breadth_first_search(graph, source, 
              visitor(make_bfs_visitor(record_distances(d.data(), on_tree_edge())))
  );

  typedef filtered_graph<Graph, keep_all, std::function<bool(Graph::vertex_descriptor)>> FilteredGraph;

	FilteredGraph fg(graph, {}, [&](Graph::vertex_descriptor vd) { return d[vd] != -1; });

  /*stringstream path;
	path << "../graphs/graph_filtered" << ".dot";
  draw(path.str(), fg);*/

  FilteredGraph::vertex_iterator vi,ve;
  vi = vertices(fg).first;
  ve = vertices(fg).second;

  vector<FilteredGraph::vertex_descriptor> connected;
  copy(vi, ve, back_inserter(connected));

  size_t n = getRndInt(connected.size()-1);

	return connected[n];

}

Instance PlanningAgent::getRandomInstance() {
	Instance instance;
	instance.start = getRandomVertex();
	instance.goal = getRandomConnectedVertex(instance.start);

	return instance;
}

vector<Edge> PlanningAgent::getAllActions() const {

	vector<Edge> allActions;

	copy(edges(graph).first, edges(graph).second, back_inserter(allActions));

	return allActions;
}

vector<Vertex> PlanningAgent::getAllStates() const {
	vector<Vertex> states;

	copy(vertices(graph).first, vertices(graph).second, 
						back_inserter(states));

	return states;
}

string PlanningAgent::planToString(const Plan& plan) {
	stringstream ss;

	//ss << "----------Plan----------" << endl;

	ss << "states: ";
	
	auto it = plan.actions.begin();
	ss << it->source << " ";
	for (; it != plan.actions.end(); ++it) {
		ss << it->target << " ";
	}

	ss << endl;

	/*
	it = plan.actions.begin();
	for (; it != plan.actions.end(); ++it) {
		ss << "time " << it->start_time << ": " << it->edge << endl;
	}
	*/
	

	ss << "cost = " << plan.cost << endl;

	ss << "------------------------" << endl;

	return ss.str();
}

void PlanningAgent::planHelper(Vertex v, 
															 const std::vector<Vertex>& p, 
															 const std::vector<int>& d, 
														   Plan& plan) {

	plan.cost = d[v];

	list<PlannedAction> plan_list;

	for (;; v = p[v]) {

		PlannedAction action;

		//action.end_time = d[v];
		action.target = v;
		if (p[v] != v) {
			action.source = p[v];
			//action.start_time = d[p[v]];
			action.edge = edge(p[v], v, graph).first;

			plan_list.push_front(action);
		}
		else break;
	}

	plan.actions.reserve(plan_list.size());

	int time = 0;
	for (auto& a : plan_list) {
		a.start_time = time++;
		a.action_cost = graph[a.edge].cost;
		plan.actions.push_back(a);
	}

	//copy(plan_list.begin(), plan_list.end(), back_inserter(plan.actions));

}

}