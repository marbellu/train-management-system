// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>


#include "customtypes.hh"


class Datastructures {
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: function returns the size of the stations map
  //                               which has a constant time complexity
  unsigned int station_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: function clears all the data structures
  //                               which has a linear time complexity for
  //                               vectors and maps
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: The actual time performance is O(1) because
  //                                function return the vector with ids.
  std::vector<StationID> all_stations();

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches from a  map  for a specific
  // id using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  bool add_station(StationID id, Name const &name, Coord xy);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches for a specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  Name get_station_name(StationID id);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches for a specific id from the
  //                               map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  Coord get_station_coordinates(StationID id);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: function sorts vector using "sort" which has
  // a linearithmic
  //                               worst case time complexity
  std::vector<StationID> stations_alphabetically();

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: function sorts vector using "sort" which has
  // a linearithmic
  //                               worst case time complexity
  std::vector<StationID> stations_distance_increasing();

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  //                               For that it has linear time complexity
  std::vector<StationID> find_stations_with_coord(Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: time complexity is determined by the loop
  // which is dependant on size of the map
  bool change_station_coord(StationID id, Coord newcoord);

  // Estimate of performance: O(n)
  // Short rationale for estimate: time complexity is determined by the loop
  // which is dependant on size of the map
  bool add_departure(StationID stationid, TrainID trainid, Time time);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches for a specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  bool remove_departure(StationID stationid, TrainID trainid, Time time);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  //                               For that it has linear time complexity
  std::vector<std::pair<Time, TrainID>>
  station_departures_after(StationID stationid, Time time);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches  for specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  bool add_region(RegionID id, Name const &name, std::vector<Coord> coords);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  //                               for that it has linear time complexity
  std::vector<RegionID> all_regions();

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches  for specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  Name get_region_name(RegionID id);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches  for specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  std::vector<Coord> get_region_coords(RegionID id);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches  for specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  bool add_subregion_to_region(RegionID id, RegionID parentid);

  // Estimate of performance: O(log n)
  // Short rationale for estimate: function searches  for specific id from the
  // map using "find"
  //                               and therefore has a logarithmic time
  //                               complexity
  bool add_station_to_region(StationID id, RegionID parentid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  //                               for that it has linear time complexity
  std::vector<RegionID> station_in_regions(StationID id);

  // Non-compulsory operations

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: at the end function sorts the vector using
  // "sort" which has a logarthmic
  //                               worst case time complexity
  std::vector<RegionID> all_subregions_of_region(RegionID id);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<StationID> stations_closest_to(Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  //                               for that it has linear time complexity
  bool remove_station(StationID id);

  // Estimate of performance:
  // Short rationale for estimate:
  RegionID common_ancestor_of_regions(RegionID id1, RegionID id2);

  //
  // New assignment 2 operations
  //

  // Estimate of performance: O(n)
  // Short rationale for estimate: function contains loop that is dependent on
  // the size of the maps
  bool add_train(TrainID trainid,
                 std::vector<std::pair<StationID, Time>> stationtimes);

  // Estimate of performance: O(n^2)
  // Short rationale for estimate: funtion contains nested loops, both of which
  // are dependent on the size of the maps
  std::vector<StationID> next_stations_from(StationID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function uses first find, which has a O log n
  //                               time complexity,
  //                               and then uses iterator from the find, to find
  //                               the needed station. The time complexity is
  //                               therefore linear.
  std::vector<StationID> train_stations_from(StationID stationid,
                                             TrainID trainid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: function loops through the map and is
  // dependent on the size of it.
  void clear_trains();

  // Estimate of performance:O(n^2)
  // Short rationale for estimate: function uses helper function which has
  //                                nested loop.
  std::vector<std::pair<StationID, Distance>> route_any(StationID fromid,
                                                        StationID toid);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<StationID, Distance>>
  route_least_stations(StationID fromid, StationID toid);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<StationID> route_with_cycle(StationID fromid);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<StationID, Distance>>
  route_shortest_distance(StationID fromid, StationID toid);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<StationID, Time>>
  route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:
  struct Station {
    StationID stationID;
    std::string name;
    Coord coord;
    std::multimap<Time, TrainID> departures;
    RegionID region = NO_REGION;
  };

  std::vector<std::pair<StationID, std::pair<int, int>>> manhattan_distances;
  std::vector<StationID> stations_ids;

  std::map<StationID, Station> stations;

  struct Region {
    RegionID id;
    std::string name;
    std::vector<Coord> coords;
    std::vector<RegionID> subregions;
    std::vector<StationID> stations_in_region;
    RegionID parent_region = NO_REGION;
  };

  std::map<TrainID, std::vector<std::pair<StationID, Time>>> trains;
  std::map<RegionID, Region> regions;

  std::vector<RegionID>
  subregions_of_region_recursion(std::vector<RegionID> regions_ids,
                                 RegionID id) {

    auto it_region = regions.find(id);

    auto subreg = it_region->second.subregions;
    if (subreg.empty()) {
      return regions_ids;
    }

    for (auto const &region : subreg) {
      auto next_region = subregions_of_region_recursion(subreg, region);

      regions_ids.insert(regions_ids.begin(), next_region.begin(),
                         next_region.end());
    }
    return regions_ids;
  }

  std::map<StationID, std::list<std::pair<StationID, Distance>>> train_graph() {

    std::map<StationID, std::list<std::pair<StationID, Distance>>> connections;

    for (auto const &train : trains) {
      for (size_t i = 0; i < train.second.size() - 1; i++) {

        StationID from = train.second[i].first;
        StationID to = train.second[i + 1].first;
        int distance = manhattan_distance_of_stations(to, from);
        connections[from].push_back({to, distance});
      }
    }
    return connections;
  }

  void depth_first_search(
      StationID current, StationID final,
      std::vector<std::pair<StationID, Distance>> &path,
      std::map<StationID, bool> &visited,
      std::map<StationID, std::list<std::pair<StationID, Distance>>> &graph,
      int distance) {

    visited[current] = true;

    if (current == final) {
      path.push_back({current, distance});
      return;
    }

    for (auto &station : graph[current]) {

      if (!visited[station.first]) {
        depth_first_search(station.first, final, path, visited, graph,
                           distance + station.second);

        if (!path.empty() && path.back().first == final) {
          path.push_back({current, distance});
          return;
        }
        path.push_back({current, distance});
      }
    }
    visited[current] = false;
  }

  std::vector<std::pair<StationID, Distance>>
  check_route(std::vector<std::pair<StationID, Distance>> &path,
              StationID final) {
    std::vector<std::pair<StationID, Distance>> checked_path;
    for (auto &station : path) {
      if (station.first == final) {
        checked_path.push_back(station);
        break;
      }
      if (std::find(checked_path.begin(), checked_path.end(), station) ==
          checked_path.end()) {
        checked_path.push_back(station);
      }
    }
    return checked_path;
  }

  int manhattan_distance_of_stations(StationID id1, StationID id2) {
    auto stat1 = stations.find(id1);

    auto stat2 = stations.find(id2);

    int manhattan_distance =
        abs(stat2->second.coord.x - stat1->second.coord.x) +
        abs(stat2->second.coord.y - stat1->second.coord.y);
    return manhattan_distance;
  }
};

#endif // DATASTRUCTURES_HH
