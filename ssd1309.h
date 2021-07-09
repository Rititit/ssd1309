/*		Libreria para el manejo de pantallas SSD1309
	
*/

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

//Libreria que contiene los array de datos para imagen de los caracteres ascii
#include "font.h"


//Libreria que contiene los array de datos para imagenes
#include "icon.h"

// Comandos ssd1309
#define SETDISPLAYCLOCKDIV 	0xD5	// 0x80 PARA 32 PIX DE ALTO - 0xf0 para 64 PIX de alto
#define SETMMULTIPLEX 		0xA8	// alto - 1 -> 0x3f
#define SETDISPLAYOFFSET 	0xD3	// 0x00, no offset
#define CHARGEPUMP 		0x8D	// ALIMENTACION DE PANTALLA - DEFAULT 0x14
#define MEMORYMODE 		0x20	// MEMORYMODE HORIZ 0x00 - VERT 0x01 - PAGE 0x02
#define SETSEGREMAP 		0xA1	// SETSEGREMAP
#define COMSCANDEC		0xC8	// COMSCANDEC
#define SETCOMPINS 		0xDA 	// SETCOMPINS //LEGAL VALUES 0x02, 0x12, 0x022, 0x032
#define SETCONTRASTE		0x81 	// SETCONTRASTE //DE 0x00 A 0xFF
#define SETPRECHANG 		0xD9 	// SETPRECHANG //SET PRECHANGED PERIOD - ALGO DE VOLTAJE - DEFAULT 0x22
#define SETVCOMH 		0xDB	// SETVCOMH //SET VCOMH DESELCTED LEVEL - DEFAULT 0x20
#define DISPLAYALLON 		0xA4 	// DISPLAYALLON (RAM A PANTALLA)
#define NORMALDISPLAY		0xA6	// NORMALDISPLAY (NORMAL 0xA6 - INVERTIDO 0xA7)
#define DEACTIVATESCROLL	0x2E	// DEACTIVATESCROLL (DESACTIVA EL SCROLL)
#define DISPLAYON 		0xAF
#define DISPLAYOFF		0xAE
#define SETPAGEADDR 		0x22	// SETPAGEADDR // SET PAGE ADDRESS 0x00 A 0x07
#define SETCOLADDRE		0x21 	// SETCOLADDRE // SET COLUMN ADDRESS 0x00 A 0x7F


#define DC 27		// Data command - le indica a la pantalla que debe recibir datos de imagen, defaul 27
#define RESET 22	// RESET PIN - reinicia la pantalla, esencial para el buen funcionamiento e inicio de la pantalla
#define MODE_3 0x000003	// modo SPI de la pantalla
#define BITRATE 500000  // Velocidad de transferencia de datos de 32K a 30M


// Definicion de la clase screen
class SSD1309{
	
	private:
	
		int spi_0;						// Identificador del puerto SPI
		
		char buffer_tx_command[2];		// Buffer de comandos
		char buffer_tx_data[24];		// Buffer de datos de vram
		char buffer_rx_data[6];			// Buffer de recepcion de datos - por definir
		
		char vram[1024];				// Buffer de ram de video

	public:
		
		// Metodo para enviar comandos y 4 bytes de data
		void command(uint8_t data, uint8_t d1 = 0x00, uint8_t d2 = 0x00, uint8_t d3 = 0x00, uint8_t d4 = 0x00)
		{
			buffer_tx_command[0]=data;
			spiWrite(spi_0, buffer_tx_command, 1);

			buffer_tx_data[0]=d1;
			buffer_tx_data[1]=d2;
			buffer_tx_data[2]=d3;
			buffer_tx_data[3]=d4;

			spiWrite(spi_0, buffer_tx_data, 4);
		}
		
