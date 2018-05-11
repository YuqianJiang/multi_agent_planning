#ifndef multi_agent_planning_Scenario_h__guard
#define multi_agent_planning_Scenario_h__guard

#include <plan_utils.h>

namespace multi_agent_planning {

class Scenario {
public:

	Scenario(const std::vector<AgentAction> actions, int numCollisions, int numSynergies);

	std::vector<AgentAction> getPotentialCollisions(AgentAction action) const;

	std::vector<AgentAction> getPotentialSynergies(AgentAction action) const;

private:

	typedef std::map<Edge, std::vector<AgentAction> > InteractionMap;

	std::vector<InteractionMap> collisionMaps;
	std::vector<InteractionMap> synergyMaps;

};

}

#endif