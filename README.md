# MEMORIA PRÁCTICA SISTEMAS EMPOTRADOS Y DE TIEMPO REAL

## Introducción :

**Autor:** Carlos Vega García  
**Fecha:** 10/06/2021  
**Descripción:** En esta práctica se implementa una cámara termográfica con interfaz gráfica y comuniciones seriales sobre la plataforma de desarrollo STM32F429I Discovery.

---

## Esquema arquitectura del proyecto.

![Alt text](<./Esquema Sistema.png?raw=true> "Title")

## Descripción elementos de sincronización y comunicación

- **char_queue** Cola que envía los caracteres recibidos por la UART.

- **app_message_queue** Cola que envía punteros a structuras App_message almacenadas en el memory Pool.

- **frameSem** Semáforo binario que regula el acceso a las variables compartidas que almacenan el frame en memoria.

- **frame_rate_queue** Cola que indica la nueva frecuencia de refresco para la cámara.

- **updateBitmap** Evento que indica al Model que existen nuevos datos para que actualice el frame.

- **usart1MUTEX** Mutex que regula el acceso a la escritura en la USART1.

- **cameraI2CMutex** Mutex que regula el accesp a las comunicaciones I2C con la cámara.
- **temp_queue** Cola que envía al Model los nuevos valores de temperatura interna de la cámara.
- **cpu_temp_queue** Cola que envía al Model los nuevos valores de temperatura interna de la CPU.
- **eventButtonPressed** Evento que notifica que ha sido pulsado el botón físico del kit.

## Listado comandos CLI implementados

- **Camera temp:** Temperatura de la cámara.
- **Camera image:** Matriz de valores de temperatura de la cámara.
- **Camera raw:** Matriz de valores en crudo obtenidos de la cámara.
- **Camera rate XX:** Actualiza frecuencia actualización cámara a XX.
- **Camera on:** Muestra la imagen de la cámara en pantalla.
- **Camera off:** Oculta la imagen de la cámara en pantalla.

## Listado archivos empleados

- **TOUCHGFX (Interfaz Gráfica)**

  - **Model.cpp/Model.hpp** Modelo que gestiona la interfaz gráfica y las comunicaciones con otras tareas y recursos compartidos. Contiene parte importante de la lógica del sistema.

  - **MainScreenPresenter.cpp/MainScreenPresenter.hpp** Implementación de los métodos del presenter de la pantalla principal.

  - **MainScreenView.cpp/MainScreenView.hpp** Implementación de los métodos del view de la pantalla principal.

  - **SettingsScreenPresenter.cpp/SettingsScreenPresenter.hpp** Implementación de los métodos del presenter de la pantalla de configuración.

  - **SettingsScreenView.cpp/SettingsScreenView.hpp** Implementación de los métodos del view de la pantalla de configuración.

  - **TopBar.cpp/TopBar.hpp** Implementación de la funcionalidad de la barra superior como widget propio.

- **TAREAS**

  - **camera.c/camera.h** En este fichero se implementan las funciones y tareas necesarias para el funcionamiento de la cámara térmica.

  - **cli.c/cli.h** En este fichero se implementan las funciones y tareas necesarias para el funcionamiento de las comunaciones seriales. También incluye el callback para la recepción de carácteres por la UART.

  - **command.c/command.h** En este fichero se define el vector que incluye el prototipo de todos los comandos implementados.

  - **cpu.c/cpu.h** En este fichero se implementan la tarea para la lectura de la temperatura de la CPU.