		//funcion de escritura de texto en pantalla, hasta 16 caracteres!
		void print( int x, int y, const char *text, int size = 16)
		{
			for(int i=0; i<=size; i++)
			{
				switch(text[i])
				{
			
				case 0x20 : draw_buffer( x + i * 8, y, _0x20); break;
				case 0x21 : draw_buffer( x + i * 8, y, _0x21); break;
				case 0x22 : draw_buffer( x + i * 8, y, _0x22); break;
				case 0x23 : draw_buffer( x + i * 8, y, _0x23); break;
				case 0x24 : draw_buffer( x + i * 8, y, _0x24); break;
				case 0x25 : draw_buffer( x + i * 8, y, _0x25); break;
				case 0x26 : draw_buffer( x + i * 8, y, _0x26); break;
				case 0x27 : draw_buffer( x + i * 8, y, _0x27); break;
				case 0x28 : draw_buffer( x + i * 8, y, _0x28); break;
				case 0x29 : draw_buffer( x + i * 8, y, _0x29); break;
				case 0x2A : draw_buffer( x + i * 8, y, _0x2A); break;
				case 0x2B : draw_buffer( x + i * 8, y, _0x2B); break;
				case 0x2C : draw_buffer( x + i * 8, y, _0x2C); break;
				case 0x2D : draw_buffer( x + i * 8, y, _0x2D); break;
				case 0x2E : draw_buffer( x + i * 8, y, _0x2E); break;
				case 0x2F : draw_buffer( x + i * 8, y, _0x2F); break;
			
				case 0x30 : draw_buffer( x + i * 8, y, _0x30); break;
				case 0x31 : draw_buffer( x + i * 8, y, _0x31); break;
				case 0x32 : draw_buffer( x + i * 8, y, _0x32); break;
				case 0x33 : draw_buffer( x + i * 8, y, _0x33); break;
				case 0x34 : draw_buffer( x + i * 8, y, _0x34); break;
				case 0x35 : draw_buffer( x + i * 8, y, _0x35); break;
				case 0x36 : draw_buffer( x + i * 8, y, _0x36); break;
				case 0x37 : draw_buffer( x + i * 8, y, _0x37); break;
				case 0x38 : draw_buffer( x + i * 8, y, _0x38); break;
				case 0x39 : draw_buffer( x + i * 8, y, _0x39); break;
				case 0x3A : draw_buffer( x + i * 8, y, _0x3A); break;
				case 0x3B : draw_buffer( x + i * 8, y, _0x3B); break;
				case 0x3C : draw_buffer( x + i * 8, y, _0x3C); break;
				case 0x3D : draw_buffer( x + i * 8, y, _0x3D); break;
				case 0x3E : draw_buffer( x + i * 8, y, _0x3E); break;
				case 0x3F : draw_buffer( x + i * 8, y, _0x3F); break;
				
				case 0x40 : draw_buffer( x + i * 8, y, _0x40); break;
				case 0x41 : draw_buffer( x + i * 8, y, _0x41); break;
				case 0x42 : draw_buffer( x + i * 8, y, _0x42); break;
				case 0x43 : draw_buffer( x + i * 8, y, _0x43); break;
				case 0x44 : draw_buffer( x + i * 8, y, _0x44); break;
				case 0x45 : draw_buffer( x + i * 8, y, _0x45); break;
				case 0x46 : draw_buffer( x + i * 8, y, _0x46); break;
				case 0x47 : draw_buffer( x + i * 8, y, _0x47); break;
				case 0x48 : draw_buffer( x + i * 8, y, _0x48); break;
				case 0x49 : draw_buffer( x + i * 8, y, _0x49); break;
				case 0x4A : draw_buffer( x + i * 8, y, _0x4A); break;
				case 0x4B : draw_buffer( x + i * 8, y, _0x4B); break;
				case 0x4C : draw_buffer( x + i * 8, y, _0x4C); break;
				case 0x4D : draw_buffer( x + i * 8, y, _0x4D); break;
				case 0x4E : draw_buffer( x + i * 8, y, _0x4E); break;
				case 0x4F : draw_buffer( x + i * 8, y, _0x4F); break;
			
				case 0x50 : draw_buffer( x + i * 8, y, _0x50); break;
				case 0x51 : draw_buffer( x + i * 8, y, _0x51); break;
				case 0x52 : draw_buffer( x + i * 8, y, _0x52); break;
				case 0x53 : draw_buffer( x + i * 8, y, _0x53); break;
				case 0x54 : draw_buffer( x + i * 8, y, _0x54); break;
				case 0x55 : draw_buffer( x + i * 8, y, _0x55); break;
				case 0x56 : draw_buffer( x + i * 8, y, _0x56); break;
				case 0x57 : draw_buffer( x + i * 8, y, _0x57); break;
				case 0x58 : draw_buffer( x + i * 8, y, _0x58); break;
				case 0x59 : draw_buffer( x + i * 8, y, _0x59); break;
				case 0x5A : draw_buffer( x + i * 8, y, _0x5A); break;
				case 0x5B : draw_buffer( x + i * 8, y, _0x5B); break;
				case 0x5C : draw_buffer( x + i * 8, y, _0x5C); break;
				case 0x5D : draw_buffer( x + i * 8, y, _0x5D); break;
				case 0x5E : draw_buffer( x + i * 8, y, _0x5E); break;
				case 0x5F : draw_buffer( x + i * 8, y, _0x5F); break;
			
				case 0x60 : draw_buffer( x + i * 8, y, _0x60); break;
				case 0x61 : draw_buffer( x + i * 8, y, _0x61); break;
				case 0x62 : draw_buffer( x + i * 8, y, _0x62); break;
				case 0x63 : draw_buffer( x + i * 8, y, _0x63); break;
				case 0x64 : draw_buffer( x + i * 8, y, _0x64); break;
				case 0x65 : draw_buffer( x + i * 8, y, _0x65); break;
				case 0x66 : draw_buffer( x + i * 8, y, _0x66); break;
				case 0x67 : draw_buffer( x + i * 8, y, _0x67); break;
				case 0x68 : draw_buffer( x + i * 8, y, _0x68); break;
				case 0x69 : draw_buffer( x + i * 8, y, _0x69); break;
				case 0x6A : draw_buffer( x + i * 8, y, _0x6A); break;
				case 0x6B : draw_buffer( x + i * 8, y, _0x6B); break;
				case 0x6C : draw_buffer( x + i * 8, y, _0x6C); break;
				case 0x6D : draw_buffer( x + i * 8, y, _0x6D); break;
				case 0x6E : draw_buffer( x + i * 8, y, _0x6E); break;
				case 0x6F : draw_buffer( x + i * 8, y, _0x6F); break;
			
				case 0x70 : draw_buffer( x + i * 8, y, _0x70); break;
				case 0x71 : draw_buffer( x + i * 8, y, _0x71); break;
				case 0x72 : draw_buffer( x + i * 8, y, _0x72); break;
				case 0x73 : draw_buffer( x + i * 8, y, _0x73); break;
				case 0x74 : draw_buffer( x + i * 8, y, _0x74); break;
				case 0x75 : draw_buffer( x + i * 8, y, _0x75); break;
				case 0x76 : draw_buffer( x + i * 8, y, _0x76); break;
				case 0x77 : draw_buffer( x + i * 8, y, _0x77); break;
				case 0x78 : draw_buffer( x + i * 8, y, _0x78); break;
				case 0x79 : draw_buffer( x + i * 8, y, _0x79); break;
				case 0x7A : draw_buffer( x + i * 8, y, _0x7A); break;
				case 0x7B : draw_buffer( x + i * 8, y, _0x7B); break;
				case 0x7C : draw_buffer( x + i * 8, y, _0x7C); break;
				case 0x7D : draw_buffer( x + i * 8, y, _0x7D); break;
				case 0x7E : draw_buffer( x + i * 8, y, _0x7E); break;
				case 0x7F : draw_buffer( x + i * 8, y, _0x7F); break;
			
				default: draw_buffer( x + i * 8, y, _0x01); break;
				}
			}
		}

