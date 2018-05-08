#ifndef multi_agent_planning_Scenario_h__guard
#define multi_agent_planning_Scenario_h__guard

#include <plan_utils.h>

namespace multi_agent_planning {

class Scenario {
public:
	// change to a vector of domains
	Scenario(const std::vector<AgentAction> actions, int numCollisions, int numSynergies);

	const std::vector<AgentAction> getPotentialCollisions(AgentAction action);

	const std::vector<AgentAction> getPotentialSynergies(AgentAction action);

private:

	typedef std::map<Edge, std::vector<AgentAction> > InteractionMap;

	std::vector<InteractionMap> collisionMaps;
	std::vector<InteractionMap> synergyMaps;

};

}

#endif