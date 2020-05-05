//********************************
// LARA - XML Preprocessor
// (c) 2016 DFKI / AV
//********************************

#include <math.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// tinyxml
#define NOMINMAX
#include "tinyxml.h"

struct feature {
  std::string type;
  int id;
};

struct pipe_node_feature : public feature {
  double x;
  double y;
  double z;
  double z_ground;
};

struct pipe_point {
  double x;
  double y;
};

struct curvy_pipe_feature : public feature {
  std::string material;
  double diameter;
  double x1;
  double y1;
  double z1;
  double z1_ground;
  double x2;
  double y2;
  double z2;
  double z2_ground;
  std::string rgb;
  std::vector<pipe_point> curve;
};

struct pipe_feature : public feature {
  std::string material;
  double diameter;
  double x1;
  double y1;
  double z1;
  double z1_ground;
  double x2;
  double y2;
  double z2;
  double z2_ground;
  std::string rgb;
};

struct manhole_feature : public feature {
  double diam_meter;
  double x;
  double y;
  double z;
  double z_ground;
  double depth;
  std::string rgb;
};

struct building_node_feature : public feature {
  double x;
  double y;
  double z_ground;
  int build_id;
};

struct building_point {
  double x;
  double y;
};

struct building_feature : public feature {
  std::vector<building_point> polygon;
  int build_id;
};

struct building_segment : public feature {
  double x1;
  double y1;
  double z1_ground;
  double x2;
  double y2;
  double z2_ground;
};

std::string extract_param_string(
    TiXmlElement* e_feature, const std::string& param_name, bool& ok) {
  std::string content = "";
  if (e_feature->FirstChild(param_name.c_str(), true) != NULL) {
    if (e_feature->FirstChild(param_name.c_str(), true)->FirstChild() != NULL) {
      content = e_feature->FirstChild(param_name.c_str(), true)
                    ->FirstChild()
                    ->Value();
      // std::cout << param_name << ": " << content << std::endl;

      return content;
    }
  }

  ok = false;
  return content;
}

double extract_param_double(
    TiXmlElement* e_feature,
    const std::string& param_name,
    bool& ok,
    unsigned int precision = 3) {
  double value = 0.0;
  if (e_feature->FirstChild(param_name.c_str(), true) != NULL) {
    if (e_feature->FirstChild(param_name.c_str(), true)->FirstChild() != NULL) {
      std::string content = e_feature->FirstChild(param_name.c_str(), true)
                                ->FirstChild()
                                ->Value();
      std::stringstream ssfull_value(content);
      double full_value;
      ssfull_value >> full_value;
      double full_valueint = round(full_value * pow(10.0, precision));
      value = full_valueint / pow(10.0, precision);

      return value;
    }
  }

  ok = false;
  return value;
}

double extract_value(const std::string& text, unsigned int precision = 3) {
  std::string local_text = text;
  // remove unwanted characters
  while (local_text.at(0) == '(') {
    local_text = local_text.substr(1, local_text.size() - 1);
  }
  while (local_text.at(local_text.size() - 1) == ')') {
    local_text = local_text.substr(0, local_text.size() - 1);
  }
  while (local_text.at(local_text.size() - 1) == ',') {
    local_text = local_text.substr(0, local_text.size() - 1);
  }

  // convert to  double with precision
  std::stringstream ssfull_value(local_text);
  double full_value;
  ssfull_value >> full_value;
  double full_valueint = round(full_value * pow(10.0, precision));
  double value = full_valueint / pow(10.0, precision);
  return value;
}

// case insensitive compare
bool ci_cmp(const std::string& str1, const std::string& str2) {
  std::string s1 = str1;
  std::string s2 = str2;
  std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
  std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

  return s1 == s2;
}