		//Funcion para dibujar una imagen de 8x8 predefinida en cualquier punto de la pantalla
		void draw_buffer(int x, int y, unsigned char *data)
		{
			for (int i=0; i<8; i++)
			{
				for(int j=0; j<8; j++)
				{
					if((data[i] & (0x80>>j))!= 0) pixel(x+j, y+i);
				}
			}
		}

		// Metodo para enviar la ram a la pantalla 16 bytes por cada vez, debe ser multiplo de 8, a mayor el numero mas rapido transmite los datos
		void flip(){
			for (int i = 0; i<1024;i+=16)
			{
				buffer_tx_data[0]=vram[i];
				buffer_tx_data[1]=vram[i+1];
				buffer_tx_data[2]=vram[i+2];
				buffer_tx_data[3]=vram[i+3];
				buffer_tx_data[4]=vram[i+4];
				buffer_tx_data[5]=vram[i+5];
				buffer_tx_data[6]=vram[i+6];
				buffer_tx_data[7]=vram[i+7];
				buffer_tx_data[8]=vram[i+8];
				buffer_tx_data[9]=vram[i+9];
				buffer_tx_data[10]=vram[i+10];
				buffer_tx_data[11]=vram[i+11];
				buffer_tx_data[12]=vram[i+12];
				buffer_tx_data[13]=vram[i+13];
				buffer_tx_data[14]=vram[i+14];
				buffer_tx_data[15]=vram[i+15];
				
				//command(0x40);
				gpioWrite(DC, 1);
				spiWrite(spi_0, buffer_tx_data, 16);
				gpioWrite(DC, 0);
			}
		}
		
		// Metodo que limpia la vram
		void clear()
		{
			for (int i = 0; i<1024; i+=1)
			{
				vram[i]=0x00;
			}
		}
		
		// Metodo que dibuja un pixel en la pantalla
		void pixel(uint8_t x, uint8_t y)
		{
			if ((x<127 && x>=0)&&(y<63 && y>=0)){
				vram[((y) / 8) + ((x)*8)] |= (0x01 <<(y%8)); //Store pixel in array
			}
		}
		
