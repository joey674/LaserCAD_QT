#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <qgraphicsitem.h>

struct Vertex
{
    QPointF point;
    double angle;
};

enum LineType
{
    OriginItem,
    offsetItem,
};

enum ItemTypeId /* 只用于对照 不参与实际使用 */
{
    Polyline = 6270,
    Arc = 6271,
};

const static Qt::GlobalColor DisplayColor = Qt::black;
const static Qt::GlobalColor EditColor = Qt::green;


#endif // PROTOCOL_H
