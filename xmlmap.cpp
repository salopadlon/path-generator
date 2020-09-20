#include "xmlmap.h"

XMLMap::XMLMap(const char* file, QObject *parent) : QObject(parent)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file);

    const std::string pose = "//pose";
    const std::string color = "//visual/geometry/mesh/uri";

    const pugi::xpath_node_set pose_nodes = doc.select_nodes(pose.c_str());
    const pugi::xpath_node_set color_nodes = doc.select_nodes(color.c_str());

    this->parse(pose_nodes, color_nodes);
}

void XMLMap::parse(pugi::xpath_node_set pose_nodes, pugi::xpath_node_set color_nodes)
{
    auto ipose = pose_nodes.begin();
    auto icolor = color_nodes.begin();

    for(; ipose != pose_nodes.end() && icolor != color_nodes.end(); ++ipose, ++icolor) {
        std::string pose = ipose->node().child_value();
        std::string color = icolor->node().child_value();
        cone cone_xml;

        cone_xml.coords.x = std::stod(pose.substr(0, pose.find(' ')));
        cone_xml.coords.y = std::stod(pose.substr(pose.find(' '), pose.find(' ')));

        if (color.find("blue") != std::string::npos) {
            cone_xml.color = "blue";
        }

        else if (color.find("yellow") != std::string::npos) {
            cone_xml.color = "yellow";
        }

        else if (color.find("orange") != std::string::npos) {
            cone_xml.color = "orange";
        }

        else {
            std::cout << "undefined color" << '\n';
        }

        this->v_cones.push_back(cone_xml);
    }
}

std::vector<cone> XMLMap::getCones() const
{
    return this->v_cones;
}
