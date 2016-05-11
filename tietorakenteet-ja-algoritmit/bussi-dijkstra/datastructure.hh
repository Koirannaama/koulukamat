// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include "time.hh"

#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>

const std::string NO_ROUTE = "Error: No route!";
const std::string NO_SUCH_STOP = "Error: No such stop!";

class Datastructure
{
public:
    Datastructure();

    ~Datastructure();

    // Add a new bus stop
    void add_stop(int stop_id, std::string stop_name);

    // Add a new bus route
    void add_route(int route_id, std::string route_name);

    // Add a new stop to a route (both the route and the stop have already been added
    // using add_route and add_stop)
    void add_stop_to_route(int route_id, int stop_id, unsigned int minutes);

    // Add a new bus driving a route (the route has already been added using add_route) leaving at a certain
    // time from the terminus (first stop on route)
    void add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes);

    // Empty the datastructure
    void empty();

    // Print information on a bus stop
    void print_stop(int stop_id);

    // Print buses leaving from a stop
    void print_buses(int stop_id);

    // Print the number of stops, bus routes, and buses
    void print_statistics();

    // Print out the fastest journey leaving from stop start_stop to stop end_stop. Journey starts at the given time
    // and the whole journey must be done within the same day (before midnight).
    void print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes);

    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

private:
    // A stop on a particular route
    struct RouteStop {
        int stopID;
        unsigned int mins;
    };

    struct Bus {
        int route;
        Time startTime;
    };

    struct Departure {
        int bus;
        Time departureTime;
        int nextStop;
        Departure* nextDept;
    };

    // See comments for member variable _paths
    struct StopInfo {
        Time arrivalTime;
        Time departureFromPrev;
        int previousBus;
        int previousStop;
    };

    // These go into the priority queue.
    // The arrivalTime is used as the priority.
    struct Stop {
        int stopID;
        Time arrivalTime;
    };

    // Comparator function for the priority queue
    struct CompareCurrentTime {
        bool operator()(const Stop &s1, const Stop &s2) {
            return s1.arrivalTime > s2.arrivalTime;
        }
    };

    // Maps stop ids to stop names
    std::map<int, std::string> _stopNames;
    // Maps route ids to route names
    std::map<int, std::string> _routeNames;
    // Maps route ids to collections of stops on the route
    std::map<int, std::vector<RouteStop>> _routes;
    // Maps bus ids to routes and start times
    std::map<int, Bus> _buses;
    // Maps stop ids to to buses departing from the stop
    std::map<int, std::vector<Departure*>> _stops;

    // The actual path from start to finish is constructed here
    // Basically maps stop ids to structs which tell
    // on what time, on which bus and from
    // where we got here.
    std::map<int, StopInfo> _paths;

    void printResults(int endStop);
    std::priority_queue<Stop, std::vector<Stop>, CompareCurrentTime> initPriorityQueue(int h, int m, int startStop);
    void printJourney(int stop, int busTaken, Time deptTime);
    // A set is used here beacuse we don't want duplicate routes
    std::set<int> getRoutesLeavingFrom(int stopID);

};

#endif // DATASTRUCTURE_HH
