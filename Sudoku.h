#include <iostream>
#include <cstdio>
#include <ctime>
#include <stdlib.h>
using namespace std;
class Sudoku {
	public:
		void giveQuestion(){
			int mondai[9][9] = {{0, 9, 0, 1, 0, 4, 6, 0, 0},
					 			{0, 7, 1, 0, 0, 0, 0, 0, 4},
					 			{6, 0, 5, 0, 0, 0, 2, 0, 0},
					 			{4, 0, 7, 0, 0, 1, 0, 0, 0},
					 			{1, 0, 9, 7, 0, 8, 5, 0, 2},
					 			{0, 0, 0, 9, 0, 0, 4, 0, 7},
					 			{0, 0, 3, 0, 0, 0, 7, 0, 5},
					 			{9, 0, 0, 0, 0, 0, 8, 2, 0},
					 			{0, 0, 4, 8, 0, 3, 0, 6, 0}
						 		};
			int i, j;
			for (i=0; i<9; i++){
				for (j=0; j<9; j++){
					cout << mondai[i][j];
					if (j!=8){
						cout << " ";
					}
				}
				cout << "\n";
			}
			cout << "\n";
		}
		void readIn(){
			int i, j;
			for (i=0; i<9; i++){
				for (j=0; j<9; j++){
					cin >> map[i][j];
				}
			}
		}
		void solve(){
			//判斷初始數獨是否正確
int i, j, t, u, v, kanou[9][9][9]={0}, kanouUse[9][9][9]={0}, kanouSuu[9][9]={0}, kanouSuuUse[9][9]={0}, seikai=0;
for (i=0; i<9; i++){
	for (j=0; j<9; j++){
		if (map[i][j]!=0){
			for (t=0; t<9; t++){ //檢查行 
				if (map[t][j]==map[i][j] && i!=t){
					cout << "0\n";
					return;
				}
			}
			for (t=0; t<9; t++){ //檢查列 
				if (map[i][t]==map[i][j] && j!=t){
					cout << "0\n";
					return;
				}
			}
		}
	} 
}

//檢查九宮格
int nine[9][9]={0}, a=0, b=0;
for (i=0; i<9; i++){
	for (j=0; j<3; j++){
		for (t=0; t<3; t++){
			if (map[j+3*a][t+3*b]!=0){
			nine[i][map[j+3*a][t+3*b]-1]++;
			}
		}
	}
	b++;
	if (b==3){
		a++;
		b=0;
	}
}
for (i=0; i<9; i++){
	for (j=0; j<9; j++){
		if (nine[i][j]>1){
			cout << "0\n";
			return;
		}
	}
}


//初始化可能性 
for (i=0; i<9; i++){
	for (j=0; j<9; j++){
		if (map[i][j]==0){
			for (t=0; t<9; t++){
				kanou[i][j][t] = 1;
				kanouUse[i][j][t] = 1;
				kanouSuu[i][j] = 9;
				kanouSuuUse[i][j] = 9;
			}
		}
	}
}
for (i=0; i<9; i++){
	for (j=0; j<9; j++){
		if (map[i][j]==0){ //檢查可能性(列出所有可能) 
			for (t=0; t<9; t++){ //檢查行 
				if (map[t][j]!=0){
					kanou[i][j][map[t][j]-1] = 0;
					kanouUse[i][j][map[t][j]-1] = 0;
					kanouSuu[i][j]--;
					kanouSuuUse[i][j]--;
				}
			}
			for (t=0; t<9; t++){ //檢查列 
				if (map[i][t]!=0){
					kanou[i][j][map[i][t]-1] = 0;
					kanouUse[i][j][map[i][t]-1] = 0;
					kanouSuu[i][j]--;
					kanouSuuUse[i][j]--;
				}
			}
			for (t=0; t<3; t++){ //檢查九宮格 
				for (u=0; u<3; u++){
					if (map[i-(i%3)+t][j-(j%3)+u]!=0){
						kanou[i][j][map[i-(i%3)+t][j-(j%3)+u]-1] = 0;
						kanouUse[i][j][map[i-(i%3)+t][j-(j%3)+u]-1] = 0;
						kanouSuu[i][j]--;
						kanouSuuUse[i][j]--;
					}
				}
			}
		}
	}
}

int sippai[9][9]={0}, w=0, wr1=0, wr2=0;
while (seikai<2){
	head1:
	for (i=0; i<9; i++){
		for (j=0; j<9; j++){
			head2:
			if (map[i][j]==0){ //若有空格則重新觀察可能 
				for (t=0; t<9; t++){
					if (map[t][j]!=0){ //行 
						kanouUse[i][j][map[t][j]-1] = 0;
						kanouSuuUse[i][j]--;
					}
				}
				for (t=0; t<9; t++){ //列 
					if (map[i][t]!=0){
						kanouUse[i][j][map[i][t]-1] = 0;
						kanouSuuUse[i][j]--;
					}
				}
				for (t=0; t<3; t++){ //九宮格 
					for (u=0; u<3; u++){
						if (map[i-(i%3)+t][j-(j%3)+u]!=0){
							kanouUse[i][j][map[i-(i%3)+t][j-(j%3)+u]-1] = 0;
							kanouSuuUse[i][j]--;
						}
					}
				}
				if (kanouSuuUse==0){
					sippai[i][j]++;
					for (t=0; t<9; t++){
						for (u=0; u<9; u++){
							if (kanouSuu[t][u]==sippai[t][u] && kanouSuu[t][u]!=0){
								wr1++;
							}
							if (kanouSuu[t][u]!=0){
								wr2++;
							}
						}
					}
					if (wr1==wr2){
						cout << "0\n";
						return;
					}
					if (sippai[i][j]==kanouSuu[i][j] && kanouSuu[i][j]!=0){
						for (t=i; t>=0; t--){
							for (u=8; u>=0; u--){
								if (t<=i && u<j){
									if(kanouSuu[t][u]!=0){
										sippai[t][u]++; 
									}
								}
							}
						}
						for (t=i; t<9; t++){
							for (u=j; u<9; u++){
								sippai[t][u] = 0;
							}
						}
						goto head1;
					}
					for (t=0; t<9; t++){
						for (u=0; u<9; u++){
							for (v=0; v<9; v++){
								kanouUse[t][u][v] = kanou[t][u][v];
								kanouSuuUse[t][u] = kanouSuu[t][u];
							}
						}
					}
					goto head2;
				}
				w = sippai[i][j];
				for (t=0; t<9; t++){
					if (kanou[i][j][t]!=0 && w==0){
						map[i][j] = t+1;
						break;
					}else {
						w--;
					}
				}
			}
		}
	}
	for (i=0; i<9; i++){
		for (j=0; j<9; j++){
			if (map[i][j]==0){
				goto head1;
			}else {
				seikai++;
				sippai[i][j]++;
			}
		}
	}
}
if (seikai==1){
	cout << "1\n";
	for (i=0; i<9; i++){
		for (j=0; j<9; j++){
			cout << map[i][j];
			if (j!=8){
				cout << " ";
			}
		}
		cout << "\n";
	}
}else {
	cout << "2\n";
	return;
}
		}
		void changeNum(int a, int b){
			int i, j;
			for (i=0; i<9; i++){
				for (j=0; j<9; j++){
					if (map[i][j] == a){
						map[i][j] = b;
					}else if (map[i][j] == b){
						map[i][j] = a;
					}else {
					}
				}
			}
		}
		void changeRow(int a, int b){
			int temp;
			int i, j;
			for (i=0; i<3; i++){
				for (j=0; j<9; j++){
					temp = map[a*3+i][j];
					map[a*3+i][j] = map[b*3+i][j];
					map[b*3+i][j] = temp;
				}
			}
		}
		void changeCol(int a, int b){
			int temp;
			int i, j;
			for (i=0; i<3; i++){
				for (j=0; j<9; j++){
					temp = map[j][a*3+i];
					map[j][a*3+i] = map[j][b*3+i];
					map[j][b*3+i] = temp;
				}
			}
		}
		void rotate(int n){
			int time = n%4;
			int temp[9][9], r, i, j;
			for (r=0; r<time; r++){
				for (i=0; i<9; i++){
					for (j=0; j<9; j++){
						temp[i][j] = map[i][j];
					}
				}
				for (i=8; i>=0; i--){
					for (j=0; j<9; j++){
						map[j][i] = temp[8-i][j];
					}
				}
			}
		}
		void flip(int n){
			int temp, i, j;
			if (n==0){
				for (i=0; i<9; i++){
					for (j=0; j<4; j++){
						temp = map[i][j];
						map[i][j] = map[i][8-j];
						map[i][8-j] = temp;
					}
				}
			}else{
				for (i=0; i<4; i++){
					for (j=0; j<9; j++){
						temp = map[i][j];
						map[i][j] = map[8-i][j];
						map[8-i][j] = temp;
					}
				}
			}
		}
		void transform(){
			readIn();
			change();
			print();
		}
		void change(){
			srand(time(NULL));
			changeNum(rand()%9+1, rand()%9+1);
			changeCol(rand()%3, rand()%3);
			changeRow(rand()%3, rand()%3);
			rotate(rand()%30);
			flip(0);
			flip(1);
		}
		void print(){
			int i, j;
			for (i=0; i<9; i++){
				for (j=0; j<9; j++){
					cout << map[i][j];
					if (j!=8){
						cout << " ";
					}
				}
				cout << "\n";
			}
			cout << "\n";
		}
	private:
		int map[9][9];
}; 
