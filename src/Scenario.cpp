#include <Scenario.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

Scenario::Scenario(vector<AgentAction> actions, int numCollisions, int numSynergies) :
		collisionMaps(), synergyMaps() {}

const vector<AgentAction> Scenario::getPotentialCollisions(AgentAction action) {
	
	/*vector<Edge> collisions;
	
	vector<AgentAction>& actions = collisionMaps[action.agent_id][action.edge];

	for (auto const& a : actions) {
		if (a.agent_id == agent_id) {
			collisions.push_back(a.edge);
		}
	}

	return collisions;*/

	return collisionMaps[action.agent_id][action.edge];
}

const vector<AgentAction> Scenario::getPotentialSynergies(AgentAction action) {
	
	/*vector<Edge> synergies;
	
	vector<AgentAction>& actions = synergyMaps[action.agent_id][action.edge];

	for (auto const& a : actions) {
		if (a.agent_id == agent_id) {
			synergies.push_back(a.edge);
		}
	}

	return synergies;*/
	return collisionMaps[action.agent_id][action.edge];
}

}