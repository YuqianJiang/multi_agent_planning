#include <Scenario.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

Scenario::Scenario(vector<vector<Edge> > actions, int numCollisions, int numSynergies) :
		interactionMaps() {}

vector<Interaction> Scenario::getAllInteractionsOfAction(int agent_id, Edge action) const {
	
	/*vector<Edge> synergies;
	
	vector<AgentAction>& actions = synergyMaps[action.agent_id][action.edge];

	for (auto const& a : actions) {
		if (a.agent_id == agent_id) {
			synergies.push_back(a.edge);
		}
	}

	return synergies;*/


	try {
		return interactionMaps[agent_id].at(action);
	}
	catch (std::out_of_range) {
		return vector<Interaction>();
	}
}

}