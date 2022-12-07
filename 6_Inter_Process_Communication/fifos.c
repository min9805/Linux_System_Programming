#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include "fifo.h"

//종료 시 할당된 fifo를 해제하고 종료한다
void SigIntHandler(int signo){
	if(remove(SERV_FIFO) < 0){
		perror("remove");
		exit(1);
	}
	exit(0);
}

int main(){
	int	fd, cfd, n;
	MsgType msg;

	//signal 등록
	if (signal(SIGINT, SigIntHandler) == SIG_ERR){
		perror("signal");
		exit(1);
	}

	//mkfifo
	if(mkfifo(SERV_FIFO, 0600) < 0){
		if (errno != EEXIST){
			perror("mkfifo");
			exit(1);
		}
	}

	//fifo file을 오픈한다
	if((fd = open(SERV_FIFO, O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}

	//계속 파일에서 read를 대기한다. 읽은 후에는 잘 받았다는 메세지를 다시 넘겨준다
	while (1) {
		if((n = read(fd, (char *)&msg, sizeof(msg))) < 0){
			if (errno = EINTR) {
				continue;
			} else {
				perror("read");
				exit(1);
			}
		}
		printf("Received request: %s.....", msg.data);

		if ((cfd = open(msg.returnFifo, O_WRONLY)) < 0)  {
			perror("open");
			exit(1);
		}
		sprintf(msg.data, "This is a reply from %d.", getpid());
		write(cfd, (char *)&msg, sizeof(msg));
		close(cfd);
		printf("Replied.\n");
	}
}
