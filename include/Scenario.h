#ifndef multi_agent_planning_Scenario_h__guard
#define multi_agent_planning_Scenario_h__guard

#include <plan_utils.h>

namespace multi_agent_planning {

struct Interaction {

	Interaction(std::pair<int, Edge> a, std::pair<int, Edge> b, int cost) :
			agentA(a.first), actionA(a.second), agentB(b.first), actionB(b.second), 
			cost(cost) {}

	int agentA;
	Edge actionA;
	int agentB;
	Edge actionB;
	int cost;
};

class Scenario {
public:

	Scenario(const std::vector<std::vector<Edge> > actions, int numCollisions, int numSynergies);

	std::vector<Interaction> getAllInteractionsOfAction(int agent_id, Edge action) const;

private:

	void insertInteraction(Interaction i);

	typedef std::map<Edge, std::vector<Interaction> > InteractionMap;
	std::vector<InteractionMap> interactionMaps;
	std::vector<std::pair<int, Edge> > allActions;

};

}

#endif