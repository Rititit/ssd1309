# ssd1309
Hola, soy un programador novato, programo como hobby, he desarrollado una libreria C++ rudimentaria para el uso de modulo Oled 128x64 con controlador ssd1306 

Esta libreria usa la comunicacion SPI a traves de la libreria PIGPIO, es necesaria ya que es la unica que permite tener velocidades decentes en la raspberry pi, si no la conocen la recomiendo basante.

## **Requisitos**

Instalar la libreria PIGPIO ya que la utiliza para la comunicacion SPI.

> sudo apt-get install pigpio

## **Conexion**

Debido a que la libreria hace uso de la conexion SPI, debe conectarse a los pines SPI 0 o 1.



## **Clase**

Para el uso de la libreria debe crearse un objeto SSD1309, desde el cual se cargan los distintos metodos.

> SSD1309 screen;


## **Metodos** 

### **init(long speed)**

Inicia la pantalla, comienza la comunicacion SPI, la configura e inicia la pantalla para funcionar correctamente.

Debe incluirse al inicio del la funcion principal antes de cargar los siguientes metodos y debe entregarse como argumento la velocidad de envio de datos, a mayor velocidad mas fps se obtendran de la pantalla (minimo 32Khz - maximo 9Mhz).

> screen.init(3000000);

### **pixel(int x, int y)**

Funcion basica de dibujado, pueden utilizarla para disenar sus propias funciones mas complejas.

> screen.pixel( 5, 5);

### **line(int x1, int y1, int x2, int y2)**

Funcion de dibujado de lineas.

> screen.pixel ( 10, 5, 118, 5);

### **triangle( int x1, int y1, int x2, int y2)**

### **rectangle()**

### **circle(int x, int y, int radius)**



### **print(int x, int y, char text[], int size)**

Imprime texto en el buffer de video de la pantalla en la posicion (x, y) entregada, debido a que la pantalla es de 128 pix de ancho no se permite mas de 16 caracteres por linea de texto.

> screen.print(5, 5, "Hola Mundo!", 11);

### **clear()**

Limpia el buffer de video sustituyendo los bytes con 0x00.

> screen.clear();

### **flip()**

Envia la informacion del buffer de video a la pantalla.

> screen.flip();

## **Ejecucion**

Para ejecutar el codigo compilado debes anteponer el sudo ya que requiere permisos root para la comunicacion SPI.

> sudo ./main


## **BUGS**

Falla despues de forzar el cierre de la app que esta utilizando la libreria. Esto puede deberse a que la comunicacion SPI se ve interrumpida. Recomiendo incluir una funcion de salida auxiliar para lo bucles.

 
