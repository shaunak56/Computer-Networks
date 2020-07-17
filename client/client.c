#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <signal.h>

// required defined constants
#define SERVER_PORT 5432
#define MAX_PENDING 15
#define MAX_LINE 48000
#define SITE_NAME_SIZE 20
#define SITE_DESC_SIZE 50
#define STATION_COUNT 1
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
    uint8_t type ; //10
    uint8_t site_name_size;
    char site_name[SITE_NAME_SIZE];
    uint8_t site_desc_size;
    char site_desc[SITE_DESC_SIZE];
    uint8_t station_count;
    station_t station_list [STATION_COUNT];
}site_t;

typedef struct station_info_request{
    uint8_t type ;
}sireq_t;

// required global variables
int x;
char **a;
int s=-1;// UDP socket 
int mic_time=0;
// required flags
int gargc, MC_PORT=-1, flagQuit=1, flagPause=1, flagQuit2=1, flagStream=-1;
int mcAdd;
GtkApplication *app1,*app;
GtkWidget *window,*window1,*window2;
char arr[5][50]={"Station..1..selected","Station..2..selected","Station..3..selected","Station..4..selected"};
static int flag;
pthread_t f1;

// thread to play the video from temporary file
void *playVideo(void * vargp) {
  usleep(mic_time);
  system("ffplay -i radio.mp4");
}

static void activate_after (GtkApplication *app,gpointer user_data);

// GUI button controls and other functions
static void print_play (GtkWidget *widget,gpointer data){
  g_print ("play clicked %d %d\n",s,MC_PORT); 
  if(flagStream!=-1){ // if receiving then play the station
    mic_time=500000;
    pthread_create(&f1,NULL,playVideo,NULL);
  }
}

static void print_pause (GtkWidget *widget,gpointer   data){
  system("killall ffplay > /dev/null 2>&1");
  system("rm radio.mp4 > /dev/null 2>&1");
  flagPause=0;
  g_print ("pause clicked\n");
}
static void print_resume (GtkWidget *widget,gpointer   data){
  flagPause=1;
  g_print ("resume clicked\n");
  if(flagStream!=-1){
    mic_time=1000000;
    pthread_create(&f1,NULL,playVideo,NULL);
  }
  
}

static void print_quit (GtkWidget *widget,gpointer   data){
  flagQuit = 1;
  system("killall ffplay > /dev/null 2>&1");
  gtk_widget_destroy(window);
}

static void activate (GtkApplication *app,gpointer user_data){
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *play,*pause,*stop;

  window = gtk_application_window_new (app);
  if(flag == 1)
    gtk_window_set_title (GTK_WINDOW (window), arr[(flag-1)]);
  else if(flag == 2)
    gtk_window_set_title (GTK_WINDOW (window), arr[(flag-1)]);
  else if(flag == 3)
    gtk_window_set_title (GTK_WINDOW (window), arr[(flag-1)]);
  else if(flag == 4)
    gtk_window_set_title (GTK_WINDOW (window), arr[(flag-1)]);
  else
    gtk_window_set_title (GTK_WINDOW (window), arr[4]);
  
  gtk_container_set_border_width (GTK_CONTAINER (window), 200);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  play = gtk_button_new_with_label ("  Play  ");
  g_signal_connect (play , "clicked", G_CALLBACK (print_play),NULL);

  pause = gtk_button_new_with_label ("Pause");
  g_signal_connect (pause , "clicked", G_CALLBACK (print_pause),NULL);

  stop = gtk_button_new_with_label ("Resume");
  g_signal_connect (stop , "clicked", G_CALLBACK (print_resume),NULL);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (print_quit), NULL);
 
  gtk_grid_attach (GTK_GRID (grid), play, 0, 0, 6, 1);

  gtk_grid_attach (GTK_GRID (grid), pause, 0, 2, 6, 1);
  gtk_grid_attach (GTK_GRID (grid) , stop, 0, 4, 6, 1);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 6, 1);

  gtk_widget_show_all (window);
  
}

static void displaysame(){

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  g_application_run (G_APPLICATION (app), x, a);
  g_object_unref (app);

}

static void print_station1 (GtkWidget *widget,gpointer   data){
  g_print ("1 Station 1 selected\n");
  flag=1;
  flagQuit=0;
  displaysame();
}

