#pragma once

#include<vector>
#include<tuple>
#include"Quad.h"

namespace Math {
	struct NormalGetter
	{
		struct Point {
			double x, y;
		};

		Point point_first, point_second;
		Point normal_vector;
		Point point_midle;

		NormalGetter() {
			point_first.x = 0;
			point_first.y = 0;

			point_second.x = 1;
			point_second.y = 1;

			point_midle.x = (0 + 1) / 2;
			point_midle.y = (0 + 1) / 2;
		}

		NormalGetter(double x_first, double y_first, double x_second, double y_second) {
			point_first.x = x_first;
			point_first.y = y_first;

			point_second.x = x_second;
			point_second.y = y_second;

			point_midle.x = (x_first + x_second) / 2;
			point_midle.y = (y_first + y_second) / 2;
		}

		short GetNormal() {
			normal_vector.x = point_second.y - point_first.y;
			normal_vector.y = point_first.x - point_second.x;
			if (normal_vector.x == 0) return 1;
			else if (normal_vector.y == 0) return -1;
			else return 0;
		}

		double ProjectionX(double x3, double y3) {
			double dx = -normal_vector.x,
				dy = normal_vector.y;
			return (point_midle.x * dx * dx + x3 * dy * dy - (point_midle.y - y3) * dx * dy) / (dx * dx + dy * dy);
		}
		//double GetFunctionOfPerpendicular(int X) {
		//	return (normal_vector.y * (X - point_midle.x) / normal_vector.x) + (point_midle.y);
		//}
	};

	std::pair<double, double> FindEdges(Quad quad, NormalGetter normal) {
		auto coordinates = quad.GetCoordsOfVertexes();
		if (normal.normal_vector.y > 1e-10) {
			double min_x = normal.ProjectionX(coordinates[0].first, coordinates[0].second), max_x = normal.ProjectionX(coordinates[0].first, coordinates[0].second);
			for (int i = 1; i < 4; ++i) {
				double projection = normal.ProjectionX(coordinates[i].first, coordinates[i].second);
				if (min_x > projection) {
					min_x = projection;
				}
				if (max_x < projection) {
					max_x = projection;
				}
			}
			return std::make_pair(min_x, max_x);
		}
		else {
			double min_y = coordinates[0].second, max_y = coordinates[0].second;
			for (int i = 1; i < 4; ++i) {
				double projection = coordinates[i].second;
				if (min_y > projection) {
					min_y = projection;
				}
				if (max_y < projection) {
					max_y = projection;
				}
			}
			return std::make_pair(min_y, max_y);
		}
	}

	bool CheckProjection(double x_first, double y_first, double x_second, double y_second, Quad qFirst, Quad qSecond) {
		NormalGetter norm_getter(x_first, y_first, x_second, y_second);
		norm_getter.GetNormal();
		auto projections_of_firsts_edges = FindEdges(qFirst, norm_getter);
		auto projections_of_second_edges = FindEdges(qSecond, norm_getter);
		return ((projections_of_firsts_edges.first <= projections_of_second_edges.first &&
			projections_of_second_edges.first <= projections_of_firsts_edges.second)
			|| (projections_of_firsts_edges.first <= projections_of_second_edges.second &&
				projections_of_second_edges.second <= projections_of_firsts_edges.second));
	}

	bool CheckProjections(Quad qFirst, Quad qSecond) {
		auto coordinates = qFirst.GetCoordsOfVertexes();
		bool result = true;
		for (int i = 0; i < 4; i++) {
			result = result && CheckProjection(coordinates[i].first, coordinates[i].second, coordinates[(i + 1) % 4].first, coordinates[(i + 1) % 4].second, qFirst, qSecond);
		}
		return result;
	}
}