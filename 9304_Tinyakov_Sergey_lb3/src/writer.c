#include "writer.h"
#include <stdlib.h>

void* writer_thread(void *arg){
    WriterThreadInfo *info = (WriterThreadInfo*) arg;
    FILE *f;
    if (info->filename == NULL){
        f = stdout;
    }else{
        f = fopen(info->filename, "w");
        if (f == NULL){
            return NULL;
        }
    }
    long counter = 0;
    while(1){
        if(counter >= info->iter_count) break;
        int *data = (*info->queue_pop_func)(info->writer_queue);
        if (data == NULL) continue;
        counter++;
        fprintf(f, "Summed matrix %d\n", counter);
        for(long i = 0; i < info->matrix_height; i++){
            for(long j = 0; j < info->matrix_width; j++){
                fprintf(f, "%d ", data[i * info->matrix_width + j]);
            }
            fprintf(f, "\n");
        }
        free(data);
    }
    if (info->filename != NULL){
        fclose(f);
    }
    return NULL;
}
