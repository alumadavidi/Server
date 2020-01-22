//
// Created by user on 13 ינואר 2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H
#include "../SerachAlgo/SearcherPriority.h"
#include "../MyStruct/MyQueqe.h"
#include "../State.h"
#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;
template <class T>
class AStar : public SearcherAbstract<T>{
    //compare func to priority queue
    class Compare {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getHeuristicVlaue() > right->getHeuristicVlaue());
        }
    };
public:
    AStar(){};
    virtual vector<State<T>*> search (Isearchable<T>* searchable); //abstract method
    bool ExistInClosed(State<T>* vertex, vector<State<T>*>);
    bool ExistInOpen(State<T> *vertex, priority_queue<State<T>*, vector<State<T>*>, Compare> open);
    double getHeuristicVal(State<pair<int,int>>* state, State<pair<int,int>>* init);
    void updatePriority(priority_queue<State<T>*, vector<State<T>*>, Compare> open);
    string getName();
};

template <class T>
vector<State<T>*> AStar<T>::search(Isearchable<T>* searchable) {
    this->numOfNodesEvaluated = 0;
    priority_queue<State<T>*, vector<State<T>*>, Compare> open;
    vector<State<T>*> closed;
    State<T>* cur_vertex;
    open.push(searchable->getInitialState());
    while (!open.empty()) {
        cur_vertex = open.top();
        open.pop();
        this->numOfNodesEvaluated++;
        if ((*cur_vertex).Equals(searchable->getgoalState())) {
            vector<State<T>*> result = this->traceBack(searchable->getInitialState(), cur_vertex);
            return result;
        }
        closed.push_back(cur_vertex);
        vector<State<T>*> successors = searchable->getAllPossibleStates(cur_vertex);
        for (int i = 0; i < successors.size(); ++i) {
            State<T>* neighbor = successors[i];
            double newCost = cur_vertex->getCost() + neighbor->getInitCost();
            if (!ExistInOpen(neighbor, open) && !ExistInClosed(neighbor,closed)) {
                neighbor->setComeFrom(cur_vertex);
                neighbor->setCost(newCost);
                neighbor->setHeuristicVlaue(newCost + getHeuristicVal(neighbor, searchable->getInitialState()));
                open.push(neighbor);
                continue;
            } else if (ExistInClosed(neighbor, closed)){
                continue;
            } else if (cur_vertex->getCost() + neighbor->getInitCost() < neighbor->getCost()) {
                neighbor->setComeFrom(cur_vertex);
                neighbor->setCost(newCost);
                neighbor->setHeuristicVlaue(newCost + getHeuristicVal(neighbor, searchable->getInitialState()));
                updatePriority(open);
            }
        }
    }
    //if there is no path return empty vector
    vector<State<T> *> emptyVector;
    return emptyVector;
}
template <class T>
bool AStar<T>::ExistInOpen(State<T>* vertex, priority_queue<State<T>*, vector<State<T>*>, Compare> open) {
    priority_queue<State<T>*, vector<State<T>*>, Compare> temp = open;
    while (!temp.empty()) {
        //found state in priority/-queue
        if ((*vertex).Equals(temp.top())) {
            return true;
        }
        temp.pop();
    }
    return false;
}
template <class T>
bool AStar<T>::ExistInClosed(State<T>* vertex, vector<State<T>*> closed) {
    for (auto state:closed) {
        if ((*vertex).Equals(state)) {
            return true;
        }
    }
    return false;
}

template <class T>
double AStar<T>::getHeuristicVal(State<pair<int,int>>* state, State<pair<int,int>>* init) {
    double dx = abs(state->getState().first - init->getState().first);
    double dy = abs(state->getState().second - init->getState().second);
    return dx + dy;
}
template <class T>
void AStar<T>::updatePriority(priority_queue<State<T>*, vector<State<T>*>, Compare> open){
    priority_queue<State<T> *, vector<State<T> *>, Compare> temp;
    while (!open.empty()) {
        temp.push(open.top());
        open.pop();
    }
    while (!temp.empty()) {
        open.push(temp.top());
        temp.pop();
    }
}

template<class T>
string AStar<T>::getName() {
    return "AStar";
}


#endif //EX4_ASTAR_H
