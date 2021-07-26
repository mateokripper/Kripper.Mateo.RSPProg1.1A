#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char marca[20];
    int tipo;
    float peso;
}eVehiculo;

eVehiculo* vehiculo_new();
eVehiculo* vehiculo_newParametros(int id,char* marca,int tipo, float peso);
void mostrarVehiculo(eVehiculo* vehiculo);
int saveAsText(char* path , eVehiculo* vehiculo);
int saveAsBinary(char* path , eVehiculo* vehiculo);

int main()
{
    char marca[20] = {"Chevrolet"};
    eVehiculo* vehiculo = NULL;

    vehiculo = vehiculo_newParametros(12,marca,12,1.5);
    mostrarVehiculo(vehiculo);
    if(!saveAsText("data.cvs", vehiculo)){
        printf("datos cargados correctamente\n");
    }else{
        printf("Error al cargar los datos");
    }

    /*if(!saveAsBinary("dataBin.bin", vehiculo)){
        printf("datos cargados correctamente\n");
    }else{
        printf("Error al cargar los datos");
    }*/

    return 0;
}
eVehiculo* vehiculo_new(){
    eVehiculo* nuevoVehiculo = NULL;
    nuevoVehiculo = (eVehiculo*) malloc (sizeof(eVehiculo));

    return nuevoVehiculo;
}

eVehiculo* vehiculo_newParametros(int id,char* marca,int tipo, float peso){
    eVehiculo* nuevoVehiculo = vehiculo_new();

    if(nuevoVehiculo != NULL){
        nuevoVehiculo->id = id;
        strcpy(nuevoVehiculo->marca, marca);
        nuevoVehiculo->tipo = tipo;
        nuevoVehiculo->peso = peso;
    }
    return nuevoVehiculo;
}

void mostrarVehiculo(eVehiculo* vehiculo){
    if(vehiculo != NULL){
        printf("  ID               Marca       tipo    peso\n");
        printf(" %04d %20s     %3d    %6f\n",vehiculo->id, vehiculo->marca, vehiculo->tipo, vehiculo->peso);
    }
}

int saveAsText(char* path , eVehiculo* vehiculo)
{
    int error = 1;
    int auxId;
    float auxPeso;
    int auxTipo;
	char auxMarca[128];
	FILE* pFile;

	if(vehiculo != NULL && path != NULL){
		pFile = fopen(path, "w");
		auxId = vehiculo->id;
		strcpy(auxMarca, vehiculo->marca);
		auxTipo = vehiculo->tipo;
		auxPeso = vehiculo->peso;
		if(pFile != NULL){
                fprintf(pFile, "%d,%s,%d,%f\n", auxId, auxMarca, auxTipo, auxPeso);
                error = 0;
            }
			fclose(pFile);
		}
    return error;
}

int saveAsBinary(char* path , eVehiculo* vehiculo)
{
    int error = 1;
	FILE* pFile;
	eVehiculo* auxVehiculo = NULL;

	if(vehiculo != NULL && path != NULL){
		pFile = fopen(path, "wb");
        auxVehiculo->id = vehiculo->id;
		strcpy(auxVehiculo->marca, vehiculo->marca);
		auxVehiculo->tipo = vehiculo->tipo;
		auxVehiculo->peso = vehiculo->peso;
        fwrite(auxVehiculo, sizeof(eVehiculo), 1, pFile);
		fclose(pFile);
		error = 0;
	}
    return error;
}
