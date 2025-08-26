# mini-rt

A mini-rt é uma implementação de um ray tracer em C que roda na CPU, em uma única thread. Nela é possível renderizar 3 opções de formas: esferas, planos e cilindros; iluminadas por 1 fonte de luz que evidencia o volume dessas formas e projeta sombras sobre outros objetos. A cena é construída a partir das configurações da câmera (C), da luz ambiente (A), do ponto de luz (L) e das formas (sp, pl e cy), que são declaradas e definidas através de um arquivo .rt.

> veja ref.rt e help.rt para mais informações sobre as configurações da cena

<img width="897" height="598" alt="image" src="https://github.com/user-attachments/assets/d80a8b26-46f4-4284-8f83-dd0ec29855e6" />

## Como executar o projeto localmente

1. Cole esse comando no terminal para clonar e compilar:
  ``` bash
  git clone --recursive git@github.com:g-joana/mini-rt && cd mini-rt && make
  ```

2. Para executar digite:
  ``` bash
  ./minirt scene/map.rt
  ```
  _./minirt scenes/ + desired map_