bool is_type(const std::string& generic_type, const std::string& feature_type) {
  if (generic_type == "pipe") {
    if (ci_cmp(feature_type, "district-heating pipe") ||
        ci_cmp(feature_type, "rainwater pipe") ||
        ci_cmp(feature_type, "sewage pipe") ||
        ci_cmp(feature_type, "water pipe") ||
        ci_cmp(feature_type, "gas pipe")) {
      return true;
    }
  } else if (generic_type == "manhole") {
    if (ci_cmp(feature_type, "district-heating manhole") ||
        ci_cmp(feature_type, "rainwater manhole") ||
        ci_cmp(feature_type, "sewage manhole") ||
        ci_cmp(feature_type, "water manhole")) {
      return true;
    }
  } else if (generic_type == "building") {
    if (ci_cmp(feature_type, "building")) {
      return true;
    }
  } else if (generic_type == "building node") {
    if (ci_cmp(feature_type, "building node") ||
        ci_cmp(feature_type, "EMPTY TYPE")) {
      return true;
    }
  } else if (generic_type == "building segment") {
    if (ci_cmp(feature_type, "building segment")) {
      return true;
    }
  } else if (generic_type == "pipe node") {
    if (ci_cmp(feature_type, "district-heating node") ||
        ci_cmp(feature_type, "rainwater node") ||
        ci_cmp(feature_type, "sewage node") ||
        ci_cmp(feature_type, "water node")) {
      return true;
    }
  } else if (generic_type == "ignored type") {
    if (ci_cmp(feature_type, "district heating node") ||
        ci_cmp(feature_type, "water node")) {
      return true;
    }
  }

  return false;
}

std::string write_elem(
    const std::string& elem_name, double value, unsigned int precision = 3) {
  std::stringstream ssElem;
  ssElem << "\t\t<" << elem_name << ">" << std::fixed
         << std::setprecision(precision) << value << "</" << elem_name << ">"
         << std::endl;
  return ssElem.str();
}

std::string write_elem(const std::string& elem_name, std::string text) {
  std::stringstream ssElem;
  ssElem << "\t\t<" << elem_name << ">" << text << "</" << elem_name << ">"
         << std::endl;
  return ssElem.str();
}

void update_mins(double& xmin, double& ymin, feature* feature_ptr) {
  if (is_type("pipe", feature_ptr->type)) {
    pipe_feature* pipe_ptr = (pipe_feature*)(feature_ptr);
    if (xmin > pipe_ptr->x1) xmin = pipe_ptr->x1;
    if (xmin > pipe_ptr->x2) xmin = pipe_ptr->x2;
    if (ymin > pipe_ptr->y1) ymin = pipe_ptr->y1;
    if (ymin > pipe_ptr->y2) ymin = pipe_ptr->y2;
  } else if (is_type("manhole", feature_ptr->type)) {
    manhole_feature* manhole_ptr = (manhole_feature*)(feature_ptr);
    if (xmin > manhole_ptr->x) xmin = manhole_ptr->x;
    if (ymin > manhole_ptr->y) ymin = manhole_ptr->y;

  } else if (is_type("building segment", feature_ptr->type)) {
    building_segment* segment_ptr = (building_segment*)(feature_ptr);
    if (xmin > segment_ptr->x1) xmin = segment_ptr->x1;
    if (xmin > segment_ptr->x2) xmin = segment_ptr->x2;
    if (ymin > segment_ptr->y1) ymin = segment_ptr->y1;
    if (ymin > segment_ptr->y2) ymin = segment_ptr->y2;
  }
}

