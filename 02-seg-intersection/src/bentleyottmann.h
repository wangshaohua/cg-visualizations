#ifndef BENTLEYOTTMANN_H
#define BENTLEYOTTMANN_H

#include <QtCore>
#include <set>
#include <map>

using namespace std;

struct Point {
    QPointF *p;
    QLineF *s1;
    QLineF *s2;
    bool left;

    Point(QPointF *point, QLineF *segment1, bool isLeftEnd, QLineF *segment2 = 0)
        : p(point), s1(segment1), s2(segment2), left(isLeftEnd) { }
} typedef Point;

struct Segment {
    QLineF *s;
    int rank;

    Segment(QLineF *segment, int rank) : s(segment), rank(rank) { }

    qreal high(const QPointF* p) const {
        return s->p1().y() + (s->p2().y() - s->p1().y()) / (s->p2().x() - s->p1().x()) * (p->x() - s->p1().x());
    }
} typedef Segment;

struct SegmentComparator {
    const QPointF *sweepPoint;

    SegmentComparator(const QPointF *sweepPoint) : sweepPoint(sweepPoint) { }

    bool operator() (const Segment *a, const Segment *b) {
        return a->high(sweepPoint) == b->high(sweepPoint) ? a->rank < b->rank : a->high(sweepPoint) < b->high(sweepPoint);
    }
} typedef SegmentComparator;

typedef set<Point*, bool (*) (const Point*, const Point*)> PointsSet;
typedef set<Segment*, SegmentComparator> SegmentsSet;

class BentleyOttmann
{
public:
    BentleyOttmann(const QVector<QLineF> &segments) : m_segments(segments) { }
    QVector<QPointF> intersectionPoints();

private:
    QVector<QLineF> m_segments;

    Point* rightIntersection(Segment *s1, Segment *s2, const QPointF *p);
};

#endif // BENTLEYOTTMANN_H
