
#include <mpi.h>
#include <stdio.h>

const int N=5000;
//----------------------------------------------------
double  dotProduct(double *x, double y, int n) {
  int i;
  double prod;
  for (i = 0; i < n; i++) {
    prod += x[i]*y;
  }
  return prod;
}//----------------------------------------------------


int main(int argc, char *argv[]) {
  int i;
  int j;
  int z;
  double prod[50];
  int my_rank;
  int num_procs;
  double data = 0;
 //----------------------------------------------------
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  //----------------------------------------------------
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int local_N = N / num_procs;
  double local_x[local_N];
  
  for(i = 0; i < local_N; i++) {
    local_x[i] = 3 * i;
  }
  

  double local_prod[local_N];
  for(j =0; j < local_N; j++){
  
  local_prod[j] = dotProduct(local_x,10.5,local_N);	
	}
  //----------------------------------------------------
	MPI_Scatter(&local_prod, 1, MPI_DOUBLE, &data, MPI_DOUBLE,0, MPI_COMM_WORLD);
  //----------------------------------------------------
  if (my_rank == 0) {	  
    printf("dotProduct = %f ",data);
}
    
  MPI_Finalize();

  return 0;
}
