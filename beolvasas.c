
#include "beolvasas.h"
#include "debugmalloc.h"
#include <stdlib.h>
#include "graphElements.h"

FILE* edges;
FILE* nodes;

void NodeInit(Node *a){
    a->hCost=INT_MAX;
    a->gCost=INT_MAX;
    a->parent = NULL;
}
void FreeNodes(int l, Node *t){
    for (int i = 0; i < l ; ++i) {
        free(t[i].p);
    }
    free(t);
}
Node *NodeInput(int *nodeNum){
    nodes = fopen("C:\\Users\\bandi\\CLionProjects\\Astar\\datas\\nodes.txt", "r");
    edges = fopen("C:\\Users\\bandi\\CLionProjects\\Astar\\datas\\edges.txt", "r");
    Node *tomb;

    if (nodes != NULL) {
        fscanf(nodes, "%d", nodeNum);
        tomb = (Node*) malloc(*nodeNum*sizeof(Node));
        char tmp[256];
        int degreeSum[*nodeNum];
        if(edges != NULL){
            int a, b;
            for (int i = 0; i < *nodeNum; ++i) {
                degreeSum[i] = 0;
            }
            while(fgets(tmp, 256, edges)){
                if(sscanf(tmp, "<data key=\"d24\">%d</data>", &a)==1){
                    degreeSum[a]++;
                }
                if(sscanf(tmp, "<data key=\"d25\">%d</data>", &b)==1){
                    degreeSum[b]++;
                }
            }
        }
        else{
            perror("Nem sikerült megnyitni a fájlt");
        }
        int id;
        while(fgets(tmp, 256, nodes)) {
            if(sscanf(tmp,"<node id=\"%d\">", &id) ==1){
                tomb[id].index= id;
                NodeInit(&tomb[id]);
                tomb[id].fokszam = degreeSum[id];
                tomb[id].p = (Edge*) malloc(degreeSum[id]*sizeof(Edge));
            }
            sscanf(tmp,"<data key=\"d5\">%lf</data>", &tomb[id].x);
            sscanf(tmp,"<data key=\"d6\">%lf</data>", &tomb[id].y);
        }
    }
    else {
        tomb = NULL;
        perror("Nem sikerült megnyitni a fájlt");
    }
    fclose(nodes);
    return tomb;
}
void EdgeInput(Node *tomb, int const *m){
    edges = fopen("C:\\Users\\bandi\\CLionProjects\\Astar\\datas\\edges.txt", "r");

    if(edges != NULL){
        char tmp[256];
        int EdgesIndex[*m];
        int a, b;
        double c, d;
        for (int i = 0; i < *m; ++i) {
            EdgesIndex[i] = 0;
        }
        while(fgets(tmp, 256, edges)){
            sscanf(tmp, "<edge source=\"%d\" target=\"%d\" id=\"%*d\">", &a, &b);
            if(sscanf(tmp, "<data key=\"d18\">%lf</data>", &c) == 1){
                tomb[a].p[EdgesIndex[a]].length = c;
                tomb[b].p[EdgesIndex[b]].length = c;
            }
            if(sscanf(tmp, "<data key=\"d20\">%lf</data>", &d)==1){
                tomb[a].p[EdgesIndex[a]].time = d;
                tomb[b].p[EdgesIndex[b]].time = d;
            }
            if(sscanf(tmp, "<data key=\"d24\">%d</data>", &b)==1){
                tomb[b].p[EdgesIndex[b]++].p1 = &tomb[a];
            }
            if(sscanf(tmp, "<data key=\"d25\">%d</data>", &a)==1){
                tomb[a].p[EdgesIndex[a]++].p1 = &tomb[b];
            }
        }
    }
    else{
        perror("Nem sikerült megnyitni a fájlt");
    }
    fclose(edges);
}
