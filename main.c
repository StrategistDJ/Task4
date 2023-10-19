#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ROWS 50
#define MAX_L 20
#define FILENAME "../meetings.csv"

//definizione di struct per il salvataggio dei dati
typedef struct{
    char giorno[MAX_L], mese[MAX_L], anno[MAX_L];
}calendario;

typedef struct {
    char riunione[MAX_L], tipo[MAX_L];
    char nome[MAX_L], posto[MAX_L];
    calendario data;
}associato;

associato *readFile(FILE* fin, int *tot);
int *ricercaAss(associato *vettore,char *nome_ass, int tot);
associato *ordinaRes(associato *vettore, int numero);
void stampaRes(associato *vettore, int *res, int numero);

int main() {
    FILE* fin;
    char input[10];
    associato *v;
    int *res_v, i, cnt_ass, cnt_tot;
    int flag = 1;
//apertura del file
    fin = fopen (FILENAME, "r");

    if( fin == NULL){
        printf("Errore apertura del file!!");
        return -1;
    }
//conta il numero totale di righe presenti nel file
    cnt_tot = 0;
    v = readFile(fin, &cnt_tot);

    /*v = ordinaRes(v, cnt_tot);*/

    while (flag){
        printf("Area da considerare\n");
        printf("Per uscire inserire (exit):");
        scanf(" %s", input);
        if(strcmp(input, "exit") == 0){
            flag = 0;
        }
    }


    res_v = ricercaAss(v, input, cnt_tot);

//conta il numero di associazioni che sono state trovate
    flag = 1;
    cnt_ass = 0;
    for(i=0; res_v[i]!=0 || flag;i++){
        if(res_v[i] == 0){
            flag = 0;
        }
        cnt_ass++;
    }
    stampaRes(v, res_v, cnt_ass);

    free(res_v);
    free(v);
    return 0;
}

//legge il file e lo salva in un vettore di struct create precedentemente
associato *readFile(FILE *fin, int *tot) {
    associato *m;
    int i=0;
    char parola[MAX_L];

    m = malloc(N_ROWS * sizeof(associato));

    while(!feof(fin)) {
        fscanf(fin, "%s %[^;];%[^/]/%[^/]/%[^;];%s", m[i].riunione, parola, m[i].data.giorno, m[i].data.mese, m[i].data.anno, m[i].posto);
        sscanf(parola, " %s %[^\n]", m[i].tipo, m[i].nome);
        i++;
    }
    *tot = i;

    return m;
}

//ricerca nel vettore di struct l'associazione inserita da tastiera
//mettere in un vettore risultato che contiene gli indici delle associazioni cercate
int *ricercaAss(associato *vettore, char *nome_ass, int tot){
    int i, j=0, *res;

    res = calloc (tot, sizeof(int));

    for(i=0; i<tot; i++){
        if(strstr(vettore[i].nome, nome_ass) != NULL || strcmp(vettore[i].tipo, "Generale") == 0){
            res[j] = i;
            j++;
        }
    }
    return res;
}
/*
 (Per motivi tempistici non ho potuto finire la funzione di ordinamento, mi dispiace)
 La logica per cui adotterei:
-la prima è quella di creare una funzione in grado di ordinare il mio vettore di struct
 letto dal file in base alla data usando le funzione della libreria string.h il salvataggio è stato avvenuto tramite stringa
 altrimenti utilizzare una funzione di atoi() per convertire la stringa in carattere.
-la seconda invece è quella di ordinare direttamente il vettore res contenente gli indici per cui si sta cercando l'associazione
associato *ordinaRes(associato *vettore, int numero){

}*/
//infine questa funziona stampa il risultato su console
void stampaRes(associato *vettore, int *res, int numero){
    int i;

    for(i=0; i<numero; i++){
        if(strlen(vettore[res[i]].nome)>2){
            printf("RIUNIONE %s %s\t\t %s-%s-%s \t%s\n", vettore[res[i]].tipo,  vettore[res[i]].nome,  vettore[res[i]].data.anno, vettore[res[i]].data.mese,
                   vettore[res[i]].data.giorno,  vettore[res[i]].posto);
        }
        else{
            printf("RIUNIONE %s %s\t\t\t\t %s-%s-%s \t%s\n", vettore[res[i]].tipo,  vettore[res[i]].nome,  vettore[res[i]].data.anno, vettore[res[i]].data.mese,
                   vettore[res[i]].data.giorno,  vettore[res[i]].posto);
        }
    }
}