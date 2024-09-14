#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

// #define GPIO_BASE 0xFE200000  // Raspberry Pi 5のGPIOベースアドレスを確認
#define GPIO_BASE 0x1F00000000  // Raspberry Pi 5のGPIOベースアドレスを確認
#define BLOCK_SIZE 4096

// GPIOピンの定義
#define PIN 3

// GPIOレジスタ
volatile uint32_t *gpio;

// GPIOピンを出力に設定する関数
void setup_gpio() {
    // GPFSEL0にあるGPIO3の設定を出力モード(001)に設定
    *(gpio + (PIN / 10)) &= ~(7 << ((PIN % 10) * 3));  // 000をクリア
    *(gpio + (PIN / 10)) |= (1 << ((PIN % 10) * 3));   // 001で出力に設定
}

// GPIOピンをHIGHにする関数
void set_pin_high() {
    *(gpio + 7) = (1 << PIN);  // GPIO SETレジスタ
}

// GPIOピンをLOWにする関数
void set_pin_low() {
    *(gpio + 10) = (1 << PIN);  // GPIO CLRレジスタ
}

int main() {
    int mem_fd;
    void *gpio_map;

    // /dev/memを開く
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        return -1;
    }

    // GPIOベースアドレスへのマッピング
    gpio_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_BASE
    );

    if (gpio_map == MAP_FAILED) {
        perror("mmap error");
        close(mem_fd);
        return -1;
    }

    // GPIOレジスタのポインタをセット
    gpio = (volatile uint32_t *)gpio_map;

    // GPIOの初期設定（3番ピンを出力モードに設定）
    setup_gpio();

    // LEDを点灯
    // set_pin_high();
    // sleep(1);  // 1秒間点灯

    // LEDを消灯
    set_pin_low();

    // メモリマッピングを解除
    munmap(gpio_map, BLOCK_SIZE);
    close(mem_fd);

    return 0;
}
