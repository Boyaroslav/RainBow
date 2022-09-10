#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>
#include <time.h>

// красный оранжевый желтый зеленый голубой синий фиолетовый


int colors[7][3] = {{255, 0, 0}, {255, 160, 0}, {255, 255, 0}, {0, 255, 0}, {100, 100, 255}, {0, 0, 255}, {230, 230, 255}};

int stepconst = 50;
int steps;

double stepr, stepb, stepg;
int r, g, b;
char *chrn = NULL;
wchar_t *wchrn = NULL;
int indC;
FILE* text;

void init(){
    steps = stepconst;
    r = colors[indC][0];
    g = colors[indC][1];
    b = colors[indC][2];
    if(++indC == 7){
        indC=0;
    }
    stepr = (colors[indC][0] - r) / (steps * 1.0);
    stepg = (colors[indC][1] - g) / (steps * 1.0);
    stepb = (colors[indC][2] - b) / (steps * 1.0);
    
}

void print_char(char *s, wchar_t *p){ // its also changes colors

    if(s && !p){

        int i=0;
        wchar_t bf[100];
        mbstowcs(bf, s, 100);
        while(bf[i]){
            printf("\e[38;2;%d;%d;%dm%lc\e[0m", r, g, b, bf[i++]);
            if (s[i - 1] != '\n' || s[1 - 1] != ' '){
                r += (int)stepr ;
                g += (int)stepg;
                b += (int)stepb;
                if(--steps == 0){
                    init();
                }
            }
  
        } 
    }

    else if(!s && p){

        printf("\e[38;2;%d;%d;%dm%lc\e[0m", r, g, b, p[0]);
        if(p[0] != ' ' || p[0] != '\n'){
        r += (int)stepr ;
        g += (int)stepg;
        b += (int)stepb;
        if(--steps == 0){
            init();
        }}
    }
    //printf("%lc", s);

    return;
}

void print_file(FILE *b){
    if (b == NULL){
        fprintf(stdout, "not file\n");
        return;
    }

    wchar_t *i;
    while((*i = fgetwc(b)) != WEOF){
        fflush(b);
        fflush(stdout);
        //char j[20];
        //*j = *i;
        
        print_char(chrn, i);
    }
    fclose(b);
    return;

}


int main(int argc, char **argv){
    if(argc <= 1){
        fprintf(stdout, "NO INPUT. ABORT\n");
    }

    srand(time(NULL)); 



    setlocale(LC_ALL, ""); // utf-8
    indC = rand() % 7;
    init();

    // starting from red
    //for(int argi=0; argi < argc; argi++){
    //    if(strcmp(argv[argi], "-"))
    //}   
    char buf[20];
    

    if (text = fopen(argv[1], "r")){

        print_file(text);
        putchar('\n');


        
        //print_file(text);
    }
    else{ // костыль #1
        for(int i=1; i<argc; i++){


            print_char(argv[i], wchrn);

            if(i + 1 != argc) putchar(' ');
        }
        
        
        //print_buffer(*argv[1], *nullf);
        }
    
    
    return 0;


}