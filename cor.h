#ifndef COR_H
#define COR_H

#include "vetor3d.h"

using Cor = Vetor3d;

void escrever_cor(std::ostream& out, const Cor& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif