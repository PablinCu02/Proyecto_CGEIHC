# 🧱 Proyecto Final

**Integrantes del equipo:**
- 🧍‍♀️ Lechuga Castillo Shareny Ixchel - 319004252
- 🧍‍♂️ Gonzalez Cuellar Pablo Arturo - 319241013
- 🧍‍♂️ Sánchez Medina José Santiago - 319246881

---

## 🎮 Descripción General

Este proyecto es un ambiente virtual interactivo 3D desarrollado en **C++** y **OpenGL** para la materia de Computación Gráfica e Interacción Humano-Computadora. El escenario representa una "zona abierta" que fusiona las temáticas de **Lucha Libre Mexicana** y **Cultura Prehispánica** con un toque futurista, integrando personajes icónicos de distintos universos:

- 🍄 **Mario Bros** (*Shareny*)
- 🐭 **Mickey Mouse** (*Santiago*)
- 🕓 **Hora de Aventura** (*Pablo*)

El sistema demuestra el dominio de técnicas avanzadas como modelado jerárquico, iluminación dinámica (ciclo día/noche), múltiples sistemas de cámara y animación por *keyframes*.

---

## ⚙️ Instalación y Configuración (¡Importante!)

Debido al tamaño de los archivos, los recursos externos (modelos, texturas y librerías) no están en el repositorio y deben descargarse por separado. Sigue estos pasos estrictamente:

1.  **Descargar el Código:** Clona este repositorio o descarga el ZIP con el código fuente y el archivo de solución (`.sln`).
2.  **Descargar Recursos:** Ve a la sección **"🗃️ Recursos"** al final de este documento y descarga todas las carpetas (`Models`, `Textures`, `Shaders`, `lib`, `include`, `glm`) desde los enlaces de Google Drive.
3.  **Organizar Carpetas:** Coloca todas las carpetas descargadas **en la misma carpeta donde se encuentra el archivo `.sln`** (la carpeta raíz de la solución).
4.  **Abrir Proyecto:** Abre el archivo `.sln` en **Visual Studio**.
5.  **🔧 CONFIGURACIÓN IMPORTANTE DEL DIRECTORIO:**
    * Ve al **Explorador de Soluciones**, haz clic derecho en el proyecto -> **Propiedades**.
    * Navega a **Propiedades de Configuración** > **Depuración**.
    * En el campo **Directorio de trabajo**, cambia el valor a:
      `$(SolutionDir)`
    * *Esto paso asegura que el ejecutable encuentre las carpetas que acabas de descargar.*
6.  **Ejecutar:** Compila y corre el programa.

---

## 🕹️ Manual de Usuario (Controles)

La interacción se divide por modos de cámara. Usa la tecla **`V`** para alternar entre ellos.

### 1. Control de Cámaras
| Tecla | Acción | Descripción |
| :--- | :--- | :--- |
| **`V`** | **Cambiar Modo** | Ciclo: **Cámara Libre** $\to$ **3ra Persona** $\to$ **Aérea**. |

---

### 2. Modo: Cámara Libre (Exploración)
Permite volar libremente por el escenario para observar detalles.
* **`W`, `A`, `S`, `D`**: Desplazarse por el mundo.
* **`Mouse`**: Girar la vista (mirar alrededor).

---

### 3. Modo: Tercera Persona (Control de Avatares)
*Actívalo presionando `V`. La cámara seguirá automáticamente al personaje seleccionado.*

**Selección de Personaje:**
| Tecla | Personaje Activo |
| :--- | :--- |
| **`1`** | **Mickey Mouse** (Avatar por defecto) |
| **`2`** | **Peach** |
| **`3`** | **Finn el Humano** |

**Movimiento del Personaje:**
| Control | Acción |
| :--- | :--- |
| **`W`** | Caminar hacia adelante (en la dirección que mira). |
| **`S`** | Caminar hacia atrás. |
| **`A` / `D`** | Desplazamiento lateral (Strafe). |
| **`Mouse`** | Girar al personaje (Cambiar dirección). |

---

### 4. Modo: Cámara Aérea
Vista cenital superior para observar la distribución del mapa.
* **`Flechas (Arriba/Abajo)`**: Desplazarse en el eje Z (Norte/Sur).
* **`Flechas (Izq/Der)`**: Desplazarse en el eje X (Este/Oeste).

---

## 💡 Iluminación y Ambiente Dinámico

| Evento / Tecla | Descripción |
| :--- | :--- |
| **Ciclo Automático** | **Día/Noche:** El sol se mueve por el cielo y la iluminación ambiental cambia cada **24 segundos**. Las bombillas (PointLights) se encienden solas al anochecer. |
| **`T`** | **Reflectores Manuales:** Enciende y apaga los *Spotlights* (conos de luz) ubicados sobre las lámparas principales. |

---

## 🎬 Animaciones y Objetos

| Tecla | Objeto | Acción |
| :--- | :--- | :--- |
| **`J`** | **Juego de Pelota** | Activa el salto de la pelota y la reacción del NPC (Jake). |

### 🎈 Animación por Keyframes (Globo Aerostático)
Permite grabar y reproducir una ruta de vuelo personalizada.

* **Grabar:** Usa **`F`, `G`, `H`, `T`** para mover el globo y **`L`** para guardar un punto clave (keyframe).
* **Reproducir:** Presiona **`K`** para ver la animación interpolada suavemente.
* **Guardar/Cargar:** Usa **`G`** para exportar la ruta a archivo y **`C`** para importarla.

---

### 🗃️ Recursos
- **Carpeta de Texturas:** [Ver Carpeta de Texturas](https://drive.google.com/drive/folders/1iSDGjujtjXizwiIFrijJAxO6rM-bI-Cf?usp=sharing)
- **Carpeta de Modelos:** [Ver Carpeta de Modelos](https://drive.google.com/drive/folders/1tDAPH9ozxmOgXA0x1NdmaJIb69-Nn54r?usp=sharing)
- **Carpeta de Shaders:** [Ver Carpeta de Shaders](https://drive.google.com/drive/folders/1KPXTRxQELVwlBXxl7NGknWgMDMBnX6wK?usp=sharing)
- **Carpeta lib:** [Carpeta lib](https://drive.google.com/drive/folders/1phx9GzvBb0pSupA4kLWQDaQQdpHY-tly?usp=sharing)
- **Carpeta include:** [Carpeta include](https://drive.google.com/drive/folders/1SuEcWnI9NnXHGzgX0b3ktQ4wJPU-Zjmn?usp=sharing)
- **Carpeta glm:** [Carpeta glm](https://drive.google.com/drive/folders/108ZuEpXoe4z1-W6F_VkIzPFuzwkITi1V?usp=sharing)
