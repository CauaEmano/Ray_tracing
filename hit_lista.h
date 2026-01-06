#ifndef HIT_LISTA_H
#define HIT_LISTA_H

#include "hit.h"

#include <vector>


class hitaveis_lista : public hitaveis {
    public:
        std::vector<shared_ptr<hitaveis>> objetos;

        hitaveis_lista() {}
        hitaveis_lista(shared_ptr<hitaveis> objeto) { add(objeto); }

        void clear() { objetos.clear(); }
        
        void add(shared_ptr<hitaveis> objeto) {
            objetos.push_back(objeto);
        }

        bool hit(const Raio& r, Intervalo ray_t, recordar_hits& rec) const override {
            recordar_hits temp_rec;
            bool hit_algo = false;
            auto closest_so_far = ray_t.max;

            for (const auto& objeto : objetos) {
                if (objeto->hit(r, Intervalo(ray_t.min, closest_so_far), temp_rec)) {
                    hit_algo = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_algo;
        }
};

#endif