Copyright (c) 2026 Vicent Roig. All rights reserved.

WARNING: This software is the proprietary property of Vicent Roig.
Unauthorized copying, modification, or distribution of this file, via any 
medium, is strictly prohibited. Proprietary and confidential.

Es necesario dar permisos de ejecución a "compilar_x64.sh" y "compilar_y_ejecutar.sh" (En caso de tener que volver a crear el parser también se deben asignar permisos a "flex_bison.sh"

Para ejecutar el código únicamente es necesario utilizar el script "compilar_y_ejecutar"
./compilar_y_ejecutar.sh <nombre_fichero>

Con el comando script flex_bison se vuelve a generar el parser (por si fuera necesario)

Se ha hecho uso de flex, bison, g++, nasm y gcc tanto para front-end y back-end, es necesario tenerlos
para que funcionen los scripts.