static void print_station2 (GtkWidget *widget,gpointer   data){
  g_print ("2 Station 2 selected\n");
  flag=2;
  flagQuit=0;
  displaysame();
}
static void print_station3 (GtkWidget *widget,gpointer   data){
  g_print ("3 Station 3 selected\n");
  flag = 3;
  flagQuit=0;
  displaysame();
}
static void print_station4 (GtkWidget *widget,gpointer   data){
  g_print ("4 Station 4 selected\n");
  flag=4;
  flagQuit=0;
  displaysame();
}

static void print_quit2 (GtkWidget *widget,gpointer   data){
  flagQuit2=0;
  gtk_widget_destroy(window1);
  usleep(100000);
  exit(0);
}
static void activate_after (GtkApplication *app,gpointer user_data){
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *station1,*station2,*station3,*station4;
  GtkWidget *name1,*name2,*name3,*name4;
  GtkWidget *addr1,*addr2,*addr3,*addr4;
  GtkWidget *dataport1,*dataport2,*dataport3,*dataport4;
  GtkWidget *infoport1,*infoport2,*infoport3,*infoport4;
  GtkWidget *bitrate1,*bitrate2,*bitrate3,*bitrate4;

  window1 = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window1), "Apna Radio");
  gtk_container_set_border_width (GTK_CONTAINER (window1), 200);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window1), grid);

  station1 = gtk_button_new_with_label ("Connect Station : 1");
  g_signal_connect (station1 , "clicked", G_CALLBACK (print_station1),NULL);
  name1 = gtk_label_new("Station 1");
  addr1 = gtk_label_new("239.192.6.1");
  dataport1 = gtk_label_new("6543");
  infoport1 = gtk_label_new("5432");
  bitrate1 = gtk_label_new("480kb/s");
  
  station2 = gtk_button_new_with_label ("Connect Station : 2");
  g_signal_connect (station2 , "clicked", G_CALLBACK (print_station2),NULL);
  name2 = gtk_label_new("Station 2");
  addr2 = gtk_label_new("239.192.6.2");
  dataport2 = gtk_label_new("6543");
  infoport2 = gtk_label_new("5432");
  bitrate2 = gtk_label_new("480kb/s");
  
  station3 = gtk_button_new_with_label ("Connect Station : 3");
  g_signal_connect (station3 , "clicked", G_CALLBACK (print_station3),NULL);
  name3 = gtk_label_new("Station 3");
  addr3 = gtk_label_new("239.192.6.3");
  dataport3 = gtk_label_new("6543");
  infoport3 = gtk_label_new("5432");
  bitrate3 = gtk_label_new("480kb/s");
  
  station4 = gtk_button_new_with_label ("Connect Station : 4");
  g_signal_connect (station4 , "clicked", G_CALLBACK (print_station4),NULL);
  name4 = gtk_label_new("Station 4");
  addr4 = gtk_label_new("239.192.6.4");
  dataport4 = gtk_label_new("6543");
  infoport4 = gtk_label_new("5432");
  bitrate4 = gtk_label_new("480kb/s");

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (print_quit2), NULL);

  gtk_grid_attach (GTK_GRID (grid), station1 , 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), name1  , 0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), addr1  , 0, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), dataport1  , 0, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), infoport1  , 0, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), bitrate1  , 0, 5, 1, 1);

  gtk_grid_attach (GTK_GRID (grid), station2 , 1, 0, 1, 1); 
  gtk_grid_attach (GTK_GRID (grid), name2  , 1, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), addr2  , 1, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), dataport2  , 1, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), infoport2  , 1, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), bitrate2  , 1, 5, 1, 1);

  gtk_grid_attach (GTK_GRID (grid), station3 , 2, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), name3  , 2, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), addr3  , 2, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), dataport3  , 2, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), infoport3  , 2, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), bitrate3  , 2, 5, 1, 1);

  gtk_grid_attach (GTK_GRID (grid), station4 , 3, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), name4  , 3, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), addr4  , 3, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), dataport4  , 3, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), infoport4  , 3, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), bitrate4  , 3, 5, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), button ,   9, 6, 6, 1);
  gtk_widget_show_all (window1);

}

// thread to start GUI

void* guiThread(void * vargp) { 
  app1 = gtk_application_new ("org.gtk.example1", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app1, "activate", G_CALLBACK (activate_after), NULL);
  g_application_run (G_APPLICATION (app1), x, a);
  g_object_unref (app1);   
}

