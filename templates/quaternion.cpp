template<typename T>
struct Quaternion {
  union {
    struct {
      T q0;
      T q1;
      T q2;
      T q3;
    };
    T elements[4] = {};
  };

  static_assert(std::is_arithmetic<T>::value, "T should be an arithmetic type.");

  static int dcmp(T x) { constexpr T eps = 1e-8; return x < -eps ? -1 : x > eps; }

  static Quaternion from_rotation_vector(T x, T y, T z, T angle) {
    static_assert(std::is_floating_point<T>::value, "T should be an floating point type");
    T l = std::sqrt(x * x + y * y + z * z);
    assert(dcmp(l) > 0);
    T s = std::sin(angle * 0.5);
    return Quaternion<T>(std::cos(angle * 0.5), x / l * s, y / l * s, z / l * s);
  }

  Quaternion() = default;
  Quaternion(T q0, T q1, T q2, T q3) : q0(q0), q1(q1), q2(q2), q3(q3) {}
  ~Quaternion() = default;

  bool operator==(const Quaternion& other) const {
    for (int i = 0; i < 4; ++i) if (dcmp(elements[i] - other.elements[i]) != 0) return false;
    return true;
  }
  bool operator!=(const Quaternion& other) const { return !((*this) == other); }

  Quaternion& operator+=(const Quaternion& other) {
    for (int i = 0; i < 4; ++i) elements[i] += other.elements[i];
    return *this;
  }
  Quaternion operator+(const Quaternion& other) const { Quaternion ret = *this; return ret += other; }

  Quaternion& operator-=(const Quaternion& other) {
    for (int i = 0; i < 4; ++i) elements[i] -= other.elements[i];
    return *this;
  }
  Quaternion operator-(const Quaternion& other) const { Quaternion ret = *this; return ret -= other; }

  Quaternion operator*(const Quaternion& other) const {
    return Quaternion(
      q0 * other.q0 - q1 * other.q1 - q2 * other.q2 - q3 * other.q3,
      q0 * other.q1 + q1 * other.q0 + q2 * other.q3 - q3 * other.q2,
      q0 * other.q2 + q2 * other.q0 + q3 * other.q1 - q1 * other.q3,
      q0 * other.q3 + q3 * other.q0 + q1 * other.q2 - q2 * other.q1);
  }
  Quaternion& operator*=(const Quaternion& other) { return (*this) = (*this) * other; }

  template<typename U>
  Quaternion<U> converted() const {
    return std::is_same<T, U>::value ? *this : Quaternion<U>(q0, q1, q2, q3);
  }

  Quaternion& operator*=(T scalar) {
    for (int i = 0; i < 4; ++i) elements[i] *= scalar;
    return *this;
  }
  template<typename Scalar>
  Quaternion<std::common_type_t<T, Scalar>> operator*(Scalar scale) const {
    return converted<std::common_type_t<T, Scalar>>() *= scale;
  }

  Quaternion& operator/=(T scalar) { return (*this) *= T(1) / scalar; }
  template<typename Scalar>
  Quaternion<std::common_type_t<T, Scalar>> operator/(Scalar scale) const {
    return (*this) * (Scalar(1) / scale);
  }

  double length_sqr() const { return q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3; }
  double length() const { return std::sqrt(length_sqr()); }
  Quaternion conj() const { return Quaternion(q0, -q1, -q2, -q3); }
  Quaternion inv() const {
    const double l2 = length_sqr();
    assert(dcmp(l2) > 0);
    return conj() / l2;
  }

  void normalize() { const double l = length(); assert(dcmp(l) > 0); (*this) /= l; }
  Quaternion normalized() const { Quaternion ret = *this; ret.normalize(); return ret; }
};

template<typename T>
std::string to_string(const Quaternion<T>& q) {
  return std::string("{") + std::to_string(q.q0) + ", " + std::to_string(q.q1) + ", " + std::to_string(q.q2) + ", " + std::to_string(q.q3) + "}";
}

void quaternion_test() {
  DUMP(Quaternion<double>(0.5, 1.0, -3.0, 2.0));
  DUMP(Quaternion<double>(0.5, 1.0, -3.0, 2.0).conj());
  DUMP(Quaternion<double>(0.5, 1.0, -3.0, 2.0).inv());
  DUMP(Quaternion<double>(0.5, 1.0, -3.0, 2.0).inv() * Quaternion<double>(0.5, 1.0, -3.0, 2.0));  // {1, 0, 0, 0}
  DUMP(Quaternion<double>::from_rotation_vector(0.0, 0.0, 1.0, M_PI / 2));
}

