#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include <sys/time.h>
#include <fcntl.h> 
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// required defined constants
#define SERVER_PORT 5432
#define PORT_STREAM 6543
#define STATION_COUNT 4
#define MAX_PENDING 15
#define MAX_LINE 48000
#define SITE_DESC_SIZE 50
#define SITE_NAME_SIZE 20
#define STATION_NAME_SIZE 20

// structures given in the lab instructions
typedef struct station_info{
	uint8_t station_number;
	uint8_t station_name_size;
	char station_name[ STATION_NAME_SIZE ];
	uint32_t multicast_address;
	uint16_t data_port;
	uint16_t info_port;
	uint32_t bit_rate;
}station_t;

typedef struct site_info{
	uint8_t type ; 
	uint8_t site_name_size;
	char site_name[SITE_NAME_SIZE];
	uint8_t site_desc_size;
	char site_desc[SITE_DESC_SIZE];
	uint8_t station_count;
	station_t station_list [STATION_COUNT];
}site_t;

typedef struct station_info_request{
	uint8_t type;	
}sireq_t;

char tcpIP[20];

// thread for all TCP communications
void* tcpConn(){
    sireq_t req;
    site_t mySite;
    struct sockaddr_in sin;
    int s, new_s, len;
    char buf[MAX_LINE];
	char str[INET_ADDRSTRLEN];

    mySite.type = 10;
    strcpy(mySite.site_name,"Apna radio");
    mySite.site_name_size = sizeof(mySite.site_name);
    strcpy(mySite.site_desc,"This is local internet radio. Use GUI for listening");
    mySite.site_desc_size = sizeof(mySite.site_desc);
    mySite.station_count = 4;

    mySite.station_list[0].station_number = 1;
    strcpy(mySite.station_list[0].station_name,"Station 1");
    mySite.station_list[0].station_name_size = sizeof("Station 1");
    mySite.station_list[0].multicast_address = inet_addr("239.192.6.1");
    mySite.station_list[0].data_port = PORT_STREAM; 
    mySite.station_list[0].info_port = 5432;
    mySite.station_list[0].bit_rate = 480;

    mySite.station_list[1].station_number = 2;
    strcpy(mySite.station_list[1].station_name,"Station 2");
    mySite.station_list[1].station_name_size = sizeof("Station 2");
    mySite.station_list[1].multicast_address = inet_addr("239.192.6.2");
    mySite.station_list[1].data_port = PORT_STREAM; 
    mySite.station_list[1].info_port = 5432;
    mySite.station_list[1].bit_rate = 480;

    mySite.station_list[2].station_number = 3;
    strcpy(mySite.station_list[2].station_name,"Station 3");
    mySite.station_list[2].station_name_size = sizeof("Station 3");
    mySite.station_list[2].multicast_address = inet_addr("239.192.6.3");
    mySite.station_list[2].data_port = PORT_STREAM; 
    mySite.station_list[2].info_port = 5432;
    mySite.station_list[2].bit_rate = 480;

    mySite.station_list[3].station_number = 4;
    strcpy(mySite.station_list[3].station_name,"Sation 4");
    mySite.station_list[3].station_name_size = sizeof("Station 4");
    mySite.station_list[3].multicast_address = inet_addr("239.192.6.4");
    mySite.station_list[3].data_port = PORT_STREAM; 
    mySite.station_list[3].info_port = 5432;
    mySite.station_list[3].bit_rate = 480;					

    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(tcpIP);
    sin.sin_port = htons(SERVER_PORT);
    
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }

    inet_ntop(AF_INET, &(sin.sin_addr), str, INET_ADDRSTRLEN);
    printf("Server is using address %s and port %d.\n", str, SERVER_PORT);

    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }
    else
        printf("Apna radio has started. bear with the songs!\n");

    listen(s, MAX_PENDING);

    while(1) {
        if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
            perror("simplex-talk: accept");
            exit(1);
        }
        printf("New user connected!.\n");
        
        len = recv(new_s, buf, sizeof(buf), 0);	
        if(len == 1){
            memcpy(&req,buf,len);
        }
        if(req.type == 1){
            memcpy(buf,&mySite,sizeof(mySite));
            send(new_s,buf,sizeof(mySite),0);
        }
    }
} 

