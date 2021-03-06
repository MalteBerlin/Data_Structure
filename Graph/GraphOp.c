#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "LinkQueue.h"

Status InitMGraph(MGraPtr *G){
    (*G) = (MGraPtr)malloc(sizeof(MGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateMGraph(MGraph *G){
    printf("Enter kind: ");
    scanf("%d",&(G->kind));
    switch(G->kind){
        case DG: return CreateMDG(G); break;
        case DN: return CreateMDN(G); break;
        case UDG:return CreateMUDG(G); break;
        case UDN:return CreateMUDN(G); break;
        default : return ERROR;
    }
}

Status CreateMDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) {
        printf("Enter vex-name: ");
        scanf("%d",&(G->vexs[i]));
    }
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=1;
    }
    return OK;
}

Status CreateMDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    getchar();
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) {
        printf("Enter vex-name: ");
        scanf("%c",&(G->vexs[i])); getchar();
    }
    for(i=0;i<MAX_VERTEX_NUM;i++)
        for(j=0;j<MAX_VERTEX_NUM;j++)
            G->arcs[i][j]=INFINITY;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=w;
        G->arcs[hd][hd] = G->arcs[tl][tl] = 0;
    }
    return OK;
}

Status CreateMUDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=G->arcs[tl][hd]=1;
    }
    return OK;
}

Status CreateMUDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=G->arcs[tl][hd]==w;
    }
    return OK;
}

