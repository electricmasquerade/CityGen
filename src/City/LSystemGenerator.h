#pragma once
#include <random>
#include <vector>
#include "CitySymbols.h"

namespace City {
    struct Production {
        //handles the production rules for the L-system
        std::string predecessor; // The predecessor string
        std::string successor; // The successor string
        float probability{1.0f}; // Probability of applying this rule (default is 1.0)
    };
    struct LSystem {
        //handles the L-system generation
        std::string axiom; // The initial string (axiom)
        std::vector<Production> productions; // List of production rules
        int iterations; // Number of iterations to apply the production rules
    };

    class LSystemGenerator {
    public:
        LSystemGenerator():rng(std::random_device{}()){}
        ~LSystemGenerator() = default;

        void generate();
        void setAxiom(const std::string &axiom){m_system.axiom = axiom;}
        void addRule(const Production &production){m_system.productions.push_back(production);}
        void setDepth(const int depth){m_system.iterations = depth;}
        std::string selectRule(const std::string& predecessor); //take a random rule based on string

        //getters
        [[nodiscard]] const std::string& getGeneratedString() const {return m_generatedString;}
        [[nodiscard]] const LSystem& getLSystem() const {return m_system;}
        [[nodiscard]] const std::vector<Production>& getProductions() const {return m_system.productions;}
        [[nodiscard]] const std::string& getAxiom() const {return m_system.axiom;}
        [[nodiscard]] int getIterations() const {return m_system.iterations;}

    private:
        LSystem m_system = {
                "", // Axiom
                {}, // Productions
                0 // Iterations
        };
        //string to store the generated string
        std::string m_generatedString;

        //random generator for rule selection
        std::mt19937 rng;

    };
} // City
