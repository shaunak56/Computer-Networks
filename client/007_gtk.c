#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int x;
char **a;
GtkApplication *app1,*app;
GtkWidget *window,*window1;
static void activate_after (GtkApplication *app,gpointer user_data);

static void print_play (GtkWidget *widget,gpointer   data){
  
  g_print ("play clicked\n");
    
}

static void print_pause (GtkWidget *widget,gpointer   data){
  g_print ("pause clicked\n");
}
static void print_stop (GtkWidget *widget,gpointer   data){
  g_print ("stop clicked\n");
}

static void activate (GtkApplication *app,gpointer user_data){
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *play,*pause,*stop;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "CN Gui");
  gtk_container_set_border_width (GTK_CONTAINER (window), 200);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  /*button = gtk_button_new_with_label ("Button 1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  */
  play = gtk_button_new_with_label ("Play");
  g_signal_connect (play , "clicked", G_CALLBACK (print_play),NULL);

  pause = gtk_button_new_with_label ("Pause");
  g_signal_connect (pause , "clicked", G_CALLBACK (print_pause),NULL);

  stop = gtk_button_new_with_label ("Stop");
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
  gtk_grid_attach (GTK_GRID (grid), pause, 1, 2, 6, 1);
  gtk_grid_attach (GTK_GRID (grid) , stop, 5, 4, 6, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
 // g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide, window);
  //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_show), window1);
  
  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 9, 6, 6, 1);

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
  displaysame();
}

static void print_station2 (GtkWidget *widget,gpointer   data){
  g_print ("2 Station 2 selected\n");
  displaysame();
}
static void print_station3 (GtkWidget *widget,gpointer   data){
  g_print ("3 Station 3 selected\n");
  displaysame();
}
static void print_station4 (GtkWidget *widget,gpointer   data){
  g_print ("4 Station 4 selected\n");
  displaysame();
}


static void activate_after (GtkApplication *app,gpointer user_data){
 // GtkWidget *window1;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *station1,*station2,*station3,*station4;

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

  station2 = gtk_button_new_with_label ("Connect Station : 2");
  g_signal_connect (station2, "clicked", G_CALLBACK (print_station2),NULL);

  station3 = gtk_button_new_with_label ("Connect Station : 3");
  g_signal_connect (station3 , "clicked", G_CALLBACK (print_station3),NULL);

  station4 = gtk_button_new_with_label ("Connect Station : 4");
  g_signal_connect (station4 , "clicked", G_CALLBACK (print_station4),NULL);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window1);


  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), station1 , 0, 3, 1, 1);
  
  gtk_grid_attach (GTK_GRID (grid), station2 , 2, 2, 1, 1); 
  
  gtk_grid_attach (GTK_GRID (grid), station3 , 4, 1, 1, 1);
  
  gtk_grid_attach (GTK_GRID (grid), station4 , 6, 0, 1, 1);
  
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


void *myThreadFun(void * vargp) 
{ 
   // sleep(1); 
  //  printf("Printing GeeksQuiz from Thread \n"); 
  
    //int status;

    app1 = gtk_application_new ("org.gtk.example1", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app1, "activate", G_CALLBACK (activate_after), NULL);
    g_application_run (G_APPLICATION (app1), x, a);
    g_object_unref (app1);
    //return status;   
} 
   
int main (int argc,char **argv){
    x=argc;
    a = argv;
  //p_thread_t thread_id;

  
  //p_thread_create(g_signal_connect (app, "activate", G_CALLBACK (activate), NULL))
    //int status;
    pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After thread");
    //exit(0); 

  return 0;
}