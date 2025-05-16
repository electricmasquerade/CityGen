#include "LSystemGenerator.h"
#include <iostream>
#include <ostream>

namespace City {
    void LSystemGenerator::generate() {
        std::string current = m_system.axiom;
        for (int i = 0; i < m_system.iterations; ++i) {
            std::string next;
            for (const char c: current) {
                bool found = false;
                for (const auto &production: m_system.productions) {
                    if (c == production.predecessor[0]) {
                        //use select rule to get a random rule
                        const std::string selectedRule = selectRule(production.predecessor);
                        next += selectedRule;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    next += c; // If no production rule matches, keep the character
                }
            }
            current = next;
        }

        std::cout << current << std::endl;
        m_generatedString = current;
    }

    std::string LSystemGenerator::selectRule(const std::string &predecessor) {
        //create a list of rules for this predecessor
        std::vector<Production> possibleRules;
        for (const auto &production: m_system.productions) {
            if (production.predecessor == predecessor) {
                possibleRules.push_back(production);
            }
        }
        // Select a rule based on the probability
        //init random generator
        float cumulativeProbability = 0.0f;
        // std::cout << "selectRule('" << predecessor
        //   << "') found " << possibleRules.size()
        //   << " productions\n";
        //sum total probability for this character
        for (const auto &production: possibleRules) {
            if (production.predecessor == predecessor) {
                cumulativeProbability += production.probability;
            }
        }
        std::uniform_real_distribution distribution(0.0f, cumulativeProbability);
        float randomValue = distribution(rng);

        for (const auto &production: possibleRules) {
            if (production.predecessor == predecessor) {
                if (randomValue <= production.probability) {
                    return production.successor; // Return the selected rule
                }
                randomValue -= production.probability;
            }
        }
        //return the last element of rules if nothing is found, as a fallback
        return possibleRules.back().successor;
    }
}
