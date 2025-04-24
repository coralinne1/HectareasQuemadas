#include <stdio.h> //Bibliota para entrada y salida estandar
#include <string.h> //Para manipular cadenas de caracteres 

// Definir constantes (Simbólicas)
#define NUM_REGIONES 5 //Se reemplaza num_regiones por 5 en todo el programa
#define NUM_MESES 6 

//Funciones a utilizar  
void Inicio(const char *nombres[NUM_REGIONES]); //Funcion para inicializar los archivos con los datos iniciales
void ImprimirTotales(); //Totales de incendios y hectareas quemadas
void BuscarMaximos(); //Busca los maximos de indendios y hectareas quemadas
void AgregarRegion(); //Agrega una nueva region
void ActualizarDatos(const char *ArchivoModificar,const char *nombres[NUM_REGIONES]); //Funcion para actualizar datos de incendios

int main() {
    printf("\t:::::::::::::SISTEMA DE INCENDIOS::::::::::::::\t\n"); //Mensaje de bienvenida
    const char *nombres[NUM_REGIONES] = {"Cuyo", "Pampeana", "Patagonia", "Noroeste", "Noreste"}; 
    int opc; //Variable para almacenar las opciones elejidas por el usuario

    // Pregunta inicial al usuario
    printf("Desea iniciar el sistema (1)\nSalir del programa (2)\nOpcion: ");
    scanf("%d", &opc);
    printf("\n\n************************************************************************************************************************\n");

    if (opc == 1) {
        // Inicializar los archivos con los datos inciales (pasando el arreglo nombres como argumento)
        Inicio(nombres);
    } else if (opc == 2) { 
        printf("Saliendo del programa.\n");
        return 0; 
    } else if (opc != 1) {
      printf("Opcion no valida. Saliendo del programa.\n");
      return 0; 
    }

    // Menú principal 
    do { // 
        printf("Que accion desea realizar?\nLectura Global(1)\nNiveles de Alertas(2)\nIngresar datos(3)\nSalir del programa(4)\nOpcion: ");
        scanf(" %d", &opc); // Se lee y almacena la opcion elejida 
        printf("\n************************************************************************************************************************\n");

        //Segun la opcion elejida se ejecuta una funcion 
        switch (opc) {
            case 1: 
                ImprimirTotales();
                BuscarMaximos();
                break;
            case 2:
                BuscarMaximos();
                break;
            case 3:
                ActualizarDatos("IncendiosTotales.txt", nombres);
                AgregarRegion();
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default: 
                printf("Opcion no valida.\n"); 
                break;
        }
    } while (opc != 4); //El bucle se sigue ejecutando mientras la opcion sea diferente a 4

    return 0;
}
 //Funcion para inicializar los archivos con los datos iniciales
void Inicio(const char *nombres[NUM_REGIONES]) { //La funcion toma como argumento el arreglo de cadenas de caracteres
  
  FILE *Zona = fopen("zonas.txt", "w");
 //Escribir los nombres de las regiones en el archivo
  for (int i = 0; i < NUM_REGIONES; i++) { //Recorre el arreglo de nombres 
    fprintf(Zona, "%s\n", nombres[i]); 
  }
  fclose(Zona);

  FILE *Estado = fopen("EstadoIncendios.txt", "w");
  //Escribir los estados de los incendios en el archivo
  fprintf(Estado, "Activo\nControlado\nContenido\n");
  fclose(Estado);

  FILE *Alerta = fopen("alertas_incendios.txt", "w");
 //Escribir los tipos de alertas en el archivo
  fprintf(Alerta, "Amarillo\nVerde\nRojo\n");
  fclose(Alerta);

 FILE *IncendiosTotales = fopen("IncendiosTotales.txt", "w");
  // Escribir los datos totales en el archivo "IncendiosTotales.txt"
    int nuevosIncendiosTotales[NUM_REGIONES][NUM_MESES] = { //Declarar un arreglo de dos dimeensiones para almacenar datos de incendios 
        {0, 2, 8, 15, 34, 33},    // CUYO
        {8, 3, 14, 47, 45, 48},   // PAMPEANA
        {2, 0, 0, 57, 45, 65},    // PATAGONICA
        {9, 28, 85, 249, 255, 284},  // NOROESTE
        {0, 0, 4, 15, 6, 8}         // NORESTE
    };
    for (int i = 0; i < NUM_REGIONES; i++) { //Recorrer las filas
        for (int j = 0; j < NUM_MESES; j++) { //Recorrer las columnas
            fprintf(IncendiosTotales, "%d ", nuevosIncendiosTotales[i][j]); // Escribir los datos en el archivo 
        }
        fprintf(IncendiosTotales, "\n"); //Salto de linea entre cada fila
    }
  fclose(IncendiosTotales);

  FILE *HectareasQuemadas = fopen("HectareasQuemadas.txt", "w");
  float nuevasHectareasTotales[NUM_REGIONES][NUM_MESES] = { 
        {0, 10.60, 341.0, 15874.0, 5685.5, 5128.3},    
        {604.0, 375.0, 926.0, 248.0, 2395.0, 6141.3},   
        {67.5, 0.0, 0.0, 273.42, 107.8, 1024.8},        
        {9.4, 37.68, 495.85, 1639.31, 3725.3, 8452.0},  
        {0.0, 0.0, 10.0, 1320.0, 1310.0, 3338.3}        
    };
     for (int i = 0; i < NUM_REGIONES; i++) {
        for (int j = 0; j < NUM_MESES; j++) {
            fprintf(HectareasQuemadas, "%.2f ", nuevasHectareasTotales[i][j]);
        }
        fprintf(HectareasQuemadas, "\n");
    }
  fclose(HectareasQuemadas); 

}

