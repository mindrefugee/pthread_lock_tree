#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "MT.h"
#include "pc_map.h"

void param_gen(int nparam, double* param);
  
int main(){

  int nset=1000;
  int nparam=100;
  int nconst=1000;
  int i,j,k;
  double **param;
  double **constrain;
  pc_element *index;
  pc_element *dic;
  int found;
  
  init_genrand(194743097);
  pc_map_init(nparam,nconst,nset);
  
  param = (double**) malloc(sizeof(double*)*nset);
  constrain = (double**) malloc(sizeof(double*)*nset);

  for(i=0;i<nset;i++){

    param[i] = (double*) malloc(sizeof(double)*nparam);
    param_gen(nparam,param[i]);
    constrain[i] = (double*) malloc(sizeof(double)*nconst);
    param_gen(nconst,constrain[i]);
    pc_map_add(param[i],constrain[i]);

    /* for(j=0;j<nparam;j++){ */
    /*   printf("%d %d %e\n", i,j,param[i][j]); */
    /* } */
    /* for(j=0;j<nconst;j++){ */
    /*   printf("%d %d %e\n", i,j,constrain[i][j]); */
    /* } */
    
  }
  /* pc_map_print(); */

  for(i=0;i<nset;i++){
    index=&(pc_map.data[i]);

    for(j=0;j<nset;j++){
      dic=&pc_map.data[j];

      found=1;
      
      for(k=0;k<nparam;k++){
	/* printf("checking %d %d %d %16.14e %16.14e\n", */
	/*        i,j,k,index->param_p[k],dic->param_p[k]); */
	if(index->param_p[k]==dic->param_p[k]){
	  // do nothing
	} else {
	  found=0;
	  break; 
	}
      } /*k-loop*/
      if(found==1) {
	printf("%d-th set is identical to %d-th check %d\n",i,j,i-j);
	break;
      }
    } /*j-loop*/
    
  } /*i-loop*/
  
  return 0;
}

void param_gen(int nparam, double* param){
  int i;
  for(i=0;i<nparam;i++){
    param[i]=genrand_res53();
    /* printf("%s %d %16.14e\n",__func__,i,param[i]); */
  }
  
}
