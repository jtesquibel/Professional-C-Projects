#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include "TSP.h"
#include <fstream>
#include <algorithm>

std::vector<Location> func(std::string file);
void randGen(int gens, int numLocs, Population& pop, std::mt19937& startSeed, int popSize, std::ofstream& myfile);
std::vector<std::pair<int, double>> fitness(Population &pop, std::vector<Location> locs);
bool pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem);
double probability(int size);
std::vector<std::pair<int, int>> selection(Population& pop, std::vector<std::pair<int, double>> fitnesses, std::mt19937& startSeed);
Population crossover(Population& pop, std::vector<std::pair<int, int>> pairs, int mutChance, std::ofstream& myfile, std::mt19937& startSeed, std::vector<Location> locs);

int main(int argc, const char* argv[])
{
    
    std::ofstream myfile;
    myfile.open("out.txt");
    
    
    // first param is string .txt
    std::string inputFile = argv[1];
    std::vector<Location> locs = func(inputFile);
    
    Population pop;
    // second is population size
    int popSize = std::stoi(argv[2]);
    
    // third is number of generations
    int numGens = std::stoi(argv[3]);
    
    // fourth is mutation chance
    int mutChance = std::stoi(argv[4]);
    
    // fifth is starting seed value
    std::mt19937 startSeed(std::stoi(argv[5]));
    
    randGen(numGens, static_cast<int>(locs.size()), pop, startSeed, popSize, myfile);
    
    for (int i = 0; i < numGens; i++)
    {
        std::vector<std::pair<int, double>> fitnesses = fitness(pop, locs);
        // std::sort(fitnesses.begin(), fitnesses.end(), pairCompare);
        myfile << "FITNESS:" << std::endl;
        for (int i = 0; i < fitnesses.size(); i++)
        {
            myfile << fitnesses[i].first << ":" << fitnesses[i].second << std::endl;
        }
        
        std::vector<std::pair<int, int>> selections = selection(pop, fitnesses, startSeed);
        myfile << "SELECTED PAIRS:" << std::endl;
        for (int i = 0; i < selections.size(); i++)
        {
            myfile << "(" << selections[i].first << "," << selections[i].second << ")" << std::endl;
        }
        
        pop = crossover(pop, selections, mutChance, myfile, startSeed, locs);
        myfile << "GENERATION: " << i+1 << std::endl;
        for (auto it = pop.mMembers.begin(); it != pop.mMembers.end(); it++)
        {
            for (int i = 0; i < (*it).size()-1; i++)
            {
                myfile << (*it)[i] << ",";
            }
            myfile << (*it)[(*it).size()-1];
            
            myfile << std::endl;
        }
    }
    
    std::vector<std::pair<int, double>> fitnesses2 = fitness(pop, locs);
    myfile << "FITNESS:" << std::endl;
    for (int i = 0; i < fitnesses2.size(); i++)
    {
        myfile << fitnesses2[i].first << ":" << fitnesses2[i].second << std::endl;
    }
    
    myfile << "SOLUTION:" << std::endl;
    
    std::vector<int> winner = pop.mMembers[fitnesses2[0].first];
    for (int i = 0; i < winner.size(); i++)
    {
        myfile << locs[winner[i]].mName << std::endl;
        
    }
    std::sort(fitnesses2.begin(), fitnesses2.end(), pairCompare);
    myfile << locs[0].mName << std::endl << "DISTANCE: " << fitnesses2[0].second;
    
    
	return 0;
}

std::vector<Location> func(std::string file)
{
    std::string line;
    std::vector<Location> locs;
    std::ifstream myfile(file);
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            std::string loc;
            double lat;
            double lon;
            Location l;
            
            std::size_t found = line.find(',');
            if (found != std::string::npos)
            {
                loc = line.substr(0, found);
                l.mName = loc;
                line = line.substr(found+1, line.size());
            }
            
            found = line.find(',');
            if (found != std::string::npos)
            {
                lat = std::stod(line.substr(0, found));
                l.mLatitude = lat;
                line = line.substr(found+1, line.size());
            }
            
            lon = std::stod(line);
            l.mLongitude = lon;
            locs.push_back(l);
            
        }
        myfile.close();
    }
 
    return locs;
}

void randGen(int gens, int numLocs, Population &pop,  std::mt19937& startSeed, int popSize, std::ofstream& myfile)
{
    myfile << "INITIAL POPULATION:" << std::endl;

    for (int i = 0; i < popSize; i++)
    {
        std::vector<int> vec2;
        for (auto i = 0; i < numLocs; i++)
        {
            vec2.push_back(i);
        }
        std::shuffle(vec2.begin()+1, vec2.end(), startSeed);
        pop.mMembers.push_back(vec2);
        for (auto itt = vec2.begin(); itt != vec2.end()-1; itt++)
        {
            myfile << *itt << ",";
        }
        myfile << vec2[vec2.size()-1];
        myfile << std::endl;
    }

}

std::vector<std::pair<int, double>> fitness(Population &pop, std::vector<Location> locs)
{
    
    std::vector<std::pair<int, double>> result;
    int i = 0;
    
    
    for (auto it = pop.mMembers.begin(); it != pop.mMembers.end(); it++)
    {
        std::vector<int> vec = (*it);
        vec.push_back(0);
        
        std::vector<double> lats;
        std::vector<double> lons;
        
        double distance = 0;
        
        
        for (int i = 0; i < vec.size()-1; i++)
        {
            double lat1 = locs[vec[i]].mLatitude*0.0174533;
            double lon1 = locs[vec[i]].mLongitude*0.0174533;
            double lat2 = locs[vec[i+1]].mLatitude*0.0174533;
            double lon2 = locs[vec[i+1]].mLongitude*0.0174533;
            
            double dlat = lat2 - lat1;
            double dlon = lon2 - lon1;
            double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
            double c = 2 * atan2(sqrt(a), sqrt(1-a));
            distance += 3961 * c;
            
        }
        
        result.push_back(std::make_pair(i, distance));
        i++;
        
    }

    return result;
}

