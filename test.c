#include "types.h"
#include "stat.h"
#include "user.h"

// cotumized handler
void my_handler(int parent_pid, int value){
    printf(1,"Handler:\nparent pid: %d\nchild pid: %d\n\n", parent_pid, getpid());
    sigsend(parent_pid,getpid());
}

void fork_test(void){
    sigset((sig_handler)&my_handler);
    int i;
    int resultfork;
    for (i = 0; i < 5; i++){
        resultfork = fork(); // the fork should copy the parent signal handler to the child(my_handler)
        if (resultfork == 0) { //child
            while(0){
            }
        }else{ // parent
            sigset((sig_handler)-1); // sets the parent handler back to the default handler
            printf(1, "fork_test-child pid: %d\n\n", resultfork);
            sigsend(resultfork, resultfork);
            wait();
        }
    }
	exit();
}
void exec_test(char *argv[]){
    sigset((sig_handler)&my_handler);
    exec(argv[0],argv); // should reset the handler to defualt handler
    int resultfork;
    resultfork = fork(); // the fork should copy the parent signal handler to the child(my_handler)
    if (resultfork == 0) { //child
        exec(argv[0],argv); // should reset the handler to defualt handler
        while(0){
        }
    }else{ // parent
        printf(1, "exec_test-child pid: %d\n\n", resultfork);   
        sigsend(resultfork, resultfork); // should call the default handler - not the costomized
        wait();
        }
		exit();
    }

int main(int argc,char *argv[])
{
    // override the current signal handler
    printf(1,"sigset test:\n");
    printf(1,"signal handler: %d\n", (int)sigset((sig_handler)5));
    printf(1,"signal handler: %d\n", (int)sigset((sig_handler)3));
    printf(1,"stack test:\n");
    testing();
    printf(1,"testing fork:\n\n\n");
    fork_test();
    printf(1,"testing exec:\n\n\n");
    exec_test(argv);

}