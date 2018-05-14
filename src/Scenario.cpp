#include <Scenario.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

Scenario::Scenario(vector<vector<Edge> > actions, int numCollisions, int numSynergies) : 
		interactionMaps(actions.size()), allActions() {

	for (int i = 0; i < actions.size(); ++i) {
		transform(actions[i].begin(), actions[i].end(), 
							back_inserter(allActions), 
							[i](Edge& e){return make_pair(i, e);});
	}

	//vector<Interaction> interactions;
	//interactions.push_back(Interaction(allActions[9], allActions[0], 1));
	Interaction inter(allActions[0], allActions[8], 1);
	insertInteraction(inter);

}

void Scenario::insertInteraction(Interaction i) {
	this->interactionMaps[i.agentA][i.actionA].push_back(i);
}

vector<Interaction> Scenario::getAllInteractionsOfAction(int agent_id, Edge action) const {

	try {
		return interactionMaps[agent_id].at(action);
	}
	catch (std::out_of_range) {
		return vector<Interaction>();
	}
}

}