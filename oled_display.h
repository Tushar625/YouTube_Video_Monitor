// this file provides an object for easy handling of oled display

#ifndef OLED_DISPLAY_HEADER
#define OLED_DISPLAY_HEADER

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

using namespace std;

#define I2C_ADDRESS_OLED 0X3C

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64

// display and ui class

class OLED_DISPLAY
{
    Adafruit_SH1106G display;

    public:
    
    OLED_DISPLAY() : display(SCREEN_WIDTH, SCREEN_HEIGHT)
    {}

    // call the following function from setup()

    void setup()
    {
        // initialize and set up our display

        delay(250); // wait for our display to power up

        display.begin(I2C_ADDRESS_OLED);

        display.setContrast(10);  // dim the display

        display.clearDisplay(); // cleanup the screen

        display.display();  // refresh the screen, so, it's nice and clean

        // setting text properties

        display.setTextSize(1);

        display.setTextColor(SH110X_WHITE);
    }

    /*
        this class is ued by the function below to display a '+' or '-' sign on the screen 
        to indicate if teh data has increased or decreased
    */

    class status
    {
        uint8_t count;  // for how many iteration we display the sign

        String str; // to store the sign string

        public:

        status() : count(0), str("")
        {}

        // ture means up, false means down

        void set(bool up)
        {
            count = 5;  // initializing iteration counter to count for 5 iterations

            // '+' sign for up, '-' sign for down

            str = up ? " +" : " -";
        }

        // get the sign, it also updates the iteration count silently

        const String& get()
        {
            if(count != 0)
            {
                count--;
            }
            else if(str.length() > 0)
            {
                str = "";   // empty the the string as counter has expired
            }

            return str;
        }
    };

    /*
        get some data about a reddit post to display in the screen

        score: no. of upvotes - no. of downvotes

        comments: no. of comments

        title: title of the post

        score_trends: -1 (score is decreasing) 0 (no change) 1 (increase)

        comments_trends: -1 (comments is decreasing) 0 (no change) 1 (increase)
    */

    void print_reddit_data(long views, long likes, long comments, long subs, String title, int8_t views_trends = 0, int8_t likes_trends = 0, int8_t comments_trends = 0, int8_t subs_trends = 0)
    {
        static status views_status, likes_status, comments_status, subs_status;

        uint8_t x, y;

        int16_t _x, _y;

        uint16_t w, h;

        // updating status according to trends

        if(views_trends)
        {
            views_status.set(views_trends == 1);
        }
        
        if(likes_trends)
        {
            likes_status.set(likes_trends == 1);
        }

        if(comments_trends)
        {
            comments_status.set(comments_trends == 1);
        }
        
        if(subs_trends)
        {
            subs_status.set(subs_trends == 1);
        }

        // makes the score and comments strings and add '+' or '-' after to indicate the trends

        String views_str = String(views) + views_status.get();

        String likes_str = String(likes) + likes_status.get();

        String comments_str = String(comments) + comments_status.get();

        String subs_str = String(subs) + subs_status.get();

        // drawing

        static const unsigned char PROGMEM image_ButtonRightSmall_bits[] = {0x20,0x60,0xe0,0x60,0x20};

        static const unsigned char PROGMEM image_cards_hearts_bits[] = {0x30,0x60,0x48,0x90,0x85,0x08,0x82,0x08,0x80,0x08,0x40,0x10,0x20,0x20,0x10,0x40,0x08,0x80,0x05,0x00,0x02,0x00};

        static const unsigned char PROGMEM image_Layer_19_bits[] = {0xdb,0xdb,0x92,0x00,0x00,0x00,0x80};

        static const unsigned char PROGMEM image_Layer_24_bits[] = {0xc3,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x80};

        static const unsigned char PROGMEM image_Layer_8_bits[] = {0x00,0x40,0x00,0x00,0x20,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0xc0,0x00,0x88,0x00};

        static const unsigned char PROGMEM image_phone_contacts_bits[] = {0x07,0x00,0x08,0x80,0x08,0x80,0x08,0x80,0x07,0x00,0x00,0x00,0x07,0x00,0x38,0xe0,0x20,0x20,0x40,0x10,0x80,0x08,0x80,0x08,0xff,0xf8};

        display.clearDisplay();

        // ButtonRightSmall
        display.drawBitmap(14, 10, image_ButtonRightSmall_bits, 3, 5, 1);

        // Layer 2
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(22, 5);
        display.print(title.substring(0, 13) + "...");

        // Layer 3
        display.drawRoundRect(5, 9, 9, 6, 1, 1);

        // Layer 4
        display.drawCircle(5, 6, 2, 1);

        // Layer 7
        display.drawRect(8, 11, 4, 1, 1);

        // Layer 8
        display.drawLine(0, 17, 127, 17, 1);

        // Layer 8
        display.drawBitmap(3, 4, image_Layer_8_bits, 11, 9, 1);

        // Layer 8
        display.drawCircle(12, 5, 3, 1);

        // Layer 10 copy
        display.drawLine(0, 63, 127, 63, 1);

        // Layer 10
        display.drawLine(0, 41, 127, 41, 1);

        // cards_hearts
        display.drawBitmap(67, 24, image_cards_hearts_bits, 13, 11, 1);

        // phone_contacts
        display.drawBitmap(67, 46, image_phone_contacts_bits, 13, 13, 1);

        // Layer 18
        display.drawRoundRect(3, 48, 14, 9, 3, 1);

        // Layer 19
        display.drawBitmap(6, 51, image_Layer_19_bits, 8, 7, 1);

        // Layer 22
        display.drawRoundRect(3, 25, 14, 9, 1, 1);

        // Layer 23
        display.drawRoundRect(5, 27, 8, 5, 1, 1);

        // comments
        display.setCursor(22, 49);
        display.print(comments_str);

        // views
        display.setCursor(22, 26);
        display.print(views_str);

        // Layer 24
        display.drawBitmap(6, 22, image_Layer_24_bits, 10, 10, 1);

        // subs
        display.setCursor(85, 49);
        display.print(subs_str);

        // likes
        display.setCursor(85, 26);
        display.print(likes_str);

        display.display();


        /*

        // cleaning the display

        display.clearDisplay();
        
        // placing score string

        display.getTextBounds(score_str, 0, 0, &_x, &_y, &w, &h);

        x = SCREEN_WIDTH / 2 - w / 2;

        y = SCREEN_HEIGHT / 2 - h - 2;

        display.setCursor(x, y);

        display.print(score_str);

        // placing comments string

        display.getTextBounds(comments_str, 0, 0, &_x, &_y, &w, &h);

        x = SCREEN_WIDTH / 2 - w / 2;

        y = SCREEN_HEIGHT / 2 + 2;

        display.setCursor(x, y);

        display.print(comments_str);

        // placing post title

        display.setCursor(0, 0);

        display.print(title);

        display.display();*/
    }
} OLED; // display and ui object

#endif // OLED_DISPLAY_HEADER