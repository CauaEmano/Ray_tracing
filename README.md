# 🖼️ Ray Tracing in One Weekend — Implementation

> Implementação de um **ray tracer básico** baseada no livro  
> **“Ray Tracing in One Weekend” — Peter Shirley**

Este projeto tem como objetivo estudar e aplicar os **fundamentos de computação gráfica**, construindo um ray tracer do zero, sem uso de bibliotecas gráficas externas.

---

## 📌 Sobre o Projeto

O **ray tracing** é uma técnica de renderização que simula o comportamento físico da luz, lançando raios a partir da câmera e calculando suas interseções com objetos na cena.

Neste projeto, implementei:

- Geração de raios a partir da câmera
- Interseção de raios com esferas
- Cálculo de normais
- Sombras simples
- Gradiente de fundo (sky)
- Geração de imagem no formato **PPM**

Tudo foi feito de forma **didática**, seguindo o livro, com foco total no entendimento matemático e computacional do processo.

---

## 🧠 Conceitos Abordados

- Vetores 3D
- Produto escalar
- Normalização de vetores
- Geometria analítica
- Câmera virtual
- Interseção raio–objeto
- Computação gráfica baseada em CPU

---

## 🖥️ Resultado

A imagem final gerada pelo ray tracer está disponível no repositório:

📄 **`imagem.ppm`**

> O formato PPM foi utilizado por ser simples e ideal para projetos educacionais de computação gráfica.

Você pode visualizar a imagem usando:
- GIMP
- ImageMagick
- Qualquer visualizador que suporte `.ppm`

Exemplo com ImageMagick:
```bash
display imagem.ppm
