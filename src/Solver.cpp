#include <Solver.h>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/graph/astar_search.hpp>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

vector<Plan> Solver::solve_baseline(vector<Instance> instances) {
	vector<Plan> plans;

	for (int i = 0; i < domains.size(); ++i) {
		WeightMap wm = domains[i].getWeightMap();
		plans.push_back(domains[i].getPlan(instances[i], wm));
	}

	return plans;
}

vector<Plan> Solver::solve_brute_force_ordering(vector<Instance> instances, Scenario scenario) {
	vector<Plan> plans;

	for (int i = 0; i < domains.size(); ++i) {
		WeightMap wm = domains[i].getWeightMap();
		plans.push_back(domains[i].getPlan(instances[i], wm));
	}

	return plans;
}

Plan Solver::inter_dependent_planning(int agent_id, Instance instance, Scenario scenario, vector<Plan> plans) {
	WeightMap wm = domains[agent_id].getWeightMap();
	Graph graph = domains[agent_id].getGraph();
	
	/*auto my_custom_weight_map = 
        boost::make_transform_value_property_map(
                [](int w) { return w>100? 10*w : w; },
                wm);

  //WeightMap new_wm(my_custom_weight_map);

  vector<Vertex> p(num_vertices(graph));
	vector<float> d(num_vertices(graph));

		astar_search(
			graph, instance.start, 
			astar_heuristic<Graph, float>(), 
			weight_map(my_custom_weight_map).
			predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, graph))).
  	  distance_map(make_iterator_property_map(d.begin(), get(vertex_index, graph))).
  	  visitor(default_astar_visitor())
  	);*/
	/*auto wmap = 
		make_transform_value_property_map(
			[graph](boost::property<boost::edge_weight_t, int>& e) { return get(edge_weight, e); }, 
			get(boost::edge_bundle, graph));*/

	return domains[agent_id].getPlan(instance, wm);
}

}