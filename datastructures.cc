// Datastructures.cc
#include "datastructures.hh"
#include <iostream>
#include <list>
#include <random>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type> Type random_in_range(Type start, Type end) {
  auto range = end - start;
  ++range;

  auto num = std::uniform_int_distribution<unsigned long int>(0, range - 1)(
      rand_engine);

  return static_cast<Type>(start + num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures() {
  // Write any initialization you need here
}

Datastructures::~Datastructures() {
  // Write any cleanup you need here
}

unsigned int Datastructures::station_count() { return stations.size(); }

void Datastructures::clear_all() {

  manhattan_distances.clear();
  stations_ids.clear();
  stations.clear();
  regions.clear();
}

std::vector<StationID> Datastructures::all_stations() { return stations_ids; }

bool Datastructures::add_station(StationID id, const Name &name, Coord coord) {
  std::map<StationID, Station>::iterator it_station;

  it_station = stations.find(id);

  if (it_station == stations.end()) {
    Station new_station;
    new_station.name = name;
    new_station.stationID = id;
    new_station.coord = coord;
    stations_ids.push_back(id);
    manhattan_distances.push_back(std::make_pair(
        id, std::make_pair(coord.y, abs(coord.x) + abs(coord.y))));
    stations.insert({id, new_station});
    return true;
  }
  return false;
}

Name Datastructures::get_station_name(StationID id) {
  std::map<StationID, Station>::iterator it_station;
  it_station = stations.find(id);

  if (it_station != stations.end()) {
    return it_station->second.name;
  }
  return NO_NAME;
}

Coord Datastructures::get_station_coordinates(StationID id) {
  std::map<StationID, Station>::iterator it_station;
  it_station = stations.find(id);

  if (it_station != stations.end()) {
    return it_station->second.coord;
  }
  return NO_COORD;
}

std::vector<StationID> Datastructures::stations_alphabetically() {

  std::vector<Station> sorted_stations;
  for (auto &station : stations) {
    sorted_stations.push_back(station.second);
  }

  std::sort(sorted_stations.begin(), sorted_stations.end(),
            [](const Station &x, const Station &y) { return x.name < y.name; });

  std::vector<StationID> ids;

  for (auto &station : sorted_stations) {
    ids.push_back(station.stationID);
  }
  return ids;
}

std::vector<StationID> Datastructures::stations_distance_increasing() {

  std::sort(manhattan_distances.begin(), manhattan_distances.end(),
            [](const auto &x, const auto &y) {
              if (x.second.second != y.second.second) {
                return x.second.second < y.second.second;
              } else if (x.second.first != y.second.first) {
                return x.second.first < y.second.first;
              } else {
                return x.first < y.first;
              }
            });

  std::vector<StationID> distance_increasing;

  for (const auto &i : manhattan_distances) {
    distance_increasing.push_back(i.first);
  }
  return distance_increasing;
}

std::vector<StationID> Datastructures::find_stations_with_coord(Coord xy) {
  std::vector<StationID> stations_with_coord;
  for (auto &it : stations) {
    if (it.second.coord == xy) {
      stations_with_coord.push_back(it.first);
    }
  }
  return stations_with_coord;
}

bool Datastructures::change_station_coord(StationID id, Coord newcoord) {
  std::map<StationID, Station>::iterator it_station;
  it_station = stations.find(id);

  if (it_station != stations.end()) {
    it_station->second.coord = newcoord;
    for (auto &coord : manhattan_distances) {
      if (coord.first == id) {
        coord.second =
            std::make_pair(newcoord.y, abs(newcoord.x) + abs(newcoord.y));
        return true;
      }
    }
  }
  return false;
}

bool Datastructures::add_departure(StationID stationid, TrainID trainid,
                                   Time time) {
  std::map<StationID, Station>::iterator it;
  it = stations.find(stationid);

  if (it == stations.end()) {
    return false;
  }

  auto &departures = it->second.departures;

  for (auto const &departure : departures) {
    if (departure.first == time && departure.second == trainid) {
      return false;
    }
  }
  departures.insert({time, trainid});
  return true;
}

bool Datastructures::remove_departure(StationID stationid, TrainID trainid,
                                      Time time) {
  std::map<StationID, Station>::iterator it_station;
  it_station = stations.find(stationid);

  if (it_station != stations.end()) {
    auto &departures = it_station->second.departures;
    auto deparure_exist = departures.find(time);
    if (deparure_exist != departures.end() &&
        deparure_exist->second == trainid) {
      departures.erase(deparure_exist);
      return true;
    }
  }
  return false;
}

std::vector<std::pair<Time, TrainID>>
Datastructures::station_departures_after(StationID stationid, Time time) {
  std::map<StationID, Station>::iterator it_station;
  std::vector<std::pair<Time, TrainID>> departures_after;

  it_station = stations.find(stationid);
  if (it_station == stations.end()) {
    return {{NO_TIME, NO_TRAIN}};
  }

  for (const auto &departure : it_station->second.departures) {
    if (departure.first >= time) {
      departures_after.push_back(departure);
    }
  }

  return departures_after;
}

bool Datastructures::add_region(RegionID id, const Name &name,
                                std::vector<Coord> coords) {
  std::map<RegionID, Region>::iterator it_region;
  it_region = regions.find(id);

  if (it_region == regions.end()) {
    Region new_region;
    new_region.id = id;
    new_region.name = name;
    new_region.coords = coords;
    regions[id] = new_region;
    return true;
  }

  return false;
}

std::vector<RegionID> Datastructures::all_regions() {
  std::vector<RegionID> ids;
  for (const auto &i : regions) {
    ids.push_back(i.first);
  }

  return ids;
}

Name Datastructures::get_region_name(RegionID id) {
  std::map<RegionID, Region>::iterator it_region;
  it_region = regions.find(id);

  if (it_region != regions.end()) {
    return it_region->second.name;
  }

  return NO_NAME;
}

std::vector<Coord> Datastructures::get_region_coords(RegionID id) {
  std::map<RegionID, Region>::iterator it_region;
  it_region = regions.find(id);

  if (it_region != regions.end()) {
    return it_region->second.coords;
  }

  return {NO_COORD};
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid) {
  std::map<RegionID, Region>::iterator it_subregion;
  std::map<RegionID, Region>::iterator it_parentID;

  it_subregion = regions.find(id);
  it_parentID = regions.find(parentid);

  if (it_subregion == regions.end()) {
    return false;
  }

  if (it_parentID == regions.end()) {
    return false;
  }

  if (it_subregion->second.parent_region != NO_REGION) {
    return false;
  }

  it_parentID->second.subregions.push_back(id);
  it_subregion->second.parent_region = parentid;
  return true;
}

bool Datastructures::add_station_to_region(StationID id, RegionID parentid) {
  std::map<RegionID, Region>::iterator it_region;
  it_region = regions.find(parentid);

  std::map<StationID, Station>::iterator it_station;
  it_station = stations.find(id);

  if (it_station == stations.end() || it_region == regions.end()) {
    return false;
  }

  if (it_station->second.region != NO_REGION) {
    return false;
  }

  it_region->second.stations_in_region.push_back(id);
  it_station->second.region = parentid;
  return true;
}

std::vector<RegionID> Datastructures::station_in_regions(StationID id) {
  auto it_station = stations.find(id);
  if (it_station == stations.end()) {
    return {NO_REGION};
  }

  std::vector<RegionID> subregions;
  auto root = it_station->second.region;

  if (root == NO_REGION) {
    return subregions;
  }

  auto it_region = regions.find(root);
  subregions.push_back(it_region->first);

  while (it_region->second.parent_region != NO_REGION) {
    subregions.push_back(it_region->second.parent_region);
    it_region = regions.find(it_region->second.parent_region);
  }

  return subregions;
}

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id) {
  auto it_region = regions.find(id);
  std::vector<RegionID> region_ids;

  if (it_region == regions.end()) {
    return {NO_REGION};
  }

  if (it_region->second.subregions.empty()) {
    return region_ids;
  }

  auto all_subregions = subregions_of_region_recursion(region_ids, id);
  std::sort(all_subregions.begin(), all_subregions.end());

  auto remove_duplicates =
      std::unique(all_subregions.begin(), all_subregions.end());

  all_subregions.resize(
      std::distance(all_subregions.begin(), remove_duplicates));
  return all_subregions;
}

