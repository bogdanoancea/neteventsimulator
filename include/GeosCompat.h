#pragma once

#include <geos/version.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/Point.h>
#include <geos/geom/GeometryFactory.h>
#include <memory>

namespace geos_compat {

#if GEOS_VERSION_MAJOR > 3 || (GEOS_VERSION_MAJOR == 3 && GEOS_VERSION_MINOR >= 11)
    using CoordView = geos::geom::CoordinateXY;

    inline geos::geom::Coordinate toCoordinate(const CoordView& c) {
        return geos::geom::Coordinate(c);
    }
#else
    using CoordView = geos::geom::Coordinate;

    inline const geos::geom::Coordinate& toCoordinate(const CoordView& c) {
        return c;
    }
#endif

template <typename Factory, typename CoordLike>
inline geos::geom::Point* createPointRaw(Factory* gf, const CoordLike& c) {
#if GEOS_VERSION_MAJOR > 3 || (GEOS_VERSION_MAJOR == 3 && GEOS_VERSION_MINOR >= 11)
    return gf->createPoint(c).release();
#else
    return gf->createPoint(c);
#endif
}

template <typename Factory>
inline geos::geom::Point* clonePointRaw(Factory* gf, const geos::geom::Point* p) {
#if GEOS_VERSION_MAJOR > 3 || (GEOS_VERSION_MAJOR == 3 && GEOS_VERSION_MINOR >= 11)
    auto coords = p->getCoordinates();
    return gf->createPoint(*coords).release();
#else
    auto coords = p->getCoordinates();
    return gf->createPoint(*coords);
#endif
}

} // namespace geos_compat