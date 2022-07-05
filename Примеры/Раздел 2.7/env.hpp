#include <unordered_map>
#include <memory>
#include <string>

class Symbol { };

class Env {
    std::unordered_map<std::string, Symbol> table;
    Env* previous;

    Env(Env* previous): previous(previous) { }
    void put(std::string s, Symbol sym) {
        table.insert({s, sym});
    }

    std::unordered_map<std::string, Symbol>::const_iterator begin() const {
        return table.begin();
    }

    std::unordered_map<std::string, Symbol>::const_iterator end() const {
        return table.end();
    }

    std::unordered_map<std::string, Symbol>::const_iterator get(std::string s) const {
        for(const Env* e = this; e != nullptr; e = e->previous) {
            auto it = e->table.find(s);
            if(it != e->table.end()) return it;
        }
        return table.end();
    }
};