std::vector<StationID> Datastructures::stations_closest_to(Coord /*xy*/) {
  // Replace the line below with your implementation
  throw NotImplemented("stations_closest_to()");
}

bool Datastructures::remove_station(StationID id) {
  auto it_station = stations.find(id);
  if (it_station == stations.end()) {
    return false;
  }

  for (auto &region : regions) {
    auto station_in_region = region.second.stations_in_region;
    if (std::find(station_in_region.begin(), station_in_region.end(), id) !=
        station_in_region.end()) {
      station_in_region.clear();
    }
  }

  for (auto it = manhattan_distances.begin(); it != manhattan_distances.end();
       ++it) {
    if (it->first == id) {
      manhattan_distances.erase(it);
      break;
    }
  }

  for (auto station = stations_ids.begin(); station != stations_ids.end();
       ++station) {
    if (*station == id) {
      stations_ids.erase(station);
      break;
    }
  }

  stations.erase(id);
  return true;
}

RegionID Datastructures::common_ancestor_of_regions(RegionID /*id1*/,
                                                    RegionID /*id2*/) {
  // Replace the line below with your implementation
  throw NotImplemented("common_ancestor_of_regions()");
}

// prg2 functions below

bool Datastructures::add_train(
    TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes) {

  auto it_train = trains.find(trainid);

  if (it_train != trains.end()) {
    return false;
  }

  for (auto &station : stationtimes) {

    if (stations.find(station.first) == stations.end()) {
      return false;
    }
  }

  for (auto &station : stationtimes) {

    std::pair stationTimes = std::make_pair(station.first, station.second);
    trains[trainid].push_back(stationTimes);
    add_departure(station.first, trainid, station.second);
  }
  return true;
}