Status ShowAdjArray(MGraph G){
    printf("\n\n----------------------------\n");
    int i,j;
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            printf("%6d  ",G.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateALGraph(ALGraph *G){
    printf("Input kind, vexnum and edgenum (kind vn en): ");
    scanf("%d%d%d",&(G->kind),&(G->vexnum),&(G->edgenum));
    getchar();
    //initialize
    int i;
    for(i=0;i<G->vexnum;i++){
        G->v[i].vertex = 'A'+i;
        G->v[i].first  = NULL;
    }
    //input
    char h,t;
    printf("Input edge x-->y (x y): ");
    scanf("%c%c",&h,&t);
    getchar();
    while(h>='A'&&h<='Z'&&t>='A'&&t<='Z'){
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = t-'A';
        p->nextarc = G->v[h-'A'].first;
        G->v[h-'A'].first = p;
        //
        if(G->kind == UDG || G->kind==UDN){//undirected graph
            ArcNode *q = (ArcNode*)malloc(sizeof(ArcNode));
            if(!q)  exit(OVERFLOW);
            q->adjvex = h-'A';
            q->nextarc = G->v[t-'A'].first;
            G->v[t-'A'].first = q;
        }
        printf("Input edge x-->y (x y): ");
        scanf("%c%c",&h,&t);
        getchar();
    }
    return OK;
}

Status ShowADJList(ALGraph G){
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("%d: %c--> ",i,G.v[i].vertex);
        ArcNode* p = G.v[i].first;
        while(p){
            printf("%d ",p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
    return OK;
}

int FirstAdjVex(ALGraph G, int x){
    //return the 1st node adjacent to node x(0-vexnum-1)
    if(x<0 || x>=G.vexnum)  return -1;
    ArcNode *p = G.v[x].first;
    if(p)   return p->adjvex;
    else return -1;
}

int NextAdjVex(ALGraph G, int x, int y){
    //return <x,y>'s next z s.t (s,z)
    if(x<0||x>=G.vexnum)    return -1;
    if(y<0||y>=G.vexnum)    return -1;
    ArcNode *p = G.v[x].first;
    while(p && p->adjvex!=y) p=p->nextarc;
    if(p && p->nextarc) return p->adjvex;
    else return -1;
}

Status InitOLGraph(OLGraPtr *P){
    (*P)=(OLGraPtr)malloc(sizeof(OLGraph));
    if(!(*P)) exit(OVERFLOW);
    return OK;
}

Status CreateOLGraph(OLGraph *G){
    printf("Enter vexnum and arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    getchar();
    int i;
    //initilaize
    for(i=0;i<G->vexnum;i++){
        G->xlist[i].data = 'A'+i;
        G->xlist[i].firstout = G->xlist[i].fisrtin = NULL;
    }
    for(i=0;i<G->arcnum;i++){
        char x,y;
        printf("Enter edge%d(x->y is x y): ",i);
        scanf("%c%c",&x,&y); getchar();
        if(x<'A'||x>'Z'||y<'A'||y>'Z'){
            printf("Over bound A-Z\n");
            exit(OVERFLOW);
        }
        //construct
        ArcBox * arcPtr = (ArcBox *)malloc(sizeof(ArcBox));
        if(!arcPtr) exit(OVERFLOW);
        arcPtr->headvex = y-'A';
        arcPtr->tailvex = x-'A';
        arcPtr->hlink = G->xlist[y-'A'].fisrtin;
        arcPtr->tlink = G->xlist[x-'A'].firstout;
        G->xlist[y-'A'].fisrtin = arcPtr;
        G->xlist[x-'A'].firstout = arcPtr;
    }//for

    return OK;
}

Status ShowOLGraph(OLGraph G){
    int i;
    printf("Every node and the dege goes from it:\n");
    for(i=0;i<G.vexnum;i++){
        printf("(%d)%c: ",i,G.xlist[i].data);
        ArcBox * p = G.xlist[i].firstout;
        while(p){
            printf("(%c,%c)",p->tailvex+'A',p->headvex+'A');
            p = p->tlink;
        }
        printf("\n");
    }
    return OK;
}

//AMLGraph
Status InitAMLGraph(AMLGraPtr *G){
    (*G)=(AMLGraPtr)malloc(sizeof(AMLGraph));
    if(!(*G))   exit(OVERFLOW);
    return OK;
}

Status CreateAMLGraph(AMLGraph *G){
    int vn,en;
    printf("Enter vexnum and edgenum(vn en): ");
    scanf("%d%d",&(vn),&(en));
    getchar();
    if(vn<0 || en<0 || en>=MAX_VERTEX_NUM){
        printf("en:>=0\nvn:0-%d",MAX_VERTEX_NUM);
        return ERROR;
    }
    G->edgenum = en;
    G->vexnum = vn;
    //initialize
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        G->adjmulist[i].data = 'A'+i;
        G->adjmulist[i].firstedga = NULL;
    }
    //input the edge
    for(i=0;i<G->edgenum;i++){
        char head,tail;
        printf("Enter vex (A-B)(eg:AB): ");//tail-head
        scanf("%c%c",&tail,&head); getchar();
        if(tail<'A'||tail>'Z'||head<'A'||head>'Z'){
            printf("Out of range!You should enter again!\n");
            i--;
            continue;
        }
        EBox * enode = (EBox*)malloc(sizeof(EBox));
        int ih = head - 'A';
        int it = tail - 'A';
        enode->ivex = it;
        enode->jvex = ih;
        enode->ilink = G->adjmulist[it].firstedga;
        enode->jlink = G->adjmulist[ih].firstedga;
        enode->mark = unvisited;
        G->adjmulist[it].firstedga = enode;
        //G->adjmulist[ih].firstedga = enode;
    }
    return OK;
}

Status ShowAMLGraph(AMLGraph G){
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("(%d)%c --> ",i,G.adjmulist[i].data);
        EBox *p=G.adjmulist[i].firstedga;
        while(p){
            printf("<%c,%c>  ",p->ivex+'A',p->jvex+'A');
            p = p->ilink;
        }
        printf("\n");
    }
    return OK;
}

Status ShowAMLGedge(AMLGraph G,int i,int *n){ //i:the index of the node
    if(i<0 || i>G.vexnum){
        printf("Out of range!\n");
        return ERROR;
    }
    int j,num=0;
    for(j=0;j<G.vexnum;j++){
        EBox *p = G.adjmulist[j].firstedga;
        while(p){
            if((p->ivex==i)||(p->jvex==i)){
                num++;
            }
            p = p->ilink;
        }
    }
    *n = num;
    return OK;
}

Status visit(ElemType e){
    printf("%4c",e);
    return OK;
}

//test:
//2 8 9 AB AC CF CG FG BD BE EH DH 1 1
//Depth First Search --- DFS
//using data structure --- positive ALGraph (adjcent list)
Status DFSGraph(ALGraph * p,Status(*visit)(ElemType e)){
    int visited[p->vexnum];
    int i;
    for(i=0;i<p->vexnum;i++)    visited[i] = False;
    for(i=0;i<p->vexnum;i++)
        if(visited[i]==False) DFS(p,visited,i,visit),printf("\n***\n");
    return OK;
}

Status DFS(ALGraph *g,int *visited,int i,Status(*visit)(ElemType e)){
    visited[i] = True;
    visit(g->v[i].vertex);
    ArcNode * arc = g->v[i].first;
    while(arc){
        if(visited[arc->adjvex]==False)
            DFS(g,visited,arc->adjvex,visit);
        arc = arc->nextarc;
    }
    return OK;
}

//BFS
//non-recursion
//key: visit and then add it to queue
//so queue has nodes having been visited
Status BFS(ALGraph* G, Status(*visit)(ElemType e)){
    int i;
    int visited[G->vexnum];
    for(i=0;i<G->vexnum;i++) visited[i]=False;
    LinkQueue *lq;
    InitQueue(&lq);
    for(i=0;i<G->vexnum;i++){
        if(visited[i]==False){
            visited[i] = True;     //set true
            visit(G->v[i].vertex); //fisrt visit it
            EnQueue(lq,i);        //then push it
            while(!IsQueueEmpty(lq)){
                int j;
                DeQueue(lq,&j);
                ArcNode * arc;
                for(arc = G->v[j].first;arc;arc=arc->nextarc){
                    if(visited[arc->adjvex]==False){
                        visit(G->v[arc->adjvex].vertex);
                        visited[arc->adjvex]=True;
                        EnQueue(lq,arc->adjvex);
                    }//if
                }//while
            }
            printf("\n");
        }//if
    }//for
    return OK;
}

Status BFS_II(ALGraph*G, Status(*visit)(ElemType e),int x){
// x is the first node to be visited
//q[0 --- head) store what has been visited
//q[head --- rear) store what are to be visited
    //int visited[G->vexnum];
    int index;
    //for(index=0;index<G->vexnum;index++) visited[index] = False; //initial it
    if(x<0 || x>= G->vexnum) return ERROR;
    int q[MAX_VERTEX_NUM+1],head,rear;
    head = rear = 0;
    q[rear++] = x;  // x add to queue
    while(head != rear){
        int j = q[head++]; //take the head of the queue
        ArcNode * arc = G->v[j].first;
        visit(G->v[j].vertex); //visited[j]=True;//visit it
        for( ; arc ; arc=arc->nextarc){//add its adjacent nodes to the queue
            for(index = 0;index<rear; index++){
                if(q[index]==arc->adjvex) break;
            }
            if(index >= rear)
                q[rear++] = arc->adjvex;
        }//for
    }//while
    return OK;
}

Status DFSPath(ALGraph *G,int a,int b,char *path){
//find a simple path from a to b
    if(!G || a<0 || b<0 || a>=G->vexnum || b>=G->vexnum) return ERROR;
    int visited[G->vexnum],i;
    for(i=0;i<G->vexnum;i++) visited[i]=False;
    *(path++) = G->v[a].vertex; visited[a]=True; //visit
    int found = 0;//1: found
    ArcNode * arc;
    for(arc = G->v[a].first; arc && (!found) ; arc = arc->nextarc){
        if(arc->adjvex == b){
            found = 1;
            *(path++) = G->v[arc->adjvex].vertex;
            *(path) = '\0';
        }else{
            DFSsearch(G,arc->adjvex,b,path,&found,visited);
        }
    }
    char s[11]="Not found"; int mmm;
    if(found==0) {
        path--;
        for(mmm=0;mmm<11;mmm++) *(path++) = s[mmm];
    }
    return OK;
}

Status DFSsearch(ALGraph *G,int start,int target,char *path,int *found,int *visited){
    visited[start]=True;
    if(start==target){
        *found = 1;
        *(path++) = G->v[start].vertex;
        *(path) = '\0';
        return OK;
    }
    *(path++) = G->v[start].vertex;
    ArcNode * arc;
    for(arc=G->v[start].first; arc&&(!*found) ;arc=arc->nextarc){
        if(visited[arc->adjvex]==False)
            DFSsearch(G,arc->adjvex,target,path,found,visited);
    }
    //if(found==0) *(--path)='\0';
    return OK;
}







