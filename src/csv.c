#include "csv.h"

char buffer[20];

void get_time() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", time_info);
}

void setup_csv() {
  FILE *file = fopen("logs/data.csv", "w");
  fprintf(file, "DATETIME, TR, TI, TE, INTENSITY\n");
  fclose(file);
}

void write_csv(float TR, float TI, float TE, float intensity) {
  // Update Datetime
  get_time();

  // Write file
  FILE *file = fopen("logs/data.csv", "a");

  fprintf(file, "%s, %4.2f, %4.2f, %4.2f, %4.2f\n", buffer, TR, TI, TE, intensity);
  fclose(file);
}