#ifndef ESFERA_H
#define ESFERA_H

#include "hit.h"

class Esfera : public hitaveis {
    private:
        Ponto3d centro;
        double raio;

    public:
        Esfera(const Ponto3d& centro, double raio) : centro(centro), raio(std::fmax(0, raio)) {}

        bool hit(const Raio& r, Intervalo ray_t, recordar_hits& rec) const override {
            Vetor3d oc = centro - r.origem();
            auto a = r.direcao().comprimento_quadrado();
            auto h = dot(r.direcao(), oc);
            auto c = oc.comprimento_quadrado() - raio*raio;

            auto discriminante = h*h - a*c;
            if (discriminante < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminante);
            auto rota = (h-sqrtd)/a;
            if (!ray_t.surround(rota)) {
                rota = (h+sqrtd)/a;
                if (!ray_t.surround(rota)) {
                    return false;
                }
            }

            rec.t = rota;
            rec.p = r.at(rec.t);
            Vetor3d outward_normal = (rec.p-centro)/ raio;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
};

#endif