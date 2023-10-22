#pragma once


namespace ge {
    struct Data;
    class State {
        public:
        State(Data* data): data(data){
            
        }
        virtual void update() = 0;
        virtual void render() = 0;
        protected:
        Data* data;
    };
}
#include "handler.hpp"