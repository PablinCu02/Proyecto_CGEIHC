
# 🧱 Proyecto_CGEIHC

**Integrantes del equipo:**
- 🧍‍♀️Lechuga Castillo Shareny Ixchel	 - 319004252
- 🧍‍♂️ Gonzalez Cuellar Pablo Arturo - 319241013	
- 🧍‍♂️ Sánchez Medina José Santiago - 319246881
  
## 🎮 Descripción General del Proyecto

Este proyecto es un **ambiente virtual 3D interactivo** desarrollado en **OpenGL**, que combina las temáticas **prehispánica** y **lucha libre mexicana**, integrando además universos distintos elegidos por cada integrante del equipo:

- 🍄 **Mario Bros** (*Shareny*)  
- 🐭 **Mickey Mouse** (*Santiago*)  
- 🕓 **Hora de Aventura** (*Pablo*)  

Cada universo aporta modelos, personajes y elementos característicos que conviven en un mismo escenario —una alameda temática—, donde el usuario puede recorrer libremente el entorno, interactuar con objetos, observar animaciones y cambiar la vista de cámara.

## 🧠 Funcionamiento Principal

### 🧭 Recorrido del escenario (Cámaras)
El usuario puede desplazarse por todo el escenario con **tres tipos de cámara**:

- 🎥 **Cámara de tercera persona:** sigue al avatar activo.  
- 🚁 **Cámara aérea:** muestra una vista superior del mapa.  
- 🕹️ **Cámara libre o isométrica:** permite explorar el entorno manualmente.  

Estas cámaras pueden alternarse mediante el teclado, ofreciendo una experiencia inmersiva y flexible.


### 🌅 Ciclo día/noche e iluminación dinámica
El escenario cuenta con un sistema de iluminación direccional que simula el paso del tiempo:

- Durante el día se muestra un skybox con cielos despejados.  
- Al caer la noche, el skybox cambia a una versión nocturna y se encienden las luminarias puntuales (lámparas del entorno), generando un ambiente visual realista y dinámico.


### 🎬 Animaciones Interactivas
El entorno contiene diversos objetos animados que el usuario puede controlar con el teclado:

- 🎈 **Globo aerostático:** se puede mover libremente en los ejes X, Y y Z.  
- 🚪 **Puertas:** se abren y cierran con las teclas O y P, mediante rotaciones y desplazamientos interpolados.  
- 🏐 **Juego de Pelota:** el personaje Jake golpea una pelota que se eleva, rebota y se desplaza horizontalmente en un ciclo continuo.  

Cada animación responde a las acciones del usuario y está sincronizada con las condiciones del entorno (como la iluminación).


### 🧱 Modelado y Texturizado
El escenario incluye modelos en 3D, algunos creados por los integrantes y otros importados, texturizados con imágenes representativas de cada universo.  
Se aplicaron materiales con propiedades de brillo y reflexión para que reaccionen correctamente a la iluminación direccional y puntual, mejorando el realismo visual y la cohesión del entorno.


### ⌨️ Interacción del Usuario
Todo el proyecto se controla mediante teclado y mouse, lo que permite:

- Mover la cámara.  
- Cambiar el modo de vista.  
- Activar animaciones.  
- Manipular objetos (globo, puertas, etc.).  

La interfaz de control busca ser intuitiva, permitiendo una navegación fluida dentro del entorno 3D.


## 🌟 Propósito del Proyecto
El objetivo principal fue integrar en un mismo entorno 3D los conceptos fundamentales de computación gráfica, tales como:

- Modelado  
- Texturizado  
- Animación  
- Iluminación  
- Cámaras  

Con ello se busca demostrar el dominio del ciclo completo de renderizado interactivo en tiempo real.  
El proyecto combina creatividad, técnica y colaboración, mostrando un escenario único que mezcla la **cultura mexicana** con personajes icónicos de universos distintos.

## 📁 Control de Documentos y Bitácoras
Para mantener un control organizado del proyecto, todos los documentos y bitácoras estarán disponibles en el siguiente drive:

### 🗃️ Bitácoras y Registros
- **Bitácora de Desarrollo:** [Ver Bitácora](https://drive.google.com/drive/folders/1PeHtp8mtOvBGTQ_S2jvSjIkZ666TdskZ)
- **Manual Técnico:** [Ver Manual Técnico](https://docs.google.com/document/d/1ZRrWnJ8PEDSoCVYZ63xxCsR5pub87ACX/edit)
- **Manual de Usuario:** [Manual de Usuario](https://docs.google.com/document/d/1nP4AMxSB3-P2ItbOTvQf6p9prw82ZFX_B9xaPbze0Zk/edit?usp=sharing)
- **General:** [Carpeta General](https://drive.google.com/drive/folders/1slKRdCUQFJRuRNLjwH2wsBf0DBJPoNXf)
