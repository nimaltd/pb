# ⚡ Non-Blocking Push-Button Library for STM32  

A lightweight and efficient **push-button driver** written in C for STM32 (HAL-based).  

Unlike simple polling implementations, this library uses a **non-blocking, timer-driven approach**, allowing the CPU to continue other tasks.  
It can run on **any GPIO pins** and supports multiple buttons simultaneously.  

The library is designed for:  

- Projects where CPU blocking must be avoided  
- Applications that require short and long press detection  
- Easy portability across STM32 families (F0/F1/F3/F4/F7/G0/G4/H7, etc.)  

---

## ✨ Features  

- 🔹 Multi-button support (`PB_KEY_COUNT`)  
- 🔹 Short and long press detection (`PB_SHORT_TIME_MS`, `PB_LONG_TIME_MS`)  
- 🔹 Event queue with configurable size (`PB_EVN_QUEUE_SIZE`)  
- 🔹 Optional callback on button events  
- 🔹 Non-blocking operation via timer interrupts  
- 🔹 Fully STM32 HAL compatible  
- 🔹 Lightweight and modular design  

---

## ⚙️ Installation  

You can install in two ways:  

### 1. Copy files directly  
Add these files to your STM32 project:  
- `pb.h`  
- `pb.c`  
- `pb_config.h`  

---

## 🔧 Configuration (`pb_config.h`)  

Defines library parameters and timing values. Example:  

```c
#define PB_TIM                htim3        // Timer used for periodic scanning
#define PB_INTERVAL_MS        10           // Scan interval in milliseconds
#define PB_SHORT_TIME_MS      50           // Minimum duration for short press
#define PB_LONG_TIME_MS       1000         // Minimum duration for long press
#define PB_EVN_QUEUE_SIZE     8            // Size of the event queue
#define PB_KEY_COUNT          3            // Number of buttons
```  

---

## 🛠 CubeMX Setup  

1. **GPIO Pins**  
   - Configure button pins as **Input with Pull-Up** (active-low buttons recommended).  

2. **Timer**  
   - Use **internal clock source**.  
   - Set prescaler so that the timer tick matches `PB_INTERVAL_MS`.  
   - Enable **Timer NVIC interrupt**.  
   - In **Project Manager → Advanced Settings**, enable **Register Callback** for the timer.  

---

## 🚀 Quick Start  

### Include header  
```c
#include "pb.h"
```

### Define button configuration  
```c
const pb_config_t pb_config[] =
{
    { .gpio = KEY_DOWN_GPIO_Port,  .pin = KEY_DOWN_Pin  },
    { .gpio = KEY_UP_GPIO_Port,    .pin = KEY_UP_Pin    },
    { .gpio = KEY_ENTER_GPIO_Port, .pin = KEY_ENTER_Pin }
};
```

---

### 1️⃣ Polling mode (no callback)  
```c
int main(void)
{
    pb_evn_t pb_evn;

    pb_init(pb_config, NULL); // Initialize without callback

    while (1)
    {
        pb_evn = pb_loop(); // Get next event from queue
        if (pb_evn)
        {
            // Handle button event manually
        }
    }
}
```

---

### 2️⃣ Callback mode  

#### Define the callback function  
```c
void my_pb_callback(bool is_long, pb_evn_t key_mask)
{
    if (is_long)
    {
        // Handle long press event
    }
    else
    {
        // Handle short press event
    }
}
```

#### Initialize with callback  
```c
int main(void)
{
    pb_init(pb_config, my_pb_callback); // Initialize with callback

    while (1)
    {
        // Optional: also poll events if needed
        pb_evn_t pb_evn = pb_loop();
        if (pb_evn)
        {
            // Manual handling if desired
        }
    }
}
```

---

## 🧰 API Overview  

| Function | Description |
|----------|-------------|
| `pb_init()` | Initialize push-button driver with config and optional callback |
| `pb_loop()` | Retrieve next event from queue and optionally call callback |
| `pb_evn_add()` | Internal function: add event to queue (called by ISR) |
| `pb_tim_cb()` | Timer callback that scans all buttons (must be registered with timer) |

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
