#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define n_of_str 5
#define size_str 50

int x;
char **a;
GtkApplication *app1,*app;
GtkWidget *window,*window1;
char arr[n_of_str][size_str]={"Station..1..selected","Station..2..selected","Station..3..selected","Station..4..selected"};
static int flag;

static void activate_after (GtkApplication *app,gpointer user_data);

static void print_play (GtkWidget *widget,gpointer data){
  g_print("%p\n",data);
  g_print ("play clicked\n");    
}

static void print_pause (GtkWidget *widget,gpointer   data){
  g_print ("pause clicked\n");
}
static void print_stop (GtkWidget *widget,gpointer   data){
  g_print ("resume clicked\n");
}

static void activate (GtkApplication *app,gpointer user_data){
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *play,*pause,*stop;

  /* create a new window, and set its title */
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

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  /*button = gtk_button_new_with_label ("Button 1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  */
  play = gtk_button_new_with_label ("Play");
  int x=4;
  g_signal_connect (play , "clicked", G_CALLBACK (print_play),(void *)&x);

  pause = gtk_button_new_with_label ("Pause");
  g_signal_connect (pause , "clicked", G_CALLBACK (print_pause),NULL);

  stop = gtk_button_new_with_label ("Resume");
  g_signal_connect (stop , "clicked", G_CALLBACK (print_stop),NULL);


  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), play, 0, 0, 1, 1);

  /*button = gtk_button_new_with_label ("Button 2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  */
  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), pause, 0, 2, 6, 1);
  gtk_grid_attach (GTK_GRID (grid) , stop, 0, 4, 6, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
 // g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide, window);
  //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_show), window1);
  
  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 6, 1);

  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */

  gtk_widget_show_all (window);
  
 // gtk_widget_hide(window); 
  //gtk_widget_show(window1);

}

static void displaysame(){

    //GtkApplication *app;
    //int status;
   // gtk_widget_hide(window1);
    //gtk_widget_destroy(window1);
    //getw.window.close(window1);
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    g_application_run (G_APPLICATION (app), x, a);
    g_object_unref (app);

}

static void print_station1 (GtkWidget *widget,gpointer   data){
  g_print ("1 Station 1 selected\n");
  flag=1;
  displaysame();
}

static void print_station2 (GtkWidget *widget,gpointer   data){
  g_print ("2 Station 2 selected\n");
  flag=2;
  displaysame();
}
static void print_station3 (GtkWidget *widget,gpointer   data){
  g_print ("3 Station 3 selected\n");
  flag = 3;
  displaysame();
}
static void print_station4 (GtkWidget *widget,gpointer   data){
  g_print ("4 Station 4 selected\n");
  flag=4;
  displaysame();
}


static void activate_after (GtkApplication *app,gpointer user_data){
 // GtkWidget *window1;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *station1,*station2,*station3,*station4;
 // GtkWidget *result1,*result2,*result3,*result4;
  GtkWidget *name1,*name2,*name3,*name4;
  GtkWidget *addr1,*addr2,*addr3,*addr4;
  GtkWidget *dataport1,*dataport2,*dataport3,*dataport4;
  GtkWidget *infoport1,*infoport2,*infoport3,*infoport4;
  GtkWidget *bitrate1,*bitrate2,*bitrate3,*bitrate4;

  /* create a new window, and set its title */
  window1 = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window1), "CN Gui");
  gtk_container_set_border_width (GTK_CONTAINER (window1), 200);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window1), grid);

  /*button = gtk_button_new_with_label ("Button 1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  */
  station1 = gtk_button_new_with_label ("Connect Station : 1");
  g_signal_connect (station1 , "clicked", G_CALLBACK (print_station1),NULL);
  name1 = gtk_label_new("1..Name..1");
  addr1 = gtk_label_new("1..Address..1");
  dataport1 = gtk_label_new("1..Dataport..1");
  infoport1 = gtk_label_new("1..Infoport..1");
  bitrate1 = gtk_label_new("1..Bitrate..1");
  
  station2 = gtk_button_new_with_label ("Connect Station : 2");
  g_signal_connect (station2, "clicked", G_CALLBACK (print_station2),NULL);
  name2 = gtk_label_new("2..Name..2");
  addr2 = gtk_label_new("2..Address..2");
  dataport2 = gtk_label_new("2..Dataport..2");
  infoport2 = gtk_label_new("2..Infoport..2");
  bitrate2 = gtk_label_new("2..Bitrate..2");
  
  station3 = gtk_button_new_with_label ("Connect Station : 3");
  g_signal_connect (station3 , "clicked", G_CALLBACK (print_station3),NULL);
  name3 = gtk_label_new("3..Name..3");
  addr3 = gtk_label_new("3..Address..3");
  dataport3 = gtk_label_new("3..Dataport..3");
  infoport3 = gtk_label_new("3..Infoport..3");
  bitrate3 = gtk_label_new("3..Bitrate..3");
  
  station4 = gtk_button_new_with_label ("Connect Station : 4");
  g_signal_connect (station4 , "clicked", G_CALLBACK (print_station4),NULL);
  name4 = gtk_label_new("4..Name..4");
  addr4 = gtk_label_new("4..Address..4");
  dataport4 = gtk_label_new("4..Dataport..4");
  infoport4 = gtk_label_new("4..Infoport..4");
  bitrate4 = gtk_label_new("4..Bitrate..4");

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window1);


  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
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

  /*button = gtk_button_new_with_label ("Button 2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  */
  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  //gtk_grid_attach (GTK_GRID (grid), pause, 1, 2, 6, 1);