// station 1 thread
void* streamS1(){
    	int s;
        int i=1,readlen,sentlen;
        char buf[MAX_LINE];
        struct sockaddr_in sin;
        char ip[] = "239.192.6.1";

        if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		  printf("station 1: socket creation failed\n");
  			exit(1);
  		}
  		
  		memset(&sin, 0, sizeof(sin));
  		sin.sin_family = AF_INET;
  		sin.sin_addr.s_addr = inet_addr(ip);
  		sin.sin_port = htons(PORT_STREAM);

  		char fname[] = "tuje_kitna.mp3";
  		FILE *fp;
  		fp = fopen(fname,"rb");
        if(fp!=NULL){    
            while((readlen = fread(buf,1,MAX_LINE,fp)) > 0 ){
                if((sentlen = sendto(s, buf, readlen, 0, (struct sockaddr*)&sin, sizeof(sin)) ) < 0){
                printf("station 1: packet %d lost\n",i);
                }
                usleep(10000);
                if(feof(fp)){
                    rewind(fp);
                }
                i++;
            }
        }
}

// station 2 thread
void* streamS2(){
    	int s;
        int i=1,readlen,sentlen;
        char buf[MAX_LINE];
        struct sockaddr_in sin;
        char ip[] = "239.192.6.2";

        if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		  printf("station 2: socket creation failed\n");
  			exit(1);
  		}
  		
  		memset(&sin, 0, sizeof(sin));
  		sin.sin_family = AF_INET;
  		sin.sin_addr.s_addr = inet_addr(ip);
  		sin.sin_port = htons(PORT_STREAM);

  		char fname[] = "1.mp4";
  		FILE *fp;
  		fp = fopen(fname,"rb");
        if(fp!=NULL){    
            while((readlen = fread(buf,1,MAX_LINE,fp)) > 0 ){
                if((sentlen = sendto(s, buf, readlen, 0, (struct sockaddr*)&sin, sizeof(sin)) ) < 0){
                printf("station 2: packet %d lost\n",i);
                }
                usleep(10000);
                if(feof(fp)){
                    rewind(fp);
                }
                i++;
            }
        }
}

// station 3 thread
void* streamS3(){
    	int s;
        int i=1,readlen,sentlen;
        char buf[MAX_LINE];
        struct sockaddr_in sin;
        char ip[] = "239.192.6.3";

        if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		  printf("station 3: socket creation failed\n");
  			exit(1);
  		}
  		
  		memset(&sin, 0, sizeof(sin));
  		sin.sin_family = AF_INET;
  		sin.sin_addr.s_addr = inet_addr(ip);
  		sin.sin_port = htons(PORT_STREAM);

  		char fname[] = "tera_ban.mp3";
  		FILE *fp;
  		fp = fopen(fname,"rb");
        if(fp!=NULL){            
            while((readlen = fread(buf,1,MAX_LINE,fp)) > 0 ){
                if((sentlen = sendto(s, buf, readlen, 0, (struct sockaddr*)&sin, sizeof(sin)) ) < 0){
                printf("station 3: packet %d lost\n",i);
                }
                usleep(10000);
                if(feof(fp)){
                    rewind(fp);
                }
                i++;
            }
        }
}

// station 4 thread
void* streamS4(){
    	int s;
        int i=1,readlen,sentlen;
        char buf[MAX_LINE];
        struct sockaddr_in sin;
        char ip[] = "239.192.6.4";

        if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		  printf("station 4: socket creation failed\n");
  			exit(1);
  		}
  		
  		memset(&sin, 0, sizeof(sin));
  		sin.sin_family = AF_INET;
  		sin.sin_addr.s_addr = inet_addr(ip);
  		sin.sin_port = htons(PORT_STREAM);

  		char fname[] = "2.mp4";
  		FILE *fp;
  		fp = fopen(fname,"rb");
        if(fp!=NULL){    
            while((readlen = fread(buf,1,MAX_LINE,fp)) > 0 ){
                if((sentlen = sendto(s, buf, readlen, 0, (struct sockaddr*)&sin, sizeof(sin)) ) < 0){
                printf("station 4: packet %d lost\n",i);
                }
                usleep(10000);
                if(feof(fp)){
                    rewind(fp);
                }
                i++;
            }
        }
}

// the second most compact main you'll see (1st is client's XD)!
int main(int argc, char** argv){

    if(argc!=2){
        printf("Error: argument not correct\n");
        printf("run as ./filename <IP>\n");
        exit(1);
    }
    else{
        strcpy(tcpIP,argv[1]);
        printf("%s\n",tcpIP);
    }

    // starting tcp and station threads
    pthread_t s1,s2,s3,s4,t1;
    pthread_create(&t1, NULL, tcpConn, NULL); 
    pthread_create(&s1, NULL, streamS1, NULL);
    pthread_create(&s2, NULL, streamS2, NULL);
    pthread_create(&s3, NULL, streamS3, NULL);
    pthread_create(&s4, NULL, streamS4, NULL);
    
    while(1){}
    return 0;
}