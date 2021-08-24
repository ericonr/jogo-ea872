# Jogo EA872

O projeto consiste no uso da biblioteca low level SDL, usada para acesso em
baixo nível de funcionalidades de áudio, vídeo, teclado e joysticks, para o
desenvolvimento de um jogo massivo multiplayer.

Nosso jogo será um shooter massivo multiplayer online, em 2D, usando pixel art.
A visão da câmera será aérea, e o jogador pode mover seu personagem em todas
direções do mapa e controlar para onde o personagem olha. O jogo será situado
em uma floresta, onde animais lutam pela suas vidas utilizando qualquer meio
necessário para garantir que sobrevivam até o próximo raiar do sol. Nesse caso,
os animais batalham utilizando os projéteis associados a elementos da floresta.

## Compilar

* Instale [meson](https://mesonbuild.com/Quick-guide.html) no seu sistema, de
  preferência utilizando um manejador de pacotes
* Rode `meson build` para configurar, e `ninja -C build/` para compilar o
  projeto.
