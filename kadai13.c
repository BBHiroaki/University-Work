#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//同じ順位の場合順位表記を削除

#define RANKING_SIZE 10 //ランキングの数の設定
#define RANGE 100 //答えの幅の設定
#define MAX_TURNS 3 //ターン数の設定
#define MAX_NAME 256 //名前の字数設定
#define RANKING_FILE "ranking.dat"

struct ranking_data_t {
  char name[MAX_NAME];
  double score;
};

void save_ranking(struct ranking_data_t ranking[]){//ok
  FILE *fp;
  fp=fopen(RANKING_FILE,"wb");
  fwrite(ranking,sizeof(struct ranking_data_t),RANKING_SIZE,fp);
  fclose(fp);
}

void load_ranking(struct ranking_data_t ranking[]){//ok
  FILE *fp;
  fp=fopen(RANKING_FILE,"rb");
  fread(ranking,sizeof(struct ranking_data_t),RANKING_SIZE,fp);
  fclose(fp);
}

int name_checker(char name[MAX_NAME]){//ok
	for(int i=0;name[i]!='\0';i++){
		if(!(name[i] == 46 || (name[i]>=48 && name[i]<=57) || (name[i]>=65 && name[i]<=90) || (name[i]>=97 && name[i]<=122))){
			return 0;
		}
	}
	return 1;
}

void name_mover(char copy_name[MAX_NAME],char replaced_name[MAX_NAME]){//名前の置き換え
	int i=0;
  for(;!(copy_name[i] =='\0' );i++){
    replaced_name[i]=copy_name[i];
  }
	replaced_name[i]='\0';
}

void print_ranking(struct ranking_data_t ranking[]){
	printf("Rank      Score     name\n");
    for(int i=0;i<RANKING_SIZE;i++){
			if(i!=0 && ranking[i].score==ranking[i-1].score){
				printf("   ・・・%f  %s\n",ranking[i].score,ranking[i].name);
      }else{
        printf("%-3d・・・%f  %s\n",i+1,ranking[i].score,ranking[i].name);
      }
    }

}

int get_rank(struct ranking_data_t ranking[], double score){
	for(int i=0;i<RANKING_SIZE;i++){
		if(score <= ranking[i].score){return i+1;}
	}
	return -1;

}

void update_ranking(struct ranking_data_t ranking[], double score,char pre_name[MAX_NAME]){
  int new_rank = get_rank(ranking, score) - 1;

	if(new_rank < 0 || new_rank >= RANKING_SIZE){
		return;
	}

	for(int i=RANKING_SIZE-1;i>new_rank ;i--){
    ranking[i]=ranking[i-1];
  }
  ranking[new_rank].score = score;
  name_mover(pre_name,ranking[new_rank].name);
}

int main (void)
{
  struct ranking_data_t ranking[RANKING_SIZE];//ok

  load_ranking(ranking);

	srandom(time(NULL));//ok

	if(ranking[0].score<1){//ランキングファイルが存在しないor壊れている場合の初期化
		ranking[0].score=1.2;//rankの数値初期値設定//ok
	  for(int i=1;i<RANKING_SIZE;i++){
		  ranking[i].score=ranking[i-1].score+0.2;
	  }

	  for(int i=0;i<RANKING_SIZE;i++){//名前の初期化
		  int j=0;
		  for(j=0;j<5;j++){
			  int make_random_name= (unsigned char)(random()%(26)+97);
			  ranking[i].name[j]=make_random_name;
		  }
		  ranking[i].name[j]= '\0';
	  }

    save_ranking(ranking);
  }



	int loop=1;//繰り返しの可否
	while(loop==1){
		int turn=0;
		int answer_count=0;//答えの回数
		double score[MAX_TURNS];//各回のスコア
    for(int i=0;i<MAX_TURNS;i++){
      score[i]=0;
    } 
		print_ranking(ranking);

    /********************************************
		 * ターンごとの処理
		*********************************************/
		for(turn=1;turn<=MAX_TURNS;turn+=1){   
		  int correct_answer= (random()%(RANGE)+1);
		  int answer=0;//予想値
			printf("ターン%dです。\n",turn);
			printf("答えは%dです。\n",correct_answer);
			for(answer_count=1;;answer_count+=1){
				printf("第%d回予想→",answer_count);
		    scanf("%d",&answer);
		    if(answer==correct_answer){
			    printf("正解！！やった%d回の予想で正解しました。\n",answer_count);
          for(int i=1;i<=MAX_TURNS;i++){
            if(turn==i){score[i-1]=answer_count;}
          }
			    break;
		    }else{
			    if((correct_answer-10) <= answer && answer <= (correct_answer+10)){
				    if((correct_answer-5) <= answer && answer <= (correct_answer+5)){
					    printf("おしい！\n");
				    }else{
					    printf("もうちょいかな\n");
				    } 
			    }else{
				    printf("ぜんぜんだめ\n");
			    }
		    }
			}
		}
    double last_score=0;
    for(int i=0;i<MAX_TURNS;i++){
      last_score+=score[i];
    }
    int total_answer_count=last_score;
		last_score/=MAX_TURNS;
	  printf("%dターンで%d回の予想をしました。スコア(平均予想回数)は%fです。\n",MAX_TURNS,total_answer_count,last_score);
		//スコア別の褒め
	  if(last_score<=2){printf("すごい！！\n");}
	  if(last_score>2 && last_score<=3){printf("やるね！！\n");}
	  if(last_score>3 && last_score<=4){printf("平凡～\n");}

		//順位に関してのコメント
    char pre_name[MAX_NAME];//名前入力用
		int pre_rank=get_rank(ranking, last_score);//現在の順位取得
		//名前の入力
	  if((pre_rank)!=-1 && (pre_rank)<=RANKING_SIZE){
			printf("おめでとう%d位です。\n",pre_rank);
			do{
				printf("名前をおしえて(ローマ字、数字、ピリオドのみ可)");
        scanf("%s",pre_name);
			}while(name_checker(pre_name)==0);
		}

	  if(pre_rank==-1){printf("残念！ランキング外でした。\n");}

		//ランキング更新及び表示
	  update_ranking(ranking, last_score,pre_name);

	  printf("現在最新のランキングは\n");
	  print_ranking(ranking );
    save_ranking(ranking);
	  printf("ゲームを続けますか？(Y:1/N:0)>>>>");
	  scanf("%d",&loop);
  }
}