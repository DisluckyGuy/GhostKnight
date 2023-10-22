#pragma once

#include "state.hpp"
#include <vector>

namespace ge {
    namespace state {
        class Handler {
        private:
        std::vector<State*> states;
        public:
            Handler() {}

            ~Handler() {}

            void update(){ for (State* state : states) { state->update(); } }
            void render(){ for (State* state : states) { state->render(); } }
            
            void addState(State* state, bool removing = true){
                if (removing && !states.empty()) {
                    removeState();
                }
                states.push_back(state);
            }

            void removeState(){
                if (states.empty()) {return;}
                delete states.at(states.size() - 1);
                states.erase(states.begin() + (states.size() - 1));
            }

            void clearState(){
                if (states.empty()) { return; }
                for (State* state : states) {delete state;}
                states.clear();
            }
        };
    }
}