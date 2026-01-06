#ifndef VETOR3D_H
#define VETOR3D_H

class Vetor3d {
    public:
        double e[3];

        Vetor3d(): e{0,0,0} {}
        Vetor3d(double e1, double e2, double e3): e{e1, e2, e3} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        Vetor3d operator-() const {return Vetor3d(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        Vetor3d operator+=(const Vetor3d v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vetor3d operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vetor3d operator/=(double t) {
            return *this *= 1/t;
        }

        double comprimento_quadrado() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double comprimento() const {
            return std::sqrt(comprimento_quadrado());
        }

};

using Ponto3d = Vetor3d;

//Funções de utlidade
inline std::ostream& operator<<(std::ostream& out, const Vetor3d& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vetor3d operator+(const Vetor3d a, const Vetor3d b) {
    return Vetor3d(a.e[0]+b.e[0], a.e[1]+b.e[1], a.e[2]+b.e[2]);
}

inline Vetor3d operator-(const Vetor3d a, const Vetor3d b) {
    return Vetor3d(a.e[0]-b.e[0], a.e[1]-b.e[1], a.e[2]-b.e[2]);
}

inline Vetor3d operator*(const Vetor3d a, const Vetor3d b) {
    return Vetor3d(a.e[0]*b.e[0], a.e[1]*b.e[1], a.e[2]*b.e[2]);
}

inline Vetor3d operator*(double t, const Vetor3d a) {
    return Vetor3d(a.e[0]*t, a.e[1]*t, a.e[2]*t);
}

inline Vetor3d operator*(const Vetor3d a, double t) {
    return t*a;
}

inline Vetor3d operator/(const Vetor3d& v, double t) {
    return (1/t)*v;
}

inline double dot(const Vetor3d& a, const Vetor3d& b) {
    return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}

inline Vetor3d cross(const Vetor3d& a, const Vetor3d& b) {
    return Vetor3d(a.e[1] * b.e[2] - a.e[2]*b.e[1], a.e[2]*b.e[0] - a.e[0]*b.e[2], a.e[0]*b.e[1] - a.e[1]*b.e[0]);
}

inline Vetor3d vetor_normalizado(const Vetor3d& a) {
    return a / a.comprimento();
}

#endif