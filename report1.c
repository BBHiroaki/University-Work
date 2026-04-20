#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

struct timeval tv_start;
struct timeval tv_finish;

typedef struct _JRWestcheck{
	int year;//年
	int month;//月

	float YOY;//取扱収入対前期比
	float Short_Trip;//取扱収入対前期比内訳、定期外近距離
	float ML_Trip;//取扱収入対前期比内訳、定期外中長距離
	float Commuter;//取扱収入対前期比内訳、定期券

    int sum;//山陽新幹線対前期比利用状況
	int Nozomi;//山陽新幹線のぞみ、さくら号対前期比利用状況
	int Hikari;//山陽新幹線ひかり、さくら号対前期比利用状況
	int Kodama;//山陽新幹線こだま号対前期比利用状況

    struct _JRWestcheck *prev;//前のノードを指すポインタ
	struct _JRWestcheck *next;//次のノードを指すポインタ
}JRWestCheck;

typedef struct _node{
      JRWestCheck *data;
      struct _node *next;
}Node;

JRWestCheck *print(JRWestCheck *head){//一覧表示する関数(全て表示)
	JRWestCheck *current=head->next;
	do{
		printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,current->year,current->month,current->YOY,current->Short_Trip,current->ML_Trip,current->Commuter,current->sum,current->Nozomi,current->Hikari,current->Kodama);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print_reverse(JRWestCheck *tail){//一覧表示する関数(全て表示)
	JRWestCheck *current = tail;
	do{
		printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,current->year,current->month,current->YOY,current->Short_Trip,current->ML_Trip,current->Commuter,current->sum,current->Nozomi,current->Hikari,current->Kodama);
    	current = current->prev;
	}while(current != tail);
    return NULL;
}

JRWestCheck *print1(JRWestCheck *head){//一覧表示する関数(取扱運輸収入のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月取扱収入前期比%5.1f。\n"
    	,current->year,current->month,current->YOY);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print2(JRWestCheck *head){//一覧表示する関数(定期外短距離利用客収入のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月の定期外短距離利用客収入対前期比は%5.1f\n",current->year,current->month,current->Short_Trip);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print3(JRWestCheck *head){//一覧表示する関数(定期外中長距離利用客収入のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月の定期外中長距離利用客収入対前期比は%5.1f\n",current->year,current->month,current->ML_Trip);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print4(JRWestCheck *head){//一覧表示する関数(定期券利用客収入のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月の定期券利用客収入対前期比は%5.1f\n",current->year,current->month,current->Commuter);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print5(JRWestCheck *head){//一覧表示する関数(山陽新幹線利用状況のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月対前期比山陽新幹線利用状況%3d。\n",current->year,current->month,current->sum);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print6(JRWestCheck *head){//一覧表示する関数(のぞみ号のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月対前期比山陽新幹線のぞみ号利用状況%3d\n",current->year,current->month,current->Nozomi);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print7(JRWestCheck *head){//一覧表示する関数(こだま号のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月対前期比山陽新幹線ひかり号利用状況：%3d\n",current->year,current->month,current->Hikari);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *print8(JRWestCheck *head){//一覧表示する関数(こだま号のみ表示)
	JRWestCheck *current=head->next;
	do{
        printf("%d年%2d月対前期比山陽新幹線こだま号利用状況：%3d\n",current->year,current->month,current->Kodama);
    	current = current->next;
	}while(current != head);
    return NULL;
}

JRWestCheck *SearchByYear(JRWestCheck *head,int year){//年で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
	while(search != head){
		if(search->year == year){
			printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,search->year,search->month,search->YOY,search->Short_Trip,search->ML_Trip,search->Commuter,search->sum,search->Nozomi,search->Hikari,search->Kodama);
			return search;
		}
		search =search->next;
	}
    return NULL;
}

