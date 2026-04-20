#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
//パイプ機能を実装する

#define MAX_CMD_LINE 1024
#define MAX_ARGS 128

#define MAX_PATH_COUNT 256
#define MAX_PATH_LENGTH 256

char path[MAX_PATH_COUNT][MAX_PATH_LENGTH];

int bg_jobs[100];
int job_count = 0;
int fg_pid = -1;
extern char **environ;


int separate_argument(char cmdline[], char *exec_args[]) {
  int j = 0;
  char *p = cmdline;

  while (j<MAX_ARGS && *p != '\0') {//終わりじゃない時
    while (*p == ' ') p++; // 空白スキップし続ける
    if (*p == '\0') break;// 終了
    exec_args[j++] = p; // 単語開始
    while (*p != '\0' && *p != ' ') p++; // 次の空白まで進む
    if (*p != '\0') {//空白の時,単語が終わりでなければ
      *p = '\0';//単語を終わりとする
      p++;
    } 
  }
  exec_args[j] = NULL;
  return j;
}

void bg_signal_handler(int signum){
  int pid;
  int status;
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
    printf("finished PID=%d \n", pid);//本来禁止らしいが、課題の都合上表示
    // Remove the finished job from bg_jobs
    for (int i = 0; i < job_count; i++) {
      if (bg_jobs[i] == pid) {
        // Shift remaining jobs
        for (int j = i; j < job_count - 1; j++) {//並び替え
          bg_jobs[j] = bg_jobs[j + 1];//本来禁止だが、課題の都合上実装
        }
        job_count--;//総数を減らす
        break;
      }
    }
   }
}

void fg_signal_handler(int signum)
{
  if(fg_pid != -1) {
    kill(-fg_pid, SIGINT); // Forward SIGINT to the foreground process
  }
}

void find_path(char test1[]){//検索すべきpathを捜索する関数
  memset(path, 0, sizeof(path));
  char *get_path = getenv("PATH");
  int k=0;
  char test[MAX_PATH_LENGTH]={0};
  memset(test, 0, sizeof(test));
  int l=strlen(test1);
  for(;l>=0;l--){//
    if(test1[l]=='/'){
      for(int i=0;i<strlen(test1)-l;i++){
        test[i]=test1[l+1];
        l++;
      }
      break;
    }
  }
  if(test[0]=='\0'){//与えられたものに/が無い場合、そのまま利用
    for(int i=0;i<strlen(test1);i++){
      test[i]=test1[i];
    }
  }

  for(int i=0;i<MAX_PATH_COUNT;i++){
      for(int j=0;j<MAX_PATH_LENGTH-1 &&get_path[k]!=':' && get_path[k]!='\0';j++,k++){
        path[i][j]= get_path[k];
      }
      if(get_path[k]=='\0'){
        path[i][strlen(path[i])]='\0';
        break;
      }
      if(get_path[k]==':'){
        path[i][strlen(path[i])]='\0';
        k++; // ':'をスキップ
      }
  }

  for(int i=0;i<MAX_PATH_COUNT;i++){
    if(strlen(path[i])==0) break;
    int test_count = strlen(test);
    for(int j=0;j<MAX_PATH_LENGTH;j++){
      if(path[i][j]=='\0'){
        path[i][j]='/';
        for(int l=0;l<test_count;l++){
          path[i][j+1+l]=test[l];
        }
        path[i][j+1+test_count] = '\0';
        break;
      }
    }
  }
}




