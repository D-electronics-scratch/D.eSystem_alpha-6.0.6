#include "video.h"
#include "main.h"
#include "keyboard.h"
#include "keyboard_input.h"
#include "util.h"
#include "clock.h"
#include <limine.h>
#include "main_ui.h"
#include "desktop_ui.h"
#include "calculator_input.h"
#include "sleep.h"


int hour = 0;
int min = 0;
int sec = 0;
int t_sec;
int t_sec2;
int clock_on_off;



void run_clock_d_elec();
void clock_ui();
void time_ui();

void clock_ui() {
    draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
    draw_text(framebuffer, 500, 60, "| [1] Timer                         |", 0xFFFFFF);
    draw_text(framebuffer, 500, 70, "| [2] Time                          |", 0xFFFFFF);
    draw_text(framebuffer, 500, 80, "| [Esc] Close                         |", 0xFFFFFF);
    draw_text(framebuffer, 500, 90, "-------------------------------------", 0xFFFFFF);

}

void time_ui() {
    draw_text(framebuffer, 500, 50, "----------------------------------------", 0xFFFFFF);
    draw_text(framebuffer, 500, 60, "|Time:                                 |", 0xFFFFFF);
    draw_text(framebuffer, 500, 70, "----------------------------------------", 0xFFFFFF);
    draw_text(framebuffer, 500, 80, "| Press [Esc]  to leave!!              |", 0xFFFFFF);
    draw_text(framebuffer, 500, 70, "----------------------------------------", 0xFFFFFF);

}


void run_clock_d_elec() {
    key = 0;
    clock_on_off = 0;

    

    clear_screen(framebuffer, 0x000000);
    print_main_ui();
    clock_ui();

    while (key == 0) {
        key = ps2_read_key();
    }

    if (key == 27) {
        clear_screen(framebuffer, 0x000000);
        ui_desktop();
        clock_on_off = 2;
        return;
        
    } else if (key == '1') {
        clear_screen(framebuffer, 0x000000);
        print_main_ui();
        draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|         How many secconds?        |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "-------------------------------------", 0xFFFFFF);
        t_sec = calculator_read_int(450, 230);
        t_sec2 = t_sec * 1000;
        clear_screen(framebuffer, 0x000000);
        print_main_ui();
        draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|          Timer is running         |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "-------------------------------------", 0xFFFFFF);
        sleep (t_sec2); 
        clear_screen(framebuffer, 0x000000);
        print_main_ui();
        draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|              Finished             |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 80, "|            [1] Continue           |", 0xFFFFFF);
        draw_text(framebuffer, 500, 90, "-------------------------------------", 0xFFFFFF);
        char buf[32];
        itoa(t_sec, buf, 10);
        draw_text(framebuffer, 500, 200, buf, 0xFFFFFF);
        
        key = 0;
        while (key == 0) {
            key = ps2_read_key();
        }
        if (key == '1') {
            run_clock_d_elec();

        }

        
    } else if (key == '2') {
        key = 0;
        clear_screen(framebuffer, 0x000000);
        print_main_ui();
        draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|              hour?                |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "-------------------------------------", 0xFFFFFF);
        hour = calculator_read_int(450, 230);
        clear_screen(framebuffer, 0x000000);print_main_ui();
        draw_text(framebuffer, 500, 50, "-------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|             minute?               |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "-------------------------------------", 0xFFFFFF);
        min = calculator_read_int(450, 230);
        clear_screen(framebuffer, 0x000000);print_main_ui();
        print_main_ui();
        draw_text(framebuffer, 500, 50, "----------------------------------------", 0xFFFFFF);
        draw_text(framebuffer, 500, 60, "|              seccond?                |", 0xFFFFFF);
        draw_text(framebuffer, 500, 70, "----------------------------------------", 0xFFFFFF);
        sec = calculator_read_int(450, 230);
        clear_screen(framebuffer, 0x000000);print_main_ui();
        
        print_main_ui();
        time_ui();

        clock_on_off = 1;

        while (key == 0) {
            key = ps2_read_key();
        }
        if (key == 27) {
            run_clock_d_elec();

        } 


    }
 
 
    

 while (1) {

    if (clock_on_off == 1) {

        sleep(1000);   // 1 Sekunde warten
        sec++;

        // --- Zeitlogik ---
        if (sec >= 60) {
            sec = 0;
            min++;
        }

        if (min >= 60) {
            min = 0;
            hour++;
        }

        if (hour >= 24) {
            hour = 0;
        }

       
        clear_screen(framebuffer, 0x000000);
        print_main_ui();
        time_ui();

        
        char buf_sec[8];
        char buf_min[8];
        char buf_hour[8];

        itoa(sec, buf_sec, 10);
        itoa(min, buf_min, 10);
        itoa(hour, buf_hour, 10);

        draw_text(framebuffer, 590, 60, buf_sec, 0xffffff);
        draw_text(framebuffer, 573, 60, buf_min, 0xffffff);
        draw_text(framebuffer, 555, 60, buf_hour, 0xffffff);

        
        if (clock_on_off == 2) {
            break;
        }
    }
}

}