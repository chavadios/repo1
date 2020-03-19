#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define TAM 10000
#define TRUE 1
#define FALSE 0
/*
typedef struct _fecha
{
	int dia,mm,year,age;
}Tfecha
*/
typedef struct alumno {
	int status;
	char Nombre[15];
	char ApPat[15];
	char ApMat[15];
	char sexo;
	char estado[3];
	int fecha;
	int edad;
	char curp[19];
	int matri;
	
}Talum;

typedef struct _tabla {
	long indice;
	long matri;
	struct _tabla *sig;
}_Tabla;

typedef _Tabla *Tabla;

void LlenarTabla(char *NombreArchivo, Tabla vect[]);
Talum ExtraerDatos(char *NombreArchivo, long ind);
Tabla LlenaDatos(Talum reg, long ind);
void CrearTabla(Tabla vect[]);
void ADDTabla(Tabla vect[], Tabla nuevo);
Tabla Eliminar(Tabla vect[], long mat);
void ImprimirReg(Talum reg);
Tabla Buscar(Tabla nodo, long mat);
Tabla Busqueda(Tabla vect[], long mat);
void Servicio(Tabla vect[]);
void Imprimir(Tabla nodo);
void ImprimirArchivo(char *NombreArchivo);
void EliminarArch(char *NombreArchivo, long ind);
void menu();

