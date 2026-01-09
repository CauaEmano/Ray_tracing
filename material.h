#ifndef MATERIAL_H
#define MATERIAL_H

#include "hit.h"

class Material {

    public:
        virtual ~Material() = default;

        virtual bool espalhar(
            const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const {
                return false;
            }

};

class Lambertian : public Material {

    public:
        Lambertian(const Cor& albedo) : albedo(albedo) {}

        bool espalhar(const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const override {
            auto espalhar_direcao = rec.normal + random_unit_vector();

            if (espalhar_direcao.proximo_zero())
                espalhar_direcao = rec.normal;

            espalhado = Raio(rec.p, espalhar_direcao);
            atenuacao = albedo;
            return true;
        }
    private:
        Cor albedo;
};

class Metal : public Material {
    public: 
        Metal(const Cor& albedo, double fuzz) : albedo(albedo), fuzz(fuzz<1? fuzz:1) {}

        bool espalhar(const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const override {
            Vetor3d refletido = refletir(r.direcao(), rec.normal);
            refletido = vetor_normalizado(refletido) + (fuzz*random_unit_vector());
            espalhado = Raio(rec.p, refletido);
            atenuacao = albedo;
            return (dot(espalhado.direcao(), rec.normal) > 0);
        }     
        
    private:
        Cor albedo;
        double fuzz;
};

class Dieletrico : public Material {

    private:
        double indice_refracao;

        static double reflectance(double cosine, double indice_refracao) {
            auto r0 = (1 - indice_refracao) / (1 + indice_refracao);
            r0 = r0*r0;
            return r0 - (1-r0)*std::pow((1-cosine), 5);
        }

    public:
        Dieletrico(double indice_refracao) : indice_refracao(indice_refracao) {}

        bool espalhar (const Raio& r, const recordar_hits& rec, Cor& atenuacao, Raio& espalhado) const override{

            atenuacao = Cor(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1.0/indice_refracao) : indice_refracao;

            Vetor3d direcao_unidade = vetor_normalizado(r.direcao());
            double cos_theta = std::fmin(dot(-direcao_unidade, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri*sin_theta > 1.0;
            Vetor3d direcao;

            if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
                direcao = refletir(direcao_unidade, rec.normal);
            }else {
                direcao = refratar(direcao_unidade, rec.normal, ri);
            }

            espalhado = Raio(rec.p, direcao);

            return true;

        }
};

#endif