#include <Scenario.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

Scenario::Scenario(vector<AgentAction> actions, int numCollisions, int numSynergies) :
		collisionMaps(), synergyMaps() {}

vector<AgentAction> Scenario::getPotentialCollisions(AgentAction action) const {
	
	/*vector<Edge> collisions;
	
	vector<AgentAction>& actions = collisionMaps[action.agent_id][action.edge];

	for (auto const& a : actions) {
		if (a.agent_id == agent_id) {
			collisions.push_back(a.edge);
		}
	}

	return collisions;*/

	try {
		return collisionMaps[action.agent_id].at(action.edge);
	}
	catch (std::out_of_range) {
		return vector<AgentAction>();
	}
}

vector<AgentAction> Scenario::getPotentialSynergies(AgentAction action) const {
	
	/*vector<Edge> synergies;
	
	vector<AgentAction>& actions = synergyMaps[action.agent_id][action.edge];

	for (auto const& a : actions) {
		if (a.agent_id == agent_id) {
			synergies.push_back(a.edge);
		}
	}

	return synergies;*/
	try {
		return synergyMaps[action.agent_id].at(action.edge);
	}
	catch (std::out_of_range) {
		return vector<AgentAction>();
	}
}

}