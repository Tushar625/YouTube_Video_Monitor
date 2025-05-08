#include"oled_display.h"
#include"buzzer.h"

// current data

long views = 0;

long likes = 0;

long comments = 0;

long subs = 0;

// previous data

long prev_views = 0;

long prev_likes = 0;

long prev_comments = 0;

long prev_subs = 0;

String title;

bool initialized = false;

void setup() {
    // put your setup code here, to run once:

    OLED.setup();

    buzzer_setup();

    Serial.begin(9600);
}

int8_t get_rank(long value, long prev_value)
{
    return ((prev_value == value) ? 0 : ((prev_value < value) ? 1 : -1));
}

void loop() {
    // put your main code here, to run repeatedly:

    // checking if any serial data is available

    // if(false)
    if(Serial.available())
    {
        /*
            reading the serial data

            format of serial data: "{score},{comments},{title}\n
        */

        views = Serial.parseInt();   // reading integer

        likes = Serial.parseInt();   // reading integer

        comments = Serial.parseInt();   // reading integer

        subs = Serial.parseInt();   // reading integer

        Serial.read();  // extracting extra ',' after last integer

        title = Serial.readStringUntil('\n'); // reading a string till we find '\n'
        
        title.trim();   // getting rid of extra '\n' at the end

        if(initialized)
        {
            /*
                previous values are already initialized so we use them to determine
                the change in score and no. of comments
            */

            if(prev_likes < likes || prev_comments < comments || prev_subs < subs)
            {
                ping(); // ping when new comments are added
            }

            OLED.print_reddit_data(
                views, 
                likes,
                comments,
                subs,
                title,
                get_rank(views, prev_views),
                get_rank(likes, prev_likes),
                get_rank(comments, prev_comments),
                get_rank(subs, prev_subs)
            );
        }
        else
        {
            /*
                previous values are not initialized yet as it's the first iteration
                so send 0 to indicate no change in score or no. of comments
            */

            OLED.print_reddit_data(views, likes, comments, subs, title);

            initialized = true; // previous values will be initialized soon
        }

        prev_views = views;

        prev_likes = likes;
        
        prev_comments = comments;

        prev_subs = subs;
    }

    delay(100);
}