// thread for all TCP communications
void* tcpConn(){

  char *host;
  char buf[MAX_LINE];
  int s, len;
  static char mip[SITE_NAME_SIZE];
  char *if_name; /* name of interface */
  char *mcast_addr; /* multicast address */
  
  struct hostent *hp; 
  struct sockaddr_in sin; /* socket struct */
  site_t site;

  if (gargc==1) {
    host = "0";
  }
  else {
    fprintf(stderr, "usage: simplex-talk host\n");
    exit(1);
  }
  hp = gethostbyname(host);
  if (!hp) {
    fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    exit(1);
  }
  memset(&sin, 0,sizeof(sin));
  sin.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  sin.sin_port = htons(SERVER_PORT);
  
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  else
    printf("Client created socket.\n");

  if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
      perror("simplex-talk: connect");
      close(s);
      exit(1);
    }
  else{
    printf("Client connected.\n");
  }
  
  sireq_t req ;
  req.type = 1;
  MC_PORT=-1;
  printf("inside tcp\n");
  memcpy(buf,&req,sizeof(req));
  
  len = send(s, buf, sizeof(req), 0);
  len = recv(s,buf,sizeof(buf),0);

  memcpy(&site,buf,len);
  printf("You are listening to %s\n",site.site_name);
  printf("%s\n",site.site_desc);
  
  while(flagQuit2){
    if(!flagQuit)
      continue;
      while(flagQuit){}
      printf("\nflag in TCP: %d\n",flag);
      MC_PORT =  site.station_list[flag-1].data_port;
      mcAdd = site.station_list[flag-1].multicast_address;
      printf("\nMC %d %d\n",MC_PORT,mcAdd);
  }
  close(s);
}

void* udpConn(){
  struct sockaddr_in sin; 
  char *if_name; 
  struct ifreq ifr; // interface for receiving
  char *mcast_addr; // multicast address 
  struct ip_mreq mcast_req;  // multicast join
  if_name = "wlp2s0";
  while(flagQuit2){
    // if the station is yet not chosen in GUI, then do nothing
    if(MC_PORT==-1 || flagQuit)
      continue;
    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("receiver: socket");
      exit(1);
    }
    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(MC_PORT);
    
    /*Use the interface specified */ 
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name , if_name, sizeof(if_name)-1);
    
    if ((setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr))) < 0){
        perror("receiver: setsockopt() error");
        close(s);
        exit(1);
    }

    int MB = 16000;  
    // increasing buffer just to ensure smoothness 
    if ((setsockopt(s, SOL_SOCKET, SO_RCVBUF, (void *)&MB, sizeof(MB))) < 0)
    {
        perror("receiver: setsockopt() buf error");
        close(s);
        exit(1);
    }

    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0) {
      perror("receiver: bind()");
      exit(1);
    }
    
    mcast_req.imr_multiaddr.s_addr = mcAdd;  //Passing the address according to the station chosen by the user.
    mcast_req.imr_interface.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &mcast_req, sizeof(mcast_req))) < 0) {
      perror("mcast join receive: setsockopt()");
      exit(1);
    }
    printf("UDP socket connected\n");
    flagStream=1;
    while(!flagQuit){}
    // close the socket when disconnected from the station
    close(s);
    s=-1;
    flagStream=-1;
  }
    
}

// thread to handle streaming part
void* stream(){

    struct sockaddr_in mcast_sin; 
    socklen_t mcast_sin_len;
    int len,j;
    char buf[MAX_LINE];
    while(flagQuit2){
      if(flagQuit || flagPause==0)
        continue;
      FILE* fp;
      fp = fopen("radio.mp4","wb+");
      while(flagStream==1){
        if(flagQuit || flagPause==0)
          break;
        /* reset sender struct */
        memset(&mcast_sin, 0, sizeof(mcast_sin));
        mcast_sin_len = sizeof(mcast_sin);
        if ((len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&mcast_sin,&mcast_sin_len)) < 0) {
          perror("receiver: recvfrom()");
          exit(1);
        }

        for(j=0;j<len;j++){
          if(fprintf(fp,"%c",buf[j])<0){
            perror("Buffer error!!\n");
          }
        }
        fflush(fp);
      }
      fclose(fp);
      system("rm radio.mp4 > /dev/null 2>&1");
  }
}

// the most elegant and compact main function you'll ever see!
int main(int argc, char**argv){
  x = gargc = argc;
  a = argv;

  // creation of above listed threads
  pthread_t g1,t1,u1,s1; 
  pthread_create(&g1, NULL, guiThread, NULL); 
  pthread_create(&t1, NULL, tcpConn, NULL);
  pthread_create(&u1, NULL, udpConn, NULL);
  pthread_create(&s1, NULL, stream, NULL);

  while(1){}
  return 0;
}
