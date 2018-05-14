#ifndef multi_agent_planning_PlanningAgent_h__guard
#define multi_agent_planning_PlanningAgent_h__guard

#include <plan_utils.h>

namespace multi_agent_planning {

class Scenario;

class PlanningAgent {
public:

	PlanningAgent(int agent_id, Graph g);

	const Graph getGraph() const { return graph; }

	void drawGraph(std::string path);

	Plan computeSingleAgentPlan(const Instance instance);

	Plan computeInterDependentPlan(const Instance& instance, const Scenario& scenario, 
																 const std::vector<Plan>& plans);

	Instance getRandomInstance();

	std::vector<Edge> getAllActions() const;

	std::vector<Vertex> getAllStates() const;

	std::string planToString(const Plan& plan);

	int getId() const {
		return agent_id;
	}

	bool operator< (const PlanningAgent& other) {
		return this->agent_id < other.agent_id;
	}

private:
	int agent_id;

	Graph graph;

	Vertex getRandomVertex();

	Vertex getRandomConnectedVertex(Vertex source);	

	void planHelper(Vertex v, const std::vector<Vertex>& p, const std::vector<int>& d, Plan& plan);

};



}



#endif