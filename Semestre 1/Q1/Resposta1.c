#include <stdio.h>
#include <stdlib.h>

int main(){
	int c[2];
	for (int j= 0; j <2; j++){
		scanf("%d", &c[j]);

	}
	int mat[c[0]][c[1]];
   for (int i = 0; i <c[0]; i++){
		for (int j= 0; j <c[1]; j++){
			scanf("%d", &mat[i][j]);
			while (mat[i][j] == 0){
				scanf("%d", &mat[i][j]);
			}
		}
	}
	for (int i = 0; i < c[0]; i++){
		for (int j = 0; j < c[1]; j++){
			printf("%d ", mat[i][j]);
		}
		printf(".\n");
	}
}
