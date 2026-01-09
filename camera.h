#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"
#include "material.h"

class Camera {
    public:
        double quadros = 1.0;
        int largura = 100;
        int samples_por_pixel = 10;
        int max_recursao = 10;

        double vfov = 90;
        Ponto3d olhandode = Ponto3d(0,0,0);
        Ponto3d olhandopara = Ponto3d(0,0,-1);
        Vetor3d vup = Vetor3d(0,1,0);

        void renderizar(const hitaveis& mundo) {
            inicializar();

            std::cout << "P3\n" << largura << ' ' << altura << "\n255\n";

            for (int j = 0; j < altura; j++) {
                std::clog << "\rScanline Remaining: " << (altura - j) << ' ' << std::flush;
                for (int i = 0; i < largura; i++) {
                    Cor pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_por_pixel; sample++) {
                        Raio r = get_raio(i,j);
                        pixel_color += raio_cor(r, max_recursao, mundo);
                    }
                    escrever_cor(std::cout, pixel_samples_scale * pixel_color);
                }
            }
        }

    private:
        int altura;
        Ponto3d centro;
        double pixel_samples_scale;
        Ponto3d pixel00_local;
        Vetor3d pixel_delta_u;
        Vetor3d pixel_delta_v;
        Vetor3d u, v, w;

        void inicializar() {
            altura = int(largura/quadros);
            altura = (altura < 1) ? 1: altura;
            pixel_samples_scale = 1.0/samples_por_pixel;
            centro = olhandode;

            auto focal_lente = (olhandode - olhandopara).comprimento();
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_altura = 2*h*focal_lente;
            auto viewport_largura = viewport_altura * (double(largura)/altura);

            w = vetor_normalizado(olhandode - olhandopara);
            u = vetor_normalizado(cross(vup, w));
            v = cross(w,u);

            auto viewport_u = viewport_largura*u;
            auto viewport_v = viewport_altura*-v;

            pixel_delta_u = viewport_u/largura;
            pixel_delta_v = viewport_v/altura;

            auto viewport_cima_esquerda = centro - (focal_lente*w) - viewport_u/2 - viewport_v/2;
            pixel00_local = viewport_cima_esquerda + 0.5 *(pixel_delta_u + pixel_delta_v);
        }

        Raio get_raio(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_local + ((i+offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
            auto raio_origem = centro;
            auto raio_direcao = pixel_sample - raio_origem;

            return Raio(raio_origem, raio_direcao);
        }

        Vetor3d sample_square() const {
            return Vetor3d(random_double() - 0.5, random_double() - 0.5, 0);
        }

        Cor raio_cor(const Raio& r, int depth, const hitaveis& mundo) {
            if (depth <= 0) {
                return Cor(0,0,0);
            }
            
            recordar_hits rec;
            if (mundo.hit(r, Intervalo(0.001, infinity), rec)) {
                Raio espalhado;
                Cor atenuacao;
                if (rec.mat->espalhar(r, rec, atenuacao, espalhado)){
                    return atenuacao * raio_cor(espalhado, depth-1, mundo);
                return Cor(0,0,0);
                }
            }

            Vetor3d direcao_unidade = vetor_normalizado(r.direcao());
            auto a = 0.5*(direcao_unidade.y() + 1.0);
            return (1.0-a) * Cor(1.0, 1.0, 1.0) + a*Cor(0.5, 0.7, 1.0);
        }
};

#endif