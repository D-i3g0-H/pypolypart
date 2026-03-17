#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/Polygon_2.h>

#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace py = pybind11;

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Traits = CGAL::Partition_traits_2<Kernel>;
using Point_2 = Traits::Point_2;
using Polygon_2 = Traits::Polygon_2;
using Polygon_list = std::list<Polygon_2>;

using PyPoint = std::pair<double, double>;
using PyPolygon = std::vector<PyPoint>;
using PyPartition = std::vector<PyPolygon>;

static Polygon_2 make_polygon_from_python(const PyPolygon& pts) {
    if (pts.size() < 3) {
        throw std::invalid_argument("Polygon must contain at least 3 points.");
    }

    Polygon_2 poly;
    for (const auto& [x, y] : pts) {
        poly.push_back(Point_2(x, y));
    }

    if (!poly.is_simple()) {
        throw std::invalid_argument(
            "Input polygon is not simple. CGAL requires a simple polygon."
        );
    }

    // CGAL Partition_2 requires counterclockwise orientation.
    if (poly.orientation() == CGAL::CLOCKWISE) {
        poly.reverse_orientation();
    }

    return poly;
}

static PyPartition convert_partition_to_python(const Polygon_list& parts) {
    PyPartition out;
    out.reserve(parts.size());

    for (const auto& poly : parts) {
        PyPolygon one;
        one.reserve(poly.size());

        for (auto vit = poly.vertices_begin(); vit != poly.vertices_end(); ++vit) {
            one.emplace_back(CGAL::to_double(vit->x()), CGAL::to_double(vit->y()));
        }

        out.push_back(std::move(one));
    }

    return out;
}

PyPartition optimal_convex_partition_2_py(const PyPolygon& polygon_points) {
    Polygon_2 polygon = make_polygon_from_python(polygon_points);

    Polygon_list partition_polys;
    CGAL::optimal_convex_partition_2(
        polygon.vertices_begin(),
        polygon.vertices_end(),
        std::back_inserter(partition_polys)
    );

    bool valid = CGAL::partition_is_valid_2(
        polygon.vertices_begin(),
        polygon.vertices_end(),
        partition_polys.begin(),
        partition_polys.end()
    );

    if (!valid) {
        throw std::runtime_error("CGAL returned an invalid partition.");
    }

    return convert_partition_to_python(partition_polys);
}

PYBIND11_MODULE(_core, m) {
    m.doc() = "Python bindings for CGAL optimal_convex_partition_2";

    m.def(
        "optimal_convex_partition_2",
        &optimal_convex_partition_2_py,
        py::arg("polygon"),
        R"pbdoc(
Compute an optimal convex partition of a simple 2D polygon.

Parameters
----------
polygon : list[tuple[float, float]]
    Polygon vertices in order. If clockwise, the binding reverses them
    automatically to satisfy CGAL's counterclockwise precondition.

Returns
-------
list[list[tuple[float, float]]]
    A list of convex polygons, each represented as a list of (x, y) vertices.
)pbdoc"
    );
}