void ImprimirTotales() {
  
     //Declarar un arreglo para almacenar los nombres de cada región
    char zonasNombres[NUM_REGIONES][50];
     //Declarar un arreglo bidimensional para almacenar los totales de incendios por región
    int incendios[NUM_REGIONES][NUM_MESES];
    //Arreglo para almacenar los totales de hectáreas quemadas por región
    float totalesHectareas[NUM_REGIONES] = {0}; // Arreglo para los totales de incendios por region (Inicializa en 0)
    
   FILE *Zona = fopen("zonas.txt", "r");
    if (Zona == NULL) { // Si no se puede abrir o no existe el archivo 
        printf("Error al abrir el archivo zonas.txt\n");
        return;
    }
    

   for (int i = 0; i < NUM_REGIONES; i++) { //Recorre el arreglo de nombres
      fscanf(Zona, "%s", zonasNombres[i]); //Lee los nombres de las regiones y los almacena en el arreglo 
}
    fclose(Zona);

    FILE *incendiosTotales = fopen("IncendiosTotales.txt", "r");
    if (incendiosTotales == NULL) {
      printf("Error al abrir el archivo IncendiosTotales.txt\n");
      return;
}

    // Leer los datos de IncendiosTotales
    for (int i = 0; i < NUM_REGIONES; i++) { 
      for (int j = 0; j < NUM_MESES; j++) {
         fscanf(incendiosTotales, "%d", &incendios[i][j]); //Lee los datos de incendios y los almacena en el arreglo
    }
  }
    fclose(incendiosTotales);

    //Imprimir los totales de incendios por region 
    printf("Total de Incendios:\n"); //Cabecera de la tabla 
    for (int i = 0; i < NUM_REGIONES; i++) { 
        int sumaFila = 0; //Variable para almacenar la suma de incendios por region 
        for (int j = 0; j < NUM_MESES; j++) { 
            sumaFila += incendios[i][j]; //Suma los incendios por region 
        }
        printf("Region %s: %d Incendios\n", zonasNombres[i], sumaFila); 
    }
    printf("\n************************************************************************************************************************\n");

    FILE *hectareasQuemadas = fopen("HectareasQuemadas.txt", "r");
    if (hectareasQuemadas == NULL) {
      printf("Error al abrir el archivo HectareasQuemadas.txt\n");
      return;
}
    
    // Leer las hectáreas quemadas de cada zona y sumarlas por región
    for (int i = 0; i < NUM_REGIONES; i++) {
      totalesHectareas[i] = 0; //Inicializar el total de hectareas quemadas en 0
      for (int j = 0; j < NUM_MESES; j++) {
         float hectareas=0; //Variable para almacenar las hectareas quemadas
         fscanf(hectareasQuemadas, "%f", &hectareas); 
         totalesHectareas[i] += hectareas; //Suma las hectareas quemadas por region 
    }
}
    fclose(hectareasQuemadas);

    //Imprimir los totales de hectareas quemadas por region 
    printf("Total de Hectareas Quemadas:\n");
    for (int i = 0; i < NUM_REGIONES; i++) { //Recorre el arreglo de nombres 
        printf("Region: %s : %.2f Hectareas\n", zonasNombres[i], totalesHectareas[i]);
    }
    printf("\n************************************************************************************************************************\n");
}

