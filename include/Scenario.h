#ifndef multi_agent_planning_Scenario_h__guard
#define multi_agent_planning_Scenario_h__guard

#include <plan_utils.h>

namespace multi_agent_planning {

struct Interaction {
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

	typedef std::map<Edge, std::vector<Interaction> > InteractionMap;
	std::vector<InteractionMap> interactionMaps;

};

}

#endif