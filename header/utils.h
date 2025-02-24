#ifndef UTILS_H
#define UTILS_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

QPointF calculateArcCenter(QPointF p1, QPointF p2, double bulge, double &radius);

QPainterPath createArcPath(QPointF p1, QPointF p2, double bulge);



#endif // UTILS_H
