#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>

#define max_valor 100

typedef struct Node{
    int menor;
    int mayor;
}Node;

int arr[max_valor];

void merge(int menor, int mitad, int mayor)
{
    int i, j, k;
    int n1 = mitad - menor + 1;
    int n2 =  mayor - mitad;
    int izq[n1], der[n2];
    for (i = 0; i < n1; i++)
        izq[i] = arr[menor + i];
    for (j = 0; j < n2; j++)
        der[j] = arr[mitad+ 1+ j];

    i = 0;
    j = 0;
    k = menor;
    while (i < n1 && j < n2)
    {
        if (izq[i] <= der[j])
        {
            arr[k] = izq[i];
            i++;
        }
        else
        {
            arr[k] = der[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = izq[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = der[j];
        j++;
        k++;
    }
}
void* mergeSort(void* arg)
{
    Node nodo = *((Node*)arg);
    int menor = nodo.menor;
    int mayor = nodo.mayor;
    if (menor < mayor)
    {
        int mitad = menor+(mayor-menor)/2;
        pthread_t thread1;
        Node n1 = {menor, mitad};
        pthread_t thread2;
        Node n2 = {mitad+1, mayor};
        pthread_create(&thread1, NULL, mergeSort, &n1);
        pthread_create(&thread2, NULL, mergeSort, &n2);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        merge(menor, mitad, mayor);
    }
}

int main()
{
        char input[max_valor];
        int i;
	int count = 1;

        printf("Ingrese numeros a ordenar, separados por comas:");
        fgets(input,sizeof(input), stdin);
        printf("Usted ingreso la lista: %s\n ",input);

        char *token = strtok(input,",");
	arr[0] = atoi(token);
        while(token!= NULL){
                arr[count]=atoi(token);
		token = strtok(NULL, ",");
                count++;
        }
        Node node = {0,count};
        pthread_t t;
        pthread_create(&t,NULL,mergeSort,&node);
        pthread_join(t,NULL);

	printf("La lista ordenada es: ");
        for (i = 1; i < count ; i++) {
                 printf("%d ", arr[i]);
        }
	printf("\n");

	return 0;
}