int main(int argc, char *argv[],char *envp[]){

  signal(SIGINT, fg_signal_handler); // Ignore SIGINT in parent
  signal(SIGCHLD, bg_signal_handler);

  char cmdline[MAX_CMD_LINE];
  char *exec_args[MAX_ARGS];
  char **current_args = exec_args; // ★これを追加：現在注目している引数リストの先頭を指す

  //while loop

  while(1){

    int status;
    int background=0;
    int pid,process_number;
    char path_get[256];
    int redirect_flag = 0;
    char filename[256];
    int pipe_flag=0;
    int pipe_separate_index=0;
    char **current_args = exec_args;//右側を実行

    //prompt
    printf(">>");

    //input
    fgets(cmdline,MAX_CMD_LINE,stdin);
    if(strlen(cmdline)>0 && cmdline[strlen(cmdline)-1]=='\n'){
      cmdline[strlen(cmdline)-1]='\0'; //remove \n
    }

    //separate
    int separate_count = separate_argument(cmdline,exec_args);
    if(exec_args[0]==NULL) continue;

    if (separate_count > 0 && strcmp(exec_args[separate_count - 1], "&") == 0) {
      background = 1;
      exec_args[separate_count - 1] = NULL; // "&" を引数から削除
      separate_count--;
    }

    //exit or quit check
    if(strcmp(exec_args[0],"exit")==0 || strcmp(exec_args[0],"quit")==0){
      printf("goodbye \n");
      exit(0);
    }

    if(strcmp(exec_args[0],"setenv")==0){
      if(exec_args[1]==NULL){//「setenv」のみが入力されると、全環境変数と、セットされた値を表示する。
        for(char **e = environ; *e; e++){
          printf("%s\n", *e);
        }
        continue;
      }else{//「setenv ABC xyz」と入力されると、環境変数ABCの値をxyzにする。
        if(exec_args[2]==NULL){
          printf("Usage: setenv <variable_name> <value>\n");
          continue;
        }
        setenv(exec_args[1],exec_args[2],1);//execargs[1]の内容をexec_args[2]でオーバーライト
        printf("setenv %s to %s\n", exec_args[1], exec_args[2]);
        continue;
      }
    }

    if(strcmp(exec_args[0],"unsetenv")==0){//「unsetenv ABC」と入力されると、環境変数ABCを削除する。
      if(exec_args[1]==NULL){
        printf("Usage: unsetenv <variable_name>\n");
        continue;
      }
      unsetenv(exec_args[1]);
      continue;
    }

    if(strcmp(exec_args[0],"jobs")==0){
      //show background jobs
      printf("background jobs:\n");
      for(int i=0;i<job_count;i++){
        printf("[%d] PID=%d\n", i+1, bg_jobs[i]);
      }
      continue;
    }

    if(strcmp(exec_args[0],"fg")==0){
      //bring to foreground
      if(separate_count < 2) {
        printf("Usage: fg <process_number>\n");
        continue;
      }
      process_number = exec_args[1][0] - '0'; // Convert string to integer//10個以上のbgには対応していない
      if(process_number < 1 || process_number > job_count) {
        printf("Invalid process number\n");
        continue;
      }
      pid = bg_jobs[process_number - 1];
      fg_pid = pid; // Set the foreground PID
      printf("bringing PID=%d to foreground\n", pid);
      waitpid(pid,&status,0);
      fg_pid = -1; // Reset the foreground PID after the process finishes

      // Shift remaining jobs
      for (int j = process_number-1; j < job_count - 1; j++) {//並び替え
        bg_jobs[j] = bg_jobs[j + 1];
      }
      job_count--;//総数を減らす
      continue;
    }

    for(int i = 0; i < separate_count; i++){
      if(strcmp(exec_args[i], "|") == 0){
        if(i == 0 || i == separate_count - 1 ||exec_args[i+1]==NULL){
          fprintf(stderr, "command not specified\n");
          pipe_flag = -1;//error
          break;
        }
        pipe_flag=1;
        pipe_separate_index = i;

        //パイプ処理をここに追加
        break;
      }

      if(strcmp(exec_args[i], ">") == 0){
        // 1. ファイル名が指定されていない場合
        if (exec_args[i+1] == NULL) {
          fprintf(stderr, "file not specified\n"); // 標準エラー出力へ
          redirect_flag = -1; // エラー状態
          break;
        }
        // 2. ファイルが2つ以上指定されている場合
        if (exec_args[i+2] != NULL && strcmp(exec_args[i+2], "&") != 0) {
          fprintf(stderr, "too many files specified\n");
          redirect_flag = -1;
          break;
        }
        redirect_flag = 1;//リダイレクトフラグを立てる
        strcpy(filename, exec_args[i+1]);//filenameに保存
        exec_args[i] = NULL; // ">"以降をコマンド引数から削除(bg処理は既に完了しているはず)
        break;
      }
    }
    // redirect_flag == -1 の場合は fork せずに continue する処理を追加
    if (redirect_flag == -1) { redirect_flag = 0; continue; }
    if (pipe_flag == -1) { pipe_flag = 0; continue; }

    //forkcd
    if((pid = fork()) == 0){ 
      //child
      //プロセスグループを新しく作る
      setpgid(0,0);
      //execve
      signal(SIGINT, SIG_DFL); // Restore default SIGINT behavior in child  
      signal(SIGCHLD, SIG_DFL); // Restore default SIGCHLD behavior in child

      if(pipe_flag == 1){
        int pipe_fds[2];
        int ret=pipe(pipe_fds);
        exec_args[pipe_separate_index] = NULL; // パイプ記号をNULLに置き換え
        if(ret < 0){
          perror("pipe");
          exit(1);
        }

        pid_t pid2 = fork();
        if(pid2 == 0) { // 孫プロセス: 左側のコマンド実行
          close(pipe_fds[0]);
          dup2(pipe_fds[1], STDOUT_FILENO);
          close(pipe_fds[1]);

          exec_args[pipe_separate_index] = NULL; 
          find_path(exec_args[0]);
          for(int i=0; path[i][0]!='\0'; i++){
            execve(path[i], exec_args, environ);//左側実行
          }
          //error
            fprintf(stderr, "exec failed(左側) \n");
            exit(1);
          }
            
          // 子プロセス（右側）: 標準入力を切り替えて続行
          close(pipe_fds[1]);
          dup2(pipe_fds[0], STDIN_FILENO);
          close(pipe_fds[0]);
          waitpid(pid2, NULL, 0); // 孫の終了を待つ

          //exec_argsの先頭を「パイプの右側」にずらす
          // これにより、後のリダイレクトと実行処理を共通で使える
          current_args = &exec_args[pipe_separate_index + 1];
          for (int i = 0; current_args[i] != NULL; i++) {
            if (strcmp(current_args[i], ">") == 0) {
              char *outfile = current_args[i+1];
              if (outfile != NULL) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);  
                // 重要: ">" 以降を NULL にして、grep に ">" が渡らないようにする
                current_args[i] = NULL; 
              }
              break;
            }
          }
        }

        if (redirect_flag == 1) {
          // O_WRONLY: 書込専用, O_CREAT: なければ作成, O_TRUNC: あれば中身を空にする 
          int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
          if (fd < 0) {
            perror("open");
            exit(1);
          }
          dup2(fd, STDOUT_FILENO); // 標準出力からfdnにむける
          close(fd); // 複製後は元のfdは閉じてよい 
        }

        find_path(current_args[0]);//path検索
        for(int i=0;i<MAX_PATH_COUNT && path[i][0]!='\0';i++){
          execve(path[i],current_args,environ);
        }
        //error
        fprintf(stderr, "exec failed \n");
        exit(1);//status 1で終了
    }else{
      //parent
      //waitpid
      if(!background) {//foreground process
        fg_pid = pid; // Set the foreground PID
        waitpid(pid,&status,0);
        fg_pid = -1; // Reset the foreground PID after the process finishes
      }else{
        //background process
        bg_jobs[job_count++] = pid;
        printf("started background job PID=%d \n", pid);
      }
    }
  } 
  return 0;
}
