# ⚡ Non-Blocking Push-Button Library for STM32  

A lightweight and efficient **push-button driver** written in C for STM32 (HAL-based).  

Unlike simple polling implementations, this library uses a **non-blocking, timer-driven approach**, allowing the CPU to continue other tasks.  
It can run on **any GPIO pins** and supports multiple buttons (up to 31) simultaneously.  

The library is designed for:  

- Projects where CPU blocking must be avoided  
- Applications that require short and long press detection
- Easy portability across STM32 families 

---

## ✨ Features  

-  Multi-button support (`PB_CONFIG_COUNT`)  
-  Short and long press detection (`PB_SHORT_TIME_MS`, `PB_LONG_TIME_MS`)  
-  Event queue with configurable size (`PB_EVN_QUEUE_SIZE`)  
-  Optional callback on button events
-  Debouncing for all buttons
-  Non-blocking operation via timer interrupts
-  Support beep on press event
-  Fully STM32 HAL compatible  
-  Lightweight and modular design  

---

## ⚙️ Installation  

You can install in two ways:  

### 1. Copy files directly  
Add these files to your STM32 project:  
- `pb.h`  
- `pb.c`  
- `pb_config.h`  

### 2. STM32Cube Pack Installer
Available in the official pack repo:  
👉 [STM32-PACK](https://github.com/nimaltd/STM32-PACK)  (Not Ready)

---

## 🔧 Configuration (`pb_config.h`)  

Defines library parameters and timing values. 
`PB_CONFIG` should be fill by your pins 

---`c
/* Pin definitions */
#define PB_CONFIG           {.gpio = KEY_DOWN_GPIO_Port,  .pin = KEY_DOWN_Pin}, \
                            {.gpio = KEY_UP_GPIO_Port,    .pin = KEY_UP_Pin},   \
                            {.gpio = KEY_ENTER_GPIO_Port, .pin = KEY_ENTER_Pin}
---

---

## 🛠 CubeMX Setup  

1. **GPIO Pins**  
   - Configure button pins as **Input with Pull-Up** (active-low buttons recommended).  

2. **Timer**  
   - Use **internal clock source**.  
   - Set prescaler to get 1us tick. e.g. for 48Mhz bus, select 48-1.
   - Enable **Timer NVIC interrupt**.
   - In Project Manager → Code Generator, enable Generate Peripheral initialization as a pair ".c/.h" files per peripheral.
   - In **Project Manager → Advanced Settings**, enable **Register Callback** for the timer.  

---

## 🚀 Quick Start  

### Include header  
```c
#include "pb.h"
```

### 1️⃣ Normal Reading Mode 
```c
int main(void)
{
    pb_evn_t pb_evn;

    pb_init();

    while (1)
    {
        pb_evn = pb_read(); // Get next event from queue
        if (pb_evn)
        {
            // 0x00000001 for short press, first key
            // 0x00000002 for short press, second key
            // 0x00000004 for short press, third key
            // Handle button event manually
        }
    }
}
```

---

### 2️⃣ Callback mode  

#### Initialize with callback  
```c
/* Optional in all cases, Can handle beep on/off by a pin or timer */
void pb_beep_on_cb(void)
{
   // turn on buzzer pin
}

void pb_beep_off_cb(void)
{
   // turn off buzzer pin
}

void pb_pressed_cb(bool is_long, pb_evn_t evn)
{
}

int main(void)
{
    pb_init(); 

    while (1)
    {
        pb_loop();
    }
}
```

---

## 🧰 API Overview  

| Function | Description |
|----------|-------------|
| `pb_init()` | Initialize push-button driver with config and optional callback |
| `pb_clear()` | Clear pending events |
| `pb_read()` | Read pending button events |
| `pb_loop()` | Retrieve event from queue and optionally call callback |
| `pb_pressed_cb()` | Callback button events |
| `pb_beep_on_cb()` | Callback beep on |
| `pb_beep_off_cb()` | Callback beep off |

---

## 💖 Support  

If you find this project useful, please **⭐ star** the repo and consider supporting!  

- [![GitHub](https://img.shields.io/badge/GitHub-Follow-black?style=for-the-badge&logo=github)](https://github.com/NimaLTD)  
- [![YouTube](https://img.shields.io/badge/YouTube-Subscribe-red?style=for-the-badge&logo=youtube)](https://youtube.com/@nimaltd)  
- [![Instagram](https://img.shields.io/badge/Instagram-Follow-blue?style=for-the-badge&logo=instagram)](https://instagram.com/github.nimaltd)  
- [![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/nimaltd)  
- [![Email](https://img.shields.io/badge/Email-Contact-red?style=for-the-badge&logo=gmail)](mailto:nima.askari@gmail.com)  
- [![Ko-fi](https://img.shields.io/badge/Ko--fi-Support-orange?style=for-the-badge&logo=ko-fi)](https://ko-fi.com/nimaltd)  

---

## 📜 License  

Licensed under the terms in the [LICENSE](./LICENSE.TXT).  