// main function
int main(int argc, char* argv[]) {
  std::string cam_mins_filename =
      "E:/ARINFUSE/Data/Cyprus_data_3/camera_mins.txt";
  std::string preprocessed_filename =
      "E:/ARINFUSE/Data/Cyprus_data_3/preprocessed.xml";
  std::string xml_filename =
      "E:/ARINFUSE/Data/Cyprus_data_3/CyprusUtilitiesXML.xml";

  // process arguments
  for (unsigned int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-i")) {
      if (i < argc - 1) xml_filename = argv[i + 1];
    }
    if (!strcmp(argv[i], "-c")) {
      if (i < argc - 1) cam_mins_filename = argv[i + 1];
    }
    if (!strcmp(argv[i], "-o")) {
      if (i < argc - 1) preprocessed_filename = argv[i + 1];
    }
    if (!strcmp(argv[i], "-h")) {
      std::cout << "Usage: " << argv[0]
                << " -i clipped_underNetworks.xml -o preprocessed.xml -c "
                   "camera_mins.txt"
                << std::endl;
      return 0;
    }
  }

  TiXmlDocument xmlDoc(xml_filename.c_str());
  if (!xmlDoc.LoadFile()) {
    std::cout << "Could not load the input file :" << xml_filename << std::endl;
    std::cout << "Call with -h for help." << std::endl;
    return 0;
  }

  TiXmlHandle doc_handle(&xmlDoc);

  // map to store all the possible features types
  std::map<std::string, unsigned int> possibleFeaturesTypes;
  std::vector<pipe_feature> vPipes;
  std::vector<curvy_pipe_feature> vCurvyPipes;
  std::vector<pipe_node_feature> vPipeNodes;
  std::vector<manhole_feature> vManholes;
  std::vector<building_node_feature> vBuildingNodes;
  std::vector<building_feature> vBuildings;
  std::vector<building_segment> vBuildingSegments;

  // look for the first feature element
  TiXmlElement* e_feature = doc_handle.Child("clipped_underNetworks", 0)
                                .FirstChild("feature")
                                .Element();

  int max_id = -2;

  // loop over the features
  for (e_feature; e_feature; e_feature = e_feature->NextSiblingElement()) {
    int feature_id = -1;
    // look for feature id
    if (e_feature->Attribute("id") != NULL) {
      // std::cout << "id=" << e_feature->Attribute("id") << std::endl;
      std::stringstream ssID(e_feature->Attribute("id"));

      ssID >> feature_id;
      if (feature_id > max_id) {
        max_id = feature_id;
      }
      // std::cout << "id=" << feature_id << std::endl;
    }

    // look for feature type
    std::string feature_type = "EMPTY TYPE";
    bool ok = true;
    std::string content = extract_param_string(e_feature, "type", ok);
    if (ok) {
      feature_type = content;
      // bugfixes
      if (feature_type == "rainwater type") feature_type = "rainwater pipe";
      if (feature_type == "Building nodes") feature_type = "building node";
      if (feature_type == "Sewage pipes") feature_type = "sewage pipe";
      if (feature_type == "Water") feature_type = "water pipe";
    }

    // count the number of feature types for each type
    possibleFeaturesTypes[feature_type]++;

    // SPECIFIC ACTIONS FOR EACH TYPE:

    if (is_type("pipe", feature_type)) {
      // this is a feature of type pipe, first read it as a curvy pipe
      curvy_pipe_feature pipe;
      pipe.type = feature_type;
      pipe.id = feature_id;

      bool ok = true;
      pipe.diameter = extract_param_double(e_feature, "DIAMETER", ok, 3);
      pipe.x1 = extract_param_double(e_feature, "X1", ok, 3);
      pipe.y1 = extract_param_double(e_feature, "Y1", ok, 3);
      pipe.z1 = extract_param_double(e_feature, "Z1", ok, 3);
      pipe.z1_ground = extract_param_double(e_feature, "Z1_ground", ok, 3);
      pipe.x2 = extract_param_double(e_feature, "X2", ok, 3);
      pipe.y2 = extract_param_double(e_feature, "Y2", ok, 3);
      pipe.z2 = extract_param_double(e_feature, "Z2", ok, 3);
      pipe.z2_ground = extract_param_double(e_feature, "Z2_ground", ok, 3);
      pipe.material = extract_param_string(e_feature, "MATERIAL", ok);
      if (!ok) {
        ok = true;
        pipe.material = "default_material";  // defaulting
      }
      pipe.rgb = extract_param_string(e_feature, "RGB", ok);

      std::string the_geom = extract_param_string(e_feature, "the_geom", ok);

      // Checking if hte pipes have z values if 0 then put dummy values
      if (pipe.z1 == 0 || pipe.z1_ground == 0) {
        pipe.z1_ground = pipe.z1 = 7;
      }

      if (pipe.z2 == 0 || pipe.z2_ground == 0) {
        pipe.z2_ground = pipe.z2 = 7;
      }
      //---------------------------------------------------------------

      // now process the polygon
      if (ok) {
        std::stringstream ss_geom(the_geom);
        std::string dummy;
        ss_geom >> dummy;  // this should be MULTILINSTRING
        std::vector<double> vCoords;
        while (!ss_geom.eof()) {
          ss_geom >> dummy;
          double value = extract_value(dummy);
          vCoords.push_back(value);
        }
        // now we have all the values of the polygon in a vector of doubles

        unsigned int size = vCoords.size();
        if (size % 2 == 1)  // if size is not even - strange
        {
          std::cout << "Strange - multilinestring coords is not an even number"
                    << std::endl;
        }

        for (unsigned int i = 0; i < size / 2; i++) {
          pipe_point point;
          point.x = vCoords[2 * i];
          point.y = vCoords[2 * i + 1];

          pipe.curve.push_back(point);
        }
      }
      if (ok) {
        vCurvyPipes.push_back(pipe);
      } else {
        std::cout << "Warning! Failed while reading a feature of type \""
                  << feature_type
                  << "\", because one of the necessary parameters is missing "
                     "or wrongly tagged."
                  << std::endl;
      }

    }

    else if (is_type("manhole", feature_type)) {
      // this is a feature of type manhole
      manhole_feature manhole;
      manhole.type = feature_type;
      manhole.id = feature_id;

      bool ok = true;

      manhole.diam_meter = extract_param_double(e_feature, "Diam_meter", ok, 3);
      if (!ok) {
        ok = true;
        manhole.diam_meter = 0.6;  // Starting to put defaults
      }
      manhole.x = extract_param_double(e_feature, "X", ok, 3);
      manhole.y = extract_param_double(e_feature, "Y", ok, 3);
      manhole.z = extract_param_double(e_feature, "Z", ok, 3);
      manhole.z_ground = extract_param_double(e_feature, "Z_ground", ok, 3);
      manhole.depth = extract_param_double(e_feature, "DEPTH", ok, 3);
      manhole.rgb = extract_param_string(e_feature, "RGB", ok);

      // Just to test Z values and replace them with dummy values.
      if (manhole.z == 0 || manhole.z_ground == 0) {
        manhole.z = 7;
        manhole.z_ground = 7;
      }

      //---------------------

      if (ok) {
        vManholes.push_back(manhole);
      } else {
        std::cout << "Warning! Failed while reading a feature of type \""
                  << feature_type
                  << "\", because one of the necessary parameters is missing "
                     "or wrongly tagged."
                  << std::endl;
      }

    }

    else if (is_type("building", feature_type)) {
      // this is a feature of type building
      building_feature building;
      building.type = feature_type;
      building.id = feature_id;

      bool ok = true;
      building.build_id = extract_param_double(e_feature, "Build_Id", ok, 0);
      std::string the_geom = extract_param_string(e_feature, "the_geom", ok);

      // now process the polygon
      if (ok) {
        std::stringstream ss_geom(the_geom);
        std::string dummy;
        ss_geom >> dummy;  // this should be MULTIPOLYGON
        std::vector<double> vCoords;
        while (!ss_geom.eof()) {
          ss_geom >> dummy;
          double value = extract_value(dummy);
          vCoords.push_back(value);
        }
        // now we have all the values of the polygon in a vector of doubles

        unsigned int size = vCoords.size();
        if (size % 2 == 1)  // if size is not even - strange
        {
          std::cout << "Strange - polygon coords is not an even number"
                    << std::endl;
        }

        for (unsigned int i = 0; i < size / 2; i++) {
          building_point point;
          point.x = vCoords[2 * i];
          point.y = vCoords[2 * i + 1];

          building.polygon.push_back(point);
        }

        vBuildings.push_back(building);

      } else {
        std::cout << "Warning! Failed while reading a feature of type \""
                  << feature_type
                  << "\", because one of the necessary parameters is missing "
                     "or wrongly tagged."
                  << std::endl;
      }

    }

    else if (is_type("building node", feature_type)) {
      // this is a feature of type building node
      building_node_feature building_node;
      building_node.type = feature_type;
      building_node.id = feature_id;

      bool ok = true;
      building_node.x = extract_param_double(e_feature, "X", ok, 3);
      building_node.y = extract_param_double(e_feature, "Y", ok, 3);
      building_node.z_ground =
          extract_param_double(e_feature, "Z_ground", ok, 3);
      building_node.build_id =
          extract_param_double(e_feature, "Build_Id", ok, 0);
      if (ok) {
        vBuildingNodes.push_back(building_node);
      } else {
        std::cout << "Warning! Failed while reading a feature of type \""
                  << feature_type
                  << "\", because one of the necessary parameters is missing "
                     "or wrongly tagged."
                  << std::endl;
      }
    }

    else if (is_type("pipe node", feature_type)) {
      // this is a feature of type pipe node
      pipe_node_feature pipe_node;
      pipe_node.type = feature_type;
      pipe_node.id = feature_id;

      bool ok = true;
      pipe_node.x = extract_param_double(e_feature, "X", ok, 3);
      pipe_node.y = extract_param_double(e_feature, "Y", ok, 3);
      pipe_node.z = extract_param_double(e_feature, "Z", ok, 3);
      pipe_node.z_ground = extract_param_double(e_feature, "Z_ground", ok, 3);

      // dummy z
      if (pipe_node.z == 0 || pipe_node.z_ground == 0) {
        pipe_node.z = pipe_node.z_ground = 0;
      }
      //----------------------------------------------------------
      if (ok) {
        vPipeNodes.push_back(pipe_node);
      } else {
        std::cout << "Warning! Failed while reading a feature of type \""
                  << feature_type
                  << "\", because one of the necessary parameters is missing "
                     "or wrongly tagged."
                  << std::endl;
      }
    }

    else if (is_type("ignored type", feature_type)) {
      // ignore this silently
    } else {
      std::cout << "Warning: found unknown type! I do not know what to do with "
                   "a feature called \""
                << feature_type
                << "\". Nothing will be rendered for that feature."
                << std::endl;
    }
  }

  /*std::cout << "list of all the types found:" << std::endl;

  for (auto&& feat : possibleFeaturesTypes)
  {
      std::cout << "[" << feat.first << "] - " << feat.second << std::endl;
  }

  std::cout << "pipes: " << vPipes.size() << std::endl;
  std::cout << "manholes: " << vManholes.size() << std::endl;
  std::cout << "buildings: " << vBuildings.size() << std::endl;
  std::cout << "building_nodes: " << vBuildingNodes.size() << std::endl;*/

  // now construct the building segments

  // create a map of all the building nodes for fast search

  std::map<std::pair<double, double>, building_node_feature>
      sorted_building_nodes;

  for (auto&& node : vBuildingNodes) {
    sorted_building_nodes[std::make_pair(node.x, node.y)] = node;
  }

  // create a map of all the pipe nodes for fast search

  std::map<std::pair<double, double>, pipe_node_feature> sorted_pipe_nodes;

  for (auto&& node : vPipeNodes) {
    sorted_pipe_nodes[std::make_pair(node.x, node.y)] = node;
  }

  // std::cout << "max_id=" << max_id << std::endl;

  // go over the buildings and create the segments
  std::map<std::pair<double, double>, building_node_feature>::iterator itMap;
  for (auto&& building : vBuildings) {
    unsigned int size = building.polygon.size();

    for (unsigned int i = 0; i < size - 1; i++) {
      // create a building segment
      building_segment segment;
      // search z-ground of one end (point 1)
      itMap = sorted_building_nodes.find(
          std::make_pair(building.polygon[i].x, building.polygon[i].y));
      if (itMap != sorted_building_nodes.end())  // if found
      {
        segment.x1 = itMap->second.x;
        segment.y1 = itMap->second.y;
        segment.z1_ground = itMap->second.z_ground;
        // std::cout << itMap->second.build_id << " - " << building.build_id <<
        // std::endl;
      } else {
        // std::cout << "node not found in building " << building.build_id <<
        // std::endl;
        continue;
      }
      // search z-ground of other end (point 2)
      itMap = sorted_building_nodes.find(
          std::make_pair(building.polygon[i + 1].x, building.polygon[i + 1].y));
      if (itMap != sorted_building_nodes.end())  // if found
      {
        segment.x2 = itMap->second.x;
        segment.y2 = itMap->second.y;
        segment.z2_ground = itMap->second.z_ground;
        // std::cout << itMap->second.build_id << " - " << building.build_id <<
        // std::endl;
      } else {
        // std::cout << "node not found in building " << building.build_id <<
        // std::endl;
        continue;
      }

      segment.type = "building segment";

      max_id++;
      segment.id = max_id;
      vBuildingSegments.push_back(segment);
    }
  }

  // go over the curvy pipes and create the segments
  std::map<std::pair<double, double>, pipe_node_feature>::iterator itPipeNode;
  for (auto&& cpipe : vCurvyPipes) {
    unsigned int size = cpipe.curve.size();

    for (unsigned int i = 0; i < size - 1; i++) {
      // create a building segment
      pipe_feature segment;
      // search z-ground of one end (point 1)

      if (i == 0) {
        segment.x1 = cpipe.x1;
        segment.y1 = cpipe.y1;
        segment.z1 = cpipe.z1;
        segment.z1_ground = cpipe.z1_ground;
      } else {
        itPipeNode = sorted_pipe_nodes.find(
            std::make_pair(cpipe.curve[i].x, cpipe.curve[i].y));
        if (itPipeNode != sorted_pipe_nodes.end())  // if found
        {
          segment.x1 = itPipeNode->second.x;
          segment.y1 = itPipeNode->second.y;
          segment.z1 = itPipeNode->second.z;
          segment.z1_ground = itPipeNode->second.z_ground;
          // std::cout << itMap->second.build_id << " - " << building.build_id
          // << std::endl;
        } else {
          segment.x1 = cpipe.curve[i].x;
          segment.y1 = cpipe.curve[i].y;
          segment.z1 = cpipe.z1;
          segment.z1_ground = cpipe.z1_ground;
        }
      }

      // search z-ground of other end (point 2)
      if (i == size - 1) {
        segment.x2 = cpipe.x2;
        segment.y2 = cpipe.y2;
        segment.z2 = cpipe.z2;
        segment.z2_ground = cpipe.z2_ground;
      } else {
        itPipeNode = sorted_pipe_nodes.find(
            std::make_pair(cpipe.curve[i + 1].x, cpipe.curve[i + 1].y));
        if (itPipeNode != sorted_pipe_nodes.end())  // if found
        {
          segment.x2 = itPipeNode->second.x;
          segment.y2 = itPipeNode->second.y;
          segment.z2 = itPipeNode->second.z;
          segment.z2_ground = itPipeNode->second.z_ground;
          // std::cout << itMap->second.build_id << " - " << building.build_id
          // << std::endl;
        } else {
          segment.x2 = cpipe.curve[i + 1].x;
          segment.y2 = cpipe.curve[i + 1].y;
          segment.z2 = cpipe.z2;
          segment.z2_ground = cpipe.z2_ground;
        }
      }

      segment.type = cpipe.type;

      segment.material = cpipe.material;
      segment.diameter = cpipe.diameter;
      segment.rgb = cpipe.rgb;
      max_id++;
      segment.id = max_id;
      vPipes.push_back(segment);
    }
  }

  // std::cout << "building_segments: " << vBuildingSegments.size() <<
  // std::endl; std::cout << "max_id=" << max_id << std::endl;

  // std::cout << "End" << std::endl;

  // now, write the file out
  // make a map of all the features to write out

  std::map<int, std::vector<feature*> >
      sorted_feature_ptrs;  // vector is used in order to handle the case where
                            // several objects have the same id...

  for (auto&& pipe : vPipes) {
    sorted_feature_ptrs[pipe.id].push_back(&pipe);
  }
  for (auto&& manhole : vManholes) {
    sorted_feature_ptrs[manhole.id].push_back(&manhole);
  }
  for (auto&& segment : vBuildingSegments) {
    sorted_feature_ptrs[segment.id].push_back(&segment);
  }

  // now go over the sorted list of features and write them out

  double xmin = std::numeric_limits<double>::max();
  double ymin = std::numeric_limits<double>::max();

  std::stringstream ssFile;

  ssFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
         << std::endl;
  ssFile << "<clipped_underNetworks>" << std::endl;

  for (auto&& map_it : sorted_feature_ptrs) {
    for (auto&& feature_ptr : map_it.second) {
      // std::cout << feature_ptr->id << " - " << feature_ptr->type <<
      // std::endl;
      update_mins(xmin, ymin, feature_ptr);
      ssFile << "\t<feature id=\"" << feature_ptr->id << "\">" << std::endl;

      if (is_type("pipe", feature_ptr->type)) {
        pipe_feature* pipe_ptr = (pipe_feature*)(feature_ptr);
        ssFile << write_elem("Type", pipe_ptr->type);
        ssFile << write_elem("X1", pipe_ptr->x1);
        ssFile << write_elem("Y1", pipe_ptr->y1);
        ssFile << write_elem("Z1", pipe_ptr->z1);
        ssFile << write_elem("Z1_ground", pipe_ptr->z1_ground);
        ssFile << write_elem("X2", pipe_ptr->x2);
        ssFile << write_elem("Y2", pipe_ptr->y2);
        ssFile << write_elem("Z2", pipe_ptr->z2);
        ssFile << write_elem("Z2_ground", pipe_ptr->z2_ground);
        ssFile << write_elem("DIAMETER", pipe_ptr->diameter, 3);
        ssFile << write_elem("MATERIAL", pipe_ptr->material);
        ssFile << write_elem("RGB", pipe_ptr->rgb);
      } else if (is_type("manhole", feature_ptr->type)) {
        manhole_feature* manhole_ptr = (manhole_feature*)(feature_ptr);
        ssFile << write_elem("Type", manhole_ptr->type);
        ssFile << write_elem("X", manhole_ptr->x);
        ssFile << write_elem("Y", manhole_ptr->y);
        ssFile << write_elem("Z", manhole_ptr->z);
        ssFile << write_elem("Z_ground", manhole_ptr->z_ground);
        ssFile << write_elem("Diam_meter", manhole_ptr->diam_meter);
        ssFile << write_elem("RGB", manhole_ptr->rgb);
      } else if (is_type("building segment", feature_ptr->type)) {
        building_segment* segment_ptr = (building_segment*)(feature_ptr);
        ssFile << write_elem("Type", segment_ptr->type);
        ssFile << write_elem("X1", segment_ptr->x1);
        ssFile << write_elem("Y1", segment_ptr->y1);
        ssFile << write_elem("Z1_ground", segment_ptr->z1_ground);
        ssFile << write_elem("X2", segment_ptr->x2);
        ssFile << write_elem("Y2", segment_ptr->y2);
        ssFile << write_elem("Z2_ground", segment_ptr->z2_ground);
      }

      ssFile << "\t</feature>" << std::endl;
    }
  }

  ssFile << "</clipped_underNetworks>" << std::endl;

  // std::cout << ssFile.str();

  std::ofstream output_file(preprocessed_filename);
  output_file << ssFile.str();
  output_file.close();

  std::ofstream output_file2(cam_mins_filename);
  output_file2 << std::fixed << std::setprecision(3) << xmin << " " << ymin
               << std::endl;
  output_file2.close();

  return 0;
}
