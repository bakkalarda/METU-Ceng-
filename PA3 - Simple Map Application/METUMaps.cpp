#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    Graph new_map(mapFilePath);
    this->map = new_map;
    KeyedHashTable new_table(potentialPathCount*new_map.TotalVertexCount());
    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;
    this->cachedPaths= new_table;
}

void METUMaps::SetDestination(const std::string& name)
{
    if(inJourney)
    {
        PrintUnableToChangeStartingLoc();
        return;
    }
    destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    if(inJourney)
    {
        PrintUnableToChangeStartingLoc();
        return;
    }
    startingLoc = name;
}

void METUMaps::StartJourney()
{
    if(inJourney)
    {
        PrintAlreadyInJourney();
        return;
    }
    PrintCalculatingRoutes(startingLoc, destination);
    bool start = false;
    bool dest = false;
    for(int i=0; i< map.TotalVertexCount(); i++)
    {
        if (map.VertexName(i) == startingLoc)
        {
            start = true;
        }
        if(map.VertexName(i) == destination)
        {
            dest = true;
        } 
    }
    if (start == false || dest == false) {
        PrintLocationNotFound();
        return;
    }
    else if(startingLoc == "" || destination == "")
    {
        PrintLocationNotFound();
        return;
    }
    inJourney = true;
    std::vector<std::vector<int> > shortestpaths;
    map.MultipleShortPaths(shortestpaths, startingLoc, destination, potentialPathCount);
    std::vector<std::vector<int> > shortestpathz = shortestpaths;
    currentRoute = shortestpaths[0];
    for(int j=0; j<(int)shortestpaths.size(); j++)
    {
        for(int k=0; k<(int)shortestpaths[j].size()-1;k++)
        {
            std::string frontname = "";
            std::string endname = "";
            frontname = map.VertexName(shortestpathz[j].front());
            endname = map.VertexName(shortestpathz[j].back());
            std::string key = GenerateKey(frontname, endname);
            cachedPaths.Insert(key, shortestpathz[j]);
            shortestpathz[j].erase(shortestpathz[j].begin());
        }
    }
    currentLoc = startingLoc;
}

void METUMaps::EndJourney()
{
    if(!inJourney)
    {
        PrintJourneyIsAlreadFinished();
        return;
    }
    cachedPaths.ClearTable();
    destination.clear();
    startingLoc.clear();
    currentLoc.clear();
    inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name)
{
    if(!inJourney)
    {
        PrintNotInJourney();
        return;
    }
    bool test= false;
    if(name == destination)
    {
        PrintJourneyCompleted();
        return;
    }
    for (int i=0; i<map.TotalVertexCount(); i++)
    {
        if (map.VertexName(i) == name)
        {
            test = true;
        }
    }
    if(!test)
    {   
        PrintLocationNotFound();
        return;
    }
    currentLoc = name;
    std::string key = GenerateKey(name, destination);
    std::vector<int> value_out;
    bool is_there_path = cachedPaths.Find(value_out, key);
    if(is_there_path)
    {
        PrintCachedLocationFound(name, destination);
        currentRoute = value_out;
        return;
    }
    PrintCalculatingRoutes(name, destination);
    std::vector<std::vector<int> > shortestpaths;
    map.MultipleShortPaths(shortestpaths, name, destination, 1);
    std::vector<std::vector<int> > shortestpathz = shortestpaths;
    currentRoute = shortestpaths[0];
    for(int j=0; j<(int)shortestpaths.size(); j++)
    {
        for(int k=0; k<(int)shortestpaths[j].size()-1;k++)
        {
            std::string frontname = "";
            std::string endname = "";
            frontname = map.VertexName(shortestpathz[j].front());
            endname = map.VertexName(shortestpathz[j].back());
            std::string key = GenerateKey(frontname, endname);
            cachedPaths.Insert(key, shortestpathz[j]);
            shortestpathz[j].erase(shortestpathz[j].begin());
        }
    }
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}