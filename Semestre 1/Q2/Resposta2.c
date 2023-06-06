#include <stdio.h>
#include <stdlib.h>

int main(){
	int c, mediaa, n = 100;
	scanf("%d", &c);
	float media[c];
   for (int i = 0; i <c; i++){
		media[i] = 0;
		int a = 0;
		scanf("%d", &a);
		int vettur[a];
		for (int j= 0; j <n; j++){
			scanf("%d", &vettur[j]);
			if(getchar() != ' '){
				break;
			}
		}
		for (int j= 0; j <a; j++){
			media[i] += (float)vettur[j];
		}
		
		media[i] = media[i]/(float)a;
		int alunMed = 0;
		for (int j= 0; j <a; j++){
			if (vettur[j] > media[i]){
				alunMed += 1;
			}
		}
		media[i] = ((float) alunMed * 100) / (float)a;
	}
	for (int i = 0; i < c; i++){
		printf("\n%.3f%%", media[i]);
	}
}
