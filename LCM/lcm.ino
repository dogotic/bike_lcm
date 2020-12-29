// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        9 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 7 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 120 // Time (in milliseconds) to pause between pixels

uint8_t cntr = 0;
uint8_t idx = 0;

uint8_t left_sequence[] = {3,2,1,0};
uint8_t right_sequence[] = {3,4,5,6};

bool run_left_sequence      = false;
bool run_right_sequence     = false;
bool run_hazzard_sequence   = false;

bool blinker_operation      = false;
bool light_operation        = false;

void setup() 
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'  
  pixels.show();  
}

void loop() 
{
  if (Serial.available())
  {
    char ch = Serial.read();
    Serial.write(ch);
    if (ch == 'R')
    {
      if (!run_right_sequence) 
      {
        run_right_sequence = true;
        run_left_sequence = false;
        blinker_operation = true;
        light_operation = false;
      }
      else 
      {
        run_right_sequence = false;      
        blinker_operation = false;
      }
      pixels.clear(); // Set all pixel colors to 'off'      
      pixels.show();        
    }
    else if(ch == 'L')
    {
      if (!run_left_sequence) 
      {
        run_left_sequence = true;        
        run_right_sequence = false;
        blinker_operation = true;
        light_operation = false;        
      }
      else 
      {
        run_left_sequence = false;
        blinker_operation = false;
      }
      pixels.clear(); // Set all pixel colors to 'off'      
      pixels.show();          
    }
    else if(ch == 'H')
    {
      if (!run_hazzard_sequence) 
      {
        run_hazzard_sequence = true;      
        run_right_sequence = false;
        run_left_sequence = false;
        blinker_operation = true;
        light_operation = false;        
      }
      else 
      {
        run_hazzard_sequence = false;
        blinker_operation = false;
      }
      pixels.clear(); // Set all pixel colors to 'off'      
      pixels.show();            
    }
    else if(ch == 'K')
    {
      if (!light_operation)
      {
        run_hazzard_sequence = false;      
        run_right_sequence = false;
        run_left_sequence = false;
        blinker_operation = false;        
        light_operation = true;

        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        delay(10);
        for (int i=0; i<NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(0xFF, 0x00, 0x0));    
        }
        pixels.setBrightness(127);        
        pixels.show();                  
      }
      else
      {
        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        light_operation = false;
      }
    }
    else if(ch == 'D')
    {
      if (!light_operation)
      {
        run_hazzard_sequence = false;      
        run_right_sequence = false;
        run_left_sequence = false;
        blinker_operation = false;        
        light_operation = true;

        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        delay(10);
        for (int i=0; i<NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(0xFF, 0x00, 0x0));    
        }
        pixels.setBrightness(255);        
        pixels.show();                  
      }
      else
      {
        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        light_operation = false;
      }
    }
    else if(ch == 'P')
    {
      if (!light_operation)
      {
        run_hazzard_sequence = false;      
        run_right_sequence = false;
        run_left_sequence = false;
        blinker_operation = false;        
        light_operation = true;

        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        delay(10);
        for (int i=0; i<NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(0xFF, 0x00, 0x0));    
        }
        pixels.setBrightness(63);        
        pixels.show();                  
      }
      else
      {
        pixels.clear(); // Set all pixel colors to 'off'      
        pixels.show();         
        light_operation = false;
      }
    }
    
    
    cntr = 0;
    idx = 0; 
  }

  if (blinker_operation)
  {
    if (cntr == 16)
    {
      if (run_left_sequence)
      {
        pixels.setPixelColor(left_sequence[idx], pixels.Color(0xFF, 0x1f, 0x0));
      }
      else if(run_right_sequence)
      {
        pixels.setPixelColor(right_sequence[idx], pixels.Color(0xFF, 0x1f, 0x0));    
      }
      else if(run_hazzard_sequence)
      {
        pixels.setPixelColor(left_sequence[idx], pixels.Color(0xFF, 0x1f, 0x0));      
        pixels.show();       
        pixels.setPixelColor(right_sequence[idx], pixels.Color(0xFF, 0x1f, 0x0));          
      }
      
      pixels.show();      
      if (idx == 4)
      {
        pixels.clear(); // Set all pixel colors to 'off'  
        pixels.show(); 
        idx = 0;
      }
      else
      {
        idx++;
      }
      cntr = 0;    
    }
    cntr++;
  }
  delay(10); // Pause before next pass through loop
}
