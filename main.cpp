#include "constantes.h"
#include "hit.h"
#include "hit_lista.h"
#include "esfera.h"

using namespace std;

Cor raio_cor(const Raio& r, const hitaveis& mundo) {
    recordar_hits rec;
    if (mundo.hit(r, Intervalo(0, infinity), rec)) {
        return 0.5 * (rec.normal + Cor(1,1,1));
    }

    Vetor3d direcao_unidade = vetor_normalizado(r.direcao());
    auto a = 0.5*(direcao_unidade.y() + 1.0);
    return (1.0-a) * Cor(1.0, 1.0, 1.0) + a*Cor(0.5, 0.7, 1.0);
}

int main() {

    //Imagem
    auto quadros = 16.0 / 9.0;
    int largura = 400;
    int altura = int(largura/quadros);
    altura = (altura<1) ? 1: altura;

    hitaveis_lista mundo;
    mundo.add(make_shared<Esfera>(Ponto3d(0,0,-1), 0.5));
    mundo.add(make_shared<Esfera>(Ponto3d(0,-100.5,-1), 100));

    //camera
    auto lente = 1.0;
    auto altura_viewport = 2.0;
    auto largura_viewport = altura_viewport * (double(largura)/altura); //Considerando as nuances dos tamanhos com os quadros
    auto camera_centro = Ponto3d(0,0,0);
    //Câmera em z=0, viewport em z=-1

    //Eixos horizontais e verticais (bordas)
    auto viewport_a = Vetor3d(largura_viewport, 0, 0);
    auto viewport_b = Vetor3d(0, -altura_viewport, 0); 

    //Dividir o viewport em pedacinhos, para cada pixel.
    auto pixel_delta_a = viewport_a / largura;
    auto pixel_delta_b = viewport_b / altura;

    //Localização do pixel de cima;esquerda -> move o plano para z=-1, depois vai para esquerda metado do viewport, e então cima metade do viewport
    auto viewport_cima_esquerda = camera_centro - Vetor3d(0,0,lente) - viewport_a/2 - viewport_b/2;
    auto pixel00_local = viewport_cima_esquerda + 0.5 * (pixel_delta_a + pixel_delta_b);
    //Centro do primeiro pixel (0.5)

    cout << "P3\n" << largura << ' ' << altura << "\n255\n";  //Formatação principal, arquivo ppm
    for (int i = 0; i < altura; i++){
        clog << "\rLinhas remanescentes: " << (altura - i) << ' ' << std::flush;
        for (int j = 0; j < largura; j++){
            auto pixel_centro = pixel00_local + (j*pixel_delta_a) + (i*pixel_delta_b);
            auto direcao_raio = pixel_centro - camera_centro;
            Raio r(camera_centro, direcao_raio);
            
            Cor pixel_color = raio_cor(r, mundo);
            escrever_cor(cout, pixel_color);
        }
    }
    clog << "\rDone.               \n";

    return 0;
}