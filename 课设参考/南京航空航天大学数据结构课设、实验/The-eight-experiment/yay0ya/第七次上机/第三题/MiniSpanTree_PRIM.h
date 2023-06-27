#include"Graph.h"
#define Max 32767
typedef struct clos{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];
static int count=0;
Status minimum(clos closedge[],MGraph G){
	int min,flag=0;
	for(int i=0;i<G.vexnum;i++){
		if(closedge[i].lowcost!=0&&closedge[i].lowcost!=Max){
			min=closedge[i].lowcost;
			flag=i;
			break;
		}
	}
	for(int i=0;i<G.vexnum;i++){
		if(closedge[i].lowcost<min&&closedge[i].lowcost!=Max&&closedge[i].lowcost!=0){
			min=closedge[i].lowcost;
			flag=i;
		}
	}
	count+=min;
	return flag;
}
void MiniSpanTree_PRIM(MGraph G,VertexType u){
	int k;
	closedge closedge;
	k=LocateVex(G,u);
	for(int j=0;j<G.vexnum;++j){
		if(j!=k){
			closedge[j].adjvex=u;
			closedge[j].lowcost=G.arcs[k][j].adj;
	}
	}
	closedge[k].lowcost=0;
	for(int i=1;i<G.vexnum;i++){
		k=minimum(closedge,G);
		cout<<"����"<<closedge[k].adjvex<<"��"<<"����"<<G.vexs[k]<<" ";
		closedge[k].lowcost=0;
		for(int j=0;j<G.vexnum;++j){
			if(G.arcs[k][j].adj<closedge[j].lowcost)
			{
				closedge[j].adjvex=G.vexs[k];
				closedge[j].lowcost=G.arcs[k][j].adj;
			}
		}
	}
	cout<<"��Сά�޷�Ϊ"<<count;
	
}//miniSpanTree
