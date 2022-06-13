#include <bits/stdc++.h>

#pragma once

namespace plot {

template<typename Edge>
class GraphPloter {
 public:
  explicit GraphPloter(std::vector<std::vector<Edge>> graph)
    : graph_(std::move(graph)), n_(graph_.size()), locations_(n_), fixed_(n_), repulsive_forces_(n_), attractive_forces_(n_), rng_(clock()) {
    initialize();
  }
  virtual ~GraphPloter() = default;

  void plot() {
    std::ofstream of("edges.dat");
    for (int u = 0; u < n_; ++u) {
      for (const Edge& e : graph_[u]) if (u < e.v) {
        of << locations_[u].x << " " << locations_[u].y << " " << u << "\n";
        of << locations_[e.v].x << " " << locations_[e.v].y << " " << e.v << "\n";
      }
    }
    of.close();

    const std::string cmd = "gnuplot -presist -e \"\
                             plot 'edges.dat' using 1:2 with lines lc rgb 'black' lw 2 notitle,\
                             'edges.dat' using 1:2:(0.6) with circles fill solid lc rgb 'black' notitle,\
                             'edges.dat' using 1:2:3 with labels tc rgb 'white' offset (0,0) notitle\"";
    system(cmd.c_str());
  }
 private:
  static int dcmp(double x) {
    static constexpr double eps = 1e-8;
    return x < -eps ? -1 : x > eps;
  }

  struct Point {
    double x, y;

    Point() = default;
    Point(double x, double y) : x(x), y(y) {}

    double length() const { return std::hypot(y, x); }

    bool operator==(const Point& rhs) { return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0; }
    Point& operator-=(const Point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Point operator-(const Point& rhs) const { Point ret = *this; return ret -= rhs; }
    Point& operator+=(const Point& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Point operator+(const Point& rhs) const { Point ret = *this; return ret += rhs; }
    Point& operator*=(double scale) { x *= scale; y *= scale; return *this; }
    Point operator*(double scale) const { Point ret = *this; return ret *= scale; }
    double distance_to(const Point& rhs) const { return (*this - rhs).length(); }
  };

  class InverseLinearTemperatureModel {
   public:
    InverseLinearTemperatureModel(double a, double b) : a_(a), b_(b) {}

    double temperature(int iteration, int max_iteration) const {
      if (iteration >= max_iteration) {
        return 0.0;
      }
      return a_ * iteration + b_;
    }

   private:
    double a_ = 0.0;
    double b_ = 0.0;
  };

  void initialize() {
    if (n_ == 0) return;
    optimal_distance_ = std::sqrt(width_ * height_ / n_);

    std::uniform_real_distribution<double> udw(0.0, width_);
    std::uniform_real_distribution<double> udh(0.0, height_);
    for (int i = 0; i < n_; ++i) {
      locations_[i] = Point(udw(rng_), udh(rng_));
    }
    // TODO: Not quite plannar. Need a bug fix next time.
    const int kMaxIteration = 100;
    InverseLinearTemperatureModel temperature_model(-std::min(width_, height_) * 1.0 / kMaxIteration, std::min(width_, height_) / 10.0);
    for (int iteration = 0; iteration < kMaxIteration; ++iteration) {
      calculate_repulsive_forces();
      calculate_attractive_forces();
      double temperature = temperature_model.temperature(iteration, kMaxIteration);
      for (int u = 0; u < n_; ++u) {
        Point displacement = repulsive_forces_[u] + attractive_forces_[u];
        double displacement_length = displacement.length();
        Point pos = locations_[u] + displacement * (std::min(temperature, displacement_length) / displacement_length);
        pos.x = std::clamp(pos.x, 0.0, width_);
        pos.y = std::clamp(pos.y, 0.0, height_);
      }
    }
  }

  double get_repulsive_force(double length) const {
    assert(length > 0.0);
    return optimal_distance_ * optimal_distance_ / length;
  }

  void calculate_repulsive_forces() {
    for (int u = 0; u < n_; ++u) {
      repulsive_forces_[u] = Point(0.0, 0.0);
      for (int v = 0; v < n_; ++v) {
        if (locations_[u] == locations_[v]) continue;
        Point delta = locations_[u] - locations_[v];
        double dist = delta.length();
        repulsive_forces_[u] += delta * (get_repulsive_force(dist) / dist);
      }
    }
  }

  double get_attractive_force(double length) const {
    assert(optimal_distance_ > 0.0);
    return length * length / optimal_distance_;
  }

  void calculate_attractive_forces() {
    for (int u = 0; u < n_; ++u) {
      attractive_forces_[u] = Point(0.0, 0.0);
      for (const Edge& e : graph_[u]) {
        int v = e.v;
        if (locations_[u] == locations_[v]) continue;
        Point delta = locations_[v] - locations_[u];
        double dist = delta.length();
        attractive_forces_[u] += delta * (get_attractive_force(dist) / dist);
      }
    }
  }

 private:
  std::vector<std::vector<Edge>> graph_;
  int n_ = 0;

  double width_ = 50.0;
  double height_ = 40.0;
  double optimal_distance_ = 0.0;

  std::vector<Point> locations_;
  std::vector<bool> fixed_;
  std::vector<Point> repulsive_forces_;
  std::vector<Point> attractive_forces_;

  std::mt19937 rng_;
};

}  // namespace