		// Metodo de dibujado de lineas
		void line(int x1, int y1, int x2, int y2)
		{
			int cx = x1;
			int cy = y1;
 
			int dx = x2-cx;
			int dy = y2-cy;
 
			if(dx<0)
			{
				dx = 0-dx;
			}
			
			if(dy<0)
			{
				dy = 0-dy;
			}
 
			int sx = 0;
			int sy = 0; 
			if(cx<x2)
			{
				sx = 1; 
			}
			else{
				sx = -1;
			}
			
			if(cy<y2)
			{
				sy = 1;
			}
			else{
				sy = -1;
			}
			int err = dx-dy;
 
			for(int n=0; n<1000; n++)
			{
				pixel(cx,cy);
				if((cx==x2) && (cy==y2))
				{ 
					return;
				}
				int e2 =2*err;
				if(e2>(0-dy))
				{
					err = err-dy;
					cx = cx+sx;
				}
				if(e2<dx)
				{ 
					err = err+dx;
					cy = cy+sy;
				}
			}
		}
		
		// Metodo de dibujado de rectangulos
		void square(int x1, int y1, int x2, int y2){
 
			int x, y; //Define x and y as integer variables
 
			for(x=x1; x<x2; x++)
			{ //Iterate over x range, draw line on y1
				pixel(x,y1); //Draw pixel
			}
			for(x=x1; x<x2; x++)
			{ //Iterate over x range, draw line on y2
				pixel(x,y2); //Draw pixel
			}
			for(y=y1; y<y2; y++)
			{ //Iterate over y range, draw line on x1
				pixel(x1,y); //Draw pixel
			}
			for(y=y1; y<y2; y++)
			{ //Iterate over y range, draw line on x2 
				pixel(x2,y); //Draw pixel
			}

		}
		
		// Metodo de dibujado de circulos
		void circle(int x0, int y0, int R){
			int x = R; //Set x equal to radius
			int y = 0;
			int de = 1-x; 
 
			while(x>=y)
			{
				pixel(x+x0, y+y0); //First octant
				pixel(y+x0, x+y0); //Second octant 
				pixel(-y+x0, x+y0); //Third octant
				pixel(-x+x0, y+y0); //Fourth octant
				pixel(-x+x0, -y+y0); //Fifth octant
				pixel(-y+x0, -x+y0); //Sixth octant
				pixel(y+x0, -x+y0); //Seventh octant
				pixel(x+x0, -y+y0); //Eight octant                 
				y++; 
				if(de<=0)
				{
					de += 2*y+1;
				}
				else{ 
					x--;
					de += 2*(y-x)+1; 
				}
			}
		}

		// Metodo de dibujado de imagenes predefinidas
		void draw_icon( int x, int y, const char icon)
		{
			unsigned char *_buffer;	
			unsigned char *_icon;	
			char _x, _y;
	
			switch(icon)
				{
				case 0x00 : _icon = _0x00_; break;
				case 0x01 : _icon = _0x01_; break;
				case 0x02 : _icon = _0x02_; break;
				case 0x03 : _icon = _0x03_; break;
				case 0x04 : _icon = _0x04_; break;
				case 0x05 : _icon = _0x05_; break;
				};
			
			_x = _icon[0];
			_y = _icon[1];
			
			int sprite = 0;
			
			for(int l = 0; l<_y; l++){
				for (int i=0; i<(8); i++){
					for(int k=0; k<_x; k++){
						for(int j=0; j<(8); j++)
						{
							if((_icon[i + 2 + ( 8 * k) + (sprite * 16)] & (0x80>>j))!= 0)pixel(x+j+(8 * k), y+i + (8*l));
						}
					}

				}
				sprite ++;
			}
			return;
		}
		
		// Metodo que inicia la pantalla
		void init(long speed = BITRATE)
		{
			// Inicia los GPIO
			gpioInitialise();
			
			// Abrimos el SPI
			spi_0 = spiOpen(0, speed, MODE_3);
		
			if(spi_0>=0){printf("SPI 0 ACTIVE\n");}
			
			gpioWrite(RESET, 0);
			usleep(150 * 1000);
			gpioWrite(RESET, 1);
			usleep(150 * 1000);

			command(SETDISPLAYCLOCKDIV, 0xf0);
			command(SETMMULTIPLEX, 0x3f);
			command(SETDISPLAYOFFSET, 0x00);	
			command(CHARGEPUMP, 0x14);
			command(MEMORYMODE, 0x01);
			command(SETSEGREMAP);
			command(COMSCANDEC);
			command(SETCOMPINS, 0x12);
			command(SETCONTRASTE, 0x73f);
			command(SETPRECHANG, 0x22);
			command(SETVCOMH, 0x20);
			command(DISPLAYALLON);
			command(NORMALDISPLAY);
			command(DEACTIVATESCROLL);
			command(DISPLAYON);
			command(SETPAGEADDR, 0x00, 0x07);
			command(SETCOLADDRE, 0x00, 0x7f);
			
			printf("inicio ok \n");
			
			usleep(150 * 1000 );
		}
};