std::vector<StationID> Datastructures::next_stations_from(StationID id) {

  auto it_station = stations.find(id);

  if (it_station == stations.end()) {
    return {NO_STATION};
  }

  std::vector<StationID> next_stations;

  if (it_station->second.departures.empty()) {
    return next_stations;
  }

  for (auto &train : trains) {
    for (auto station = train.second.begin(); station != train.second.end();
         ++station) {

      if (station->first == id) {
        auto next_station = std::next(station);

        if (next_station != train.second.end()) {
          next_stations.push_back(next_station->first);
        }
      }
    }
  }
  return next_stations;
}

std::vector<StationID> Datastructures::train_stations_from(StationID stationid,
                                                           TrainID trainid) {
  auto it_station = stations.find(stationid);
  if (it_station == stations.end()) {

    return {NO_STATION};
  }

  auto it_train = trains.find(trainid);
  if (it_train == trains.end()) {

    return {NO_STATION};
  }

  StationID last_station_of_the_route = it_train->second.back().first;
  if (stationid == last_station_of_the_route) {

    return {NO_STATION};
  }

  StationID first_station_of_the_route = it_train->second.begin()->first;

  std::vector<StationID> train_stations_from;
  bool station_in_route = false;

  for (auto station = it_train->second.begin();
       station != it_train->second.end(); ++station) {

    auto next_station = std::next(station);

    if (station->first == stationid) {
      station_in_route = true;
    }

    if (next_station->first == last_station_of_the_route) {
      train_stations_from.push_back(next_station->first);
      break;
    }

    if (next_station->first != stationid) {
      train_stations_from.push_back(next_station->first);
    }
  }

  if (!station_in_route) {
    return {NO_STATION};
  }

  return train_stations_from;
}
void Datastructures::clear_trains() {

  for (auto &station : stations) {
    station.second.departures.clear();
  }

  trains.clear();
}

std::vector<std::pair<StationID, Distance>>
Datastructures::route_any(StationID fromid, StationID toid) {

  auto it_from_station = stations.find(fromid);
  auto it_to_station = stations.find(toid);

  if (it_from_station == stations.end() || it_to_station == stations.end()) {
    return {{NO_STATION, NO_DISTANCE}};
  }

  std::vector<std::pair<StationID, Distance>> route;

  if (fromid == toid) {
    return route;
  }

  std::map<StationID, std::list<std::pair<StationID, Distance>>> graph =
      train_graph();
  std::map<StationID, bool> visited;

  depth_first_search(fromid, toid, route, visited, graph, 0);
  std::reverse(route.begin(), route.end());

  if (route.size() == 1) {
    route.erase(route.begin());
    return route;
  }
  std::vector<std::pair<StationID, Distance>> checked_route =
      check_route(route, toid);

  return checked_route;
}

std::vector<std::pair<StationID, Distance>>
Datastructures::route_least_stations(StationID /*fromid*/, StationID /*toid*/) {
  // Replace the line below with your implementation
  throw NotImplemented("route_least_stations()");
}

std::vector<StationID> Datastructures::route_with_cycle(StationID /*fromid*/) {
  // Replace the line below with your implementation
  throw NotImplemented("route_with_cycle()");
}

std::vector<std::pair<StationID, Distance>>
Datastructures::route_shortest_distance(StationID /*fromid*/,
                                        StationID /*toid*/) {
  // Replace the line below with your implementation
  throw NotImplemented("route_shortest_distance()");
}

std::vector<std::pair<StationID, Time>>
Datastructures::route_earliest_arrival(StationID /*fromid*/, StationID /*toid*/,
                                       Time /*starttime*/) {
  // Replace the line below with your implementation
  throw NotImplemented("route_earliest_arrival()");
}
