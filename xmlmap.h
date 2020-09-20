#ifndef XMLMAP_H
#define XMLMAP_H

#pragma once

#include <QObject>
#include <pugixml.hpp>
#include <iostream>
#include <vector>
#include <string>

typedef struct  {
    double x;
    double y;
} coord;

typedef struct  {
    coord coords;
    std::string color;
} cone;

class XMLMap : public QObject
{
    Q_OBJECT
public:
    explicit XMLMap(const char* file, QObject *parent = nullptr);   
    std::vector<cone> getCones() const;

signals:

private:
    void parse(pugi::xpath_node_set pose_nodes, pugi::xpath_node_set color_nodes);
    std::vector<cone> v_cones;
};

#endif // XMLMAP_H
