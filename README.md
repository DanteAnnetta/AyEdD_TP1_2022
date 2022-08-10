# Trabajo Práctico 1 Algoritmos y Estructuras de Datos

  En el siguiente repositorio se pueden encontrar los siguientes archivos de interés:

* alfa.cpp
* beta.cpp

  Si bien ambos archivos cumplen perfectamente con las consignas enunciadas en la actividad, cabe destacar las diferencias entre ambos:


## alfa.cpp

Como su nombre lo indica, esta es la primera versión del código,  por lo que su función principal es orientar al lector en cómo fue concebido el mismo. Tiene bastantes líneas comentadas con explicaciones y pruebas parciales del correcto funcionamiento de cosas puntuales que me ayudaron a realizar el debbugging del programa. Otra cosa que es importante mencionar, es que la prioridad en este programa siempre fue un funcionamiento "rápido y sucio" y, que esto se hizo intencionalmente para probar distintas formas de encarar los distintos problemas. Es por esto, que en ciertos lugares hay párrafos comentados con lo que se me ocurrió a medida que lo escribí, junto con anotaciones de cosas a mejorar en la segunda versión.

## beta.cpp

Para analizar este programa, es recomendable haber entendido a grandes rasgos su versión anterior, junto con las acotaciones en este, ya que la estructura general del programa aún se mantiene intacta. Los cambios más importantes son:

* Reemplazo de la array data: en la versión alfa, por cuestiones de comodidad, todos los datos del archivo "Datos.txt" se almacenan en una array de valores flotantes, ya que permite desde el minuto 1 el poder hacer operaciones matemáticas con los valores que contiene. Sin embargo esto dista bastante de ser la opción más eficiente, en primer lugar porque el archivo es leído dos veces, uno para saber la cantidad de líneas y otra para organizar los datos en sus respectivas filas y columnas, habiendo convertido dos columnas enteras de datos enteros en flotantes únicamente por cuestiones de comodidad. Para reemplazar esto, se utilizan 4 vectores, que almacenan los datos correspondientes a cada columna, de modo que se lee una única vez y no hay enteros convertidos a flotantes.
* Eliminación de aclaraciones redundantes y comentarios sin contexto.
* Nombres de variables más amigables para entender la sintáxis.









© 2022 Dante Annetta