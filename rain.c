#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

#define WIDTH 80
#define HEIGHT 24
#define DELAY 100000 // 微秒

char screen[HEIGHT][WIDTH + 1]; // +1 是为了存储字符串结束符 '\0'
bool running = true;

// 初始化屏幕的函数
void init_screen() {
    for (int i = 0; i < HEIGHT; i++) {
        memset(screen[i], ' ', WIDTH);
        screen[i][WIDTH] = '\0'; // 添加字符串结束符
    }
}

// 清屏并输出当前屏幕内容的函数
void render_screen() {
    printf("\033[H\033[J"); // ANSI转义序列：移动光标到左上角并清除屏幕
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", screen[i]);
    }
    fflush(stdout); // 确保所有输出都被刷新到终端
}

char random_char(){
     const char charset[]=
            "ABCDEFGHIGKLMNOPQRSTUVWXYZ"
            "abcdefghigklmnopqistuvwxyz"
            "0123456789"
            "~!@#$%^&*()_+=`[{]{]:;'\|/?.>,<";
            size_t max_index = strlen( charset) -1;
            return charset[rand()%max_index];
}      
// 更新雨滴位置的函数
void update_rain() {
    // 简单的更新逻辑：每个字符向下移动一行，到达底部后“消失”（被新字符覆盖）
    for (int i = HEIGHT - 1; i > 0; i--) {
        strcpy(screen[i], screen[i - 1]);
    }
    // 顶部行初始化为空格
    memset(screen[0], ' ', WIDTH);

    // 随机在顶部行添加雨滴（这里用字符'*'表示雨滴）
    for (int j = 0; j < WIDTH / 10; j++) { // 控制雨滴密度
        int pos = rand() % WIDTH;
        while (screen[0][pos] !=' '){
        pos = (pos +1) % WIDTH;
        }
        screen[0][pos] = random_char();
    }
}

// 信号处理函数，用于捕获Ctrl+C并优雅地退出程序
void handle_sigint(int sig) {
    running = false;
}

int main() {
    srand(time(NULL)); // 初始化随机数生成器
    init_screen(); // 初始化屏幕

    // 设置SIGINT的信号处理函数
    signal(SIGINT, handle_sigint);

    while (running) {
        update_rain(); // 更新雨滴位置
        render_screen(); // 渲染屏幕
        usleep(DELAY); // 延迟
    }

    printf("\nExiting...\n"); // 程序退出前的提示信息
    return 0;
}
