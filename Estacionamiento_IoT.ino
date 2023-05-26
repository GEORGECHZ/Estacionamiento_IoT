#include "Tareas.h"
millis_tasks tsk;

void setup ( void ) {
  
  Serial.begin ( 115200 );        /* Inicializar baudrate a 115200 */
  tsk.tareas_init();

}

void loop ( void ) {
  tsk.actualizar_tareas();
  tsk.tarea1();
  tsk.tarea2();
  tsk.tarea3();
  tsk.tarea4();
}