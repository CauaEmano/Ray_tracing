#ifndef INTERVALO_H
#define INTERVALO_H

class Intervalo {

    public:
        double min, max;
        Intervalo(): min(+infinity), max(-infinity) {}

        Intervalo(double min, double max) : min(min), max(max) {}

        double size() const {
            return max - min;
        }

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surround(double x) const {
            return min < x && x < max;
        }

        static const Intervalo empty, universe;

};

const Intervalo Intervalo::empty = Intervalo(+infinity, -infinity);
const Intervalo Intervalo::universe = Intervalo(-infinity, +infinity);

#endif