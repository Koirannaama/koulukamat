// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hh"
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>


Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
    for (auto stop : _stops) {
        for (auto dept : stop.second) {
            delete dept;
        }
    }
}

void Datastructure::add_stop(int stop_id, std::string stop_name)
{
    _stopNames[stop_id] = stop_name;
}

void Datastructure::add_route(int route_id, std::string route_name)
{
    _routeNames[route_id] = route_name;
}

void Datastructure::add_stop_to_route(int route_id, int stop_id, unsigned int minutes)
{
    if (_routes.count(route_id) > 0) {
        _routes[route_id].push_back({stop_id, minutes});
    }
    else {
        std::vector<RouteStop> v;
        v.push_back({stop_id, minutes});
        _routes[route_id] = v;
    }
}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    Bus b = {route_id, Time(start_hours, start_minutes)};
    _buses[bus_id] = b;

    std::vector<RouteStop> route = _routes[route_id];
    std::vector<Departure*> createdDepartures;
    int i = 1;
    // Create a departure for each stop this bus has on this route.
    for (auto stop : route) {

        // Calculate departure time
        unsigned int  m, h;
        if ( stop.mins + start_minutes >= 60) {
            m = stop.mins + start_minutes - 60;
            h = start_hours + 1;
        }
        else {
            m = stop.mins + start_minutes;
            h = start_hours;
        }
        Time deptTime(h, m);

        // Get the next stop for this departure
        int nextStop;
        if (i < route.size()) {
            nextStop = route[i].stopID;
        }
        else {
            nextStop = -1;
        }

        Departure* d = new Departure {bus_id, deptTime, nextStop, nullptr};
        if (_stops.count(stop.stopID) > 0) {
           _stops[stop.stopID].push_back(d);
        }
        else {
            std::vector<Departure*> v;
            v.push_back(d);
            _stops[stop.stopID] = v;
        }
        createdDepartures.push_back(d);
        i++;
    }

    // Link departures together
    for (int i = 1; i < createdDepartures.size(); i++) {
        createdDepartures[i - 1]->nextDept = createdDepartures[i];
    }
}

void Datastructure::empty()
{
    _stopNames.clear();
    _routeNames.clear();
    _routes.clear();
    _buses.clear();
    _paths.clear();
    for (auto stop : _stops) {
        for (auto dept : stop.second) {
            delete dept;
        }
    }
    _stops.clear();
}

void Datastructure::print_stop(int stop_id)
{
    if (_stopNames.count(stop_id) > 0) {
        std::cout << _stopNames[stop_id] << std::endl;
    }
    else {
        std::cout << NO_SUCH_STOP << std::endl;
    }
}

void Datastructure::print_buses(int stop_id)
{
    if (_stops.count(stop_id) > 0) {
        std::set<int> routes = getRoutesLeavingFrom(stop_id);

        for (auto route : routes) {
            std::cout << _routeNames[route] << std::endl;
        }
    }
    else {
        std::cout << NO_SUCH_STOP << std::endl;
    }
}

void Datastructure::print_statistics()
{
    std::cout << _stops.size() << " stops, "
              << _routes.size() << " routes, "
              << _buses.size() << " buses." << std::endl;
}

void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{
    _paths.clear();
    std::priority_queue<Stop, std::vector<Stop>, CompareCurrentTime> stops
            = initPriorityQueue(hours, minutes, start_stop);

    int currentStop;
    while(( currentStop = stops.top().stopID ) != end_stop && !stops.empty()) {
        Time currentTime = _paths[currentStop].arrivalTime;

        for (Departure* d : _stops[currentStop]) {
            // We check departures that depart after we got to this top and are not final stops of their routes.
            if (d->departureTime >= currentTime && d->nextStop != -1) {
                Departure* nextDept = d->nextDept;

                // We create a new stop in _paths if none exist for this stop
                // or we found a faster a connection to the next stop of this departure.
                if (_paths.count(d->nextStop) == 0
                    || nextDept->departureTime < _paths[d->nextStop].arrivalTime) {

                    _paths[d->nextStop] = {nextDept->departureTime, d->departureTime, d->bus, currentStop};
                    stops.push({d->nextStop, nextDept->departureTime});
                }
            }
        }
        stops.pop();
    }
    printResults(end_stop);

}

std::priority_queue<Datastructure::Stop, std::vector<Datastructure::Stop>, Datastructure::CompareCurrentTime> Datastructure::initPriorityQueue(int h, int m, int startStop)
{
    std::priority_queue<Stop, std::vector<Stop>, CompareCurrentTime> stops;
    _paths[startStop] = {Time(h, m), Time(-1,-1), -1, -1};
    stops.push({startStop, Time(h, m)});
    return stops;
}

void Datastructure::printResults(int endStop)
{
    if (_paths.count(endStop) > 0) {
        printJourney(endStop, -1, _paths[endStop].arrivalTime);
    }
    else {
        std::cout << NO_ROUTE << std::endl;
    }
}

void Datastructure::printJourney(int stop, int busTaken, Time deptTime)
{
    StopInfo pathStop = _paths[stop];
    // Traverse the path from end to start
    if (pathStop.previousStop != -1) {
        printJourney(pathStop.previousStop,
                     pathStop.previousBus,
                     pathStop.departureFromPrev);
    }

    // Extra printing if we changed buses on the way
    if (busTaken != pathStop.previousBus && busTaken != -1) {
        // We don't want to print an arrow for the first stop of the path though
        if (pathStop.previousStop != -1) {
            std::cout << "->" << pathStop.arrivalTime.toString() << " " << stop
                      << ", " << _stopNames[stop] << std::endl;
        }
        std::cout << _routeNames[_buses[busTaken].route] << std::endl;
    }

    // Prints the arrow for the final stop
    std::string arrowOrEmpty;
    if (busTaken == -1) {
        arrowOrEmpty = "->";
    }
    else {
        arrowOrEmpty = "  ";
    }
    std::cout << arrowOrEmpty << deptTime.toString() << " "
              << stop << ", " << _stopNames[stop] << std::endl;


}

std::set<int> Datastructure::getRoutesLeavingFrom(int stopID)
{
    std::set<int> routes;
    for (auto departure : _stops[stopID]) {
        routes.insert(_buses[departure->bus].route);
    }
    return routes;
}

