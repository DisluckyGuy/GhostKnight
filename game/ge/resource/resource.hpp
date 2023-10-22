#pragma once
#include <map>
#include <string>
#include <fstream>
#include <iostream>

namespace ge
{
    template <class ResourceObj>
    class ResourceObjArr {
        private:
        ResourceObj *objs;
        unsigned int size;
        public:
        ResourceObjArr(ResourceObj *objs, unsigned int size): objs(objs), size(size) {}

        ~ResourceObjArr() {
            size = 0;
            delete [] objs;
        }

        ResourceObj &operator[](int index){return objs[index];}
        unsigned int getSize() {
            return size;
        }
    };
    template <class ResourceObj> 
    class Resource {
        protected:
        std::map<std::string,ResourceObjArr<ResourceObj>*> resources;
    
        public:
        virtual void read(std::string path) {
            std::filebuf fb;
            if (!fb.open(path, std::ios::in)) {
                std::cout << " Error: couldn't open path: " << path << " " << std::endl;
                std::exit(-1);
            }
            std::istream is(&fb);
            while(is) {
                std::string temp;
                std::getline(is,temp);
                if (temp.find(':') == std::string::npos) {continue;}
                std::string root = path.substr(0,path.find_last_of('/') + 1);
                std::string first = temp.substr(0, temp.find(':'));
                std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);
                load(first ,root + second);
            }
            fb.close();
        }

        
        void load(std::string name, std::string path) {
            ResourceObj *obj = new ResourceObj();
            if (!obj->loadFromFile(path)) {
                delete obj;
                std::cout << "Error: couldn't load resource: " << name << ", from path " << path << " " << std::endl;
                std::exit(-1);
            }
            resources[name] = new ResourceObjArr<ResourceObj>(obj, 1);
            }
        ResourceObjArr<ResourceObj> &getResource(std::string name) {
            return *resources[name];
        }
        };
    
} // namespace ge