int main()
{
	srand(time(0));
	menu();
	return 0;
}
//************************************************************************** 
void menu() {
	int op, i;
	char NombreArchivo[] = { "Info.dat" }; 
	long ind = 1, matri;
	Tabla vect[TAM], temp = NULL;
	Talum reg;

	CrearTabla(vect);
	LlenarTabla(NombreArchivo, vect);

	do {
		system("cls");
		printf("M E N U");
		printf("\n1.- Buscar");
		printf("\n2.- Mostrar Archivo");
		printf("\n3.- Mostrar Tabla Hash");
		printf("\n4.- Eliminar");
		printf("\n5.- Salir");
		printf("\nDigita una opcion: ");
		scanf("%d", &op);
		switch(op)
		{
        case 1:
				system("cls");
				printf("Digita la matri a buscar: ");
				scanf("%ld", &matri);
				temp = Busqueda(vect, matri);
				if (temp)
				{
					reg = ExtraerDatos(NombreArchivo, temp->indice);
					ImprimirReg(reg);
				}
				else
				{
					printf("No encontrado");
				}
				system("pause");
				break;
		case 2:
				system("cls");
				ImprimirArchivo(NombreArchivo);
				break;
		case 3:
				system("cls");
				Servicio(vect);
				system("pause");
				break;
		case 4:
				system("cls");
				printf("Digita la matricula: ");
				scanf("%ld", &matri);
				temp = Eliminar(vect, matri);
				if (temp)
				{
					printf(" eliminado");
					EliminarArch(NombreArchivo, temp->indice);
					free(temp);
				}
				else
				{
					printf("No encontrado");
				}
				system("pause");
				break;
		}
	} while (op != 5);
}
//**************************************************************************
void LlenarTabla(char *NombreArchivo, Tabla vect[])
{
	FILE *fa;
	Talum reg;
	Tabla nuevo = NULL;
	long i = 1;

	fa = fopen(NombreArchivo, "rb");
	if (fa)
	{
		while (fread(&reg, sizeof(Talum), 1, fa))
		{
			if (reg.status != 0)
			{
				nuevo = LlenaDatos(reg, i);
				ADDTabla(vect, nuevo);
			}
			i++;
		}
		fclose(fa);
	}
	else
	{
		printf("Error al accesar al archivo");
	}
}
//**************************************************************************
Talum ExtraerDatos(char *NombreArchivo, long ind)
{
	FILE *fa;
	Talum reg;

	fa = fopen(NombreArchivo, "rb");
	if (fa)
	{
		rewind(fa);
		fseek(fa, (ind - 1) * sizeof(Talum), SEEK_SET);
		fread(&reg, sizeof(Talum), 1, fa);
		fclose(fa);
	}
	else
	{
		printf("Error al leer el archivo");
	}
	return reg;
}
//**************************************************************************
Tabla LlenaDatos(Talum reg, long ind)
{
	Tabla nuevo = (Tabla)malloc(sizeof(_Tabla));
	nuevo->indice = ind;
	nuevo->matri = reg.matri;
	nuevo->sig = NULL;
	return nuevo;
}
//**************************************************************************
void CrearTabla(Tabla vect[])
{
	long i;
	for (i = 0; i < TAM; i++)
	{
		vect[i] = NULL;
	}
}
//**************************************************************************
void ADDTabla(Tabla vect[], Tabla nuevo)
{
	long pos;
	pos = ((nuevo->matri) % TAM);
	if (vect[pos] == NULL)
	{
		vect[pos] = nuevo;
	}
	else
	{
		nuevo->sig = vect[pos];
		vect[pos] = nuevo;
	}
}
//**************************************************************************
Tabla Eliminar(Tabla vect[], long mat)
{
	int pos, band = FALSE;
	Tabla temp = NULL, nodo =NULL, aux = NULL;
	pos = (mat % TAM);
	if (vect[pos])
	{
		nodo = vect[pos];
		if (nodo->matri == mat)
		{
			if (nodo->sig)
			{
				temp = nodo;
				nodo = temp->sig;
				temp->sig = NULL;
				vect[pos] = nodo;
				return temp;
			}
			else
			{
				vect[pos] = NULL;
				return nodo;
			}
		}
		else
		{
			temp = nodo;
			while (temp->sig && band == FALSE)
			{
				if ((temp->sig)->matri == mat)
				{
					band = TRUE;
				}
				else
				{
					temp = temp->sig;
				}
			}
			if (temp->sig && temp->sig->matri == mat)
			{
				aux = temp->sig;
				temp->sig = aux->sig;
				aux->sig = NULL;
				return aux;
			}
			return temp = NULL;
		}
	}
	return temp = NULL;
}
//**************************************************************************
void ImprimirReg(Talum reg)
{
	printf("(Acitvo:1,Inactivo:0):\t%d\n", reg.status);
	printf("Nombre:\t\t\t%s\n", reg.Nombre);
	printf("Apellido Materno:\t%s\n", reg.ApMat);
	printf("Apellido Paterno:\t%s\n", reg.ApPat);
	printf("Fecha:\t\t%d\n", reg.fecha);
	printf("Edad:\t\t%s\n", reg.edad);
	printf("Sexo:\t\t%s\n", reg.sexo);
	printf("Estado:\t\t%s\n", reg.estado);
	printf("Curp:\t\t%s\n", reg.curp);
	printf("Matri\t\t%d\n", reg.matri);
}
//**************************************************************************
Tabla Busqueda(Tabla vect[], long mat)
{
	Tabla temp = NULL;
	int pos;
	pos = (mat % TAM);
	if (vect[pos])
	{
		temp = vect[pos];
		temp = Buscar(temp, mat);
		return temp;
	}
	return temp = NULL;
}
//**************************************************************************
Tabla Buscar(Tabla nodo, long mat)
{
	Tabla temp = NULL;
	temp = nodo;
	while (temp)
	{
		if (temp->matri == mat)
		{
			return temp;
		}
		temp = temp->sig;
	}
	return temp = NULL;
}
//**************************************************************************
void Servicio(Tabla vect[])
{
	int i = 0, j = 0;
	Tabla nodo = NULL;
	do {
		if (vect[j])
		{
			nodo = vect[j];
			printf("[%d] ", j);
			Imprimir(nodo);
			i++;
		}
		j++;
	} while (i < 100);
}
//**************************************************************************
void Imprimir(Tabla nodo)
{
	Tabla temp = NULL;
	temp = nodo;

	while (temp) {
		printf("-> |[%ld][%ld]|", temp->indice, temp->matri);
		temp = temp->sig;
	}
	printf("-> NULL\n");
}
//**************************************************************************
void ImprimirArchivo(char *NombreArchivo)
{
	FILE *fa;
	Talum reg;
	int i = 0, tecla = 0, j = 0, band = TRUE;
	fa = fopen(NombreArchivo, "rb");
	if (fa)
	{

		do {
			//system("cls");
			printf("\t|-----------------------------------------------------------------------------------------------------------|\n");
			printf("\t|  status |N  |  Nombre    |   Apellido materno   | 	 Apellido paterno 	    | sexo  |Estado |Fecha   |Edad |       Curp       |Matricula |");
			printf("\n\t|---------------------------------------------------------------------------------------------------------|"); 
			while (j<100 && fread(&reg, sizeof(Talum), 1, fa))
			{
				fprintf(stdout, "\n\t|%5d| %5d |   %-18s |   %-18s |   %-18s |  %-8s |  %-3s   |%5d     |%5d |   %18s   |%5d  ",
				reg.status,	++i  ,reg.Nombre,reg.ApMat, reg.ApPat,reg.sexo,reg.estado,  reg.fecha,reg.edad,reg.curp,reg.matri );
				j++;
			}
			printf("\n\t|---------------------------------------------------------------------------|");
			printf("\n\t|      		Presione ESC para salir Enter para los siguientes 100 registros |");
			printf("\n\t|---------------------------------------------------------------------------|");
			tecla = _getch();
			if (tecla == 13)
			{
				j = 0;
				system("cls");
			}
			else
			{
				band = FALSE;
			}
		} while (tecla != 27);
	}
	else
	{
		printf("Error al leer el archivo");
	}

}
//**************************************************************************
void EliminarArch(char *NombreArchivo, long ind)
{
	FILE *fa;
	Talum reg;
	fa = fopen(NombreArchivo, "r+b");
	if (fa)
	{
		reg = ExtraerDatos(NombreArchivo, ind);
		rewind(fa);
		fseek(fa, (ind - 1) * sizeof(Talum), SEEK_SET);
		reg.status = 0;
		fwrite(&reg, sizeof(Talum), 1, fa);
		fclose(fa);
	}
}