JRWestCheck *SearchByMonth(JRWestCheck *head,int month){//月で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->month == month){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByYearAndMonth(JRWestCheck *head,int year,int month){//年月で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->month == month && search->year == year){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByYOY(JRWestCheck *head,int minYOY, int maxYOY){//取扱収入対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->YOY >= minYOY && search->YOY <=maxYOY){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByShort_Trip(JRWestCheck *head,int minShort_Trip, int maxShort_Trip){//短距離利用客取扱収入対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->Short_Trip >= minShort_Trip && search->Short_Trip <=maxShort_Trip){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByML_Trip(JRWestCheck *head,int minML_Trip, int maxML_Trip){//中長距離利用客取扱収入対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->ML_Trip >= minML_Trip && search->ML_Trip <=maxML_Trip){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByCommuter(JRWestCheck *head,int minCommuter, int maxCommuter){//定期券利用客取扱収入対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->Commuter >= minCommuter && search->Commuter <=maxCommuter){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchBySum(JRWestCheck *head,int minSum, int maxSum){//山陽新幹線利用状況対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->sum >= minSum && search->sum <=maxSum){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByNozomi(JRWestCheck *head,int minNozomi, int maxNozomi){//山陽新幹線のぞみ号利用状況対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->Nozomi >= minNozomi && search->Nozomi <=maxNozomi){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByHikari(JRWestCheck *head,int minHikari, int maxHikari){//山陽新幹線ひかり号利用状況対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->Hikari >= minHikari && search->Hikari <=maxHikari){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

JRWestCheck *SearchByKodama(JRWestCheck *head,int minKodama, int maxKodama){//山陽新幹線こだま号利用状況対前期比で検索する関数
	JRWestCheck *search=head->next;//現在チェック中のノード
    while(search != head){
        if(search->Kodama >= minKodama && search->Kodama <=maxKodama){
        	return search;
        }
        search = search->next;
    }
    return NULL;
}

void jump_next(JRWestCheck **a){
	*a = (*a)->next;
}

void jump_prev(JRWestCheck **a){
	*a = (*a)->prev;
}

void swap_data(JRWestCheck *a, JRWestCheck *b) {//データ交換
    JRWestCheck temp = *a;//aのデータをtempに避難

    // データのみをコピー
    a->year = b->year;
    a->month = b->month;
    a->YOY = b->YOY;
    a->Short_Trip = b->Short_Trip;
    a->ML_Trip = b->ML_Trip;
    a->Commuter = b->Commuter;
    a->sum = b->sum;
    a->Nozomi = b->Nozomi;
    a->Hikari = b->Hikari;
    a->Kodama = b->Kodama;

    b->year = temp.year;
    b->month = temp.month;
    b->YOY = temp.YOY;
    b->Short_Trip = temp.Short_Trip;
    b->ML_Trip = temp.ML_Trip;
    b->Commuter = temp.Commuter;
    b->sum = temp.sum;
    b->Nozomi = temp.Nozomi;
    b->Hikari = temp.Hikari;
    b->Kodama = temp.Kodama;
}

void bubble_YOY(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->YOY > b->YOY) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_Short_Trip(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->Short_Trip > b->Short_Trip) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_ML_Trip(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->ML_Trip > b->ML_Trip) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_Commuter(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->Commuter > b->Commuter) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_sum(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->sum > b->sum) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_Nozomi(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->Nozomi > b->Nozomi) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_Hikari(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->Hikari > b->Hikari) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void bubble_Kodama(JRWestCheck *head, int n) {
    for (int i = 0; i < n - 1; i++) {
        JRWestCheck *a = head->next;
        for (int j = 0; j < n - i - 1; j++) {
            JRWestCheck *b = a->next;
            if (a->Kodama > b->Kodama) {
                swap_data(a, b);
            }
            a = a->next;
        }
    }
}

void selection_YOY(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->YOY < min->YOY){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_Short_Trip (JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->Short_Trip  < min->Short_Trip){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_ML_Trip(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->ML_Trip < min->ML_Trip){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_Commuter(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->Commuter < min->Commuter){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_sum(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->sum < min->sum){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_Nozomi(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->Nozomi < min->Nozomi){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_Hikari(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->Hikari < min->Hikari){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void selection_Kodama(JRWestCheck *head,int n){
	JRWestCheck *a;
	JRWestCheck *temp;
	a = head;
	for(int i = 0; i < n-1 ; i++){		
		JRWestCheck *min = a;//仮の最小値設定
		temp = a->next;//a[ｊ]またはa[i+1]を表現
		for(int j = i+1; j < n ;j++){
			if(temp->Kodama < min->Kodama){min = temp;}//最小値捜索、更新
			temp = temp->next;
		} 
	    swap_data(min,a);//交換
	    a = a->next;
	}
}

void inseration_YOY(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->YOY > current->YOY) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_Short_Trip(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->Short_Trip > current->Short_Trip) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_ML_Trip(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->ML_Trip > current->ML_Trip) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_Commuter(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->Commuter > current->Commuter) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_sum(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->sum > current->sum) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_Nozomi(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->Nozomi > current->Nozomi) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_Hikari(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->Hikari > current->Hikari) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void inseration_Kodama(JRWestCheck *head, int n){
    JRWestCheck *current = head->next->next;  // 2番目のノードから開始
    while (current != head) {
        JRWestCheck *pos = current->prev;
        JRWestCheck *next_current = current->next;  // currentが移動する前に次を保存

        // 挿入位置を探す
        while (pos != head && pos->Kodama > current->Kodama) {
            pos = pos->prev;
        }

        // すでに正しい位置なら何もしない
        if (pos->next != current) {
            // currentノードをリストから外す
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // 挿入位置の直後にcurrentを挿入
            current->next = pos->next;
            current->prev = pos;
            pos->next->prev = current;
            pos->next = current;
        }

        current = next_current;
    }
}

void merge_YOY(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_YOY(head, n/2);
    merge_YOY(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->YOY <= b->YOY) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_Short_Trip(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_Short_Trip(head, n/2);
    merge_Short_Trip(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->Short_Trip <= b->Short_Trip) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_ML_Trip(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_ML_Trip(head, n/2);
    merge_ML_Trip(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->ML_Trip <= b->ML_Trip) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_Commuter(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_Commuter(head, n/2);
    merge_Commuter(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->Commuter <= b->Commuter) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_sum(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_sum(head, n/2);
    merge_sum(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->sum <= b->sum) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_Nozomi(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_Nozomi(head, n/2);
    merge_Nozomi(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->Nozomi <= b->Nozomi) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_Hikari(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_Hikari(head, n/2);
    merge_Hikari(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->Hikari <= b->Hikari) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}

void merge_Kodama(JRWestCheck *head, int n) {
    if (n <= 1) return;

    JRWestCheck *mid_node = head;
    for (int i = 0; i < n/2; i++) {
        mid_node = mid_node->next;
    }

    // 再帰呼び出し
    merge_Kodama(head, n/2);
    merge_Kodama(mid_node, n - n/2);

    // 両方のソート済みリストをマージして、head から順に上書き
    JRWestCheck *a = head;
    JRWestCheck *b = mid_node;

    JRWestCheck *buffer = (JRWestCheck *)malloc(sizeof(JRWestCheck) * n);


    int ia = 0, ib = 0, ic = 0;
    int na = n/2;
    int nb = n - n/2;

    while (ia < na && ib < nb) {
        if (a->Kodama <= b->Kodama) {
            buffer[ic++] = *a;
            a = a->next;
            ia++;
        } else {
            buffer[ic++] = *b;
            b = b->next;
            ib++;
        }
    }

    while (ia < na) {
        buffer[ic++] = *a;
        a = a->next;
        ia++;
    }

    while (ib < nb) {
        buffer[ic++] = *b;
        b = b->next;
        ib++;
    }

    // ソート結果を head から順に上書き
    JRWestCheck *cur = head;
    for (int i = 0; i < n; i++) {
        cur->year = buffer[i].year;
        cur->month = buffer[i].month;
        cur->YOY = buffer[i].YOY;
        cur->Short_Trip = buffer[i].Short_Trip;
        cur->ML_Trip = buffer[i].ML_Trip;
        cur->Commuter = buffer[i].Commuter;
        cur->sum = buffer[i].sum;
        cur->Nozomi = buffer[i].Nozomi;
        cur->Hikari = buffer[i].Hikari;
        cur->Kodama = buffer[i].Kodama;
        cur = cur->next;
    }

    free(buffer);
}


int count_nodes(JRWestCheck *head) {
    int count = 0;
    JRWestCheck *cur = head->next;
    while (cur != head) {
        count++;
        cur = cur->next;
    }
    return count;
}



int main(){

	JRWestCheck *dummy = malloc(1*sizeof(JRWestCheck));
	JRWestCheck *head = dummy;
	JRWestCheck *tail = dummy;
	dummy->prev = dummy->next=dummy;

	JRWestCheck *x = malloc(1*sizeof(JRWestCheck));
	x->year = 2025;
	x->month = 3;

	x->YOY = 104.6;
	x->Short_Trip = 104.3;
	x->ML_Trip = 103.8;
	x->Commuter = 107.6;

    x->sum = 103;
	x->Nozomi = 104;
	x->Hikari = 101;
	x->Kodama = 79;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2025;
	x->month = 2;

	x->YOY = 104.4;
	x->Short_Trip = 103.8;
	x->ML_Trip = 104.8;
	x->Commuter = 103.3;

    x->sum = 105;
	x->Nozomi = 106;
	x->Hikari = 104;
	x->Kodama = 83;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2025;
	x->month = 1;

	x->YOY = 107.3;
	x->Short_Trip = 106.2;
	x->ML_Trip = 109.3;
	x->Commuter = 101.8;

    x->sum = 104;
	x->Nozomi = 105;
	x->Hikari = 104;
	x->Kodama = 89;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 12;

	x->YOY = 105.9;
	x->Short_Trip = 107.0;
	x->ML_Trip = 106.3;
	x->Commuter = 101.9;

    x->sum = 107;
	x->Nozomi = 110;
	x->Hikari = 101;
	x->Kodama = 89;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 11;

	x->YOY = 105.9;
	x->Short_Trip = 105.1;
	x->ML_Trip = 107.7;
	x->Commuter = 98.7;

    x->sum = 105;
	x->Nozomi = 108;
	x->Hikari = 96;
	x->Kodama = 87;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 10;

	x->YOY = 104.3;
	x->Short_Trip = 103.5;
	x->ML_Trip = 107.0;
	x->Commuter = 97.5;

    x->sum = 101;
	x->Nozomi = 105;
	x->Hikari = 91;
	x->Kodama = 84;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 9;

	x->YOY = 107.1;
	x->Short_Trip = 105.0;
	x->ML_Trip = 107.9;
	x->Commuter = 106.9;

    x->sum = 102;
	x->Nozomi = 106;
	x->Hikari = 93;
	x->Kodama = 85;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 8;

	x->YOY = 101.8;
	x->Short_Trip = 104.6;
	x->ML_Trip = 101.3;
	x->Commuter = 99.1;

    x->sum = 96;
	x->Nozomi = 97;
	x->Hikari = 94;
	x->Kodama = 88;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 7;

	x->YOY = 106.7;
	x->Short_Trip = 104.4;
	x->ML_Trip = 109.0;
	x->Commuter = 100.7;

    x->sum = 102;
	x->Nozomi = 105;
	x->Hikari = 95;
	x->Kodama = 92;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 6;

	x->YOY = 108.2;
	x->Short_Trip = 107.9;
	x->ML_Trip = 108.4;
	x->Commuter = 107.9;

    x->sum = 103;
	x->Nozomi = 106;
	x->Hikari = 95;
	x->Kodama = 92;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 5;

	x->YOY = 106.7;
	x->Short_Trip = 103.4;
	x->ML_Trip = 109.5;
	x->Commuter = 100.9;

    x->sum = 102;
	x->Nozomi = 104;
	x->Hikari = 97;
	x->Kodama = 96;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 4;

	x->YOY = 110.7;
	x->Short_Trip = 109.4;
	x->ML_Trip = 111.1;
	x->Commuter = 110.8;

    x->sum = 106;
	x->Nozomi = 109;
	x->Hikari = 97;
	x->Kodama = 99;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 3;

	x->YOY = 106.4;
	x->Short_Trip = 105.8;
	x->ML_Trip = 111.1;
	x->Commuter = 94.0;

    x->sum = 105;
	x->Nozomi = 106;
	x->Hikari = 99;
	x->Kodama = 111;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 2;

	x->YOY = 112.6;
	x->Short_Trip = 111.0;
	x->ML_Trip = 115.3;
	x->Commuter = 102.3;

    x->sum = 112;
	x->Nozomi = 113;
	x->Hikari = 108;
	x->Kodama = 124;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2024;
	x->month = 1;

	x->YOY = 114.0;
	x->Short_Trip = 115.1;
	x->ML_Trip = 116.0;
	x->Commuter = 106.4;

    x->sum = 113;
	x->Nozomi = 113;
	x->Hikari = 111;
	x->Kodama = 124;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 12;

	x->YOY = 114.9;
	x->Short_Trip = 114.7;
	x->ML_Trip = 117.7;
	x->Commuter = 102.6;

    x->sum = 111;
	x->Nozomi = 110;
	x->Hikari = 115;
	x->Kodama = 116;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
 	x->year = 2023;
	x->month = 11;

	x->YOY = 118.2;
	x->Short_Trip = 114.8;
	x->ML_Trip = 123.2;
	x->Commuter = 102.8;

    x->sum = 121;
	x->Nozomi = 120;
	x->Hikari = 126;
	x->Kodama = 130;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 10;

	x->YOY = 117.5;
	x->Short_Trip = 114.9;
	x->ML_Trip = 121.7;
	x->Commuter = 109.2;

    x->sum = 125;
	x->Nozomi = 121;
	x->Hikari = 137;
	x->Kodama = 140;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 9;

	x->YOY = 122.3;
	x->Short_Trip = 122.6;
	x->ML_Trip = 129.7;
	x->Commuter = 106.3;

    x->sum = 136;
	x->Nozomi = 132;
	x->Hikari = 150;
	x->Kodama = 152;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 8;

	x->YOY = 131.8;
	x->Short_Trip = 124.7;
	x->ML_Trip = 141.2;
	x->Commuter = 105.1;

    x->sum = 144;
	x->Nozomi = 141;
	x->Hikari = 160;
	x->Kodama = 150;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 7;

	x->YOY = 127.8;
	x->Short_Trip = 122.9;
	x->ML_Trip = 136.8;
	x->Commuter = 105.9;

    x->sum = 131;
	x->Nozomi = 127;
	x->Hikari = 149;
	x->Kodama = 139;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 6;

	x->YOY = 118.7;
	x->Short_Trip = 113.3;
	x->ML_Trip = 127.1;
	x->Commuter = 98.9;

    x->sum = 130;
	x->Nozomi = 126;
	x->Hikari = 145;
	x->Kodama = 138;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 5;

	x->YOY = 124.1;
	x->Short_Trip = 118.9;
	x->ML_Trip = 135.0;
	x->Commuter = 98.5;

    x->sum = 139;
	x->Nozomi = 135;
	x->Hikari = 156;
	x->Kodama = 154;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 4;

	x->YOY = 123.8;
	x->Short_Trip = 120.7;
	x->ML_Trip = 139.5;
	x->Commuter = 100.6;

    x->sum = 146;
	x->Nozomi = 138;
	x->Hikari = 173;
	x->Kodama = 160;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 3;

	x->YOY = 142.4;
	x->Short_Trip = 132.1;
	x->ML_Trip = 161.4;
	x->Commuter = 114.4;

    x->sum = 179;
	x->Nozomi = 177;
	x->Hikari = 189;
	x->Kodama = 176;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 2;

	x->YOY = 181.4;
	x->Short_Trip = 156.6;
	x->ML_Trip = 227.6;
	x->Commuter = 106.1;

    x->sum = 241;
	x->Nozomi = 245;
	x->Hikari = 236;
	x->Kodama = 199;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2023;
	x->month = 1;

	x->YOY = 140.0;
	x->Short_Trip = 125.7;
	x->ML_Trip = 165.3;
	x->Commuter = 103.5;

    x->sum = 146;
	x->Nozomi = 152;
	x->Hikari = 156;
	x->Kodama = 137;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 12;

	x->YOY = 112.1;
	x->Short_Trip = 109.0;
	x->ML_Trip = 116.5;
	x->Commuter = 99.6;

    x->sum = 115;
	x->Nozomi = 115;
	x->Hikari = 117;
	x->Kodama = 120;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 11;

	x->YOY = 117.3;
	x->Short_Trip = 113.0;
	x->ML_Trip = 125.6;
	x->Commuter = 96.6;

    x->sum = 130;
	x->Nozomi = 132;
	x->Hikari = 127;
	x->Kodama = 122;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 10;

	x->YOY = 135.6;
	x->Short_Trip = 131.0;
	x->ML_Trip = 153.8;
	x->Commuter = 107.6;

    x->sum = 160;
	x->Nozomi = 165;
	x->Hikari = 146;
	x->Kodama = 137;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 9;

	x->YOY = 156.1;
	x->Short_Trip = 139.2;
	x->ML_Trip = 216.2;
	x->Commuter = 104.4;

    x->sum = 219;
	x->Nozomi = 228;
	x->Hikari = 199;
	x->Kodama = 169;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 8;

	x->YOY = 161.2;
	x->Short_Trip = 142.6;
	x->ML_Trip = 197.4;
	x->Commuter = 105.5;

    x->sum = 194;
	x->Nozomi = 204;
	x->Hikari = 166;
	x->Kodama = 154;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 7;

	x->YOY = 133.7;
	x->Short_Trip = 118.8;
	x->ML_Trip = 154.6;
	x->Commuter = 105.7;

    x->sum = 151;
	x->Nozomi = 156;
	x->Hikari = 137;
	x->Kodama = 133;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 6;

	x->YOY = 157.6;
	x->Short_Trip = 146.7;
	x->ML_Trip = 200.1;
	x->Commuter = 99.5;

    x->sum = 212;
	x->Nozomi = 218;
	x->Hikari = 197;
	x->Kodama = 180;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 5;

	x->YOY = 193.0;
	x->Short_Trip = 189.2;
	x->ML_Trip = 258.9;
	x->Commuter = 112.0;

    x->sum = 283;
	x->Nozomi = 291;
	x->Hikari = 271;
	x->Kodama = 205;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 4;

	x->YOY = 144.7;
	x->Short_Trip = 137.4;
	x->ML_Trip = 183.0;
	x->Commuter = 111.1;

    x->sum = 170;
	x->Nozomi = 174;
	x->Hikari = 164;
	x->Kodama = 137;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 3;

	x->YOY = 112.4;
	x->Short_Trip = 108.5;
	x->ML_Trip = 123.7;
	x->Commuter = 98.2;

    x->sum = 120;
	x->Nozomi = 124;
	x->Hikari = 112;
	x->Kodama = 104;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 2;

	x->YOY = 110.1;
	x->Short_Trip = 104.0;
	x->ML_Trip = 120.4;
	x->Commuter = 97.9;

    x->sum = 115;
	x->Nozomi = 117;
	x->Hikari = 111;
	x->Kodama = 107;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2022;
	x->month = 1;

	x->YOY = 142.4;
	x->Short_Trip = 131.9;
	x->ML_Trip = 181.6;
	x->Commuter = 105.1;

    x->sum = 196;
	x->Nozomi = 201;
	x->Hikari = 186;
	x->Kodama = 163;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 12;

	x->YOY = 153.0;
	x->Short_Trip = 135.2;
	x->ML_Trip = 191.4;
	x->Commuter = 96.6;

    x->sum = 181;
	x->Nozomi = 184;
	x->Hikari = 173;
	x->Kodama = 161;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 11;

	x->YOY = 117.2;
	x->Short_Trip = 109.5;
	x->ML_Trip = 129.8;
	x->Commuter = 96.6;

    x->sum = 112;
	x->Nozomi = 112;
	x->Hikari = 114;
	x->Kodama = 106;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 10;

	x->YOY = 105.7;
	x->Short_Trip = 98.0;
	x->ML_Trip = 102.4;
	x->Commuter = 119.2;

    x->sum = 104;
	x->Nozomi = 103;
	x->Hikari = 108;
	x->Kodama = 100;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 9;

	x->YOY = 88.0;
	x->Short_Trip = 89.5;
	x->ML_Trip = 80.9;
	x->Commuter = 95.6;

    x->sum = 79;
	x->Nozomi = 78;
	x->Hikari = 82;
	x->Kodama = 77;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 8;

	x->YOY = 105.2;
	x->Short_Trip = 99.9;
	x->ML_Trip = 113.7;
	x->Commuter = 95.7;

    x->sum = 126;
	x->Nozomi = 127;
	x->Hikari = 123;
	x->Kodama = 116;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 7;

	x->YOY = 116.6;
	x->Short_Trip = 113.4;
	x->ML_Trip = 122.4;
	x->Commuter = 109.1;

    x->sum = 119;
	x->Nozomi = 121;
	x->Hikari = 111;
	x->Kodama = 112;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 6;

	x->YOY = 96.5;
	x->Short_Trip = 99.7;
	x->ML_Trip = 103.0;
	x->Commuter = 85.4;

    x->sum = 100;
	x->Nozomi = 101;
	x->Hikari = 97;
	x->Kodama = 96;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 5;

	x->YOY = 147.4;
	x->Short_Trip = 156.9;
	x->ML_Trip = 208.1;
	x->Commuter = 103.8;

    x->sum = 206;
	x->Nozomi = 243;
	x->Hikari = 134;
	x->Kodama = 163;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 4;

	x->YOY = 217.9;
	x->Short_Trip = 213.4;
	x->ML_Trip = 314.1;
	x->Commuter = 169.1;

    x->sum = 276;
	x->Nozomi = 290;
	x->Hikari = 246;
	x->Kodama = 216;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 3;

	x->YOY = 108.0;
	x->Short_Trip = 113.3;
	x->ML_Trip = 116.0;
	x->Commuter = 94.6;

    x->sum = 100;
	x->Nozomi = 103;
	x->Hikari = 93;
	x->Kodama = 86;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 2;

	x->YOY = 49.9;
	x->Short_Trip = 61.5;
	x->ML_Trip = 37.0;
	x->Commuter = 87.6;

    x->sum = 34;
	x->Nozomi = 33;
	x->Hikari = 34;
	x->Kodama = 35;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);
  
   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2021;
	x->month = 1;

	x->YOY = 41.1;
	x->Short_Trip = 51.9;
	x->ML_Trip = 26.2;
	x->Commuter = 81.1;

    x->sum = 27;
	x->Nozomi = 27;
	x->Hikari = 26;
	x->Kodama = 130;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 12;

	x->YOY = 48.6;
	x->Short_Trip = 59.4;
	x->ML_Trip = 35.7;
	x->Commuter = 100.4;

    x->sum = 40;
	x->Nozomi = 41;
	x->Hikari = 39;
	x->Kodama = 40;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 11;

	x->YOY = 59.9;
	x->Short_Trip = 71.0;
	x->ML_Trip = 48.1;
	x->Commuter = 98.9;

    x->sum = 54;
	x->Nozomi = 55;
	x->Hikari = 50;
	x->Kodama = 53;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 10;

	x->YOY = 68.6;
	x->Short_Trip = 74.9;
	x->ML_Trip = 54.4;
	x->Commuter = 123.6;

    x->sum = 47;
	x->Nozomi = 48;
	x->Hikari = 42;
	x->Kodama = 49;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 9;

	x->YOY = 48.7;
	x->Short_Trip = 62.8;
	x->ML_Trip = 38.8;
	x->Commuter = 59.0;

    x->sum = 39;
	x->Nozomi = 39;
	x->Hikari = 37;
	x->Kodama = 44;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 8;

	x->YOY = 40.8;
	x->Short_Trip = 53.9;
	x->ML_Trip = 28.1;
	x->Commuter = 87.2;

    x->sum = 25;
	x->Nozomi = 24;
	x->Hikari = 26;
	x->Kodama = 29;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 7;

	x->YOY = 45.4;
	x->Short_Trip = 59.9;
	x->ML_Trip = 33.8;
	x->Commuter = 75.6;

    x->sum = 38;
	x->Nozomi = 37;
	x->Hikari = 39;
	x->Kodama = 42;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 6;

	x->YOY = 50.3;
	x->Short_Trip = 57.6;
	x->ML_Trip = 33.7;
	x->Commuter = 113.5;

    x->sum = 32;
	x->Nozomi = 31;
	x->Hikari = 32;
	x->Kodama = 37;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 5;

	x->YOY = 26.1;
	x->Short_Trip = 28.0;
	x->ML_Trip = 12.4;
	x->Commuter = 79.5;

    x->sum = 11;
	x->Nozomi = 9;
	x->Hikari = 15;
	x->Kodama = 16;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);

   x = malloc(1*sizeof(JRWestCheck));
	x->year = 2020;
	x->month = 4;

	x->YOY = 21.7;
	x->Short_Trip = 26.6;
	x->ML_Trip = 10.1;
	x->Commuter = 45.8;

    x->sum = 12;
	x->Nozomi = 12;
	x->Hikari = 12;
	x->Kodama = 16;

	x->next = tail->next;
	x->prev = tail;

	tail->next->prev = x;
	tail->next = x;
    tail = tail->next;

    printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);
    putchar('\n');

//管理機能ここから
    int tugi=0;//今後の操作確定用
    do{
        int tugi2=0;//switch分岐二つ目用
        int tugi3=0;//switch分岐三つ目用
        int tugi4=0;//switch分岐４つめ用
        int searchyear = 0;
        int searchmonth = 0;
        int minYOY = 0;
        int maxYOY = 0;
        int minShort_Trip = 0;
        int maxShort_Trip = 0;
        int minML_Trip = 0;
        int maxML_Trip = 0;
        int minCommuter = 0;
        int maxCommuter = 0;
        int minSum = 0;
        int maxSum = 0;
        int minNozomi = 0;
        int maxNozomi = 0;
        int minHikari = 0;
        int maxHikari = 0;
        int minKodama = 0;
        int maxKodama = 0;


    	do{
    		printf("どんな操作をしますか？1：一覧表示、2：追加、3：削除、４：検索、5：一部データのみ表示、6：ソート、７：終了 ->");scanf("%d",&tugi);
    	}while(tugi<1 && tugi>6);//１から６の数字を入力するまでループ

    	switch(tugi){
    	  case 1:printf("一覧表示します。\n");//一覧表示
    	  	     print(head);
    	         break;

    	  case 2:printf("ノードを追加します。\n");//追加
    	  	     x = malloc(1*sizeof(JRWestCheck));
    	  	     printf("何年のデータですか？");scanf("%d",&x->year);
    	  	     printf("%d年のデータですね\n",x->year);
    	  	     printf("何月のデータですか？");scanf("%d",&x->month);
    	  	     printf("%d月のデータですね\n",x->month);
    	  	     printf("取扱収入前期比のデータを教えてください");scanf("%f",&x->YOY);
    	  	     printf("取扱収入前期比は%5.1fですね？\n",x->YOY);
    	  	     printf("前期比定期外短距離利用客のデータを教えてください");scanf("%f",&x->Short_Trip);
    	  	     printf("前期比定期外短距離利用客は%5.1fですね？\n",x->Short_Trip);
    	  	     printf("前期比定期券利用客のデータを教えてください");scanf("%f",&x->Commuter);
    	  	     printf("前期比定期券利用客は%5.1fですね？\n",x->Commuter);
    	  	     printf("対前期比山陽新幹線利用状況のデータを教えてください");scanf("%d",&x->sum);
    	  	     printf("対前期比山陽新幹線利用状況は%3dですね？\n",x->sum);
    	  	     printf("のぞみ号のデータを教えてください");scanf("%d",&x->Nozomi);
    	  	     printf("のぞみ号は%3dですね？\n",x->Nozomi);
    	  	     printf("ひかり号のデータを教えてください");scanf("%d",&x->Hikari);
    	  	     printf("ひかり号は%3dですね？\n",x->Hikari);
    	  	     printf("こだま号のデータを教えてください");scanf("%d",&x->Kodama);
    	  	     printf("こだま号は%3dですね？\n",x->Kodama);

    	  	     x->next = tail->next;
	             x->prev = tail;

	             tail->next->prev = x;
	             tail->next = x;
                 tail = tail->next;

                 printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	                ,tail->year,tail->month,tail->YOY,tail->Short_Trip,tail->ML_Trip,tail->Commuter,tail->sum,tail->Nozomi,tail->Hikari,tail->Kodama);
                 putchar('\n');

                 break;

                     
    	  case 3://削除
    	  	     printf("何を基準に削除しますか？１：年、２：月、３：年月、４：取扱収入前年比、５：山陽新幹線利用状況 ->");
    	         scanf("%d",&tugi2);
                 switch(tugi2){
                 case 1:puts("年を基準に削除します。");
                 	    printf("何年ですか？："); scanf("%d",&searchyear);
                 	    printf("%d年の以下のデータを削除します。\n",searchyear);
                 	    do{
                 	    	JRWestCheck *found = SearchByYear(head,searchyear);
                 	    	found->next->prev = found->prev;
                            found->prev->next = found->next;
                            free(found);
                 	    }while(SearchByYear(head,searchyear) !=NULL);
                 	    puts("削除後の一覧を表示します。");
                 	    print(head);
                 	    break;
                 case 2:puts("月を基準に削除します。");
                        printf("何月ですか？："); scanf("%d",&searchmonth);
                        printf("%d月の以下のデータを削除します。\n",searchyear);
                        do{
                        	JRWestCheck *found = SearchByMonth(head,searchmonth);
                 	    	found->next->prev = found->prev;
                            found->prev->next = found->next;
                            free(found);
                        }while(SearchByMonth(head,searchmonth) != NULL);
                        puts("削除後の一覧を表示します。");
                        print(head);
                 	    break;
                 case 3:puts("年月を基準に削除します。");
                        printf("何年ですか？："); scanf("%d",&searchyear);
                        printf("何月ですか？："); scanf("%d",&searchmonth);
                        printf("%d年%d月の以下のデータを削除します。\n",searchyear,searchmonth);
                        JRWestCheck *found = SearchByYearAndMonth(head,searchyear,searchmonth);
                 	    found->next->prev = found->prev;
                        found->prev->next = found->next;
                        free(found);
                        puts("削除後の一覧を表示します。");
                        print(head);
                 	    break;
                 case 4:puts("取扱収入対前期比を基準に削除します。");
                        printf("取扱収入対前期比のうち、どれを基準に削除しますか？１：全体、２：定期外短距離、３：定期外中長距離、４：定期利用 ->");scanf("%d",&tugi3);
                        switch(tugi3){
                           case 1:puts("取扱収入対前期比全体を基準に削除します。");
                           	      printf("削除する取扱収入対前期比全体の下限値を入力してください");scanf("%d",&minYOY);
                           	      printf("削除する取扱収入対前期比全体の上限値を入力してください");scanf("%d",&maxYOY);
                           	      printf("%dから%dまでの取扱収入対前期比全体の以下のデータを削除します\n",minYOY,maxYOY);
                           	      do{
                        	      JRWestCheck *found = SearchByYOY(head,minYOY,maxYOY);
                 	    	      found->next->prev = found->prev;
                                  found->prev->next = found->next;
                                  free(found);
                                  }while(SearchByYOY(head,minYOY,maxYOY) != NULL);
                                  puts("削除後の一覧を表示します。");
                                  print(head);
                                  break;
                           case 2:puts("定期外短距離利用客収入対前期比を基準に削除します。");
                          		  printf("削除する定期外短距離利用客収入対前期比の下限値を入力してください");scanf("%d",&minShort_Trip);
                           	      printf("削除する定期外短距離利用客収入対前期比の上限値を入力してください");scanf("%d",&maxShort_Trip);
                           	      printf("%dから%dまでの定期外短距離利用客収入対前期比の以下のデータを削除します\n",minShort_Trip,maxShort_Trip);
                           	      do{
                           	      JRWestCheck *found = SearchByShort_Trip(head,minShort_Trip,maxShort_Trip);
                 	    	      found->next->prev = found->prev;
                                  found->prev->next = found->next;
                                  free(found);
                           	      }while(SearchByShort_Trip(head,minShort_Trip,maxShort_Trip) != NULL);
                           	      puts("削除後の一覧を表示します。");
                                  print(head);
                                  break;
                           case 3:puts("定期外中長距離利用客利用客収入対前期比を基準に削除します。");
                                  printf("削除する定期外中長距離利用客収入対前期比の下限値を入力してください");scanf("%d",&minML_Trip);
                           	      printf("削除する定期外中長距離利用客収入対前期比の上限値を入力してください");scanf("%d",&maxML_Trip);
                           	      printf("%dから%dまでの定期外中長距離利用客収入対前期比の以下のデータを削除します\n",minML_Trip,maxML_Trip);
                           	      do{
                           	      JRWestCheck *found = SearchByML_Trip(head,minML_Trip,maxML_Trip);
                 	    	      found->next->prev = found->prev;
                                  found->prev->next = found->next;
                                  free(found);
                                  }while(SearchByML_Trip(head,minML_Trip,maxML_Trip) != NULL);
                                  puts("削除後の一覧を表示します。");
                                  print(head);
                                  break;
                           case 4:puts("定期券利用客利用客収入対前期比を基準に削除します。");
                                  printf("削除する定期券利用客収入対前期比の下限値を入力してください");scanf("%d",&minCommuter);
                           	      printf("削除する定期券利用客収入対前期比の上限値を入力してください");scanf("%d",&maxCommuter);
                           	      printf("%dから%dまでの定期券利用客収入対前期比の以下のデータを削除します\n",minCommuter,maxCommuter);
                           	      do{
                           	      JRWestCheck *found = SearchByCommuter(head,minCommuter,maxCommuter);
                 	    	      found->next->prev = found->prev;
                                  found->prev->next = found->next;
                                  free(found);
                                  }while(SearchByCommuter(head,minCommuter,maxCommuter) != NULL);
                                  puts("削除後の一覧を表示します。");
                                  print(head);
                                  break;
                        }
                 	    break;
                 case 5:puts("山陽新幹線利用状況対前期比を基準に削除します。");
                 	    printf("山陽新幹線利用状況対前期比のうち、どれを基準に削除しますか？１：全体、２：のぞみ号、３：ひかり号、４：こだま号 ->");scanf("%d",&tugi3);
                 	    switch(tugi3){
                 	      case 1:puts("山陽新幹線利用状況を基準に削除します。");
                                 printf("削除する山陽新幹線利用状況対前期比の下限値を入力してください");scanf("%d",&minSum);
                           	     printf("削除する山陽新幹線利用状況対前期比の上限値を入力してください");scanf("%d",&maxSum);
                           	     printf("%dから%dまでの山陽新幹線利用状況対前期比の以下のデータを削除します\n",minSum,maxSum);
                           	     do{
                           	     JRWestCheck *found = SearchBySum(head,minSum,maxSum);
                 	    	     found->next->prev = found->prev;
                                 found->prev->next = found->next;
                                 free(found);
                                 }while(SearchBySum(head,minSum,maxSum) != NULL);
                                 puts("削除後の一覧を表示します。");
                                 print(head);
                                 break;
                 	      case 2:puts("山陽新幹線のぞみ号利用状況対前期比を基準に削除します。");
                                 printf("削除する山陽新幹線のぞみ号利用状況対前期比の下限値を入力してください");scanf("%d",&minNozomi);
                           	     printf("削除する山陽新幹線のぞみ号利用状況対前期比の上限値を入力してください");scanf("%d",&maxNozomi);
                           	     printf("%dから%dまでの山陽新幹線のぞみ号利用状況対前期比の以下のデータを削除します\n",minNozomi,maxNozomi);
                           	     do{
                           	     JRWestCheck *found = SearchByNozomi(head,minNozomi,maxNozomi);
                 	    	     found->next->prev = found->prev;
                                 found->prev->next = found->next;
                                 free(found);
                                 }while(SearchByNozomi(head,minNozomi,maxNozomi) != NULL);
                                 puts("削除後の一覧を表示します。");
                                 print(head);
                                 break;
                 	      case 3:puts("山陽新幹線ひかり号利用状況対前期比を基準に削除します。");
                                 printf("削除する山陽新幹線ひかり号利用状況対前期比の下限値を入力してください");scanf("%d",&minHikari);
                           	     printf("削除する山陽新幹線ひかり号利用状況対前期比の上限値を入力してください");scanf("%d",&maxHikari);
                           	     printf("%dから%dまでの山陽新幹線ひかり号利用状況対前期比の以下のデータを削除します\n",minHikari,maxHikari);
                           	     do{
                           	     JRWestCheck *found = SearchByHikari(head,minHikari,maxHikari);
                 	    	     found->next->prev = found->prev;
                                 found->prev->next = found->next;
                                 free(found);
                                 }while(SearchByHikari(head,minHikari,maxHikari) != NULL);
                                 puts("削除後の一覧を表示します。");
                                 print(head);
                                 break;
                 	      case 4:puts("山陽新幹線こだま号利用状況対前期比を基準に削除します。");
                                 printf("削除する山陽新幹線こだま号利用状況対前期比の下限値を入力してください");scanf("%d",&minKodama);
                           	     printf("削除する山陽新幹線こだま号利用状況対前期比の上限値を入力してください");scanf("%d",&maxKodama);
                           	     printf("%dから%dまでの山陽新幹線こだま号利用状況対前期比の以下のデータを削除します\n",minKodama,maxKodama);
                           	     do{
                           	     JRWestCheck *found = SearchByKodama(head,minKodama,maxKodama);
                 	    	     found->next->prev = found->prev;
                                 found->prev->next = found->next;
                                 free(found);
                                 }while(SearchByKodama(head,minKodama,maxKodama) != NULL);
                                 puts("削除後の一覧を表示します。");
                                 print(head);
                                 break;
                 	    }
                 	    break;
                 }
                 
    	  	     break;

    	  case 4://検索
    	  		 puts("検索します。");
    	  		 printf("何を基準に検索しますか？１：年月、２：取扱運輸収入対前期比、３：定期外短距離利用客収入対前期比、４：定期外中長距離利用客収入対前期比、５：定期券利用客収入、６：対前期比山陽新幹線利用者数、７：対前期比山陽新幹線のぞみ号利用者数、８：対前期比山陽新幹線ひかり号利用者数、９：対前期比山陽新幹線こだま号利用者数->");
    	  		 scanf("%d",&tugi2);
    	  		 switch(tugi2){
    	  		 case 1:puts("「年月」を基準に検索します。(線形探索)");
    	               	printf("何年ですか？：");
    	               	scanf("%d",&searchyear);
    	               	printf("何月ですか？：");
    	               	scanf("%d",&searchmonth);
    	               	printf("%d年%d月のデータを表示します。\n",searchyear,searchmonth);
    	               	gettimeofday(&tv_start,NULL); //処理開始
    	                JRWestCheck *found = SearchByYearAndMonth(head,searchyear,searchmonth);
    	            	gettimeofday(&tv_finish,NULL);//処理終了
    	               	printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
    	                       ,found->year,found->month,found->YOY,found->Short_Trip,found->ML_Trip,found->Commuter,found->sum,found->Nozomi,found->Hikari,found->Kodama);
    	               	puts("発見したデータに対応する構造体のアドレスは以下の通り");
    	                printf("年：%p、月：%p、取扱収入前期比：%p。内訳、定期外短距離利用客：%p、中長距離利用客：%p、定期券利用客：%p。\n対前期比山陽新幹線利用状況%p。内訳、のぞみ号：%p、ひかり号：%p、こだま号：%p\n"
    	                      ,&found->year,&found->month,&found->YOY,&found->Short_Trip,&found->ML_Trip,&found->Commuter,&found->sum,&found->Nozomi,&found->Hikari,&found->Kodama);
    	               	printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
    	               	break;
    	  		 case 2:puts("「取扱運輸収入対前期比」を基準に検索します。(ハッシュ法)");
    	  		 	    Node *table[13];

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					JRWestCheck *temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->YOY*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					float key = 0;
      					Node *kekka = NULL;
      					printf("探す取扱収入前期比："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					int idx = (int)(key*10)%13;
      					kekka = table[idx];
      					int find = 0;
      					while(kekka != NULL){
            				if(kekka->data->YOY == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  				break;
    	  		 case 3:puts("「定期外短距離利用客収入対前期比」を基準に検索します。(ハッシュ法)");
      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

						temp = head->next;
      					while(temp != head){
          	    			idx = (int)(temp->Short_Trip*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す定期外短距離利用客："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->Short_Trip == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		        break;
    	  		 case 4:puts("「定期外中長距離利用客収入対前期比」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

						temp = head->next;
      					while(temp != head){
          	    			idx = (int)(temp->ML_Trip*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す定期外中長距離利用客収入対前期比："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->ML_Trip == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 case 5:puts("「定期券利用客収入」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->Commuter*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す定期券利用客収入："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->Commuter == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 case 6:puts("「対前期比山陽新幹線利用者数」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->sum*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す対前期比山陽新幹線利用者数："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->sum == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 case 7:puts("「対前期比山陽新幹線のぞみ号利用者数」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->Nozomi*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す対前期比山陽新幹線のぞみ号利用者数："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->Nozomi == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 case 8:puts("「対前期比山陽新幹線ひかり号利用者数」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->Hikari*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す対前期比山陽新幹線ひかり号利用者数："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->Hikari == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 case 9:puts("「対前期比山陽新幹線こだま号利用者数」を基準に検索します。(ハッシュ法)");

      					for(int i=0;i<13;i++){
      						table[i] = NULL;//とりあえずNULLを代入
      					}

      					temp = head->next;
      					while(temp != head){
          	    			int idx = (int)(temp->Kodama*10)%13;//ハッシュ法分類余り計算

            				Node *a = (Node*)malloc(sizeof(Node));
            				a->data = temp;//tempの中身をcurからもらう
            				a->next = table[idx];//tableに残っている古いものを新しいものの後ろにつける
            				table[idx] = a;//tableに新しい値を代入

            				temp = temp->next;//curの更新、次へ
      					}

      					key = 0;
      					kekka = NULL;
      					printf("探す対前期比山陽新幹線こだま号利用者数："); scanf("%f",&key);
      					printf("%.1fで探します\n",key);
      					gettimeofday(&tv_start,NULL); //処理開始

      					idx = (int)(key*10)%13;
      					kekka = table[idx];
      					find = 0;
      					while(kekka != NULL){
            				if(kekka->data->Kodama == key){
            					gettimeofday(&tv_finish,NULL);//処理終了
                  				printf("見つかりました！！\n");
                  				printf("%d年%2d月取扱収入前期比%5.1f。内訳、定期外短距離利用客：%5.1f、中長距離利用客：%5.1f、定期券利用客：%5.1f。\n対前期比山陽新幹線利用状況%3d。内訳、のぞみ号：%3d、ひかり号：%3d、こだま号：%3d\n"
      									,kekka->data->year,kekka->data->month,kekka->data->YOY,kekka->data->Short_Trip,kekka->data->ML_Trip,kekka->data->Commuter,kekka->data->sum,kekka->data->Nozomi,kekka->data->Hikari,kekka->data->Kodama);
                  				find =1;
                  				printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
                  				break;
            				}
            				kekka = kekka->next;
      					}
      					if(!find){
            				printf("何も発見で来ませんでした。\n");
     			 		}
    	  		 	    break;
    	  		 }
    	         break;

    	  case 5:puts("一部のデータのみを表示します。(年月日は必ず表示されます。)");//一部データのみ表示
    	         printf("表示したいデータを選んでください。\n１：取扱収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入\n５：対前期比山陽新幹線利用者数、６：のぞみ号対前期比利用客数、７：ひかり号対前期比利用客数、８：こだま号前期比利用客数 ->");
                 scanf("%d",&tugi2);
                 switch(tugi2){
                   case 1:puts("取扱運輸収入対前期比のみを表示します。");
                   	      print1(head);
                   	      break;
                   case 2:puts("定期外短距離利用客収入対前期比のみを表示します。");
                   	      print2(head);
                   	      break;
                   case 3:puts("定期外中長距離利用客収入対前期比のみを表示します。");
                   	      print3(head);
                   	      break;
                   case 4:puts("定期券利用客収入のみを表示します。");
                   	      print4(head);
                   	      break;
                   case 5:puts("対前期比山陽新幹線利用者数のみを表示します。");
                   	      print5(head);
                   	      break;
                   case 6:puts("対前期比山陽新幹線のぞみ号利用者数のみを表示します。");
                   	      print6(head);
                   	      break;
                   case 7:puts("対前期比山陽新幹線ひかり号利用者数のみを表示します。");
                   	      print7(head);
                   	      break;
                   case 8:puts("対前期比山陽新幹線こだま号利用者数のみを表示します。");
                   	      print8(head);
                   	      break;
                 }
                 break;
          case 6:puts("このデータをソートします");
          	     printf("並べ方の種類を指定してください１：バブルソート、２選択法、３：挿入法、４；マージソート->");scanf("%d",&tugi2);
          	     switch(tugi2){
          	     	case 1:puts("バブルソートでソートします。");
          	               printf("どのようにソートしますか？１：昇順、２：降順->");scanf("%d",&tugi3);
          	               switch(tugi3){
          	               		case 1:puts("昇順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、７：対前期比山陽新幹線ひかり号利用者数、８：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   bubble_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   bubble_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               					       gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               		case 2:puts("降順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、７：対前期比山陽新幹線ひかり号利用者数、８：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   bubble_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   bubble_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   bubble_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               						   print_reverse(head);
          	               						   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               }
          	               break;
          	     	case 2:puts("選択法でソートします。");
          	     	       printf("どのようにソートしますか？１：昇順、２：降順->");scanf("%d",&tugi3);
          	     	       switch(tugi3){
          	               		case 1:puts("昇順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   selection_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   selection_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               		case 2:puts("降順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   selection_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   selection_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   selection_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               }
          	     		   break;
          	     	case 3:puts("挿入法でソートします。");
          	     		   printf("どのようにソートしますか？１：昇順、２：降順->");scanf("%d",&tugi3);
          	     		   switch(tugi3){
          	               		case 1:puts("昇順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   inseration_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   inseration_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               		case 2:puts("降順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   inseration_YOY(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   inseration_Short_Trip(head,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_ML_Trip(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Commuter(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_sum(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Nozomi(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Hikari(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   inseration_Kodama(head,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
   												   print_reverse(head);
   												   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               }
          	     		   break;
          	     	case 4:puts("マージソートでソートします。");
          	     		   printf("どのようにソートしますか？１：昇順、２：降順->");scanf("%d",&tugi3);
          	     		   switch(tugi3){
          	               		case 1:puts("昇順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   merge_YOY(head->next,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   merge_Short_Trip(head->next,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_ML_Trip(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Commuter(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_sum(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Nozomi(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Hikari(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Kodama(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               		case 2:puts("降順でソートします。");
          	               			   printf("何を基準でソートしますか？\n１：取扱運輸収入対前期比、２：定期外短距離利用客収入対前期比、３：定期外中長距離利用客収入対前期比、４：定期券利用客収入、５：対前期比山陽新幹線利用者数、６：対前期比山陽新幹線のぞみ号利用者数、7：対前期比山陽新幹線ひかり号利用者数、8：対前期比山陽新幹線こだま号利用者数->");
          	               			   scanf("%d",&tugi4);
          	               			   switch(tugi4){
          	               			   		case 1:puts("取扱運輸収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   merge_YOY(head->next,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               			   			   break;
          	               			   		case 2:puts("定期外短距離利用客収入対前期比でソートします");
          	               			   			   gettimeofday(&tv_start,NULL); //処理開始
          	               			   			   merge_Short_Trip(head->next,count_nodes(head));
          	               			   			   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 3:puts("定期外中長距離利用客収入対前期比でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_ML_Trip(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 4:puts("定期券利用客収入でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Commuter(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 5:puts("対前期比山陽新幹線利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_sum(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 6:puts("対前期比山陽新幹線のぞみ号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Nozomi(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 7:puts("対前期比山陽新幹線ひかり号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Hikari(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               					case 8:puts("対前期比山陽新幹線こだま号利用者数でソートします");
          	               						   gettimeofday(&tv_start,NULL); //処理開始
          	               						   merge_Kodama(head->next,count_nodes(head));
          	               						   gettimeofday(&tv_finish,NULL);//処理終了
          	               			   			   print_reverse(head);
          	               			   			   printf("処理時間は%ld.%d秒です\n", tv_finish.tv_sec - tv_start.tv_sec, tv_finish.tv_usec - tv_start.tv_usec);
          	               						   break;
          	               			   }
          	               			   break;
          	               }
          	     		   break;
          	     }

          		break;

    	}


    }while(tugi!=7);//６の数字を入力するまでループ
    puts("プログラミングを終了します。");
}//検索検索アドレス表示も