bool pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem)
{
    return firstElem.second < secondElem.second;
    
}

double probability(int size)
{
    return (1.0/size);
}

std::vector<std::pair<int, int>> selection(Population& pop, std::vector<std::pair<int, double>> fitnesses, std::mt19937& startSeed)
{
    std::sort(fitnesses.begin(), fitnesses.end(), pairCompare);
    
    std::vector<double> probs;
    probs.resize(fitnesses.size());
    int size = static_cast<int>(pop.mMembers.size());
    std::generate(probs.begin(), probs.end(), [&size]{ return 1.0/size; });
    for (auto it = fitnesses.begin(); it != fitnesses.begin()+2; it++)
    {
        probs[(*it).first] *= 6.0;
    }
    
    int half = static_cast<int>(fitnesses.size())/2;
    for (auto it = fitnesses.begin()+2; it != fitnesses.begin()+half; it++)
    {
        probs[(*it).first] *= 3.0;
    }
    
    double sum = std::accumulate(probs.begin(), probs.end(), 0.0);
    
    std::transform(probs.begin(), probs.end(), probs.begin(), [&sum](double d){return d/sum;});
    
    std::vector<std::pair<int, int>> pairs;
    
    for (int i = 0; i < fitnesses.size(); i++)
    {
        // std::random_device rd;
        // std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0,1);
        
        double parentA = dis(startSeed);
        double parentB = dis(startSeed);
        
        // std::cout << parentA << ", " << parentB << std::endl;
        
        double sum2 = probs[0];
        int indexA = 0;
        int indexB = 0;
        bool last = true;

        for (int i = 1; i < probs.size(); i++)
        {
            if (sum2 >= parentA)
            {
                indexA = i-1;
                last = false;
                break;
            }
            sum2 += probs[i];
        }
        
        if (last == true)
        {
            indexA = static_cast<int>(probs.size()-1);
        }
        
        sum2 = probs[0];
        last = true;
        
        for (int i = 1; i < probs.size(); i++)
        {
            if (sum2 >= parentB)
            {
                indexB = i-1;
                last = false;
                break;
            }
            sum2 += probs[i];
        }
        
        if (last == true)
        {
            indexB = static_cast<int>(probs.size()-1);
        }
        
        // std::cout << "(" << indexA << "," << indexB << ")" << std::endl;
        
        pairs.push_back(std::make_pair(indexA, indexB));
    }
    
    return pairs;
}

Population crossover(Population &pop, std::vector<std::pair<int, int>> pairs, int mutChance, std::ofstream& myfile, std::mt19937& startSeed, std::vector<Location> locs)
{
    Population newPop;
    
    
    
    for (auto it = pairs.begin(); it != pairs.end(); it++)
    {
        std::uniform_int_distribution<int> dis(1,static_cast<int>(locs.size()-2));
        int crossIndex = dis(startSeed);
        
        std::uniform_int_distribution<int> dis2(0,1);
        int parentChoice = dis2(startSeed);
        
        std::cout << "cross = " << crossIndex << std::endl;
        
        
        std::cout << "choice = " << parentChoice << std::endl;
        
        std::vector<int> child;
        std::vector<int> parentA = pop.mMembers[(*it).first];
        // std::cout << "first = " << (*it).first << std::endl;
        std::vector<int> parentB = pop.mMembers[(*it).second];
        // std::cout << "parent b = " << std::endl;
        for (int i = 0; i < parentB.size(); i++)
        {
            std::cout << parentB[i] << ",";
        }
        std::cout << "second = " << (*it).second << std::endl;
        
        if (parentChoice == 1)
        {
            // Parent A goes first
            std::copy_n(parentA.begin(), crossIndex+1, std::back_inserter(child));
            // std::cout << child << '\n';
            for (int i = 0; i < parentB.size(); i++)
            {
                if (std::find(child.begin(), child.end(), parentB[i]) != child.end())
                {
                    // it contains it so skip
                    continue;
                } else
                {
                    // doesn't contain so add
                    child.push_back(parentB[i]);
                }
            }
            
        }
        else if (parentChoice == 0)
        {
            // Parent B goes first
            // std::cout << "parent b first" << std::endl;
//            for (int i = 0; i < crossIndex; i++)
//            {
//                child.push_back(parentB[i]);
//            }
            std::copy_n(parentB.begin(), crossIndex+1, std::back_inserter(child));
            for (int i = 0; i < parentA.size(); i++)
            {
                if(std::find(child.begin(), child.end(), parentA[i]) != child.end())
                {
                    // it contains it so skip
                    continue;
                } else
                {
                    // doesn't contain so add
                    child.push_back(parentA[i]);
                }
            }
        }
        
        std::uniform_real_distribution<double> dis3;
        double mutation = dis3(startSeed);
        
        if (mutation <= mutChance)
        {
            std::uniform_int_distribution<int> dis4(1,static_cast<int>(locs.size()-1));
            int firstIndex = dis4(startSeed);
            int secondIndex = dis4(startSeed);
            std::swap(child[firstIndex], child[secondIndex]);
        }
        // crossIndex = dis(startSeed);
        
        newPop.mMembers.push_back(child);
    }
    

    
    return newPop;
}


