# YouTube Video Monitor (Arduino + Python)

A small desktop companion that shows live stats of a YouTube video on an OLED screen, using an Arduino Pro Micro and a Python script.

![pic1](https://github.com/user-attachments/assets/56501f45-d0de-41e4-b42f-5e88aa3a3c42)

![pic2](https://github.com/user-attachments/assets/de520bbc-f1c0-4c62-9e7c-bc7d4e2a6c60)

![pic3](https://github.com/user-attachments/assets/090aa0a1-8404-4f21-8a35-e7f26d016da8)

---

## ✨ What It Does

This project tracks a specific YouTube video and displays its stats in real time. It shows:

* A portion of the video title
* Number of Views, likes, comments, and subscribers (with a **+** or **–** to indicate recent changes)
* A **buzzer sound** when someone likes, comments, or subscribes

---

## 🔧 How It Works

A Python script fetches YouTube video data from the **YouTube API** once every few seconds using the **Requests** library. It sends the data to an **Arduino Pro Micro** through serial communication using the **pySerial** library.

The Arduino receives the data and displays it on a **1.3" OLED screen**. It also uses an **active buzzer** to play a short ping sound whenever there’s a new comment or someone likes or subscribes.

---

## ⚙️ Key Features

**Script**

* Runs inside a venv virtual environment
* A `.bat` file is included to activate the virtual environment and run the script (in background) easily
* Checks for USB device (port) availability before starting
* Runs an infinite loop, that fetchs and sends YouTube video data to the Arduino every few seconds
* Breaks out of the loop and Auto-terminates if the Arduino is disconnected or internet connection is lost

**Sketch**

* Receives serial data from the python script and displays it
* Detect if the Views, like, comment, or subscriber count is going up or down and indicates that with **+** (up) and **-** (down) sign
* Pings the buzzer if like, comment, or subscriber count is going up

---

## 🧰 What You Need

**Hardware:**

* Arduino Pro Micro
* 1.3" 128x64 I2C OLED Display (SH110X-based, Monochrome)
* Active buzzer

**Python Libraries:**

* `requests`
* `pyserial`

---

## 🚀 Getting Started

1. **Clone the Repo**

   ```cmd
   git clone https://github.com/Tushar625/YouTube_Video_Monitor
   ```

2. **Upload Arduino Sketch**
   
   Move the downloaded folder containing this repository to the `Arduino` folder inside the `Documents` folder (Windows). Now, this project should appear in the **SKETCHBOOK** tab in Arduino IDE. Upload this into your Arduino.

3. **Set up the Python Environment**

   Open `Command Prompt` inside `python script to access youtube api` folder and run the following commands. 
   
   ```cmd
   python -m venv .venv
   .venv\Scripts\activate
   pip install -r requirements.txt
   ```

   This will create a `venv` virtual environment inside `python script to access youtube api` folder, activate it, and install all the dependencies.

4. **Configure YouTube Access**

   Create YouTube API Key

   https://youtu.be/LLAZUTbc97I?si=Ch9TK1rJHtKX7Eef

   Add your YouTube API Key and YouTube Video ID of the YouTube video you want to track in the text file accessed by the python script (check out the comments in the python script for more details about this text file).

5. **Run the Script**
   
   Plug in the Arduino to a USB port, activate the virtual environment and run the script, you can also Double-click the `.bat` file to do the same, though it will run the script in background.

---

## 📟 UI Design

I used [lopaka](http://lopaka.app/) to design the UI for this project. Check out the [UI Design](https://lopaka.app/gallery/7867/16273). Here's a tutorial,

https://youtu.be/Eyvzw_ujcS0?si=CqvXaAZHakmCfEcZ

---