void BuscarMaximos() {
  const char *meses[NUM_MESES] = {"Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}; 
  int mes1 = 0; //Mes con el mayor numero de incendios
  int mes = 0; //Mes con la mayor cantidad de hectareas quemadas 
  float maxHectareas = 0; //Maximo de hectareas quemadas 
  int zonaMaxHectareas = 0; //indice con el maximo de hectareas quemadas 
  int maxIncendios = 0;
  int zonaMaxIncendios = 0;
  int totalActivo[NUM_MESES] = {0}; //Total de incendios por mes 
  int totalControlado[NUM_MESES] = {0};
  int totalContenido[NUM_MESES] = {0};

  FILE *hectareasQuemadas = fopen("HectareasQuemadas.txt", "r");
  if (hectareasQuemadas == NULL) {
    printf("Error al abrir el archivo %s.\n", "HectareasQuemadas.txt");
    return;
  }

  float hectareas[NUM_REGIONES][NUM_MESES]; //Arreglo para hectareas quemadas por region 
  for (int i = 0; i < NUM_REGIONES; i++) { 
    for (int j = 0; j < NUM_MESES; j++) {
      fscanf(hectareasQuemadas, "%f", &hectareas[i][j]); //Lee los valores desde el archivo y lo almacena en la matriz 
      //Verificar si el valor actual es mayor al maximo actual 
      if (hectareas[i][j] > maxHectareas) {
        //Actualizo max con el nuevo valor maximo 
        maxHectareas = hectareas[i][j];
        //Actualizo con el indice de la region actual  
        zonaMaxHectareas = i + 1;
        //Actualizo el mes con el indice del mes actual 
        mes = j + 1; //Sumo 1 para que el mes sea del 1 al 6 (los indices de las matrices comienzan con 0)
      }
    }
  }
  fclose(hectareasQuemadas);

  FILE *incendiosTotales = fopen("IncendiosTotales.txt", "r");
  if (incendiosTotales == NULL) {
    printf("Error al abrir el archivo IncendiosTotales.txt.\n");
    return;
  }
  int incendios[NUM_REGIONES][NUM_MESES];
  for (int i = 0; i < NUM_REGIONES; i++) {
  for (int j = 0; j < NUM_MESES; j++) {
     fscanf(incendiosTotales, "%d", &incendios[i][j]);

     //Si los meses estan entre 0 y 3, sumar los incendios a la variable totalContenido
     if (j >= 0 && j <= 3) { 
     totalContenido[j] += incendios[i][j];
     }
     //Se suma los incendios del mes de diciembre
     totalActivo[j] += incendios[i][5]; 
     //Se suman los incendios del mes de noviembre 
     totalControlado[j] += incendios[i][4];
   
     // Actualizar mes1 al encontrar el número máximo de incendios
     if (incendios[i][j] > maxIncendios) {
      //Actualizar maxIncendios con el nuevo valor máximo
      maxIncendios = incendios[i][j];
      //Actualizar con el indice de la region actual
      zonaMaxIncendios = i + 1;
      //Actualizar con el indice del mes actual 
      mes1 = j + 1;
    }
  }
}
  fclose(incendiosTotales);

  FILE *Zona = fopen("zonas.txt", "r");
  if (Zona == NULL) {
    printf("Error al abrir el archivo zonas.txt\n");
    return;
  }
  char zonasNombres[NUM_REGIONES][50]; // Arreglo para nombres de las regiones 
  for (int i = 0; i < NUM_REGIONES; i++) { //Recorre el arreglo de nombres 
    fscanf(Zona, "%s", zonasNombres[i]); 
  }
  fclose(Zona);

  char zonanombre[50]; //Nombre de la region con mas hectareas quemadas
  char zonanombre2[50]; //Nombre de la region con mas incendios 

if (zonaMaxHectareas > 0 && zonaMaxHectareas <= NUM_REGIONES) { //Si la zona con mas hectareas quemadas esta entre 0 y 5 
  strcpy(zonanombre, zonasNombres[zonaMaxHectareas - 1]); //Copia el nombre de la region 
} else {
  strcpy(zonanombre, "Sin Nombre"); //Si no se encuentra el nombre, se asigna sin nombre
}

if (zonaMaxIncendios > 0 && zonaMaxIncendios <= NUM_REGIONES) {  
  strcpy(zonanombre2, zonasNombres[zonaMaxIncendios - 1]); 
} else {
  strcpy(zonanombre2, "Sin Nombre");
}

//Imprimir los resultados de la busqueda de maximos 
printf("Zona con mas incendios: Zona %s, %d incendios en el mes %s\n", zonanombre2, maxIncendios, meses[mes1 - 1]);
printf("Zona con mas hectareas quemadas: Zona %s, %.2f hectareas en el mes %s\n", zonanombre, maxHectareas, meses[mes - 1]); //Mes - 1 porque los indices comienzan en 0 

printf("\n************************************************************************************************************************\n");

//Imprimir los totales de incendios por estado 
printf("Los Incendios Activos, son: %d\n", totalActivo[5]); 
printf("Los Incendios Controlados, son: %d\n", totalControlado[4]);
printf("Los Incendios Contenidos, son: %d\n", totalContenido[3] + totalContenido[2] + totalContenido[1] + totalContenido[0]); 

printf("\n************************************************************************************************************************\n");

//Declarar arreglos para almacenar las zonas segun la alerta 
int zonasAlertaRoja[NUM_REGIONES] = {0}; 
  int zonasAlertaAmarilla[NUM_REGIONES] = {0};
  int zonasAlertaVerde[NUM_REGIONES] = {0};
  
  for (int i = 0; i < NUM_REGIONES; i++) { 
    int acum = 0; //Variable para acumular los incendios por region 
    for (int j = 0; j < NUM_MESES; j++) { 
      acum += incendios[i][j]; //Suma los incendios por region 
    }

        if (acum >= 500) { //Mayor o igual a 500
            zonasAlertaRoja[i] = acum; 
        } else if (acum>= 100 && acum < 500) { //Mayor o igual a 100 y menor a 500
            zonasAlertaAmarilla[i] = acum;
        } else {
            zonasAlertaVerde[i] = acum; //Menor a 100
        }
 }

// Imprimir los resultados de la comparación
printf("Comparacion de zonas por estado de alerta:\n");
printf("\nAlerta Roja: \n");
for (int i = 0; i < NUM_REGIONES; i++) { 
    if (zonasAlertaRoja[i] >= 500) { 
        printf("Region: %s: %d incendios\n", zonasNombres[i], zonasAlertaRoja[i]); 
    }
}

printf("\nAlerta Amarilla: \n");
for (int i = 0; i < NUM_REGIONES; i++) {
    if (zonasAlertaAmarilla[i] > 0) {
        printf("Region: %s: %d incendios\n", zonasNombres[i], zonasAlertaAmarilla[i]);
    }
}

printf("\nAlerta Verde: \n");
for (int i = 0; i < NUM_REGIONES; i++) {
    if (zonasAlertaVerde[i] > 0) {
        printf("Region: %s: %d incendios\n", zonasNombres[i], zonasAlertaVerde[i]);
    }
}
printf("\n************************************************************************************************************************\n");
}

void AgregarRegion() {

  char nuevoNombre[50]; //Nuevo nombre de la region 
  int incendiosIngresados[NUM_MESES]; // Incendios ingresados por el usuario
  float hectareasIngresadas[NUM_MESES]; //Hectareas quemadas 
  const char *meses[NUM_MESES] = {"Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}; 

  printf("Desea agregar una nueva region? (1: Si / 0: No): ");
  int respuesta; //Variable para almacenar la respuesta del usuario
  scanf("%d", &respuesta); //Lee y guarda la respuesta

  if (respuesta != 1) {
      printf("No se agregaran nuevas regiones.\n");
      return;
  }

  printf("Ingrese el nombre de la nueva region: ");
  scanf("%s", &nuevoNombre);

  //Agregamos el nuevo nombre al archivo 
  FILE *Zona = fopen("zonas.txt", "a"); //Abrimos el archivo en modo escritura-añadir
  if (Zona == NULL) {
      perror("\nError al abrir el archivo zonas.txt para agregar nueva region");
      return;
  }
  fprintf(Zona, "%s\n", nuevoNombre); 
  fclose(Zona);
  
  //Agregamos los datos de incendios 
  FILE *IncendiosTotales = fopen("IncendiosTotales.txt", "a");
  if (IncendiosTotales == NULL) {
      perror("\nError al abrir el archivo IncendiosTotales.txt para agregar nueva region");
      return;
  }
  printf("Ingrese los datos de incendios para la nueva region %s:\n", nuevoNombre);
  for (int j = 0; j < NUM_MESES; j++) { 
      printf("Ingrese el numero de incendios para %s: ", meses[j]); //Se pie ingresar para cada mes 
      scanf("%d", &incendiosIngresados[j]); //Se lee y guarda el numero de incendios 
      fprintf(IncendiosTotales, "%d ", incendiosIngresados[j]); 
  }
  fprintf(IncendiosTotales, "\n");
  fclose(IncendiosTotales);
  
  //Agregamos datos de hectareas quemadas 
  FILE *HectareasQuemadas = fopen("HectareasQuemadas.txt", "a");
  if (HectareasQuemadas == NULL) {
      perror("\nError al abrir el archivo HectareasQuemadas.txt para agregar nueva region");
      return;
  }
  printf("Ingrese los datos de hectareas quemadas para la nueva region %s:\n", nuevoNombre);
  for (int j = 0; j < NUM_MESES; j++) {
      printf("Ingrese la cantidad de hectareas para %s: ", meses[j]); //Se pide ingresar para cada mes
      scanf("%f", &hectareasIngresadas[j]); //Lee y guarda la cantidad de hectareas quemadas 
      fprintf(HectareasQuemadas, "%.2f ", hectareasIngresadas[j]); 
  }
  fprintf(HectareasQuemadas, "\n");
  fclose(HectareasQuemadas);

  //Imprimir los datos ingresados 
   for (int j = 0; j < NUM_MESES; j++) { 
      printf("%s -> Incendios: %d, Hectareas quemadas: %.2f\n", meses[j], incendiosIngresados[j], hectareasIngresadas[j]); 
  }
  printf("************************************************************************************************************************\n");
}

void ActualizarDatos(const char *ArchivoModificar, const char *nombres[NUM_REGIONES]) {
  int IncendiosTotales[NUM_REGIONES][NUM_MESES];
  float HectareasTotales[NUM_REGIONES][NUM_MESES];
  int respuesta = 0; //Variable para guardar la respuesta del usuario 
  const char *mes[NUM_MESES] = {"Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

  printf("Desea modificar datos de Incendios ? (1: Si / 0: No): ");
  scanf("%d", &respuesta);

  if (respuesta == 1) {
    int region;
    printf("\nIngrese la Region que desea actualizar\nCuyo(1)\nPampeana(2)\nPatagonica(3)\nNoroeste(4)\nNoreste(5)\n");
    scanf(" %d", &region);

    //Verificar si la region es valida 
    if (region < 1 || region > NUM_REGIONES) {
      printf("Region no valida.\n");
      return;
    }

    //Abrimos el archivo para lectura 
    FILE *archivo_lectura = fopen(ArchivoModificar, "r"); //Archivo_Modificar = IncendiosTotales.txt
    if (!archivo_lectura) {
      perror("\nError al abrir el archivo para lectura");
      return;
    }

    // Leer datos desde el archivo
    for (int i = 0; i < NUM_REGIONES; i++) { 
      for (int j = 0; j < NUM_MESES; j++) {
        fscanf(archivo_lectura, "%d", &IncendiosTotales[i][j]);
      }
    }
    fclose(archivo_lectura);

    // Actualizar la región seleccionada por el usuario
    printf("Region %s:\n", nombres[region - 1]); //region -1 para que el indice sea del 0 al 4

    int mes, cantidad; // Almacena el mes y la cantidad de incendios 
    int tipo_incendio; //Almacena el tipo de incendio
    char *tipo_nombre; //Almacena el nombre del tipo de incendio seleccionado
    
    printf("Ingrese el numero del mes que desea actualizar (1-6):\n");
    printf("1. Julio\n2. Agosto\n3. Septiembre\n4. Octubre\n5. Noviembre\n6. Diciembre\n");
    scanf("%d", &mes);
    
    //Verificar si el mes es valido 
    if (mes >= 1 && mes <= 6) {
        printf("Seleccione el tipo de incendio:\n"); 
        printf("1. Activo\n2. Controlado\n3. Contenido\n");
        scanf("%d", &tipo_incendio);
        
        switch (tipo_incendio) { //Segun el tipo de incendio seleccionado
            case 1: tipo_nombre = "Activo"; break;
            case 2: tipo_nombre = "Controlado"; break;
            case 3: tipo_nombre = "Contenido"; break;
            default: tipo_nombre = "Desconocido"; break;
        }
        
        //Verificar si el tipo de incendio es valido 
        if (tipo_incendio >= 1 && tipo_incendio <= 3) { 
            printf("Ingrese numero de cantidad de incendios para el mes seleccionado: ");
            scanf("%d", &cantidad);
            printf("Se han registrado %d incendios del tipo %s en el mes seleccionado.\n", cantidad, tipo_nombre);
        } else {
            printf("Opcion de tipo de incendio no valida.\n");
        }
    } else {
        printf("Opcion de mes no valida.\n");
    }
    return 0;
  }
  printf("************************************************************************************************************************\n");
}
