#include<stdio.h>
#include<stdlib.h>
typedef struct tree {
    int value;
    struct tree*left;
    struct tree*right;
}tree;
int main(){
    int N;
    printf(" enter size of array: ");
    scanf("%d",&N);
    tree**arrytree=(tree**)malloc(sizeof(tree*)*N);
    if (arrytree==NULL){
        exit(1);}
        for (int i=0;i<N;i++){
            arrytree[i]=NULL;}
            printf("{");
            for(int i=0;i<N;i++){
                printf("tree %d",i+1);
                if (i<N-1){ printf(";");} 
            } printf("}");
            free(arrytree);
            return 0;}
