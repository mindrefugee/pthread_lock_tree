#include <stdlib.h>
#define DEBUG
#ifdef DEBUG
#include "stdio.h"
#endif



struct _pc_management{
  int nparm;
  int nconst;
  int ndata;
};
typedef struct _pc_management pc_management;

struct _pc_element{
  double* param_p;
  double* const_p;
};

typedef struct _pc_element pc_element;

struct _pc_map_struct
{
  int nparam;
  int nconst;
  int ndata;
  //pc_management manager;
  int idata;
  
  pc_element*  data;
};

typedef struct _pc_map_struct pc_map_struct;

pc_map_struct pc_map;



int pc_map_add(const double* param,const double* constrain){
  int i;
  
  // This is a critical session. -start
  
  if(pc_map.idata<pc_map.ndata){
    pc_map.data[pc_map.idata].param_p
      =(double*) malloc(sizeof(double)*pc_map.nparam);
    pc_map.data[pc_map.idata].const_p
      =(double*) malloc(sizeof(double)*pc_map.nconst);
    for(i=0;i<pc_map.nparam;i++){
      pc_map.data[pc_map.idata].param_p[i]=param[i];
    }
    for(i=0;i<pc_map.nconst;i++){
      pc_map.data[pc_map.idata].const_p[i]=constrain[i];
    }
    pc_map.idata++;
  } else {
    printf("pc_map.data is full!\n");
  }
  
  // This is a critical session - end.
  return 0;
}

double pc_map_const(const double* param, const int iconst){
  int i;
  int isave;

  
  // This is a critical session. -start
  
  for(i=0;i<pc_map.idata;i++){
    if(pc_map_param_compare(pc_map.data[i].param_p,param)){
	isave=i;
	break;
    }
  }
  return pc_map.data[isave].const_p[iconst];

  
  // This is a critical session - end.
  
    
}
int pc_map_param_compare(const double* p1, const double* p2){
  int i;
  
  for(i=0;i<pc_map.nparam;i++){
    if(p1[i]!=p2[i]){
      /* status=false; */
      /* break; */
      return 0;
    }
  }
  return 1;
}


int pc_map_print(){
  int i,j;

  printf("pc_map status nparam=%d nconst=%d ndata=%d idata=%d\n",
	pc_map.nparam,
	pc_map.nconst,
	pc_map.ndata,
	pc_map.idata);

  for(i=0;i<pc_map.idata;i++){
    printf("pc_map %d-th pc_map_element\n",i);
    printf("parameter\n");
    for(j=0;j<pc_map.nparam;j++){
      printf("%s %d %d %16.14e\n",__func__,i,j,pc_map.data[i].param_p[j]);
    }
    printf("constrain\n");
    for(j=0;j<pc_map.nconst;j++){
      printf("%s %d %d %16.14e\n",__func__,i,j,pc_map.data[i].const_p[j]);
    }
	   
  }

  return 0;
}



int pc_map_init(int _nparam,int _nconst, int _ndata){
  // pc_map.manager.nparam=0;
     pc_map.nparam=_nparam;
     pc_map.nconst=_nconst;
     pc_map.ndata=_ndata;
     pc_map.idata=0;
     pc_map.data=(pc_element*) malloc(sizeof(pc_element)*_ndata);
    
     
#ifdef DEBUG
     printf("%s nparam=%d nconst=%d ndata=%d\n",
	    __func__,
	    pc_map.nparam,
	    pc_map.nconst,
	    pc_map.ndata
	    );
#endif
     return 1;
}
