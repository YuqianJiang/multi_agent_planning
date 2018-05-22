#include <Scenario.h>

using namespace std;
using namespace boost;

namespace multi_agent_planning {

Scenario::Scenario(const std::vector<std::vector<Edge> >& actions, 
									 const std::vector<Graph>& graphs, int numInteractions) : 
		interactionMaps(actions.size()), allActions() {

	for (int i = 0; i < actions.size(); ++i) {
		transform(actions[i].begin(), actions[i].end(), 
							back_inserter(allActions), 
							[i](const Edge& e){return make_pair(i, e);});
	}

	set<pair<int, int> > generated;

	for (int i = 0; i < numInteractions; ++i) {

		int actA, actB;
		
		do {
			actA = getRndInt(allActions.size()-1);
			actB = getRndInt(allActions.size()-1);
		} while ((allActions[actA].first == allActions[actB].first) || 
					  (generated.find(make_pair(actA, actB)) != generated.end()));

		generated.insert(make_pair(actA, actB));
 
 		std::pair<int, Edge> action = allActions[actB];

 		Graph g = graphs[action.first];
 		int cost = g[action.second].cost;

 		int interactionCost;
 		do {
 			interactionCost = getRndInt(-cost, cost);
 		} while (interactionCost == 0);

		Interaction interaction(allActions[actA], allActions[actB], interactionCost);
		insertInteraction(interaction);
	}

}

Scenario::Scenario(const vector<std::vector<Edge> >& actions, 
									const vector<Graph>& graphs, 
									int numConflicts,
									int numSynergies) : 
		interactionMaps(actions.size()), allActions() {

	for (int i = 0; i < actions.size(); ++i) {
		transform(actions[i].begin(), actions[i].end(), 
							back_inserter(allActions), 
							[i](const Edge& e){return make_pair(i, e);});
	}

	set<pair<int, int> > generated;

	for (int i = 0; i < numConflicts; ++i) {

		int actA, actB;
		
		do {
			actA = getRndInt(allActions.size()-1);
			actB = getRndInt(allActions.size()-1);
		} while ((allActions[actA].first == allActions[actB].first) || 
					  (generated.find(make_pair(actA, actB)) != generated.end()));

		generated.insert(make_pair(actA, actB));
 
 		std::pair<int, Edge> action = allActions[actB];

 		Graph g = graphs[action.first];
 		int cost = g[action.second].cost;

 		int interactionCost;
 		do {
 			interactionCost = getRndInt(cost);
 		} while (interactionCost == 0);

		Interaction interaction(allActions[actA], allActions[actB], interactionCost);
		insertInteraction(interaction);
	}

	for (int i = 0; i < numSynergies; ++i) {

		int actA, actB;
		
		do {
			actA = getRndInt(allActions.size()-1);
			actB = getRndInt(allActions.size()-1);
		} while ((allActions[actA].first == allActions[actB].first) || 
					  (generated.find(make_pair(actA, actB)) != generated.end()));

		generated.insert(make_pair(actA, actB));
 
 		std::pair<int, Edge> action = allActions[actB];

 		Graph g = graphs[action.first];
 		int cost = g[action.second].cost;

 		int interactionCost;
 		do {
 			interactionCost = getRndInt(-cost, 0);
 		} while (interactionCost == 0);

		Interaction interaction(allActions[actA], allActions[actB], interactionCost);
		insertInteraction(interaction);
	}
	
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

string Scenario::toString() const {
	stringstream ss;
	for (auto& act : allActions) {
		vector<Interaction> interactions = this->getAllInteractionsOfAction(act.first, act.second);
		for (auto& inter : interactions) {
			ss << inter.toString() << endl;
		}
	}
	return ss.str();
}

string Interaction::toString() {
	stringstream ss;
	ss << agentA << actionA << " -> " << agentB << actionB << ": " << cost;
	return ss.str();
}

}