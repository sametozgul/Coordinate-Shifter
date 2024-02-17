#include <iostream>
#include <cmath>
#include <numbers>
#include <map>
#include <string>
#include <iomanip>
#include <regex>
#include <vector>

using string = std::string;
using myMap = std::map<string,double>;
using myVector = std::vector<double>;

static double ToRadians(double degrees)
{
    return degrees * (std::numbers::pi / 180.0);
}

static myMap CalculateShiftedPoint(double initialLat, double initialLon, double shiftNorth, double shiftEast)
{
    double earthRadius = 6371000.0;
    double latRad = ToRadians(initialLat);
    double lonRad = ToRadians(initialLon);
    double newLat = initialLat + (shiftNorth / earthRadius) * (180.0 / std::numbers::pi);
    double newLon = initialLon + (shiftEast / earthRadius) * (180.0 / std::numbers::pi) / cos(latRad);
    myMap tempMap {{"Latitude",newLat},{"Longitude",newLon}};
    return tempMap;
}


int main()
{
    std::cout<<"Please enter Latitude,Longitude,ShiftingFromLat (m),ShiftingFromLon (m) respectively as:\n";
    std::cout<<"Latitude Longitude ShiftingFromLat ShiftingFromLon   and type enter...\n";
    myVector inputs{};

    for(string s{}; std::cin >> s;)
    {
        inputs.push_back(std::stod(s));
        if(inputs.size() == 4){
            myMap newCoordinates = CalculateShiftedPoint(inputs.at(0), inputs.at(1), inputs.at(2), inputs.at(3));
            // Display the results
            std::cout<<
                "Initial Point: Latitude "<<std::setprecision(15)<<inputs.at(0)
                <<", Longitude "<<std::setprecision(15)<<inputs.at(1)<<"\n";
            std::cout<<
                "Shifted Point: Latitude "<<std::setprecision(15)<<newCoordinates["Latitude"]
                <<", Longitude "<<std::setprecision(15)<<newCoordinates["Longitude"]<<"\n";
            inputs.clear();
        }
    }
    return 0;
}