//  gtk_grid_attach (GTK_GRID (grid) , stop, 5, 4, 6, 1);

  
  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  
  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window1);

}

void* guiThread(void * vargp) { 
  app1 = gtk_application_new ("org.gtk.example1", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app1, "activate", G_CALLBACK (activate_after), NULL);
  g_application_run (G_APPLICATION (app1), x, a);
  g_object_unref (app1);
  //return status;   
}

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

  memcpy(buf,&req,sizeof(req));
  len = send(s, buf, sizeof(req), 0);

  len = recv(s,buf,sizeof(buf),0);

  memcpy(&site,buf,len);
  printf("  -->  %s  <--\n",site.site_name);
  printf("%s\n",site.site_desc);
  printf("Number of channels: %d\n\n",site.station_count);
  int i;
  for(i = 0; i < site.station_count; i++){
      printf("Station Number: %d\n", site.station_list[i].station_number);
      printf("Station Name: %s\n", site.station_list[i].station_name);
      printf("%d\n",site.station_list[i].multicast_address );
      inet_ntop(AF_INET, &(site.station_list[i].multicast_address), mip, INET_ADDRSTRLEN);
      //printf("hgch\n");
      printf("Multicast Address: %s\n", mip);
      printf("Data Port: %d\n", site.station_list[i].data_port);
      printf("Info Port: %d\n", site.station_list[i].info_port);
      printf("Bit Rate: %d\n\n", site.station_list[i].bit_rate);
  }
  while(flagGUI){}
  flagTCP=1;
  MC_PORT =  site.station_list[0].data_port;
  mcastaddrShare = site.station_list[0].multicast_address;
  fflush(stdin);

}

void* udpConn(){
  while(!flagTCP){}
  struct sockaddr_in sin; /* socket struct */
  char *if_name; /* name of interface */
  struct ifreq ifr; /* interface struct */
  // /* Multicast specific */
   char *mcast_addr; /* multicast address */
   struct ip_mreq mcast_req;  /* multicast join struct */

  if_name = "wlp2s0";
  if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("receiver: socket");
    exit(1);
  }
  while(1){
    while(!flagGUI2){}
    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(MC_PORT);
    
    /*Use the interface specified */ 
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name , if_name, sizeof(if_name)-1);
    
    if ((setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, 
            sizeof(ifr))) < 0)
      {
        perror("receiver: setsockopt() error");
        close(s);
        exit(1);
      }

    int MegaByte = 10240;  
    // Increasing the UDP buffer size to 10MegaBytes using setsockopt()
    if ((setsockopt(s, SOL_SOCKET, SO_RCVBUF, (void *)&MegaByte, sizeof(MegaByte))) < 0)
    {
        perror("receiver: setsockopt() buf error");
        close(s);
        exit(1);
    }

    /* bind the socket */
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0) {
      perror("receiver: bind()");
      exit(1);
    }
    
    /* Multicast specific code follows */
      //build IGMP join message structure 
    mcast_req.imr_multiaddr.s_addr = mcastaddrShare;  //Passing the address according to the station chosen by the user.
    mcast_req.imr_interface.s_addr = htonl(INADDR_ANY);
    //printf("%d\n",*mcastaddrShare);
    /* send multicast join message */
    if ((setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &mcast_req, sizeof(mcast_req))) < 0) {
      perror("mcast join receive: setsockopt()");
      exit(1);
    }
    printf("UDP socket connected\n");
    flagUDP=1;
    while(flagQuit){}
    flagUDP=0;
  }
}

void* stream(){
  while(1){
    while(!flagUDP){}
    printf("i am in file\n");
    struct sockaddr_in mcast_sin; /* multicast sender*/
    socklen_t mcast_sin_len;
    int len,j;
    char buf[MAX_LINE];

    FILE* fp;
    fp = fopen("radio.mp4","wb+");
    printf("I am in file.\n");
    while(flagQuit){
      /* reset sender struct */
      memset(&mcast_sin, 0, sizeof(mcast_sin));
      mcast_sin_len = sizeof(mcast_sin);
      if (flagPause && (len = recvfrom(s, buf, MAX_LINE, 0, (struct sockaddr*)&mcast_sin,&mcast_sin_len)) < 0) {
        perror("receiver: recvfrom()");
        exit(1);
      }
      for(j=0;j<len;j++){
        if(fprintf(fp,"%c",buf[j])<0){
          perror("Error Writing to File");
        }
      }
      fflush(fp);
    }
    printf("file closed.\n");
    remove("radio.mp4");
    fclose(fp);
  }
}

int main (int argc,char **argv){
  x = gargc = argc;
  a = argv;
  flagTCP=0;
  flagGUI=1;
  flagUDP=0;
  flagPause=1;
  flagQuit=1;

  pthread_t g1,t1,u1,s1; 
  pthread_create(&g1, NULL, guiThread, NULL); 
  pthread_create(&t1, NULL, tcpConn, NULL);
  pthread_create(&u1, NULL, udpConn, NULL);
  pthread_create(&s1, NULL, stream, NULL);
  while(1){}

  return 0;
}