#ifndef multi_agent_planning_Scenario_h__guard
#define multi_agent_planning_Scenario_h__guard

#include <Domain.h>

namespace multi_agent_planning {

typedef std::pair<int, Edge> AgentAction; 
typedef std::map<AgentAction, AgentAction> EventMap;

//key is action causing collision/synergy

/*enum EventType { Collision, Synergy };

struct Event {
	EventType type;
	int agentA;
	int agentB;
	Edge actionA;
	Edge actionB;
};*/

class Scenario {
public:
	Scenario(Domain domain, int numCollisions, int numSynergies);

private:
	EventMap collisionEvents;
	EventMap synergyEvents;
};

}

#endif