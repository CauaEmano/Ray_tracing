#ifndef HIT_H
#define HIT_H


class recordar_hits {
    public: 
        Ponto3d p;
        Vetor3d normal;
        double t;
        bool front_face; 

        void set_face_normal(const Raio& r, const Vetor3d& outward_normal) {
            front_face = dot(r.direcao(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hitaveis {
    public:
        virtual ~hitaveis() = default;

        virtual bool hit(const Raio& r, Intervalo ray_t, recordar_hits& rec) const = 0;
};

#endif