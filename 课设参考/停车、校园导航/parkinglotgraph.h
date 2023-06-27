#ifndef PARKINGLOTGRAPH_H
#define PARKINGLOTGRAPH_H

#include "Road.h"
#include "ParkingSpaceWidget.h"
#include "path.h"
#include <QVector>
#include <QPoint>
#include <QGraphicsScene>
#include <QMap>
#include <QPixmap>
#include "Road.h"
#include "car.h"

class Car;
class ParkingLotGraph
{
public:
    struct Node{
    public:
        enum Type{entry = 1, stair, exit, queueHead, space, road, act};
        Node(const QPoint& p, Type t, uint n, int idd) : number(n), id(idd), type(t), data(p) {}
        void addPath(Node* another);
        uint number;
        int id;
        Type type;
        QPoint data;
        Road::Action action = Road::Action::none;
        QVector<Node*> adjacent;
        QVector<float> weight;
        int getId() const;
        Road::Action getAction() const;
        void setAction(const Road::Action &value) {
            action = value;
        }
    };
    ParkingLotGraph(const ParkingLotWidget*pkl);
    Node* addNode(QPoint p, Node::Type t, uint n) {
        Node* no = new Node(p, t, n, m_all.size());
        m_all.push_back(no);
        return no;
    }
    void paint(QGraphicsScene* scene);

    Path* findPath(Node::Type t1, int n1, Node::Type t2, int n2);

    Path* findPath(Car* car, int entry);
    uint getNodeId(Node::Type t, int n);
    ~ParkingLotGraph();
    QPixmap *getPixmap();

private:
    QVector<Node* > m_all;
    QVector<Node* > m_spaceList;
    QVector<Node* > m_roadNodeList;
    QVector<Node* > m_actionList;
    QPixmap* m_pixmap = nullptr;
    void generatePixmap();
    const ParkingLotWidget* pk;
};

#endif // PARKINGLOTGRAPH_H
