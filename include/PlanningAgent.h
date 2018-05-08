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

	Plan computeSingleAgentPlan(Instance instance);

	Plan computeInterDependentPlan(const Instance& instance, const Scenario& scenario, const std::vector<Plan>& plans);

	Instance getRandomInstance();

	std::vector<AgentAction> getAllActions();

	std::string planToString(const Plan& plan);


private:
	int agent_id;

	Graph graph;

	Vertex getRandomVertex();

	Vertex getRandomConnectedVertex(Vertex source);	

	void planHelper(Vertex v, const std::vector<Vertex>& p, const std::vector<int>& d, Plan& plan);

};



}



#endif